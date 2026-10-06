// cl: /O2

// Retail 0x001BD7D0 copies the three words at this+0x48 into the hidden return
// slot and leaves that slot's address in EAX. The matched caller
// Object::bfmeGetLastShotPosition (0x001BF970, ObjectDamageAndWeapons.cpp)
// calls it through ILT 0x000228BD and reads the result through EAX, so the body
// returns the position by value rather than filling an out parameter. The
// owner class is not proven, so the name stays address-derived.

// The same view of the position the caller uses: the words move through the
// general registers, one load and one store at a time, not the x87 stack.
union BfmeFiringPositionWord
{
	float f;
	volatile unsigned int u;
};

struct BfmeFiringPosition
{
	BfmeFiringPosition() {}
	BfmeFiringPosition(const BfmeFiringPosition &other)
	{
		x.u = other.x.u;
		y.u = other.y.u;
		z.u = other.z.u;
	}
	BfmeFiringPositionWord x;
	BfmeFiringPositionWord y;
	BfmeFiringPositionWord z;
};

class Rva001BD7D0
{
	char m_lead[0x48];
	BfmeFiringPosition m_48;

public:
	BfmeFiringPosition get() const;
};

// ?get@Rva001BD7D0@@QBE?AUBfmeFiringPosition@@XZ
BfmeFiringPosition Rva001BD7D0::get() const
{
	return m_48;
}
