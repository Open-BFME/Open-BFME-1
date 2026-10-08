// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Include

#include <math.h>

#include <Lib/Coord3D.h>

// ?setCoord@@YAXPAUCoord3D@@PBU1@@Z absent-from-retail
static inline void setCoord(Coord3D *to, const Coord3D *from)
{
    to->x=from->x; to->y=from->y; to->z=from->z;
}

struct Rva003A2070Elem
{
    // Only point is exposed; the non-trivial element prefix and tail stay opaque.
    char m_body[0xa4];
    Coord3D point;
    char tail[8];
};

class View;
class TerrainLogic;
class BfmeMgrGK;
// Retail ignores ECX; this complete view preserves the witnessed member-call ABI.
class Rva003A1A30Dispatch {};
extern View *TheTacticalView;
extern TerrainLogic *TheTerrainLogic;
extern BfmeMgrGK *g_bfmeMgrGK;
extern void j_000481fd();

class Rva0045BA00Dispatch
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10();
    virtual void Rva0045BA00Slot(const Coord3D *, const Coord3D *, unsigned int, unsigned int);
};

class Rva012EF4CCDispatch
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual float slot18(float x, float y, Coord3D *normal);
};

struct Rva003A2070Range
{
    Rva003A2070Elem *m_begin;
    Rva003A2070Elem *m_end;
    // ?size@Rva003A2070Range@@QBEIXZ absent-from-retail
    unsigned int size() const { return (unsigned int)(m_end - m_begin); }
    // ??ARva003A2070Range@@QAEAAURva003A2070Elem@@I@Z absent-from-retail
    Rva003A2070Elem &operator[](unsigned int i) { return m_begin[i]; }
};

class Rva003A2070Obj
{
public:
    void update(float dt);
    char m_pad0[0x18];
    float m_accum;
    char m_pad1[0x2c - 0x1c];
    Rva003A2070Range entries;
    char m_pad2[0x48 - 0x34];
    Coord3D m_point;
};

void Rva003A2070Obj::update(float dt)
{
    m_accum = dt - (float)fmod((double)dt, 15.0);
    if (entries.size() < 4)
        return;
    ((Rva0045BA00Dispatch *)TheTacticalView)->Rva0045BA00Slot(&entries[0].point, &entries[1].point, 0xffffffff, 0);
    ((Rva0045BA00Dispatch *)TheTacticalView)->Rva0045BA00Slot(&entries[entries.size() - 1].point, &entries[entries.size() - 2].point, 0xffffffff, 0);
    bool first = true;
    Coord3D previous;
    setCoord(&previous, &entries[1].point);
    typedef char (Rva003A1A30Dispatch::*Check)(Rva003A2070Obj *, bool, float *);
    union { void (*function)(); Check member; } check;
    check.function = j_000481fd;
    if ((((Rva003A1A30Dispatch *)g_bfmeMgrGK)->*check.member)(this, false, 0))
    {
        do
        {
            m_accum += 15.0f;
            if (!first)
                ((Rva0045BA00Dispatch *)TheTacticalView)->Rva0045BA00Slot(&previous, &m_point, 0xffff0000, 0);
            previous = m_point;
            first = false;
            previous.z = ((Rva012EF4CCDispatch *)TheTerrainLogic)->slot18(previous.x, previous.y, 0);
            ((Rva0045BA00Dispatch *)TheTacticalView)->Rva0045BA00Slot(&previous, &m_point, 0xccdd7755, 0);
            previous.z = m_point.z;
        } while ((((Rva003A1A30Dispatch *)g_bfmeMgrGK)->*check.member)(this, false, 0));
    }
}
