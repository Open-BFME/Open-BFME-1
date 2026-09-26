// ?rva00150A70@AIGroup@@QAEXPAUCoord3D@@PBU2@W4CommandSourceType@@@Z
// partial score=0.74 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00150A70, 181 bytes. Owning class is proven real: `this` (ecx)
// is passed straight through to the matched-signature pins
// ?prepFollow@AIGroup@@QAEXW4CommandSourceType@@H@Z (ILT 0x0002e636) and
// bfmeRunGK@BfmeOwnerGK (ILT 0x00006258), and the member-list walk at +4
// (mov eax,[this+4]; mov edi,[eax]; cmp edi,eax) is exactly AIGroup's
// _STL::list<Object*> m_memberList from the landed
// Code/GameEngine/Source/Common/RTS/AIGroupMembership.cpp -- reused here
// verbatim. Two prior blocked passes named the behavior (per-member
// position/orientation transform) but found no method name, since the
// only caller is anonymous; this stays address-derived on the proven
// AIGroup class.
//
// Per member: rotate the object's cached (m_offsetX, m_offsetY) by the
// direction from `pB` (2nd arg) to `pA`... no: by calling the banked
// rotate-by-direction helper at 0x00150100 with (pB=arg1 "anchor",
// pA=arg2, vec=&offset), add the rotated offset to anchor's x/y (keeping
// anchor's raw 3rd dword as the new z untouched), set the member's
// position via BfmeHostTP::bfmeSetPositionTP, compute its new relative
// angle via Thing::bfmeRelativeAngleTo(arg2), and apply it via
// BfmeD1044::bfmeStep1044. All three tail calls are proven non-virtual
// real symbols; BfmeD1044/BfmeHostTP/Thing are unrelated-type casts (zero
// `this` adjustment, matching the direct ecx=member reuse retail shows).

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Player;
class AIGroup;

struct Coord3D
{
	Real x, y, z;
};

// The rotated-in-place offset buffer only ever needs x/y as floats and the
// z dword copied verbatim (retail moves it with a plain `mov`, never an
// `fld`), so keep it an int here to keep the copy an integer store.
struct Vec3Raw
{
	Real x, y;
	Int zRaw;
};

class Thing
{
public:
	Real bfmeRelativeAngleTo(const Coord3D *) const;
};

class BfmeD1044
{
public:
	void bfmeStep1044(Int angleBits);
};

class BfmeHostTP
{
public:
	void bfmeSetPositionTP(const Vec3Raw *pos, Bool flag);
};

class BfmeOwnerGK
{
public:
	void bfmeRunGK();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;		// ILT 0x00020824
	void leaveGroup(void);					// ILT 0x0001F212

	unsigned char m_pad300[0x320];
	Real m_offsetX;						// +0x320
	Real m_offsetY;						// +0x324
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isMember(Object *obj);
	Bool containsAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);
	Bool remove(Object *obj);
	Bool removeAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);
	void prepFollow(CommandSourceType type, Int flag);

	void rva00150A70(Coord3D *anchor, const Coord3D *facing, CommandSourceType source);

	Bool isEmpty(void) { return m_memberList.empty(); }

private:
	virtual ~AIGroup();					// pool object vptr, this+0x00

	_STL::list<Object *> m_memberList;			// this+0x04
	UnsignedInt m_memberListSize;				// this+0x08
	void *m_groundPath;					// this+0x0C
	Bool m_dirty;						// this+0x10
};

#pragma comment(linker, "/alternatename:?rva00150100RotateFwd@@YAXPBXPBXPAX@Z=?j_0003d104@@YAXXZ")
extern "C" void j_0003d104();
void __cdecl rva00150100RotateFwd(const void *pB, const void *pA, void *vecInOut);

void AIGroup::rva00150A70(Coord3D *anchor, const Coord3D *facing, CommandSourceType source)
{
	((BfmeOwnerGK *)this)->bfmeRunGK();
	prepFollow(source, 0);

	for (_STL::list<Object *>::iterator it = m_memberList.begin();
		it != m_memberList.end(); ++it)
	{
		Object *member = *it;
		if (member == 0)
			continue;

		Vec3Raw pos;
		pos.x = member->m_offsetX;
		pos.y = member->m_offsetY;

		rva00150100RotateFwd(anchor, facing, &pos);

		pos.x = pos.x + anchor->x;
		pos.y = pos.y + anchor->y;
		pos.zRaw = ((const Int *)anchor)[2];

		((BfmeHostTP *)member)->bfmeSetPositionTP(&pos, false);

		Real angle = ((Thing *)member)->bfmeRelativeAngleTo(facing);
		((BfmeD1044 *)member)->bfmeStep1044(*(Int *)&angle);
	}
}
