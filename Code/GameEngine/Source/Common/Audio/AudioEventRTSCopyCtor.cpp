// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS copy constructor (0x000B2FB0, 451B) and
// operator= (0x000B2690, 360B). Copy-ctor ILT 0x00047B27 (Player radar
// MiscAudio by-value). Assign ILT 0x0001F753. The ledger name
// ??4AudioEventRTS@@QAEAAV0@ABV0@@Z is already a StringBase::set alias
// at 0x00887C90, so this row is ?assign@ with object-symbol= to the
// compiled operator=.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

struct Coord3D
{
	unsigned int x, y, z;
};

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

class Counted
{
public:
	virtual ~Counted();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
	}

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
	CountedPtr() : m_ptr(0) {}
	~CountedPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	CountedPtr &operator=(const CountedPtr &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				other.m_ptr->Add_Ref();
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	Counted *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &right);
	AudioEventRTS &operator=(const AudioEventRTS &right);
	virtual ~AudioEventRTS();

private:
	AsciiString m_filenameToLoad;	// +0x04
	CountedPtr m_eventInfo;			// +0x08
	unsigned int m_playingHandle;	// +0x0C
	unsigned int m_killThisHandle;	// +0x10
	AsciiString m_eventName;		// +0x14
	AsciiString m_attackName;		// +0x18
	AsciiString m_decayName;		// +0x1C
	unsigned int m_pitchShift;		// +0x20
	unsigned int m_volume;			// +0x24
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
	unsigned int m_float4C;			// +0x4C
	unsigned int m_float50;			// +0x50
	unsigned int m_int54;			// +0x54
	unsigned int m_int58;			// +0x58
	unsigned int m_int5C;			// +0x5C
	unsigned int m_int60;			// +0x60
	unsigned int m_loopCount;		// +0x64
	unsigned int m_int68;			// +0x68
	AsciiString m_tail;				// +0x6C
};

// ??0AudioEventRTS@@QAE@ABV0@@Z
AudioEventRTS::AudioEventRTS(const AudioEventRTS &right)
{
	m_filenameToLoad = right.m_filenameToLoad;
	m_eventInfo = right.m_eventInfo;
	m_playingHandle = right.m_playingHandle;
	m_killThisHandle = right.m_killThisHandle;
	m_eventName = right.m_eventName;
	m_pitchShift = right.m_pitchShift;
	m_volume = right.m_volume;
	m_ownerType = right.m_ownerType;
	m_timeOfDay = right.m_timeOfDay;
	m_flag41 = right.m_flag41;
	m_flag42 = right.m_flag42;
	m_float4C = right.m_float4C;
	m_float50 = right.m_float50;
	m_int58 = right.m_int58;
	m_int5C = right.m_int5C;
	m_int54 = right.m_int54;
	m_attackName = right.m_attackName;
	m_decayName = right.m_decayName;
	m_int60 = right.m_int60;
	m_flag43 = right.m_flag43;
	m_flag44 = right.m_flag44;
	m_flag45 = right.m_flag45;
	m_flag46 = right.m_flag46;
	m_flag47 = right.m_flag47;
	m_flag48 = right.m_flag48;
	m_flag49 = right.m_flag49;
	m_loopCount = right.m_loopCount;
	m_int68 = right.m_int68;
	m_tail = right.m_tail;
	m_position.x = right.m_position.x;
	m_position.y = right.m_position.y;
	m_position.z = right.m_position.z;
	m_flag40 = right.m_flag40;
	if (m_ownerType == 1)
		m_objectID = right.m_objectID;
	else if (m_ownerType == 2)
		m_objectID = right.m_objectID;
	else if (m_ownerType == 5)
		m_objectID = right.m_objectID;
}

// ??4AudioEventRTS@@QAEAAV0@ABV0@@Z
AudioEventRTS &AudioEventRTS::operator=(const AudioEventRTS &right)
{
	m_filenameToLoad = right.m_filenameToLoad;
	m_eventInfo = right.m_eventInfo;
	m_playingHandle = right.m_playingHandle;
	m_killThisHandle = right.m_killThisHandle;
	m_eventName = right.m_eventName;
	m_pitchShift = right.m_pitchShift;
	m_volume = right.m_volume;
	m_ownerType = right.m_ownerType;
	m_timeOfDay = right.m_timeOfDay;
	m_flag41 = right.m_flag41;
	m_flag42 = right.m_flag42;
	m_float4C = right.m_float4C;
	m_float50 = right.m_float50;
	m_int58 = right.m_int58;
	m_int5C = right.m_int5C;
	m_int54 = right.m_int54;
	m_attackName = right.m_attackName;
	m_decayName = right.m_decayName;
	m_int60 = right.m_int60;
	m_flag43 = right.m_flag43;
	m_flag44 = right.m_flag44;
	m_flag45 = right.m_flag45;
	m_flag47 = right.m_flag47;
	m_flag48 = right.m_flag48;
	m_flag49 = right.m_flag49;
	m_flag46 = right.m_flag46;
	m_loopCount = right.m_loopCount;
	m_int68 = right.m_int68;
	m_tail = right.m_tail;
	m_position.x = right.m_position.x;
	m_position.y = right.m_position.y;
	m_position.z = right.m_position.z;
	m_flag40 = right.m_flag40;
	if (m_ownerType == 1)
	{
		m_objectID = right.m_objectID;
		return *this;
	}
	if (m_ownerType == 2)
	{
		m_objectID = right.m_objectID;
		return *this;
	}
	if (m_ownerType == 5)
		m_objectID = right.m_objectID;
	return *this;
}
