#include "vector.h"


Vector::Vector() : x_(0.0f), y_(0.0f), z_(0.0f)
{
}

Vector::Vector(double x, double y, double z) : x_(x), y_(y), z_(z)
{
   // printf("x_ = %lg, y_ = %lg, z_ = %lg\n", x_, y_, z_);
}

Vector::Vector(double t) : x_(t), y_(t), z_(t)
{
    // printf("x_ = %lg, y_ = %lg, z_ = %lg\n", x_, y_, z_);
}

Vector::~Vector()
{
}

Vector operator+(const Vector &v1, const Vector &v2)
{
    return Vector(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

Vector operator-(const Vector &v1, const Vector &v2)
{
    return Vector(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

Vector operator*(const Vector &v, double k)
{
    return Vector(v.x_ * k, v.y_ * k, v.z_ * k);
}


Vector operator*(double k, const Vector& v)
{
    return Vector(v.x_ * k, v.y_ * k, v.z_ * k);
}

Vector operator*(const Vector& v1, const Vector& v2)
{
    return Vector(v1.x_ * v2.x_, v1.y_ * v2.y_, v1.z_ * v2.z_);
}

Vector operator^(const Vector& v1, const Vector& v2)
{
    return Vector(v1.y_ * v2.z_ - v1.z_ * v2.y_,
                  v1.z_ * v2.x_ - v1.x_ * v2.z_,
                  v1.x_ * v2.y_ - v1.y_ * v2.x_);
}

double sc_dot (const Vector& v1, const Vector& v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

Vector& operator+=(Vector& v1, const Vector& v2)
{
    v1.x_ += v2.x_;
    v1.y_ += v2.y_;
    v1.z_ += v2.z_;
    return v1;
}

Vector operator/(const Vector& v, double value)
{
    return Vector(v.x_ / value, v.y_ / value, v.z_ / value);
}

double Vector::dot(const Vector &v)
{
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vector Vector::normalize()
{
    double len = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    if (len != 0)
    {
        x_ /= len;  
        y_ /= len;
        z_ /= len;
    }

    return *this;
}

Vector Vector::transformMatrixToVector(const double m[16])
{
    Vector ret( x_ * m[0] + y_ * m[4] + z_ * m[8] + m[12],
                x_ * m[1] + y_ * m[5] + z_ * m[9] + m[13],
                x_ * m[2] + y_ * m[6] + z_ * m[10] + m[14]);
    return ret;
}

void Vector::set(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

void Vector::print(const char* name)
{
    if (name)
        printf("%s(%lg, %lg, %lg)\n", name, x_, y_, z_);
    else
        printf("No_name(%lg, %lg, %lg)\n", x_, y_, z_);
    return;
}
