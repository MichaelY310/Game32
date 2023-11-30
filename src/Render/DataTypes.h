#pragma once

class vec2
{
public:
    vec2()
    {
        x = 0.0f;
        y = 0.0f;
    };

    vec2(double xx, double yy)
    {
        x = xx;
        y = yy;
    };

    double x;
    double y;

    vec2 operator*(double scalar) const {
        return vec2(x * scalar, y * scalar);
    };

    vec2 operator+(vec2 vector) const {
        return vec2(x + vector.x, y + vector.y);
    };
};

class vec3
{
public:
    vec3()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    };

    vec3(double xx, double yy, double zz)
    {
        x = xx;
        y = yy;
        z = zz;
    };

    double x;
    double y;
    double z;

    vec3 operator*(double scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    };

    vec3 operator+(vec3 vector) const {
        return vec3(x + vector.x, y + vector.y, z + vector.z);
    };
};