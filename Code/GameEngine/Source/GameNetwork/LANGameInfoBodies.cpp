// cl: /DNDEBUG /MD /EHsc

// The LANGameInfo and LANGameSlot bodies BFME out-of-lined: the game the LAN
// browser is sitting in, and the eight slots inside it.
//
//   LANGameInfo::LANGameInfo            0x0068E980  176 B  QAE
//   LANGameInfo::getPlayerName          0x004C8800   38 B  QAE
//   LANGameInfo::getPlayerLastHeard     0x00684C60   39 B  QAE
//   LANGameInfo::setPlayerLastHeard     0x00688960   37 B  QAE
//   LANGameInfo::setSlot                0x0068EA70  119 B  QAE
//   LANGameInfo::resetAccepted          0x0068D4D0   98 B  UAE (virtual)
//   LANGameSlot::~LANGameSlot           0x006858A0   89 B  QAE
//   LANGameSlot::setLogin               0x006853C0   75 B  QAE
//   LANGameSlot::isLocalPlayer          0x0068D340  124 B  QBE (const)
//
// One class per file meant eight private models of the same four classes, and
// they contradicted each other on the one question that matters -- how big is a
// slot and where does the next one start:
//
//   GameSlot was an opaque 0x44-byte block in four files, 0x68 bytes in the
//     constructor's (which folded LANGameSlot's own members into the base),
//     and a polymorphic class with named state fields in two more.
//   LANGameSlot's m_serial was `void *` in three files and StringBase<char> in
//     two, and only the destructor's file named all three members.
//   LANGameInfo's array was m_LANSlot in six files and m_slots in the seventh,
//     and only the constructor carried what follows it.
//
// Reconciled, every offset survives and the arithmetic closes: GameSlot is
// 0x44, LANGameSlot adds m_user at +0x44, m_serial at +0x60 and m_lastHeard at
// +0x64 for a stride of 0x68, and 0x58 + 8 * 0x68 lands exactly on 0x398, the
// m_next the LAN browser list walks (LANAPIGames.cpp's addGame threads it).
// +0x88 for the array cannot be right; it would put m_next at 0x3C8.
//
// Two pieces of drift are NOT merged away, because the bytes pin them apart:
//
//   GameSlot is modelled with a plain m_vptr member rather than a virtual
//     function. Retail's GameSlot IS polymorphic, but giving the model a vtable
//     makes MSVC open ~LANGameSlot with a six-byte vptr store retail does not
//     have. A data member keeps every offset and emits nothing.
//   The local address behind LANAPI slot 55 is read at two widths: the
//     constructor copies eight bytes into GameInfo::m_localAddress (ip and port
//     both 32-bit), while isLocalPlayer compares a 32-bit ip against a 16-bit
//     port and adds 8 to that port as a short. Both shapes are declared, and
//     the slot returns the constructor's; isLocalPlayer casts, which is what
//     retail's own code does with the same eight bytes.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_SLOTS = 8 };

// The eight bytes at GameInfo+0x34, as the constructor copies them.
struct LANAddress
{
	UnsignedInt m_address;
	UnsignedInt m_port;
};

// The same eight bytes as the slot carries them at GameSlot+0x30 and as
// isLocalPlayer compares them.
struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();				// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	__forceinline UnicodeString() : m_data(0) {}
	~UnicodeString();

	void translate(const AsciiString &src);		// retail 0x008891F0

private:
	void *m_data;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();				// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	~LANPlayer();					// ILT thunk 0x000240FF

	void setLogin(const AsciiString &name) { m_login.translate(name); }

	UnicodeString m_name;				// this+0x00
	UnicodeString m_login;				// this+0x04
	UnicodeString m_host;				// this+0x08
	UnsignedByte m_bfmeTail[0x1C - 0x0C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	~GameSlot();					// ILT thunk 0x0000B988

	Bool isHuman(void) const;			// ILT thunk 0x000279CB
	UnicodeString getName(void) const;		// ILT thunk 0x0003A20B
	void unAccept(void);
	void setAccept(void) { m_isAccepted = true; }
	void setMapAvailability(Bool hasMap);

	void *m_vptr;					// this+0x00, see the note at the top
	Int m_state;					// this+0x04
	Bool m_isAccepted;				// this+0x08
	Bool m_hasMap;					// this+0x09
	Bool m_isMuted;					// this+0x0a
	UnsignedByte m_bfmeBeforeAddress[0x30 - 0x0b];
	BfmeNetAddress m_address;			// this+0x30
	UnsignedByte m_bfmeTail[0x44 - 0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	LANGameSlot();
	~LANGameSlot();
	LANGameSlot &operator=(const LANGameSlot &other);

	UnsignedInt getLastHeard(void) const { return m_lastHeard; }
	void setLastHeard(UnsignedInt lastHeard) { m_lastHeard = lastHeard; }
	void setLogin(AsciiString name);
	Bool isLocalPlayer(void) const;

private:
	LANPlayer m_user;				// this+0x44
	StringBase<char> m_serial;			// this+0x60
	UnsignedInt m_lastHeard;			// this+0x64
};

// The BFME LAN interface adds six virtual entries before the Zero Hour
// interface's utility calls; the slots below keep every call these bodies make
// on its retail entry.
class LANGameInfo;

class LANAPI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void ResetGameStartTimer(void);		// slot 26, vtable+0x68
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual Bool AmIHost(void);			// slot 46, vtable+0xB8
	virtual void slot47(void) = 0;
	virtual LANGameInfo *GetMyGame(void);		// slot 48, vtable+0xC0
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual const LANAddress &getLocalAddress(void) = 0;	// slot 55, vtable+0xDC
};

