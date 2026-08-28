// cl: /DNDEBUG /MD /EHsc

// LANGameInfo::setPlayerLastHeard, 0x00688960, 37 bytes.
//
// The reference's inline, out of line here: guard on GameSlot::isHuman
// (0x0061E580, already ledgered) and, if it passes, stamp the slot's
// m_lastHeard. Nothing else in the reference has that shape with two
// arguments, and the two offsets the body uses settle the layout.
//
// Those offsets are the reason this is worth more than 37 bytes. The slot
// array is at LANGameInfo+0x58, not +0x88: the stride is 0x68 -- LANGameSlot's
// size, which LANGameSlot_dtor.cpp pins independently -- and 0x58 + 8 * 0x68
// lands exactly on 0x398, the m_next the LAN list walks. +0x88 cannot be
// right; it would put m_next at 0x3C8. The second offset, m_lastHeard at
// 0xBC from the object, is 0x58 + 0x64, and 0x64 is where LANGameSlot's own
// destructor leaves it.
//
// GameInfo and GameSlot are opaque blocks sized to their bases; this body
// touches neither one's fields.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isHuman(void) const;			// ILT thunk 0x000279CB

	UnsignedByte m_bfmeBody[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	UnsignedByte m_bfmeBody[0x1C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	void setLastHeard(UnsignedInt lastHeard) { m_lastHeard = lastHeard; }

private:
	LANPlayer m_user;				// this+0x44
	void *m_serial;					// this+0x60
	UnsignedInt m_lastHeard;			// this+0x64
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	UnsignedByte m_bfmeBody[0x58];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public GameInfo
{
public:
	void setPlayerLastHeard(Int who, UnsignedInt lastHeard);

private:
	LANGameSlot m_LANSlot[MAX_SLOTS];		// this+0x58
};

// ?setPlayerLastHeard@LANGameInfo@@QAEXHI@Z
void LANGameInfo::setPlayerLastHeard( Int who, UnsignedInt lastHeard )
{
	if (m_LANSlot[who].isHuman())
		m_LANSlot[who].setLastHeard(lastHeard);
}
