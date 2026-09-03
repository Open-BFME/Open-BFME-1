// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS(const AsciiString &, ObjectID), retail 0x000B4350,
// 188 bytes. Named by the byte-true call in
// FlammableUpdateStartBurningSoundThunk.cpp
// (??0AudioEventRTS@@QAE@ABVAsciiString@@W4ObjectID@@@Z).
//
// Shared field init is the body at 0x000B24C0 (ILT 0x0002E68B). After the name
// is assigned, +0x08 is released as a refcounted pointer -- the same
// InterlockedDecrement + scalar-deleting-dtor shape setEventName uses. The
// trailing call (ILT 0x00029AE1 -> 0x000B4020) writes the owner position into
// a stack Coord3D.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3D
{
	float x, y, z;
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
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	virtual ~AudioEventRTS();

	void commonInit(void);
	void resolveOwnerPosition(Coord3D *pos, bool *found);

private:
	AsciiString m_filenameToLoad;	// +0x04
	CountedPtr m_eventInfo;			// +0x08
	unsigned int m_playingHandle;	// +0x0C
	unsigned int m_killThisHandle;	// +0x10
	AsciiString m_eventName;		// +0x14
	AsciiString m_attackName;		// +0x18
	AsciiString m_decayName;		// +0x1C
	char m_20[8];
	unsigned int m_timeOfDay;		// +0x28
	ObjectID m_objectID;			// +0x2C
	int m_ownerType;				// +0x30
	char m_34[0x6C - 0x34];
	AsciiString m_tail;				// +0x6C
};

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
