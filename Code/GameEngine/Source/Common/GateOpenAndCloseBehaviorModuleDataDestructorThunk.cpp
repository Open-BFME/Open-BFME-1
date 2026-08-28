// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Seven members, destroyed in reverse declaration order with the unwind state
// counting down from 6: two vectors of strings at +0x34 and +0x28, four
// references at +0x24 through +0x18, and a string at +0x14.
//
// The vectors' destructor is CALLED rather than inlined -- an element with its
// own destructor makes the teardown a loop, which MSVC emits once as a COMDAT
// and calls, where a POD element inlines the whole thing. Both forms appear in
// this family and the difference is only the element type.
//
// The class installs its own vptr at entry so it is not novtable, and the store
// of 0x01073744 at the end is Snapshot's from the base destructor inlined last.
// The reference release is `delete this` inside Release_Ref, which is what keeps
// the second null test after the caller has already tested the pointer; with
// four uses the import entry is hoisted into ebx.
#include <vector>

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

class GateOpenAndCloseBehaviorModuleData : public Snapshot
{
public:
	virtual ~GateOpenAndCloseBehaviorModuleData();

private:
	unsigned char m_gap0[0x10];
	BFMERetailAsciiString m_name;
	ThingRef m_ref0;
	ThingRef m_ref1;
	ThingRef m_ref2;
	ThingRef m_ref3;
	std::vector<BFMERetailAsciiString> m_vec0;
	std::vector<BFMERetailAsciiString> m_vec1;
};

// ??1GateOpenAndCloseBehaviorModuleData@@UAE@XZ
GateOpenAndCloseBehaviorModuleData::~GateOpenAndCloseBehaviorModuleData()
{
}
