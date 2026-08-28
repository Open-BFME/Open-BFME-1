// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DLaserDrawModuleData@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp

// Five members destroyed in reverse declaration order -- the strings at +0x18
// and +0x14, then the three references at +0x10, +0x0C and +0x08 -- with the
// unwind state counting down 4 to 0, which is a single class's member list. The
// class installs its own vptr at entry so it is not novtable, and the store of
// 0x01073744 at the end is Snapshot's, from the base destructor inlined last.
//
// The reference release is `delete this` inside Release_Ref. That is what keeps
// the second null test in each of the three copies: the caller has already
// tested the pointer, but once Release_Ref is inlined its `this` is a value the
// optimiser does not connect to what the caller tested, so the delete keeps its
// own check.
//
// InterlockedDecrement is dllimport, so the call goes through the import table.
// With three uses the compiler loads the table entry into ebx once rather than
// spelling out call dword ptr [...] at each site.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DLaserDraw.h
class W3DLaserDrawModuleData : public Snapshot
{
public:
	virtual ~W3DLaserDrawModuleData();

private:
	unsigned char m_gap0[0x04];
	ThingRef m_ref0;
	ThingRef m_ref1;
	ThingRef m_ref2;
	BFMERetailAsciiString m_name0;
	BFMERetailAsciiString m_name1;
};

// ??1W3DLaserDrawModuleData@@UAE@XZ
W3DLaserDrawModuleData::~W3DLaserDrawModuleData()
{
}
