// cl: /DNDEBUG /MD /EHsc

// A single reference member at +0x24 and nothing else. The class installs its
// own vptr at entry so it is not novtable, and the store of 0x01073744 at the
// end is Snapshot's, from the base destructor inlined last.
//
// The release is `delete this` inside Release_Ref, which is what keeps the
// second null test after the caller has already tested the pointer: once
// inlined, the callee's this is a value the optimiser does not connect to what
// the caller tested, so the delete expansion keeps its own check.
//
// InterlockedDecrement is dllimport. With one call site it stays as
// call dword ptr [__imp__...] rather than being hoisted into a register.
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h
class MinefieldBehaviorModuleData : public Snapshot
{
public:
	virtual ~MinefieldBehaviorModuleData();

private:
	unsigned char m_gap0[0x20];
	ThingRef m_ref;
};

// ??1MinefieldBehaviorModuleData@@UAE@XZ
MinefieldBehaviorModuleData::~MinefieldBehaviorModuleData()
{
}
