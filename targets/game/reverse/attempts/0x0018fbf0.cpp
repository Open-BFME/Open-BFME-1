// ?bfmeClipSegment6DF730@BfmePolygon6DF1F0@@QBEDPBUBfmeCoord6DF1F0@@0PAU2@H@Z
// partial score=0.8139 date=2026-10-03
// cl: /O2 /G6 /DNDEBUG /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWMath
#include "coord3d.h"
#include <math.h>
// Existing caller ABI from Rva006DF730ClampToArea.cpp. Polygon layout is
// witnessed by PolygonTrigger_pointInTrigger.cpp and retail +0x10/+0x14.
// 0x0018FBF0..0x0018FFA7: 951 bytes; all exits use ret 0x10.
// Existing caller identity retained, including its char result and int flags.
// Retail tests only the low byte of flags. The semantic original name remains
// unknown. Intended home: GameEngine/Source/GameLogic/Map/PolygonTriggerClipSegment.cpp.
// The coordinate records here retain the established caller ABI; Coord3D's
// existing header supplies the actual normalize() callee declaration.
struct BfmeCoord6DF1F0 { float x, y, z; };
struct ClipPoint0018FBF0 { int x, y, z; };
struct ClipPair0018FBF0 { float x, y; };
extern bool IntersectLine2D(const Coord2D *, const Coord2D *, const Coord2D *, const Coord2D *, Coord2D *);
// Authentic visible helper from coord3d.cpp; independently probes 79/79
// at RVA 0x000FB930. Visibility improves the caller to 949/951 bytes,
// 173 raw differences; the remaining x87/local-lifetime mismatch is unlanded.
__declspec(noinline) void Coord3D::normalize()
{
    float len = (float)sqrt(x*x + y*y + z*z);
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale; y *= scale; z *= scale;
    }
}
class BfmePolygon6DF1F0 {
    char m_unmodelled00[0x10];
    ClipPoint0018FBF0 *m_points;
    int m_numPoints;
public:
    char bfmeContains6DF1F0(const BfmeCoord6DF1F0 &) const;
    char bfmeClipSegment6DF730(const BfmeCoord6DF1F0 *from,
        const BfmeCoord6DF1F0 *to, BfmeCoord6DF1F0 *clipped, int flags) const;
};
char BfmePolygon6DF1F0::bfmeClipSegment6DF730(const BfmeCoord6DF1F0 *from,
    const BfmeCoord6DF1F0 *to, BfmeCoord6DF1F0 *clipped, int flags) const
{
    ClipPair0018FBF0 end, start, delta;
    start.x = from->x;
    start.y = from->y;
    end.x = to->x;
    end.y = to->y;
    delta.x = end.x - start.x;
    delta.y = end.y - start.y;
    if (bfmeContains6DF1F0(*to)) { *clipped = *to; return 1; }
    if (!bfmeContains6DF1F0(*from)) { *clipped = *from; return 0; }
    for (int i = 0; i < m_numPoints; ++i) {
        ClipPoint0018FBF0 pt1 = m_points[i];
        ClipPoint0018FBF0 pt2 = (i ? m_points[i-1] : m_points[m_numPoints-1]);
        ClipPair0018FBF0 a = {(float)pt1.x, (float)pt1.y};
        ClipPair0018FBF0 b = {(float)pt2.x, (float)pt2.y};
        ClipPair0018FBF0 intersection;
        if (IntersectLine2D((Coord2D*)&a, (Coord2D*)&b, (Coord2D*)&start, (Coord2D*)&end, (Coord2D*)&intersection)) {
            float side = (from->y - pt1.y)*(pt2.x - pt1.x) - (from->x - pt1.x)*(pt2.y - pt1.y);
            ClipPair0018FBF0 normal = {(float)(pt2.y-pt1.y), (float)(pt1.x-pt2.x)};
            float len = sqrt(normal.x*normal.x + normal.y*normal.y);
            if (len != 0.0f) { normal.x /= len; normal.y /= len; }
            if (side > 0.0f) { normal.x *= -1.0f; normal.y *= -1.0f; }
            normal.x *= 0.1f; normal.y *= 0.1f;
            BfmeCoord6DF1F0 result = {normal.x + intersection.x, normal.y + intersection.y, 0.0f};
            if (!bfmeContains6DF1F0(result)) { *clipped = *from; return 0; }
            if ((char)flags) {
                BfmeCoord6DF1F0 slide = {(float)pt2.x, (float)pt2.y, 0.0f}; BfmeCoord6DF1F0 p1 = {(float)pt1.x, (float)pt1.y, 0.0f}; slide.x -= p1.x; slide.y -= p1.y;
                if (delta.x*slide.x + delta.y*slide.y < 0.0f) { slide.x *= -1.0f; slide.y *= -1.0f; slide.z *= -1.0f; }
                BfmeCoord6DF1F0 moved = {result.x-from->x, result.y-from->y, -from->z};
                float remaining = sqrt(delta.x*delta.x + delta.y*delta.y) - sqrt(moved.x*moved.x + moved.y*moved.y + moved.z*moved.z);
                if (remaining > 0.1f) {
                    remaining *= 0.4f;
                    ((Coord3D*)&slide)->normalize();
                    slide.x *= remaining; slide.y *= remaining; slide.z *= remaining;
                    BfmeCoord6DF1F0 next = {result.x + slide.x, result.y + slide.y, slide.z};
                    if (bfmeContains6DF1F0(next)) { *clipped = next; return 1; }
                }
            }
            *clipped = result; return 1;
        }
    }
    return 0;
}

