// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: lift MASM dump to standalone C++ thunk.
//
// Shape: `class GettingBuiltBehaviorModuleData : public Snapshot`. Snapshot supplies
// the single vptr store (root polymorphic, own vtable stored directly -- a
// constructor never elides its vptr store the way a derived destructor can).
// Three ThingRef members at +0x08/+0x0C/+0x10 default-construct to a zeroed
// pointer with no call (their non-trivial destructors are what gives this
// ctor its EH unwind frame, matching retail's SEH prologue). Two AsciiString
// sub-objects at +0x14/+0x18 default-construct their internal pointer to
// zero, then the body explicitly calls set() on each -- retail's
// `?set@AsciiString@@QAEXPBDH@Z` (see reverse/symbols.csv). +0x04 is a gap
// retail never stores to, so it is declared but left uninitialised. The body
// statement order below is not declaration order: it is deliberately the
// order retail's scheduler places the stores in (m_width1/m_count0 land
// before the two set() calls; the rest land after), reproduced here by
// writing the assignments in that literal sequence.

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
	~AsciiString();

	void set(const char *s, int len);

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class GettingBuiltBehaviorModuleData : public Snapshot
{
public:
	GettingBuiltBehaviorModuleData();
	virtual ~GettingBuiltBehaviorModuleData();

private:
	unsigned char m_gap0[4];
	ThingRef m_ref0;
	ThingRef m_ref1;
	ThingRef m_ref2;
	AsciiString m_name0;
	AsciiString m_name1;
	bool m_flag0;
	float m_width0;
	float m_width1;
	unsigned int m_count0;
	bool m_flag1;
	float m_f0;
	float m_f1;
	float m_f2;
	float m_f3;
};

// ??0GettingBuiltBehaviorModuleData@@QAE@XZ
GettingBuiltBehaviorModuleData::GettingBuiltBehaviorModuleData()
{
	m_width1 = 60.0f;
	m_count0 = 0;
	m_name0.set("", 0);
	m_name1.set("", 0);
	m_flag1 = false;
	m_flag0 = false;
	m_width0 = 30.0f;
	m_f0 = 0.25f;
	m_f1 = 0.5f;
	m_f2 = 0.75f;
	m_f3 = 1.0f;
}
