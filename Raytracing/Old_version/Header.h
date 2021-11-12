#pragma once


void DrawScene(const Vector& lightPos, double r);

Vector PhongLightning(const Vector& p, const Vector& N, const Vector& V,
    const Vector& lightPos, const Vector& lightColor,
    const Vector& materialColor,
    const Vector& ambientColor = Vector(0, 0, 0));

Vector Bump(const Vector& p = Vector(), double r = 0);

void DrawPixel(double x, double y, Vector color);

inline double Random(double min, double max);

inline double Clamp(double value, double min, double max);