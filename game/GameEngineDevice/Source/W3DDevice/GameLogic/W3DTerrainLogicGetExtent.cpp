// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?getExtent@W3DTerrainLogic@@UBEXPAURegion3D@@@Z

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
    virtual void getExtent(Region3D *extent) const;

private:
    char m_pad04[0x24 - 4];
    BoundaryVector m_boundaries;
    char m_pad30[0x18fc - 0x30];
    Real m_mapMinZ;
    Real m_mapMaxZ;
};

void W3DTerrainLogic::getExtent(Region3D *extent) const
{
    extent->lo.x = 0.0f;
    extent->lo.y = 0.0f;

    struct Extrema
    {
        Real x;
        Real y;
    } extrema;

    if (!m_boundaries.empty())
    {
        extrema.x = m_boundaries[0].x;
        extrema.y = m_boundaries[0].y;

        for (Int i = 1; i < m_boundaries.size(); ++i)
        {
            if (m_boundaries[i].x > extrema.x)
                extrema.x = m_boundaries[i].x;
            if (m_boundaries[i].y > extrema.y)
                extrema.y = m_boundaries[i].y;
        }

        extent->hi.x = extrema.x * MAP_XY_FACTOR;
        extent->hi.y = extrema.y * MAP_XY_FACTOR;
    }
    else
    {
        extent->hi.x = 0.0f;
        extent->hi.y = 0.0f;
    }

    extent->lo.z = m_mapMinZ;
    extent->hi.z = m_mapMaxZ;
}
