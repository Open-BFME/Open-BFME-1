// ?adjustSlotsForMap@GameInfo@@UAEXXZ
// partial score=0.55 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gameinfo /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#define ASCIISTRING_H
#define UNICODESTRING_H

template <typename T> struct RvaStringData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &other);
	~StringBase();

protected:
	RvaStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}

	static AsciiString TheEmptyString;
	const char *str() const { return m_data ? m_data->m_text : ""; }
	int compareNoCase(const AsciiString &other) const;
	void toLower();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other);
		return *this;
	}

	static UnicodeString TheEmptyString;
	int compareNoCase(const UnicodeString &other) const;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compareNoCase(right) == 0;
}

inline bool operator<(const AsciiString &left, const AsciiString &right)
{
	return left.compareNoCase(right) < 0;
}

#include "PreRTS.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

enum
{
	MAX_SLOTS = 8
};

struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch(const char *name);
};

extern GameTextInterface *TheGameText;

class GameSlot
{
public:
	GameSlot(const GameSlot &other);

	virtual void reset()
	{
		m_state = SLOT_CLOSED;
		m_isAccepted = false;
		m_hasMap = true;
		m_color = -1;
		m_startPos = -1;
		m_playerTemplate = -1;
		m_teamNumber = -1;
		m_connectInfo.m_nat = 1;
		m_bfme38 = 0;
		m_bfme40 = false;
		m_connectInfo.m_port = 0;
		m_isMuted = false;
		m_origPlayerTemplate = -1;
		m_origStartPos = -1;
		m_origColor = -1;
	}

	GameSlot()
	{
		reset();
	}

	void setState(SlotState state,
		UnicodeString name = UnicodeString::TheEmptyString,
		const GameSlotConnectInfo *connectInfo = 0)
	{
		if (!(isAI() && (state == SLOT_EASY_AI || state == SLOT_MED_AI ||
			state == SLOT_BRUTAL_AI)))
		{
			m_color = -1;
			m_startPos = -1;
			m_playerTemplate = -1;
			m_teamNumber = -1;
		}
		if (state == SLOT_PLAYER)
		{
			reset();
			m_state = state;
			m_name = name;
		}
		else
		{
			m_state = state;
			m_isAccepted = true;
			m_hasMap = true;
			switch (state)
			{
			case SLOT_OPEN:
				m_name = TheGameText->fetch("GUI:Open");
				break;
			case SLOT_EASY_AI:
				m_name = TheGameText->fetch("GUI:EasyAI");
				break;
			case SLOT_MED_AI:
				m_name = TheGameText->fetch("GUI:MediumAI");
				break;
			case SLOT_BRUTAL_AI:
				m_name = TheGameText->fetch("GUI:HardAI");
				break;
			case SLOT_CLOSED:
			default:
				m_name = TheGameText->fetch("GUI:Closed");
				break;
			}
		}
		m_connectInfo = *connectInfo;
	}

	Bool isOccupied() const
	{
		return m_state == SLOT_PLAYER || m_state == SLOT_EASY_AI ||
			m_state == SLOT_MED_AI || m_state == SLOT_BRUTAL_AI;
	}

	Bool isAI() const
	{
		return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI ||
			m_state == SLOT_BRUTAL_AI;
	}

protected:
	SlotState m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
	Int m_origColor;
	Int m_origStartPos;
	Int m_origPlayerTemplate;
	UnicodeString m_name;
	AsciiString m_IP;
	GameSlotConnectInfo m_connectInfo;
	UnsignedInt m_bfme38;
	UnsignedInt m_bfme3c;
	UnsignedByte m_bfme40;
};

class MapMetaData
{
	public:
	unsigned char m_pad00[0x20];
	Int m_numPlayers;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString name);
};

extern MapCache *TheMapCache;

class GameInfo
{
public:
	void setSlot(Int slot, GameSlot slotInfo);
};

// The BFME map-name member is one dword later than the Zero Hour header says.
// This one-word view is intentional: the target call aliases the shared narrow
// StringBase copy body under the GameSpyGroupRoom name.
class Rva00620B00GameInfo
{
public:
	virtual void adjustSlotsForMap();

	unsigned char m_pad04[0x10];
	GameSlot *m_slot[MAX_SLOTS];
	UnsignedInt m_localIP;
	UnsignedInt m_bfme38;
	AsciiString m_mapName;

	GameSlot *getSlot(Int slotNum)
	{
		if (m_slot == NULL)
			return NULL;

		if (slotNum < 0 && slotNum >= MAX_SLOTS)
			return NULL;

		return m_slot[slotNum];
	}
};

// ?adjustSlotsForMap@GameInfo@@UAEXXZ
void Rva00620B00GameInfo::adjustSlotsForMap()
{
	const MapMetaData *md = TheMapCache->findMap(m_mapName);
	if (md != NULL)
	{
		Int numPlayers = md->m_numPlayers;
		Int numPlayerSlots = 0;

		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *tempSlot = getSlot(i);
			if (tempSlot->isOccupied())
				++numPlayerSlots;
		}

		for (i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = getSlot(i);
			if (numPlayers > numPlayerSlots)
			{
				if (!(slot->isOccupied()))
				{
					GameSlot newSlot;
					newSlot.setState(SLOT_OPEN);
					reinterpret_cast<GameInfo *>(this)->setSlot(i, newSlot);
					++numPlayerSlots;
				}
			}
			else
			{
				if (!(slot->isOccupied()))
				{
					GameSlot newSlot;
					newSlot.setState(SLOT_CLOSED);
					reinterpret_cast<GameInfo *>(this)->setSlot(i, newSlot);
				}
			}
		}
	}
}
