// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::commonInit, retail 0x000B24C0, 187B.
// Shared field-init already called via ILT 0x0002E68B from the ObjectID /
// DrawableID / LivingWorld / extra / positional constructors.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

#include "../../../../Libraries/Include/Lib/Coord3D.h"


// Retail inlines this wrapper into StringBase<char> directly; declare just the
// StringBase<char> members it reaches (see build/whatif/wrapfix.py).
template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	void set(const StringBase<T> &other);
private:
	void releaseBuffer();
};
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&other); return *this; }
	void clear();
	void set(const AsciiString &other);

	static const AsciiString TheEmptyString;

	char *m_data;
};

class Counted
{
public:
	virtual ~Counted();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class CountedPtr
{
public:
	void bind(const AsciiString &name);
	void clear(void)
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
	}

	Counted *m_ptr;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
// getPitchShift/getVolume place the -1.0f sentinels at +0x20 / +0x24.
class AudioEventRTS
{
public:
	__declspec(noinline) void commonInit(void);
	void initFromName(const AsciiString &name);

private:
	void *m_vftable;
	AsciiString m_filenameToLoad;	// +0x04
	CountedPtr m_eventInfo;			// +0x08
	unsigned int m_playingHandle;	// +0x0C
	unsigned int m_killThisHandle;	// +0x10
	AsciiString m_eventName;		// +0x14
	AsciiString m_attackName;		// +0x18
	AsciiString m_decayName;		// +0x1C
	float m_pitchShift;				// +0x20
	float m_volume;					// +0x24
	unsigned int m_timeOfDay;		// +0x28
	unsigned int m_objectID;		// +0x2C
	int m_ownerType;				// +0x30
	Coord3D m_position;				// +0x34
	unsigned char m_shouldFade;			// +0x40
	unsigned char m_isLogicalAudio; // +0x41, BFME layout witness / AudioEventRTS.h
	unsigned char m_uninterruptable; // +0x42, BFME layout witness / AudioEventRTS.h
	unsigned char m_flag43;
	unsigned char m_flag44;
	unsigned char m_flag45;
	unsigned char m_flag46;
	unsigned char m_flag47;
	unsigned char m_flag48;
	unsigned char m_flag49;
	unsigned char m_pad4A[2];
	float m_float4C;				// +0x4C
	float m_volumeShift;				// +0x50
	int m_delay;					// +0x54
	int m_int58;					// +0x58
	int m_playerIndex;					// +0x5C
	int m_portionToPlayNext;					// +0x60
	int m_loopCount;				// +0x64
	int m_int68;					// +0x68
	AsciiString m_tail;				// +0x6C
};

// ?commonInit@AudioEventRTS@@QAEXXZ
void AudioEventRTS::commonInit(void)
{
	unsigned int zero = 0;

	m_pitchShift = -1.0f;
	m_volume = m_pitchShift;
	{ Coord3D *const position = &m_position; position->x = 0.0f; position->y = 0.0f; position->z = 0.0f; }

	m_shouldFade = 0;
	m_ownerType = 4;
	m_timeOfDay = zero;
	m_isLogicalAudio = 0;
	m_uninterruptable = 0;
	m_filenameToLoad = AsciiString::TheEmptyString;

	m_eventInfo.clear();

	m_playingHandle = zero;
	m_killThisHandle = zero;
	m_float4C = 1.0f;
	m_volumeShift = 1.0f;
	m_int58 = -1;
	m_playerIndex = -1;
	m_delay = 0;
	m_flag43 = 0;
	m_flag44 = 0;
	m_flag45 = 0;
	m_flag46 = 1;
	m_flag47 = 0;
	m_flag48 = 0;
	m_flag49 = 0;
	m_portionToPlayNext = 0;

	m_attackName.clear();
	m_decayName.clear();
	m_loopCount = 1;
	m_tail.clear();
	m_int68 = -1;
}

// Retail RVA 0x000B2610, called by thin constructors via ILT 0x0004A86D.
// ?initFromName@AudioEventRTS@@QAEXABVAsciiString@@@Z
void AudioEventRTS::initFromName(const AsciiString &name)
{
	commonInit();
	if (name.m_data)
	{
		m_eventName.set(*reinterpret_cast<const AsciiString *>(name.m_data + 8));
		m_eventInfo.bind(name);
	}
	else
	{
		m_eventName.set(AsciiString::TheEmptyString);
		m_eventInfo.clear();
	}
}
