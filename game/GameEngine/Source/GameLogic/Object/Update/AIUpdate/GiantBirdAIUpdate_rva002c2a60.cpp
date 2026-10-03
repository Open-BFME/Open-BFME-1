// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// RVA 0x002C2A60, 338 bytes. GiantBirdAIUpdate primary vtable
// 0x010C7F40 slot 0x58 -> ILT 0x00019B2D proves the class; the
// method spelling and the semantic type of its second word are unproven.
// Matched 0x002C2C10 supplies the Waypoint layout and Coord3D copy shape.
// The shared path action at slot 0x68 is matched 0x002BCE00.

typedef int Int;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    Real x, y, z;
    Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
};

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
    Int getNumLinks() const { return m_numLinks; }
    const Waypoint *getLink(Int ndx) const
    {
        if (ndx < 0 || ndx >= 8)
            return 0;
        return m_links[ndx];
    }
    const Coord3D *getLocation() const { return &m_location; }

private:
    void *m_vptr;
    Int m_id;
    void *m_name;
    Coord3D m_location;
    unsigned char m_pad_018[8];
    const Waypoint *m_links[8];
    unsigned char m_pad_040[0xC];
    Int m_numLinks;
};

class Locomotor
{
public:
    unsigned char m_pad_000[0x44];
    Int m_dword44;
};

class Object;
class Rva002BCE00Path
{
public:
    Real *m_begin;
    Real *m_end;
};

class Rva002BCE00StateAction
{
public:
    void run(Rva002BCE00Path *path, Object *obstacle, void *finishArgument,
        void *unused);
};

class GiantBirdAIUpdate
{
protected:
    virtual void rva002c2a60(void *segmentList, void *arg1);

private:
    unsigned char m_pad_004[0x1CC - 4];
    Locomotor *m_curLocomotor;
    unsigned char m_pad_1D0[0x478 - 0x1D0];
    Int m_field478;
    unsigned char m_pad_47C[0x488 - 0x47C];
    unsigned char m_z488;
};

void GiantBirdAIUpdate::rva002c2a60(void *segmentList, void *arg1)
{
    if (m_curLocomotor)
        m_field478 = m_curLocomotor->m_dword44;
    m_z488 = 0;

    std::vector<Coord3D> path;
    const Waypoint *way = static_cast<const Waypoint *>(segmentList);
    if (way == 0)
        return;

    const Waypoint *cur = way;
    for (;;)
    {
        Coord3D pos = *cur->getLocation();
        path.push_back(pos);
        if (cur->getNumLinks() == 0)
            break;
        cur = cur->getLink(0);
        if (cur == way)
        {
            m_z488 = 1;
            break;
        }
    }

    reinterpret_cast<Rva002BCE00StateAction *>(this)->run(
        reinterpret_cast<Rva002BCE00Path *>(&path), 0, arg1, 0);
}
