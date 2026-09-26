// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?getMaximumPathfindExtent@W3DTerrainLogic@@UBEXPAURegion3D@@@Z

#include <vector>

typedef float Real;
typedef int Int;

#define MAP_XY_FACTOR 10.0f

struct ICoord2D
{
    Int x;
    Int y;
};

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};

struct Region3D
{
    Coord3D lo;
    Coord3D hi;
};

typedef _STL::vector<ICoord2D> BoundaryVector;

class W3DTerrainLogic
{
public:
    virtual void getMaximumPathfindExtent(Region3D *extent) const;

private:
    char m_pad04[0x24 - 4];
    BoundaryVector m_boundaries;
    char m_pad30[0x18fc - 0x30];
    Real m_mapMinZ;
    Real m_mapMaxZ;
};

void W3DTerrainLogic::getMaximumPathfindExtent(Region3D *extent) const
{
    extent->lo.x = 0.0f;
    extent->lo.y = 0.0f;
    extent->hi.x = 0.0f;
    extent->hi.y = 0.0f;

    for (Int i = 0; i < m_boundaries.size(); ++i)
    {
        if (extent->hi.x < m_boundaries[i].x * MAP_XY_FACTOR)
            extent->hi.x = m_boundaries[i].x * MAP_XY_FACTOR;
        if (extent->hi.y < m_boundaries[i].y * MAP_XY_FACTOR)
            extent->hi.y = m_boundaries[i].y * MAP_XY_FACTOR;
    }

    extent->lo.z = m_mapMinZ;
    extent->hi.z = m_mapMaxZ;
}
