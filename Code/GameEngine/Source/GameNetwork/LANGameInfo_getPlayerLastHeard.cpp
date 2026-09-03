// cl: /DNDEBUG /MD /EHsc

// LANGameInfo::getPlayerLastHeard, 0x00684C60, 39 bytes.
//
// ZH inlines this in LANGameInfo.h; BFME out-of-lined it beside the other
// LANGameInfo slot helpers. The isHuman guard uses the same ILT thunk
// (0x000279CB -> GameSlot::isHuman at 0x0061E580) as setPlayerLastHeard at
// 0x00688960, and the slot array layout is pinned there: m_LANSlot at +0x58,
// stride 0x68, m_lastHeard at +0x64 within each LANGameSlot.

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
	UnsignedInt getLastHeard(void) const { return m_lastHeard; }

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
	UnsignedInt getPlayerLastHeard(Int who);

private:
	LANGameSlot m_LANSlot[MAX_SLOTS];		// this+0x58
};

// ?getPlayerLastHeard@LANGameInfo@@QAEIH@Z
UnsignedInt LANGameInfo::getPlayerLastHeard( Int who )
{
	if (m_LANSlot[who].isHuman())
		return m_LANSlot[who].getLastHeard();
	return 0;
}
