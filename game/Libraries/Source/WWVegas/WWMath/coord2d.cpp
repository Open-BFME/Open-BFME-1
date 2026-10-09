// cl: /Igame/GameEngine/Source/Common
#include "coord2d.h"
#include "debug.h"
#include "coord3d.h"

#include <math.h>

extern float ACos(float);  // Lib/trig.h, defined in Trig.cpp (retail 0x00873940)

// Retail's toAngle clamps the cosine against named globals rather than
// literals: 0x01075350 (0.0f), 0x0109BF3C (-1.0f) and 0x01075334 (1.0f).
extern const float g_rva01075350;
extern const float BfmeShadowScale;
extern float g_bfmeDefaultBU;

Coord2DBase &Coord2DBase::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

Coord2D::Coord2D(const Coord2D &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Coord2D::Coord2D(int x, int y)
{
    this->x = (float)x;
    this->y = (float)y;
}

Coord2D &Coord2D::operator=(const Coord2D &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

Coord2D &Coord2D::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

Coord2D &Coord2D::operator=(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

float Coord2D::operator*(const Coord2D &that) const
{
    return x * that.x + y * that.y;
}

float Coord2D::operator*(const Coord3DBase &that) const
{
    return x * that.x + y * that.y;
}

Coord2D &Coord2D::operator*=(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::operator+=(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord2D &Coord2D::operator+=(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord2D &Coord2D::operator-=(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord2D &Coord2D::operator-=(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord2D &Coord2D::Add(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord2D &Coord2D::Add(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

float Coord2D::GetLength() const
{
    float x_value = x;
    float y_value = y;

    return (float)sqrt(x_value * x_value + y_value * y_value);
}

float Coord2D::GetLengthSqrd() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
}

bool Coord2D::IsExactlyEqualTo(const Coord2D &that) const
{
    return x == that.x && y == that.y;
}

inline float Coord2D::length() const
{
    return (float)sqrt(x * x + y * y);
}

Coord2D &Coord2D::Negate()
{
    x = -x;
    y = -y;
    return *this;
}

static const float one = 1.0f;
static const float zero_value = 0.0f;
static const float length_estimate_factor = 0.25f;

void Coord2D::normalize()
{
    float len = (float)sqrt(x * x + y * y);
    if (len != zero_value) {
        float scale = one / len;
        x *= scale;
        y *= scale;
    }
}

float Coord2D::Normalize()
{
    // The locals preserve retail's x87 load order.
    float x_value = x;
    float y_value = y;
    float len = (float)sqrt(x_value * x_value + y_value * y_value);
    float scale = one / len;
    x *= scale;
    y *= scale;
    return len;
}

float Coord2D::GetLengthEstimate() const
{
    float ax = fabs(x);
    float ay = fabs(y);
    if (ax > ay) {
        return ax + length_estimate_factor * ay;
    }
    return ay + length_estimate_factor * ax;
}

Coord2D &Coord2D::Rotate(float sine, float cosine)
{
    float new_x = cosine * x - sine * y;

    y = cosine * y + sine * x;
    x = new_x;
    return *this;
}

Coord2D &Coord2D::Rotate(Coord2D &coord, float sine, float cosine)
{
    x = cosine * coord.x - sine * coord.y;
    y = cosine * coord.y + sine * coord.x;
    return *this;
}

float Coord2D::toAngle() const
{
    const float len = length();
    if (len == g_rva01075350)
        return g_rva01075350;

    const float c = x / len;
    // bound it in case of numerical error
    const float bounded = c < BfmeShadowScale ? -1.0f : (c > g_bfmeDefaultBU ? 1.0f : c);

    return y < g_rva01075350 ? -ACos(bounded) : ACos(bounded);
}

Coord2D &Coord2D::Rotate(float angle)
{
    struct TrigValues
    {
        float cosine;
        float sine;
    } trig;

    trig.sine = sin(angle);
    trig.cosine = cos(angle);
    __asm {
        fld angle
        fsincos
        fstp trig.cosine
        fstp trig.sine
    }

    float new_x = trig.cosine * x - trig.sine * y;
    float new_y = trig.cosine * y;
    new_y += trig.sine * x;
    y = new_y;
    x = new_x;
    return *this;
}

Coord2D &Coord2D::Rotate(const Coord2D &source, float angle)
{
    float sine;
    float cosine;
    __asm {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }

    x = cosine * source.x - sine * source.y;
    y = cosine * source.y + sine * source.x;
    return *this;
}

Coord2D &Coord2D::Scale(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::Set(float x, float y)
{
    this->x = x;
    this->y = y;
    return *this;
}

Coord2D &Coord2D::SetMaxVect()
{
    y = 3.4028234663852886e38f;
    x = 3.4028234663852886e38f;
    return *this;
}

Coord2D &Coord2D::SetMinVect()
{
    y = -3.4028234663852886e38f;
    x = -3.4028234663852886e38f;
    return *this;
}

Coord2D &Coord2D::SetXAxis()
{
    x = 1.0f;
    y = 0.0f;
    return *this;
}

Coord2D &Coord2D::SetYAxis()
{
    x = 0.0f;
    y = 1.0f;
    return *this;
}

Coord2D &Coord2D::SetZero()
{
    y = 0.0f;
    x = 0.0f;
    return *this;
}

Coord2D &Coord2D::Sub(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord2D &Coord2D::Sub(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Debug &operator<<(Debug &debug, const Coord2D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ")";
    return debug;
}
