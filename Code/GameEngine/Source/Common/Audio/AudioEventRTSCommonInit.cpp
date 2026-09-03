// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::commonInit, retail 0x000B24C0, 187B.
// Shared field-init already called via ILT 0x0002E68B from the ObjectID /
// DrawableID / LivingWorld / extra / positional constructors.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

struct Coord3D
{
	float x, y, z;

	void zero(void)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);
	void clear();

	static const AsciiString TheEmptyString;

private:
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
// getPitchShift/getVolume place the -1.0f sentinels at +0x20 / +0x24.
class AudioEventRTS
{
public:
	void commonInit(void);

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
	unsigned char m_flag40;			// +0x40
	unsigned char m_flag41;
	unsigned char m_flag42;
	unsigned char m_flag43;
	unsigned char m_flag44;
	unsigned char m_flag45;
	unsigned char m_flag46;
	unsigned char m_flag47;
	unsigned char m_flag48;
	unsigned char m_flag49;
	unsigned char m_pad4A[2];
	float m_float4C;				// +0x4C
	float m_float50;				// +0x50
	int m_int54;					// +0x54
	int m_int58;					// +0x58
	int m_int5C;					// +0x5C
	int m_int60;					// +0x60
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
	m_position.zero();

	m_flag40 = 0;
	m_ownerType = 4;
	m_timeOfDay = zero;
	m_flag41 = 0;
	m_flag42 = 0;
	m_filenameToLoad = AsciiString::TheEmptyString;

	m_eventInfo.clear();

	m_playingHandle = zero;
	m_killThisHandle = zero;
	m_float4C = 1.0f;
	m_float50 = 1.0f;
	m_int58 = -1;
	m_int5C = -1;
	m_int54 = 0;
	m_flag43 = 0;
	m_flag44 = 0;
	m_flag45 = 0;
	m_flag46 = 1;
	m_flag47 = 0;
	m_flag48 = 0;
	m_flag49 = 0;
	m_int60 = 0;

	m_attackName.clear();
	m_decayName.clear();
	m_loopCount = 1;
	m_tail.clear();
	m_int68 = -1;
}
