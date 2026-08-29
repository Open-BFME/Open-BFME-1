// cl: /DNDEBUG /MD /EHsc
//
// Two more relocation-blind twins.
//
// 0x00075C10 is a twin of
// Code/GameEngine/Source/GameNetwork/SkirmishGameInfoCtorThunk.cpp
// (0x00619720) whose only differing slots are its own EH table and its own
// two vtables -- all three are per-class symbols, so a distinct class name is
// the whole conversion.
//
// 0x006589E0 is a twin of
// Code/Libraries/Source/WWVegas/WWLib/BFMENetworkQueueItem1Assign.cpp
// (0x00658340) differing in one slot: the assignment operator of the large
// member at +4.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot();
	~GameSlot();
private:
	unsigned char m_storage[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	void setSlotPointer(int index, GameSlot *slot);
private:
	unsigned char m_storage[0x54];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
};

class Open2SlotOwner75C10 : public GameInfo, public Snapshot
{
public:
	Open2SlotOwner75C10();
	virtual ~Open2SlotOwner75C10();
private:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();
	GameSlot m_slots[8];
};

// @??0Open2SlotOwner75C10@@QAE@XZ 0x00075C10
Open2SlotOwner75C10::Open2SlotOwner75C10()
{
	for (int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_slots[i]);
}

// ---------------------------------------------------------------------------

class Open2Stats6589E0
{
public:
	Open2Stats6589E0 &operator=(const Open2Stats6589E0 &other);

private:
	char m_storage[0x1C4];
};

struct Open2Record6589E0
{
	int m_word0;
	int m_word1;
	int m_word2;
	int m_word3;
	int m_word4;
};

class Open2QueueItem6589E0
{
public:
	Open2QueueItem6589E0 &operator=(const Open2QueueItem6589E0 &other);

	int m_kind;					// +0x000
	Open2Stats6589E0 m_stats;			// +0x004
	Open2Record6589E0 m_record;			// +0x1C8
	int m_extra0;					// +0x1DC
	int m_extra1;					// +0x1E0
	int m_extra2;					// +0x1E4
	int m_extra3;					// +0x1E8
	bool m_flag;					// +0x1EC
};

// @??4Open2QueueItem6589E0@@QAEAAV0@ABV0@@Z 0x006589E0
Open2QueueItem6589E0 &Open2QueueItem6589E0::operator=(const Open2QueueItem6589E0 &other)
{
	m_kind = other.m_kind;
	m_stats = other.m_stats;
	m_record = other.m_record;
	m_extra0 = other.m_extra0;
	m_extra1 = other.m_extra1;
	m_extra2 = other.m_extra2;
	m_extra3 = other.m_extra3;
	m_flag = other.m_flag;

	return *this;
}
