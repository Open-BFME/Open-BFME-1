// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/shims/stringinline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define ASCIISTRING_H
#define UNICODESTRING_H

template <typename T> struct StringInlineData
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

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}

	static AsciiString TheEmptyString;
	const char *str(void) const
	{
		return m_data ? m_data->m_text : "";
	}
	int getLength(void) const;
	int compareNoCase(const AsciiString &other) const;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text)
		: StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other);
		return *this;
	}

	static UnicodeString TheEmptyString;
	int getLength(void) const;
	bool isEmpty(void) const;
	const unsigned short *str(void) const;
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

inline bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compareNoCase(right) == 0;
}

inline bool operator<(const UnicodeString &left, const UnicodeString &right)
{
	return left.compareNoCase(right) < 0;
}

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

#include "PreRTS.h"

typedef int Int;
typedef unsigned int UnsignedInt;
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
	int m_unused;
	unsigned short m_port;
	char m_padding[2];
};

struct Rva0061F6C0ResetConnectInfo
{
	int m_unused;
	unsigned short m_port;
	char m_padding[2];
};

struct GameSlotConnectStorage
{
	GameSlotConnectStorage &operator=(const GameSlotConnectInfo &that)
	{
		*(unsigned int *)this = *(const unsigned int *)&that.m_port;
		return *this;
	}

	unsigned short m_port;
	char m_padding[2];
};

struct Rva0061F6C0LocalPad
{
	Rva0061F6C0LocalPad() {}
	~Rva0061F6C0LocalPad() {}
	char m_data[8];
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
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &other);
	void reset();

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
	m_ip = 0;
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

private:
	void *m_vtable;
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
	BFMERetailAsciiString m_slotNameKeyText;
	UnsignedInt m_ip;
	GameSlotConnectStorage m_connectInfo;
	Int m_nat;
	UnsignedInt m_lastFrameInGame;
	Bool m_disconnected;
};

GameSlot::GameSlot()
	: m_vtable((void *)0x01075D50),
	  m_name(),
	  m_slotNameKeyText()
{
	reset();
}

void GameSlot::reset()
{
	int emptyValue = -1;
	m_color = (m_state = SLOT_CLOSED, m_isAccepted = false,
		m_hasMap = true, emptyValue);
	Rva0061F6C0ResetConnectInfo emptyConnectInfo;
	emptyConnectInfo.m_port = 0;
	*(volatile unsigned int *)&m_connectInfo =
		*(const unsigned int *)&emptyConnectInfo.m_port;
	m_startPos = emptyValue;
	m_playerTemplate = emptyValue;
	m_teamNumber = emptyValue;
	m_nat = 1;
	m_lastFrameInGame = 0;
	m_disconnected = false;
	m_ip = 0;
	m_isMuted = false;
	m_origPlayerTemplate = emptyValue;
	m_origStartPos = emptyValue;
	m_origColor = emptyValue;
	m_slotNameKeyText.clear();
}

// The retail caller reaches these bodies through the ILT entries.
#pragma comment(linker, "/alternatename:??0GameSlot@@QAE@ABV0@@Z=?j_00034c34@@YAXXZ")
#pragma comment(linker, "/alternatename:?setSlot@GameInfo@@QAEXHVGameSlot@@@Z=?j_0001da39@@YAXXZ")

class GameInfo
{
public:
	virtual void closeOpenSlots();
	void setSlot(Int slot, GameSlot slotInfo);

private:
	char m_pad04[0x10];
	GameSlot *m_slot[MAX_SLOTS];

	GameSlot *getSlot(Int slotNum)
	{
		if (m_slot == 0)
			return 0;
		if (slotNum < 0 && slotNum >= MAX_SLOTS)
			return 0;
		return m_slot[slotNum];
	}
};

// ?closeOpenSlots@GameInfo@@UAEXXZ
void GameInfo::closeOpenSlots()
{
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (!(getSlot(i)->isOccupied()))
		{
			GameSlot newSlot;
			GameSlotConnectInfo connectInfo;
			connectInfo.m_port = 0;
			newSlot.setState(SLOT_CLOSED, UnicodeString::TheEmptyString,
				(const GameSlotConnectInfo *)&connectInfo);
			setSlot(i, newSlot);
		}
	}
}
