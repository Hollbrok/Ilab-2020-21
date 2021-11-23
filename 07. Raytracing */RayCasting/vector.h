#ifndef __VECTOR_H__
#define __VECTOR_H__


#define PRINT_VEC(vec)      \
    vec.print(#vec)

#define _CRT_SECURE_NO_WARNINGS

/* Includes */

#include "Libraries.h"

/* Class */

class Vector
{
public:
    Vector();
    Vector(double x, double y, double z);
    Vector(double t);
    ~Vector();

    /* Operators */
    friend Vector  operator + (const Vector &v1, const Vector &v2);
    friend Vector  operator - (const Vector &v1, const Vector &v2);

    friend Vector  operator * (const Vector &v, double k);
    friend Vector  operator * (double k, const Vector& v);
    friend Vector  operator * (const Vector& v1, const Vector& v2);

    friend Vector  operator / (const Vector& v, double value);
    friend Vector  operator ^ (const Vector& v1, const Vector& v2);
    friend Vector& operator += (Vector& a, const Vector& b);

    friend double  sc_dot(const Vector& v1, const Vector& v2);


    double dot(const Vector &v);
    Vector normalize();

    Vector transformMatrixToVector(const double m[16]);

    double getX() { return x_; }
    double getY() { return y_; }
    double getZ() { return z_; }

    double setX(double x) { x_ = x; }
    double setY(double y) { y_ = y; }
    double setZ(double z) { z_ = z; }

    void set(double x, double y, double z);
    void print(const char* = nullptr);

    double x_;
    double y_;
    double z_;

private:

};


#endif
