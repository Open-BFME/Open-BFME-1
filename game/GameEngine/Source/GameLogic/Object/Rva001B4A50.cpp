// cl: /O2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "vector3.h"
#include "matrix3d.h"
// Retail [0x001B4A50,0x001B4B30): receiver's matrix is at +0x64.
// Native Vector3 cross products preserve the x87 multiply/reload schedule.
// No independent witness proves the old BfmeXformXC/bfmeSetXC identity.
float Cos(float);
float Sin(float);
class Rva001B4A50
{
public:
    void method(float angle);
    unsigned char m_unmodelled00[0x64];
    Matrix3D m_matrix64;
};
void Rva001B4A50::method(float angle)
{
    Vector3 u, x, y, z, pos;
    pos.X = m_matrix64[0].W;
    pos.Y = m_matrix64[1].W;
    pos.Z = m_matrix64[2].W;
    z.X = 0.0f;
    z.Y = 0.0f;
    z.Z = 1.0f;
    u.X = Cos(angle);
    u.Y = Sin(angle);
    u.Z = 0.0f;
    Vector3::Cross_Product(z, u, &y);
    Vector3::Cross_Product(y, z, &x);
    m_matrix64.Set(x.X, y.X, z.X, pos.X,
                   x.Y, y.Y, z.Y, pos.Y,
                   x.Z, y.Z, z.Z, pos.Z);
}
