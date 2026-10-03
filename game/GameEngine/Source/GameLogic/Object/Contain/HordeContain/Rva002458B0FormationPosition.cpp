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

// ILT 0x0001F91F is the thiscall map subscript at 0x226FA0; called through the ILT thunk
extern void j_0001f91f();
class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **key)
	{
		typedef void **(BfmeSubDSU::*Sub)(void **);
		union { void (*raw)(); Sub member; } f;
		f.raw = j_0001f91f;
		return (this->*f.member)(key);
	}
	int &lookup(const unsigned &key)
	{
		typedef int &(BfmeSubDSU::*Fn)(const unsigned &);
		union { void (*raw)(); Fn member; } f;
		f.raw = j_0001f91f;
		return (this->*f.member)(key);
	}
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

struct BfmeHordeSlot
{
	void *m_key;
	UnsignedByte m_tail[0xc];
};

// Retail writes the 12-byte return value into the first stack argument.
struct Rva00242A30Value
{
	Real x;
	Real y;
	Real z;
	Rva00242A30Value() {}
	Rva00242A30Value(const Rva00242A30Value &other)
		: x(other.x), y(other.y), z(other.z) {}
};

struct Rva00242A30FormationEntry
{
	UnsignedByte m_pad00[4];
	Rva00242A30Value m_coord04;
	UnsignedByte m_byte10;
	UnsignedByte m_pad11[0x1c - 0x11];
};

template<class T> struct Rva00242A30VectorView
{
	T *m_begin;
	T *m_end;
	T *m_endStorage;
	unsigned size() const { return (unsigned)(m_end - m_begin); }
	T *begin() { return m_begin; }
};

struct Rva00233F30Offset { Real x, y; };

struct BfmeRva44E60Record
{
	Int m_dword00;
	Rva00233F30Offset m_pair04;
	Real m_float0C;
};

extern void j_00019736();

class Rva00242A30Owner
{
public:
	Rva00242A30Value rva00242a30(Object *member, Real *outThird);

private:
	UnsignedByte m_pad00[8];
	Object *m_object08;
	UnsignedByte m_pad0c[0x120 - 0xc];
	UnsignedByte m_at120[0xc];
	Rva00242A30VectorView<BfmeHordeSlot> m_vector12c;
	UnsignedByte m_pad138[0x1d8 - 0x138];
	Rva00242A30VectorView<Rva00242A30FormationEntry> m_vector1d8;
	UnsignedByte m_pad1e4[0x1fc - 0x1e4];
	UnsignedByte m_byte1fc;
};

Rva00242A30Value Rva00242A30Owner::rva00242a30(Object *member, Real *outThird)
{
	Rva00242A30Value *pos = (Rva00242A30Value *)&m_object08->m_cachedPos;
	unsigned key = (unsigned)member->m_id;
	int index = ((BfmeSubDSU *)m_at120)->lookup(key);
	{
		Rva00242A30Value result;
		result = *pos;
		if (index >= 0 && (unsigned)index <= m_vector12c.size()) {
			if (m_byte1fc && !m_vector1d8.begin()[index].m_byte10) {
				result = m_vector1d8.begin()[index].m_coord04;
				return result;
			}
		} else return result;
	}
	{
		typedef void (Rva00242A30Owner::*RecordFn)(BfmeRva44E60Record *, Int);
		union { void (*raw)(); RecordFn member; } recordCall;
		recordCall.raw = j_00019736;
		BfmeRva44E60Record record;
		(this->*recordCall.member)(&record, index);
		Rva00242A30Value result;
		result.x = record.m_pair04.x + pos->x;
		result.y = record.m_pair04.y + pos->y;
		result.z = pos->z;
		*outThird = record.m_float0C;
		return result;
	}
}
