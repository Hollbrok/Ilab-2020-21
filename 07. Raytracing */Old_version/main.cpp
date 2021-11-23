#include "vector.h"
#include "Header.h"

bool UseTxPixel = false;

int main()
{

	Vector vec1(1, 1, 1);
	Vector vec2(23, -1, 0);


	Vector vec3 = vec1 ^ vec2;
	Vector vec4 = vec1 - vec2;

	PRINT_VEC(vec3);
	PRINT_VEC(vec4);
	vec1.print();
	vec1 += vec2;
	vec1.print();

	double r = 200;
	
	txCreateWindow(800, 600);
	txTextCursor(false);
	txBegin();
	//printf("1 cycle\n");
	static double perf = txQueryPerformance();
	//printf("2 cycle\n");
	txSetTextAlign(TA_CENTER);
	txSetColor(TX_DARKGRAY);
	txSelectFont("Lucida Console", 15, 0);

	txTextOut(txGetExtentX() / 2, txGetExtentY() * 19 / 20, "Press Z, R, X, H to bump, T to use txSetPixel(), "
																"ESC to exit");
	
	//printf("start cycle\n");

	int counter = 0;
	for (double t = txPI / 2; ; t += 0.1)
    {
		//printf("counter = %d\n", counter++);
		DrawScene(Vector(-2 * r * (1 + cos(t)),
					- 2 * r * cos(t),
					+ 2 * r * sin(t)), r);
		txSleep();
		
		if (GetAsyncKeyState(VK_ESCAPE) && GetForegroundWindow() == txWindow()) break;
		
		/* For FPS testing only: */

		if (GetAsyncKeyState(VK_SPACE)) continue;
			UseTxPixel = GetAsyncKeyState('T');
		
		static char s[128] = "";
		sprintf(s, "tx[Q]ueryPerformance(): %.2f. FPS %.2f. Using %s",
					perf, txGetFPS(), (UseTxPixel ? "txSetPixel" : "direct memory access"));
		SetWindowText(txWindow(), s);
	}
	//printf("end cycle\n");
	txEnd();
	return 0;

}


//--------------------------------------------------------------------------------------

void DrawScene(const Vector& lightPos, double r)
{
	const Vector viewPos(0, 0, +5 * r);

	const Vector materialColor(0.0, 1.0, 0.0);
	const Vector lightColor(1.0, 0.7, 0.0);
	const Vector ambientColor(0.2, 0.2, 0.2);

	for (double y = +r; y >= -r; y--)
		for (double x = -r; x <= +r; x++)
		{
			if (x * x + y * y > r * r) continue;

			Vector p(x, y, 0);
			p = p + Bump(p, r) * 100;
			if (p.x_ * p.x_ + p.y_ * p.y_ > r * r) { DrawPixel(x, y, Vector()); continue; }

			p.z_ = sqrt(r * r - p.x_ * p.x_ - p.y_ * p.y_);
			Vector N = p.normalize() + Bump(p, r);

			Vector V = (viewPos - p).normalize();
			Vector L = (lightPos - p).normalize();

			double diffuse = N.dot(L);
			if (diffuse < 0) diffuse = 0;

			Vector Lr = 2 * (N.dot(L)) * N - L;
			double spec = Lr.dot(V);
			if (spec < 0) spec = 0;
			double specular = pow(spec, 25);

			Vector color = ambientColor * materialColor +
				diffuse * materialColor * lightColor +
				specular * lightColor +

				PhongLightning(p, N, V,
					Vector(+2 * r, -1 * r, 0),
					Vector(0.5, 0.5, 0.5),
					materialColor);
			DrawPixel(x, y, color);
		}
}

//----------------------------------------------------------------------------

inline void DrawPixel(double x, double y, Vector color)
{
	static POINT scr = txGetExtent();

	POINT   p = { (int)(x + scr.x / 2 + 0.5),
					(int)(y + scr.y / 2 + 0.5) };

	RGBQUAD rgb = { (BYTE)(Clamp(color.x_, 0, 1) * 255 + 0.5),
	(BYTE)(Clamp(color.y_, 0, 1) * 255 + 0.5),
	(BYTE)(Clamp(color.z_, 0, 1) * 255 + 0.5) };

	if (UseTxPixel)
		txSetPixel(p.x, p.y, RGB(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue));
	else
		*(txVideoMemory() + p.x + (-p.y + scr.y) * scr.x) = rgb;

}


//----------------------------------------------------------------------------

Vector PhongLightning(const Vector& p, const Vector& N, const Vector& V,
	const Vector& lightPos, const Vector& lightColor,
	const Vector& materialColor,
	const Vector& ambientColor)
{
	Vector L = (lightPos - p).normalize();

	double diffuse = sc_dot(N, L); //N.dot(L);
	if (diffuse < 0) return ambientColor;

	Vector Lr = 2 * diffuse * N - L;
	double specular = pow(Lr.dot(V), 25);

	return diffuse * lightColor * materialColor +
		specular * lightColor + ambientColor;
}

//----------------------------------------------------------------------------

Vector Bump(const Vector& p, double r)
{
	bool bXY = (GetAsyncKeyState('X') != 0),
		bXY2 = (GetAsyncKeyState('H') != 0),
		bZ = (GetAsyncKeyState('Z') != 0),
		bRnd = (GetAsyncKeyState('R') != 0);

	if (!bXY && !bXY2 && !bZ && !bRnd) return Vector();

	const int sz = 100;
	static Vector env[sz][sz] = {};

	static bool init = false;

	if (!init)
	{
		for (int y = 0; y < sz; y++) for (int x = 0; x < sz; x++)
			env[y][x] = Vector(Random(-1, +1), Random(-1, +1), Random(-1, +1));

		init = true;
	}

	Vector bump(0, 0, 0);

	if (bXY)  bump += p * ((sin(p.x_ / 4) + cos(p.y_ / 4)) / 4 + 1.5) / 5000.0;
	if (bXY2) bump += p * ((cos(p.x_ / 4) + sin(p.y_ / 4)) / 2 + 1.0) / 3000.0;
	if (bZ)   bump += p * (sin(p.z_ * p.z_ / 500) / 2 + 1.5) / 5000.0;
	if (bRnd) bump += env[(unsigned)ROUND(p.y_ + r) % sz][(unsigned)ROUND(p.x_ + r) % sz] / 100.0;

	return bump;
}

inline double Random(double min, double max)
{
	return min + (max - min) * rand() / RAND_MAX;
}

inline double Clamp(double value, double min, double max)
{
	return (value < min) ? min : (value > max) ? max : value;
}

