// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DLaserDrawModuleData@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp
// readable body of ??1W3DLaserDrawModuleData@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp
//
// Constructor and destructor of one class, so they need one declaration of it.
// Field names come from retail's own INI field table joined to upstream's parse
// table on the key: retail supplies every offset, upstream only the word. The
// offsets were derived from this class's declaration sequence and type sizes,
// never read out of the old placeholder names.
//
// Shape: `class W3DLaserDrawModuleData : public Snapshot`. Snapshot supplies the
// single vptr store (root polymorphic, own vtable stored directly -- a
// constructor never elides its vptr store the way a derived destructor can).
// Three ThingRef members at +0x08/+0x0C/+0x10 default-construct to a zeroed
// pointer with no call; their non-trivial destructors are what gives the
// constructor its EH unwind frame, matching retail's SEH prologue. Two
// AsciiString sub-objects at +0x14/+0x18 default-construct their internal
// pointer to zero, then the body explicitly calls set() on each. +0x04 is a gap
// retail never stores to, so it is declared but left uninitialised.
//
// The constructor's statement order is not declaration order: it is deliberately
// the order retail's scheduler places the stores in (m_width1/m_count0 land
// before the two set() calls; the rest land after), reproduced here by writing
// the assignments in that literal sequence.
//
// The destructor destroys five members in reverse declaration order -- the
// strings at +0x18 and +0x14, then the three references at +0x10, +0x0C and
// +0x08 -- with the unwind state counting down 4 to 0, which is a single class's
// member list. The class installs its own vptr at entry so it is not novtable,
// and the store of 0x01073744 at the end is Snapshot's, from the base destructor
// inlined last.
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
//
// AsciiString's destructor is written inline as a call to releaseBuffer because
// that is the shape retail's destructor carries; reverse/symbols.csv pins
// ?releaseBuffer@AsciiString@@AAEXXZ and ??1AsciiString@@QAE@XZ to the same body
// at 0x00887940, so both spellings emit the same call.

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
	ThingRef() : m_ptr(0) {}
	~ThingRef()
	{
		if (m_ptr) {
			m_ptr->Release_Ref();
		}
	}

private:
	RefCountedThing *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString() { releaseBuffer(); }

	void set(const char *s, int len);

private:
	void releaseBuffer();

	char *m_data;
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
	W3DLaserDrawModuleData();
	virtual ~W3DLaserDrawModuleData();

private:
	unsigned char m_gap0[4];
	ThingRef m_ref0;
	ThingRef m_ref1;
	ThingRef m_ref2;
	AsciiString m_name0;
	AsciiString m_name1;
	bool m_tile;
	float m_width0;
	float m_width1;
	unsigned int m_count0;
	bool m_textureName;
	float m_f0;
	float m_f1;
	float m_segments;
	float m_arcHeight;
};

// ??0W3DLaserDrawModuleData@@QAE@XZ
W3DLaserDrawModuleData::W3DLaserDrawModuleData()
{
	m_width1 = 60.0f;
	m_count0 = 0;
	m_name0.set("", 0);
	m_name1.set("", 0);
	m_textureName = false;
	m_tile = false;
	m_width0 = 30.0f;
	m_f0 = 0.25f;
	m_f1 = 0.5f;
	m_segments = 0.75f;
	m_arcHeight = 1.0f;
}

// ??1W3DLaserDrawModuleData@@UAE@XZ
W3DLaserDrawModuleData::~W3DLaserDrawModuleData()
{
}
