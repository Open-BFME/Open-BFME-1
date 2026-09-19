// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// ContestableContain's periodic contest refresh, retail 0x0021BCA0.
//
// The owner is fixed by the retail thunk at 0x0002F919: the sole named
// caller, Rva0021D4A0::check, passes the complete ContestableContain object
// (its secondary interface has this+0x10) and refreshes it when the cached
// frame at this+0x9D4 expires.  The refresh walks OpenContain's real
// contained-object list, then ContestableContain's object list, and advances
// that cache by thirty logic frames.

#include <list>
#include <map>

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object
{
};

// The BFME GameLogic frame is the field used by the surrounding
// ContestableContain state machine at GameLogic+0x3C.
class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return m_frame;
	}

private:
	unsigned char m_unreconstructed_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// OpenContain's multiple-inheritance prefix is the same layout recovered by
// ContestableContainDestructorThunk.cpp.  Its first real data member begins
// at +0x38; the remaining opaque base data ends at +0x3FC.
class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase();

private:
	unsigned char m_pad[8];
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase();
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase();

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
protected:
	_STL::list<Object *> m_containList; // +0x38, upstream ContainedItemsList

private:
	unsigned char m_pad[0x3c0];
};

class Coord3D
{
private:
	float m_value[3];
};

class __declspec(novtable) GarrisonContain : public OpenContain
{
private:
	Coord3D m_garrisonPoint[3][40]; // base ends at +0x99C
};

// These are the payload types already recovered from the ContestableContain
// destructor's real STLport instantiations.  The refresh only needs the list
// heads, but retaining the member types keeps the proven offsets truthful.
struct ContestableMapEntry
{
	int a[2];
};

struct ContestableRecord
{
	int a[2];
};

class ContestableContain : public GarrisonContain
{
public:
	void updateContestStatus();
	void updateObject(Object *object, Bool contesting);

private:
	unsigned char m_unreconstructed_99c[0x20];
	_STL::list<Object *> m_contestList; // +0x9BC
	_STL::list<Object *> m_contestListShadow; // +0x9C0
	_STL::map<int, ContestableMapEntry> m_objectData; // +0x9C4
	_STL::list<ContestableRecord> m_records; // +0x9D0
	UnsignedInt m_lastContestUpdateFrame; // +0x9D4
};

// 0x00026396 is the existing incremental-link thunk for the real
// ContestableContain::updateObject(Object *, Bool) implementation at
// 0x0021BAF0. The typed helper pin in reverse/symbols.csv preserves this
// independently verified ILT route until the callee is converted.

// ?updateContestStatus@ContestableContain@@QAEXXZ
void ContestableContain::updateContestStatus()
{
	for (_STL::list<Object *>::iterator it = m_containList.begin();
		it != m_containList.end(); ++it)
	{
		updateObject(*it, false);
	}

	for (_STL::list<Object *>::iterator it = m_contestList.begin();
		it != m_contestList.end(); ++it)
	{
		updateObject(*it, true);
	}

	m_lastContestUpdateFrame = TheGameLogic->getFrame() + 30;
}
