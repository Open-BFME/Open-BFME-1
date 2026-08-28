// cl: /DNDEBUG /MD /EHsc

// Two members destroyed in reverse declaration order: the reference at +0x20
// first, then the string at +0x8. The unwind state counts DOWN, 1 then 0, which
// is what a single class's member list does; an inlined base's member would make
// it count up. This class installs its own vptr at entry so it is not novtable,
// and the store of 0x01073744 at the end is Snapshot's, from the base destructor
// inlined last.
//
// The release is two nested pieces, and the shape says so. The caller tests the
// pointer once, and after the interlocked decrement the pointer is tested AGAIN
// before the virtual delete -- a check the compiler would remove if both lived
// in one function, since the first test dominates the second. It survives
// because the inner half is `delete this` inside Release_Ref: once inlined, the
// callee's this is a different value to the pointer the caller tested, and MSVC
// does not re-derive the fact.
//
// InterlockedDecrement is reached indirectly through the import table, so it has
// to be declared dllimport; without that the call comes out as a direct e8.
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0) {
			delete this;
		}
	}

	long m_refCount;
};

class ThingRef
{
public:
	~ThingRef()
	{
		if (m_ptr) {
			m_ptr->Release_Ref();
		}
	}

private:
	RefCountedThing *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class OneRingPenaltyUpdateModuleData : public Snapshot
{
public:
	virtual ~OneRingPenaltyUpdateModuleData();

private:
	unsigned char m_gap0[0x04];
	BFMERetailAsciiString m_name;
	unsigned char m_gap1[0x14];
	ThingRef m_ref;
};

// ??1OneRingPenaltyUpdateModuleData@@UAE@XZ
OneRingPenaltyUpdateModuleData::~OneRingPenaltyUpdateModuleData()
{
}
