// Retail 0x002458B0: HordeContain/HorseHordeContain interface slot 7.
// Anonymous method spelling retained from bank; boundary ret 12 at +0xda.
// Index lookup is unconditional. Ready selects local formation coordinates or
// owner fallback at interface-0xe4. Native STLport vector restores retail reloads.
// Object+0x74 is m_id and Thing+0x38 is m_cachedPos (name_oracle witnesses);
// these replace the banked shim names m_formationSlot and m_defaultX/Y/Z.
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>

#include "coord.h"
#define BFME_HAVE_COORD3D 1
#include "../../object.h"

struct FormationSlot
{
	UnsignedByte m_pad0[4];
	float x;
	float y;
	float z;
	UnsignedByte m_invalid;
	UnsignedByte m_padTail[0x1c - 0x11];
};

// still a dump: 0x0001F91F -> pinned ?bfmeTwoDSU@BfmeSubDSU@@QAEPAPAXPAPAX@Z
class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **key);
};

extern void j_0002c53e();

// owning object embedded at this-0xE4; real identity unproven (AOD layout
// unwitnessed), so address-qualified.
class Rva002458B0Owner
{
public:
	void rva00242a30(Coord3D *out, Object *member, float scalar)
	{
		union {
			void (*entry)();
			void (Rva002458B0Owner::*method)(Coord3D *, Object *, float);
		} call;
		call.entry = j_0002c53e;
		(this->*call.method)(out, member, scalar);
	}
};

class Rva002458B0Host
{
public:
	Coord3D *rva002458b0(Coord3D *out, Object *member, float scalar);

private:
	UnsignedByte m_pad000[0x3c];
	UnsignedByte m_pad03c[0xf4 - 0x3c];
	_STL::vector<FormationSlot> m_formation;
	UnsignedByte m_pad0fc[0x118 - 0xf4 - sizeof(_STL::vector<FormationSlot>)];
	bool m_ready;
};

Coord3D *Rva002458B0Host::rva002458b0(Coord3D *out, Object *member, float scalar)
{
	int key = member->m_id;
	int index = (int)*((BfmeSubDSU *)((char *)this + 0x3c))->bfmeTwoDSU((void **)&key);
	if (m_ready) {
		Coord3D result;
		result = member->m_cachedPos;
		// Retail uses JA, retaining the inclusive upper bound.
		if (index >= 0 && (unsigned int)index <= m_formation.size() && !m_formation[index].m_invalid)
			result = *(Coord3D *)&m_formation[index].x;
		out->x = result.x;
		out->y = result.y;
		out->z = result.z;
		return out;
	}
	((Rva002458B0Owner *)((char *)this - 0xe4))->rva00242a30(out, member, scalar);
	return out;
}
