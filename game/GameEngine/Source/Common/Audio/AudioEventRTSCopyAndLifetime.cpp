// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: AudioEventRTS copy constructor (0x000B2FB0, 451B) and
// operator= (0x000B2690, 360B). Copy-ctor ILT 0x00047B27 (Player radar
// MiscAudio by-value). Assign ILT 0x0001F753. The ledger name
// ??4AudioEventRTS@@QAEAAV0@ABV0@@Z is already a StringBase::set alias
// at 0x00887C90, so this row is ?assign@ with object-symbol= to the
// compiled operator=.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

enum ObjectID
{
	INVALID_ID = 0
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

enum LivingWorldID
{
	INVALID_LIVING_WORLD_ID = 0
};

struct Coord3D
{
	unsigned int x, y, z;
};

#include "ascii_string.h"

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
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	AudioEventRTS(const AsciiString &eventName, DrawableID drawableID);
	AudioEventRTS(const AsciiString &eventName, LivingWorldID ownerID);
	AudioEventRTS(const AsciiString &eventName, int timeOfDay);
	AudioEventRTS(const AsciiString &eventName, const Coord3D *positionOfAudio, int timeOfDay);
	AudioEventRTS(const AudioEventRTS &right);
	AudioEventRTS &operator=(const AudioEventRTS &right);
	virtual ~AudioEventRTS();
	void commonInit(void);
	void bfmeReset000B25B0(const AsciiString &eventName);
	void resolveOwnerPosition(Coord3D *pos, bool *found);

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
	unsigned int m_float4C;			// +0x4C
	unsigned int m_volumeShift;			// +0x50
	unsigned int m_delay;			// +0x54
	unsigned int m_int58;			// +0x58
	unsigned int m_playerIndex;			// +0x5C
	unsigned int m_portionToPlayNext;			// +0x60
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
	m_isLogicalAudio = right.m_isLogicalAudio;
	m_uninterruptable = right.m_uninterruptable;
	m_float4C = right.m_float4C;
	m_volumeShift = right.m_volumeShift;
	m_int58 = right.m_int58;
	m_playerIndex = right.m_playerIndex;
	m_delay = right.m_delay;
	m_attackName = right.m_attackName;
	m_decayName = right.m_decayName;
	m_portionToPlayNext = right.m_portionToPlayNext;
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
	m_shouldFade = right.m_shouldFade;
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
	m_isLogicalAudio = right.m_isLogicalAudio;
	m_uninterruptable = right.m_uninterruptable;
	m_float4C = right.m_float4C;
	m_volumeShift = right.m_volumeShift;
	m_int58 = right.m_int58;
	m_playerIndex = right.m_playerIndex;
	m_delay = right.m_delay;
	m_attackName = right.m_attackName;
	m_decayName = right.m_decayName;
	m_portionToPlayNext = right.m_portionToPlayNext;
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
	m_shouldFade = right.m_shouldFade;
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

// Retail 0x000B31F0 releases the same strings and counted event metadata.
// ??1AudioEventRTS@@UAE@XZ
AudioEventRTS::~AudioEventRTS()
{
}

// Open-BFME5: AudioEventRTS constructors.
//   (const AsciiString &, ObjectID)              retail 0x000B4350, 188B
//     named by FlammableUpdateStartBurningSoundThunk.cpp
//   (const AsciiString &, DrawableID)            retail 0x000B44F0, 188B
//   (const AsciiString &, LivingWorldID)         retail 0x000B4690, 192B
//     ownerType=5, same type isDead already uses for LivingWorld
//   (const AsciiString &, int extra)             retail 0x000B2CC0, 159B
//     ILT 0x00025306: BloodthirstyUpdate 0x70-byte members with extra=0
//   (const AsciiString &, const Coord3D *, int)  retail 0x000B2E10, 180B
//     named by ScriptActions_doPlaySoundEffectAt_Thunk.cpp
//   bfmeReset000B25B0(const AsciiString &)       retail 0x000B25B0, 67B
//     BFME-only member: commonInit, assign the name, clear +0x08. No vptr
//     store, so not a constructor; no named caller (ILT 0x00048545 is a gap
//     thunk), so the name is address-derived.
//
// Shared field init is the body at 0x000B24C0 (ILT 0x0002E68B). After the name
// is assigned, +0x08 is released as a refcounted pointer -- the same
// InterlockedDecrement + scalar-deleting-dtor shape setEventName uses. The
// trailing call (ILT 0x00029AE1 -> 0x000B4020) writes the owner position into
// a stack Coord3D.

// ??0AudioEventRTS@@QAE@ABVAsciiString@@W4ObjectID@@@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, ObjectID ownerID)
{
	commonInit();

	m_eventName = eventName;
	m_eventInfo.clear();

	m_objectID = ownerID;
	m_timeOfDay = 0;
	if (ownerID)
		m_ownerType = 2;
	else
		m_objectID = INVALID_ID;

	// Retail reuses the dead eventName argument slot as the Bool out-param.
	// The Coord3D local sits at [esp+0x10]; that slot is 0x1C bytes later.
	Coord3D pos;
	resolveOwnerPosition(&pos, reinterpret_cast<bool *>(
		reinterpret_cast<char *>(&pos) + 0x1C));
}

// ??0AudioEventRTS@@QAE@ABVAsciiString@@W4DrawableID@@@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, DrawableID drawableID)
{
	commonInit();

	m_eventName = eventName;
	m_eventInfo.clear();

	m_objectID = static_cast<ObjectID>(drawableID);
	m_timeOfDay = 0;
	if (drawableID)
		m_ownerType = 1;
	else
		m_objectID = INVALID_ID;

	Coord3D pos;
	resolveOwnerPosition(&pos, reinterpret_cast<bool *>(
		reinterpret_cast<char *>(&pos) + 0x1C));
}

// ??0AudioEventRTS@@QAE@ABVAsciiString@@W4LivingWorldID@@@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, LivingWorldID ownerID)
{
	commonInit();

	m_eventName = eventName;
	m_eventInfo.clear();

	m_objectID = static_cast<ObjectID>(ownerID);
	m_timeOfDay = 1;
	if (ownerID)
		m_ownerType = 5;
	else
		m_objectID = INVALID_ID;

	Coord3D pos;
	resolveOwnerPosition(&pos, reinterpret_cast<bool *>(
		reinterpret_cast<char *>(&pos) + 0x1C));
}

// ??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, int timeOfDay)
{
	commonInit();

	m_eventName = eventName;
	m_eventInfo.clear();

	m_timeOfDay = static_cast<unsigned int>(timeOfDay);
}

// ??0AudioEventRTS@@QAE@ABVAsciiString@@PBUCoord3D@@H@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, const Coord3D *positionOfAudio, int timeOfDay)
{
	commonInit();

	m_eventName = eventName;
	m_eventInfo.clear();

	m_position = *positionOfAudio;
	m_ownerType = 0;
	m_shouldFade = 1;
	m_timeOfDay = static_cast<unsigned int>(timeOfDay);
}

// ?bfmeReset000B25B0@AudioEventRTS@@QAEXABVAsciiString@@@Z
void AudioEventRTS::bfmeReset000B25B0(const AsciiString &eventName)
{
	commonInit();
	m_eventName = eventName;
	m_eventInfo.clear();
}
