// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// One vector member and an inlined base destructor.
//
// The teardown is STLport's size-dispatched deallocate: capacity in bytes from
// +0x48 minus +0x40, rounded by the sar 2 / shl 2 pair to a multiple of four, so
// the element is four bytes and has no destructor -- there is no loop before the
// free.
//
// This class stores its own vptr at entry, so it is not novtable, and the store
// of 0x01073744 at the end is Snapshot's from the base destructor inlined last.
// The mangling is MAE rather than UAE, which makes the destructor protected.
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon : public Snapshot
{
protected:
	virtual ~Weapon();

private:
	unsigned char m_gap[0x3C];
	std::vector<int> m_entries;
};

// ??1Weapon@@MAE@XZ
Weapon::~Weapon()
{
}
