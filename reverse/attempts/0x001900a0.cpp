// ?bfmeRayIntersectAt001900A0@PolygonTrigger@@QBE_NPBVVector3@@0PAV2@@Z
// partial score=0.3 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc- /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// BFME-only ray/plane query. The method's original name is not recovered.
// Retail 001900A0..001901AC (268 bytes); helper pointInTrigger is independently
// byte-matched at0018F8A0, reached viaILT0004AB6F on this same receiver.
#include "vector3.h"

extern const float BfmeZeroRange;
extern const float Rva0109BF40ZeroRange;

struct ICoord3D { int x, y, z; };

class PolygonTrigger
{
public:
    bool pointInTrigger(ICoord3D &point) const;
    bool bfmeRayIntersectAt001900A0(const Vector3 *origin,
        const Vector3 *direction, Vector3 *result) const;
private:
    unsigned char m_unmodelled00[0x10];
    ICoord3D *m_points;
};

bool PolygonTrigger::bfmeRayIntersectAt001900A0(const Vector3 *origin,
    const Vector3 *direction, Vector3 *result) const
{
    const Vector3 normal(0.0f, 0.0f, 1.0f);
    float denominator = Vector3::Dot_Product(normal, *direction);
    if (fabs(denominator) > Rva0109BF40ZeroRange)
    {
        float distance = -(Vector3::Dot_Product(normal, *origin) -
            m_points[0].z) / denominator;
        Vector3 intersection = *direction;
        intersection *= distance;
        intersection += *origin;
        ICoord3D integerPoint;
        integerPoint.x = (int)intersection.X;
        integerPoint.y = (int)intersection.Y;
        integerPoint.z = (int)intersection.Z;
        if (pointInTrigger(integerPoint))
        {
            *result = intersection;
            return true;
        }
    }
    return false;
}
