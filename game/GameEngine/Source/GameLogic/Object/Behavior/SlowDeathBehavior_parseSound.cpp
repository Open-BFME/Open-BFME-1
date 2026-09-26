// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef int Int;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	static Int scanIndexList(const char *token, const char *const *nameList);
};

class AudioEventInfo
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

struct Rva000BD3B0Element
{
	Rva000BD3B0Element(const Rva000BD3B0Element &other) : m_info(other.m_info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	~Rva000BD3B0Element(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}

	AudioEventInfo *m_info;
};

class Rva0020A5A0Name : public AsciiString
{
public:
	Rva0020A5A0Name(const char *text) : AsciiString(text) {}
};

class Rva005A00B0AudioClient
{
public:
#define AUDIO_SLOT(n) virtual void slot##n(void);
	AUDIO_SLOT(0)  AUDIO_SLOT(1)  AUDIO_SLOT(2)  AUDIO_SLOT(3)
	AUDIO_SLOT(4)  AUDIO_SLOT(5)  AUDIO_SLOT(6)  AUDIO_SLOT(7)
	AUDIO_SLOT(8)  AUDIO_SLOT(9)  AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26) AUDIO_SLOT(27)
	AUDIO_SLOT(28) AUDIO_SLOT(29) AUDIO_SLOT(30) AUDIO_SLOT(31)
	AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34) AUDIO_SLOT(35)
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43)
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47)
	AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51)
	AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67)
	AUDIO_SLOT(68) AUDIO_SLOT(69)
#undef AUDIO_SLOT
	virtual Rva000BD3B0Element findAudioEventInfo(const AsciiString *eventName) const;
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;
extern const char *const Rva002098B0PhaseNames[];

struct Rva0020A5A0Owner
{
	char m_unreconstructed00[0xE8];
	_STL::vector<Rva000BD3B0Element> m_sounds[4];
	char m_unreconstructed118[0x1A4 - 0x118];
	unsigned char m_flags;
};

// ?parseSound@@YAXPAVINI@@PAX1PBX@Z
void parseSound(INI *ini, void *instance, void *, const void *)
{
	Rva0020A5A0Owner *self = (Rva0020A5A0Owner *)instance;
	Int phase = INI::scanIndexList(ini->getNextToken(), Rva002098B0PhaseNames);
	const char *token;
	if ((token = ini->getNextToken()) != 0)
	{
		_STL::vector<Rva000BD3B0Element> &sounds = self->m_sounds[phase];
		do
		{
			Rva000BD3B0Element sound = TheAudioClientUpdate->findAudioEventInfo(
				&Rva0020A5A0Name(token));
			sounds.push_back(sound);
			if (sound.m_info)
				self->m_flags |= 8;
		}
		while ((token = ini->getNextTokenOrNull()) != 0);
	}
}
