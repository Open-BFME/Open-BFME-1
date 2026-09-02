// cl: /DNDEBUG /MD /EHsc

// LANGameSlot::LANGameSlot(const LANGameSlot &), 0x00686D50, 110 bytes.
//
// The implicit copy constructor for the layout LANGameSlot_dtor.cpp destroys:
// base copy, then LANGameSlot's own vtable at 0x0111B6A0, then m_user at +0x44,
// m_serial at +0x60 and the trailing m_lastHeard dword at +0x64. Member
// construction order and the offsets are what identify it, and they agree with
// both the destructor and the matched operator= in LANGameSlot_operator.cpp.
//
// Two callee names come out of it and are pinned rather than owned:
// ??0GameSlot@@QAE@ABV0@@Z at 0x0006E600, called on (this, src) at offset 0
// before the vptr store, which is the base-class copy constructor by
// construction; and ??0LANPlayer@@QAE@ABV0@@Z at 0x006869C0, called on
// this+0x44 from src+0x44, which is m_user. That second body is one
// instruction pair short of matching on its own -- see its verdict in
// reverse/re_attempts.log -- but the call site names it either way.
//
// Unlike the destructor's model, GameSlot keeps virtuals here: the vptr store
// is in retail's bytes, so the derived vtable has to exist.

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

template <typename T>
class StringBase
{
	friend class LANGameSlot;
	friend class GameSlot;
	friend class BfmeWideSlotString;
	friend class BfmeAsciiSlotString;

public:
	~StringBase() { releaseBuffer(); }

private:
	StringBase(const StringBase<T> &src);		// ??0?$StringBase@D@@AAE@ABV0@@Z
	void releaseBuffer();				// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	void *m_data;
};

class BfmeWideSlotString : public StringBase<unsigned short>
{
public:
	BfmeWideSlotString(const BfmeWideSlotString &other)
		: StringBase<unsigned short>(other)
	{
	}
};

class BfmeAsciiSlotString : public StringBase<char>
{
public:
	BfmeAsciiSlotString(const BfmeAsciiSlotString &other)
		: StringBase<char>(other)
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot(const GameSlot &other);		// retail 0x0006E600
	~GameSlot();					// ILT thunk 0x0000B988

	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;

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
	BfmeWideSlotString m_name;
	BfmeAsciiSlotString m_IP;
	UnsignedInt m_bfme30;
	UnsignedInt m_bfme34;
	UnsignedInt m_bfme38;
	UnsignedInt m_bfme3c;
	UnsignedByte m_bfme40;
};

// ??0GameSlot@@QAE@ABV0@@Z
// Open-BFME5: convert GameSlot copy construction from retail ASM to clean C++.
GameSlot::GameSlot(const GameSlot &other)
	: m_state(other.m_state),
	  m_isAccepted(other.m_isAccepted),
	  m_hasMap(other.m_hasMap),
	  m_isMuted(other.m_isMuted),
	  m_color(other.m_color),
	  m_startPos(other.m_startPos),
	  m_playerTemplate(other.m_playerTemplate),
	  m_teamNumber(other.m_teamNumber),
	  m_origColor(other.m_origColor),
	  m_origStartPos(other.m_origStartPos),
	  m_origPlayerTemplate(other.m_origPlayerTemplate),
	  m_name(other.m_name),
	  m_IP(other.m_IP),
	  m_bfme30(other.m_bfme30),
	  m_bfme34(other.m_bfme34),
	  m_bfme38(other.m_bfme38),
	  m_bfme3c(other.m_bfme3c),
	  m_bfme40(other.m_bfme40)
{
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	LANPlayer(const LANPlayer &other);		// retail 0x006869C0
	~LANPlayer();					// ILT thunk 0x000240FF

	UnsignedByte m_bfmeBody[0x1C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	LANGameSlot(const LANGameSlot &other);

private:
	LANPlayer m_user;				// this+0x44
	StringBase<char> m_serial;			// this+0x60
	UnsignedInt m_lastHeard;			// this+0x64
};

// ??0LANGameSlot@@QAE@ABV0@@Z
LANGameSlot::LANGameSlot(const LANGameSlot &other)
	: GameSlot(other), m_user(other.m_user), m_serial(other.m_serial)
{
	m_lastHeard = other.m_lastHeard;
}
