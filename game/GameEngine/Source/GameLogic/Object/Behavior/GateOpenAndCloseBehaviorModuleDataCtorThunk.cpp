// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// GateOpenAndCloseBehaviorModuleData default constructor (0x001FCEC0, 483 B).
// Identity: the matched GateOpenAndCloseBehavior::friend_newModuleData
// (0x00123AB0) news this class and calls this body; the vtable it installs
// (0x010A4210) is the one the matched destructor installs. Layout follows the
// destructor TU: a string at +0x14, four references at +0x18..+0x24, two
// vectors of strings at +0x28 and +0x34. The two trailing words take the
// value of the global the matched Rva001FC2F0/Rva001FC310 getters treat as
// "unset" (fall back to +0x0C).
#include <vector>
#include "ascii_string.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

extern unsigned int g_sentinel012ADC38;

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

class GateOpenAndCloseBehaviorModuleData : public Snapshot
{
public:
	GateOpenAndCloseBehaviorModuleData();
	virtual ~GateOpenAndCloseBehaviorModuleData();

private:
	unsigned int m_unknown04;
	bool m_byte08;
	int m_dword0C;
	int m_dword10;
	AsciiString m_string14;
	ThingRef m_ref18;
	ThingRef m_ref1C;
	ThingRef m_ref20;
	ThingRef m_ref24;
	std::vector<AsciiString> m_vector28;
	std::vector<AsciiString> m_vector34;
	unsigned int m_dword40;
	unsigned int m_dword44;
};

GateOpenAndCloseBehaviorModuleData::GateOpenAndCloseBehaviorModuleData()
	: m_ref18(), m_ref1C(), m_ref20(), m_ref24()
{
	m_byte08 = false;
	m_dword0C = 50;
	m_dword10 = 50;
	m_string14.clear();
	AsciiString openLeft("OpenLeft");
	AsciiString openRight("OpenRight");
	AsciiString closed("Closed");
	m_vector28.clear();
	m_vector28.push_back(openLeft);
	m_vector28.push_back(openRight);
	m_vector34.clear();
	m_vector34.push_back(closed);
	unsigned int value = g_sentinel012ADC38;
	m_dword40 = value;
	m_dword44 = value;
}
