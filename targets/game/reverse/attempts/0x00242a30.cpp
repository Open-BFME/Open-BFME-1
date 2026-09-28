// ?d_00242a30@@YAXXZ
// partial score=0.4065934066 date=2026-09-28
// ?rva00242A30GetFormationPosition@Rva00242A30Owner@@QAE?AUCoord3D@@PAVObject@@PAM@Z
// Retail 0x00242A30 ret12: hidden Coord3D return; owner object at +8.
// Corrected stash: the fallback position belongs to owner+8, not the member.
// Helper at 0x002350C0 returns the 16-byte BfmeRva44E60Record by value
// with index + hidden buffer (ret8), established by its landed source.
// Native scoped aggregate lifetimes reproduce retail's 16-byte frame.
// Current residue: index EAX/ECX allocation, slot pointer/CSE; 271/273B.
typedef float Real;
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[0x38];
	Coord3D m_bfmePosition;					///< object position at +0x38
	char m_bfmeMid[0x74 - 0x38 - 0xc];
	void *m_id;								///< retail this+0x74
};

// the index map BfmeConv776/HordeContainMemberNameMatches pins at 0x0001F91F
extern void j_0001f91f();
class BfmeSubDSU
{
public:
	int &lookup(const unsigned &key) {
        typedef int &(BfmeSubDSU::*Fn)(const unsigned&);
        union { void (*raw)(); Fn member; } f;
        f.raw=j_0001f91f; return (this->*f.member)(key);
    }
};

// matches HordeContainMemberNameMatches.cpp's BfmeHordeRosterEntry-adjacent
// BfmeHordeSlot exactly (16 bytes); only used here for its begin/end extent
struct BfmeHordeSlot
{
	char m_bfmeBody[0x10];
};

struct Rva00242A30FormationSlot
{
	char m_pad00[4];
	Coord3D m_position;					///< offset 0x4
	Bool m_busy;							///< offset 0x10
	char m_pad11[0x1c - 0x11];
};

struct Rva00233F30Offset { float x,y; };
struct BfmeRva44E60Record {
    int m_dword00;
    Rva00233F30Offset m_pair04;
    float m_float0C;
};
class Rva00233F30 {
public: BfmeRva44E60Record rva002350c0(int index);
};
class Rva00242A30Owner
{
public:
    Coord3D rva00242A30GetFormationPosition(Object *member, Real *outThird);
    char m_pad00[8];
    Object *m_object08;
    char m_pad0c[0x120-0xc];
    char m_indices120[0xc];
    BfmeHordeSlot *m_bfmeSlotsBegin;
    BfmeHordeSlot *m_bfmeSlotsEnd;
    char m_pad134[0x1d8-0x134];
    Rva00242A30FormationSlot *m_formationSlots;
    char m_pad1dc[0x1fc-0x1dc];
    Bool m_readyFlag;
};
Coord3D Rva00242A30Owner::rva00242A30GetFormationPosition(Object *member, Real *outThird)
{
    Coord3D *pos = &m_object08->m_bfmePosition;
    unsigned key = (unsigned)member->m_id;
    int index = ((BfmeSubDSU*)m_indices120)->lookup(key);
    {
    Coord3D result; result = *pos;
    if (index >= 0 && (unsigned)index <= (unsigned)(m_bfmeSlotsEnd-m_bfmeSlotsBegin)) {
        if (m_readyFlag && !m_formationSlots[index].m_busy) {
            result = m_formationSlots[index].m_position;
            return result;
        }
    } else return result;
    }
    {
        BfmeRva44E60Record record = ((Rva00233F30*)this)->rva002350c0(index);
        Coord3D result;
        result.x = record.m_pair04.x + pos->x;
        result.y = record.m_pair04.y + pos->y;
        result.z = pos->z;
        *outThird = record.m_float0C;
    return result;
    }
}