extern LANAPI *TheLAN;
extern void LANEnableStartButton(Bool enabled);
extern int g_Va012F49D4;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual Int getLocalSlotNum(void) const;

	void setSlotPointer(Int index, GameSlot *slot);

protected:
	unsigned char m_gap04[0x30];
	LANAddress m_localAddress;			// this+0x34
	unsigned char m_gap3c[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public GameInfo
{
public:
	LANGameInfo();
	virtual ~LANGameInfo();
	virtual Int getLocalSlotNum(void) const;
	virtual void resetAccepted(void);

	UnicodeString getPlayerName(Int who);
	UnsignedInt getPlayerLastHeard(Int who);
	void setPlayerLastHeard(Int who, UnsignedInt lastHeard);
	void setSlot(Int slotNum, LANGameSlot slotInfo);

private:
	LANGameSlot m_LANSlot[MAX_SLOTS];		// this+0x58, stride 0x68
	LANGameInfo *m_next;				// this+0x398
	UnsignedInt m_lastHeard;			// this+0x39c
	UnicodeString m_gameName;			// this+0x3a0
	Bool m_isDirectConnect;				// this+0x3a4
};


LANGameInfo::LANGameInfo()
	: m_next(0), m_lastHeard(0), m_isDirectConnect(false)
{
	for (UnsignedInt i = 0; i < 8; ++i)
		setSlotPointer(i, &m_LANSlot[i]);

	m_localAddress = TheLAN->getLocalAddress();
}

// LANGameInfo::getPlayerLastHeard, 0x00684C60, 39 bytes.
//
// ZH inlines this in LANGameInfo.h; BFME out-of-lined it beside the other
// LANGameInfo slot helpers. The isHuman guard uses the same ILT thunk
// (0x000279CB -> GameSlot::isHuman at 0x0061E580) as setPlayerLastHeard at
// 0x00688960, and the slot array layout is pinned there: m_LANSlot at +0x58,
// stride 0x68, m_lastHeard at +0x64 within each LANGameSlot.
UnsignedInt LANGameInfo::getPlayerLastHeard( Int who )
{
	if (m_LANSlot[who].isHuman())
		return m_LANSlot[who].getLastHeard();
	return 0;
}

// LANGameInfo::getPlayerName, 0x004C8800, 38 bytes: ZH's inline, out of line;
// callers are LANAPI::update, LANDisplayGameList and the game info window.
UnicodeString LANGameInfo::getPlayerName( Int who )
{
	return m_LANSlot[who].getName();
}

// LANGameInfo::setPlayerLastHeard, 0x00688960, 37 bytes.
//
// The reference's inline, out of line here: guard on GameSlot::isHuman
// (0x0061E580, already ledgered) and, if it passes, stamp the slot's
// m_lastHeard. Nothing else in the reference has that shape with two
// arguments, and the two offsets the body uses settle the layout.
//
// Those offsets are the reason this is worth more than 37 bytes. The slot
// array is at LANGameInfo+0x58, not +0x88: the stride is 0x68 -- LANGameSlot's
// size, which the destructor below pins independently -- and 0x58 + 8 * 0x68
// lands exactly on 0x398, the m_next the LAN list walks. +0x88 cannot be
// right; it would put m_next at 0x3C8. The second offset, m_lastHeard at
// 0xBC from the object, is 0x58 + 0x64, and 0x64 is where LANGameSlot's own
// destructor leaves it.
//
// This body touches no field of either base; before the merge both were
// opaque blocks sized to fit, and the shared model above names them without
// moving anything it reads.
void LANGameInfo::setPlayerLastHeard( Int who, UnsignedInt lastHeard )
{
	if (m_LANSlot[who].isHuman())
		m_LANSlot[who].setLastHeard(lastHeard);
}

// LANGameInfo::setSlot, retail 0x0068EA70 (119 bytes).
void LANGameInfo::setSlot(Int slotNum, LANGameSlot slotInfo)
{
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return;

	m_LANSlot[slotNum] = slotInfo;

	if (slotNum == 0)
	{
		m_LANSlot[slotNum].setAccept();
		m_LANSlot[slotNum].setMapAvailability(true);
	}
}

// LANGameInfo::resetAccepted, retail 0x0068D4D0 (98 bytes).
// The BFME LAN interface adds six virtual entries before the Zero Hour
// interface's utility calls; the slots below keep the three calls at +0x68,
// +0xB8, and +0xC0 on their retail entries.
void LANGameInfo::resetAccepted(void)
{
	if (TheLAN)
	{
		TheLAN->ResetGameStartTimer();
		if (TheLAN->GetMyGame() == this && TheLAN->AmIHost() &&
			g_Va012F49D4 == 0)
			LANEnableStartButton(true);
	}

	for (Int i = 0; i < 8; ++i)
		m_LANSlot[i].unAccept();
}

// LANGameSlot::~LANGameSlot, 0x006858A0, 89 bytes.
//
// An empty body: everything in it is member and base destruction, in reverse
// declaration order, and each of the three calls is already ledgered or
// pinned. That is also what names it. The layout it destroys is exactly the
// one LANGameSlot_operator.cpp pins from the other side --
//
//   0x00  GameSlot base, 0x44 bytes, destroyed through ??1GameSlot@@QAE@XZ
//   0x44  LANPlayer m_user, destroyed through ??1LANPlayer@@QAE@XZ (0x00685830)
//   0x60  AsciiString m_serial, released in place
//   0x64  UnsignedInt m_lastHeard, trivial
//
// -- and it lands sizeof(LANGameSlot) on 0x68, which is the per-slot stride
// LANGameInfo's slot array already uses.
//
// This body is why GameSlot carries a plain m_vptr member above instead of a
// virtual function, and that is not cosmetic: give the model a vtable and MSVC
// opens this destructor with a six-byte vptr store retail does not have.
// LANGameSlot does have its own vtable -- its copy constructor at 0x00686D50
// installs 0x0111B6A0 -- so the store is one MSVC emits and retail elided, not
// evidence that the class is non-polymorphic. LANGameSlot_operator.cpp keeps
// its own model for the opposite reason: its matched operator= needs GameSlot's
// virtual to skip the vptr, which is why it is not merged in here.
LANGameSlot::~LANGameSlot()
{
}

// LANGameSlot::setLogin(AsciiString), 0x006853C0, 75 bytes.
//
// One line, and the offset is the whole identification: it translates the
// by-value AsciiString into the UnicodeString at this+0x48. In the
// LANGameSlot layout the destructor and copy constructor pin, +0x44 is
// LANPlayer m_user and +0x48 is that player's m_login, so this is the
// reference's `inline void setLogin(AsciiString name) { m_user.setLogin(name); }`
// with LANPlayer::setLogin -- itself a one-liner -- inlined into it. The
// reference declares a UnicodeString overload beside it; that one would not
// call translate.
//
// The inner setter takes a const reference here rather than the reference's
// by-value AsciiString. That is not cosmetic either: by value MSVC has to
// build a second copy of the parameter and reserves a frame slot for it, which
// costs the body twenty-six bytes it does not have. Nothing outside this file
// sees the difference -- the inner setter is inlined and emits no symbol.
void LANGameSlot::setLogin(AsciiString name)
{
	m_user.setLogin(name);
}

// LANGameSlot::isLocalPlayer, retail 0x0068D340 (124 bytes).
Bool LANGameSlot::isLocalPlayer() const
{
	if (!isHuman() || TheLAN == 0)
		return false;

	BfmeNetAddress *local = (BfmeNetAddress *)&TheLAN->getLocalAddress();
	if (local->ip == m_address.ip && local->port == m_address.port)
		return true;

	BfmeNetAddress localAddress = *(BfmeNetAddress *)&TheLAN->getLocalAddress();
	localAddress.port = (UnsignedShort)(localAddress.port + 8);
	return localAddress.ip == m_address.ip &&
		localAddress.port == m_address.port;
}
