// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
// The matched Player::findClosestByKindOf body at 0x000CFD20 constructs this
// object through the ILT thunk at 0x00037FE7, which lands at 0x000CFAC0.
// The upstream Player.cpp supplies the class and constructor identity.  BFME's
// variant stores the query position as a Coord3D, giving the retail 68-byte
// layout rather than Zero Hour's Object-pointer source field.

#include <float.h>
#include <string.h>

typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags() { clear(); }

	void clear()
	{
		memset(this, 0, sizeof(*this));
	}

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

class Object;

class ClosestKindOfData
{
public:
	ClosestKindOfData();

private:
	KindOfMaskType m_setKindOf;
	KindOfMaskType m_clearKindOf;
	Coord3D m_source;
	Object *m_closest;
	Real m_closestDistSq;
};

// ??0ClosestKindOfData@@QAE@XZ
ClosestKindOfData::ClosestKindOfData()
{
	m_setKindOf.clear();
	m_clearKindOf.clear();
	m_source.x = 0.0f;
	m_source.y = 0.0f;
	m_source.z = 0.0f;
	m_closest = 0;
	m_closestDistSq = FLT_MAX;
}
