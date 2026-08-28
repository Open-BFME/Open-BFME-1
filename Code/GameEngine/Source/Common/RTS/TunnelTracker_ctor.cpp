// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0TunnelTracker@@: Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp
// Open-BFME: TunnelTracker::TunnelTracker, retail 0x000F8980, 140 bytes.
//
// The reference's constructor body -- four counters zeroed, in the reference's
// own order -- wrapped in the three list constructions the compiler puts ahead
// of it. Those are most of the 140 bytes: each list takes a 0x0C-byte header
// node from the STLport node allocator and points it at itself, and the two
// unwind states between them are what the SEH frame is for.
//
// That fixes the layout as the reference has it: the pool object's vptr at +0,
// then m_tunnelIDs, m_containList and m_xferContainList at +4, +8 and +0x0C,
// then m_containListSize, m_tunnelCount, m_curNemesisID and m_nemesisTimestamp
// filling +0x10 to +0x1C. The stores land in the constructor's order rather
// than the declaration's, which is what identifies which counter is which.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

typedef int ObjectID;
enum { INVALID_ID = 0 };

class Object;
class Xfer;

// Empty, but with a destructor: the unwind state is raised before the first
// list is built, which only happens when something ahead of the members already
// needs unwinding.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolObject
{
public:
	MemoryPoolObject(void) {}
	~MemoryPoolObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker : public MemoryPoolObject
{
public:
	TunnelTracker(void);

	virtual ~TunnelTracker();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:

	_STL::list<ObjectID> m_tunnelIDs;		// this+0x04
	_STL::list<Object *> m_containList;		// this+0x08
	_STL::list<ObjectID> m_xferContainList;		// this+0x0C
	Int m_containListSize;				// this+0x10
	UnsignedInt m_tunnelCount;			// this+0x14

	ObjectID m_curNemesisID;			// this+0x18
	UnsignedInt m_nemesisTimestamp;			// this+0x1C
};

TunnelTracker::TunnelTracker()
{
	m_tunnelCount = 0;
	m_containListSize = 0;
	m_curNemesisID = (ObjectID)INVALID_ID;
	m_nemesisTimestamp = 0;
}
