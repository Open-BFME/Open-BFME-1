// ?rva000BDD20@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.5169 date=2026-10-03
// Bank only: retail385B; candidate384B, shape0.977,184 non-reloc diffs.
// NOT byte exact: frame14 versus10; empty vector tag at local13 versus
// incoming store slot; temporary release register/compare scheduling differs.
// Native INIException lifetime is retained, but retail descriptor11DFC30
// destroys through41460F->61BD0, while current named destructor is139FF0.
// Coordinate that existing exception-family defect before promotion.
// Audio ref layout comes from AudioManagerFindAllAudioEventsOfType.cpp;
// its ownership needs reconciliation with the old POD overflow TU atBD3B0.
// Complete literal NoSound and Invalid Sound '%s' read through terminators.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Common/INI /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/iniexception
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "INI.h"
#include "Common/INIException.h"
#include <string.h>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
struct AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(AudioEventInfo *info = 0) : m_info(info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	AudioEventInfoRef(const AudioEventInfoRef &other) : m_info(other.m_info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	~AudioEventInfoRef(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}

	AudioEventInfoRef &operator=(const AudioEventInfoRef &other) {
        if (this != &other) {
            if (other.m_info) InterlockedIncrement(&other.m_info->m_refCount);
            if (m_info) m_info->Release_Ref();
            m_info = other.m_info;
        }
        return *this;
    }
    AudioEventInfo *m_info;
};

// The element type as the ledger names the vector's _M_insert_overflow
// (0x000BD3B0): an AudioEventInfoRef by its copy (store + InterlockedIncrement)
// and its destroy (InterlockedDecrement + deleting destructor).
struct Rva000BD3B0Element : public AudioEventInfoRef
{
	Rva000BD3B0Element(AudioEventInfo *info = 0) : AudioEventInfoRef(info) { }
};

class Rva000BDD20AudioView { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual AudioEventInfoRef find(const AsciiString *) const;
};
extern void *TheAudioClientUpdate;
void __cdecl rva000BDD20(INI *ini, void *, void *store, const void *) {
    const char *token=ini->getNextTokenOrNull();
    while (token) {
        Rva000BD3B0Element value;
        if (_strcmpi(token,"NoSound") != 0) {
            value.AudioEventInfoRef::operator=(((Rva000BDD20AudioView *)TheAudioClientUpdate)->find(&AsciiString(token)));
            if (!value.m_info) throw INIException(3,"Invalid Sound '%s'",token);
        }
        ((_STL::vector<Rva000BD3B0Element> *)store)->push_back(value);
        token=ini->getNextTokenOrNull();
    }
}
