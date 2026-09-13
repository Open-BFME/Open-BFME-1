// cl: /DNDEBUG /MD /EHsc
// Open-BFME: RecorderClass::isMultiplayer, retail 0x00097800, 103 bytes.
//
// The reference's body with BFME's game-mode list. The playback scan is
// unchanged -- m_mode at this+0x18 against PLAYBACK, then the eight slots of
// the embedded GameInfo at this+0x20 -- and so is the tail, TheNetwork or
// TheSkirmishGameInfo meaning multiplayer.
//
// The mode tests in between are where BFME shows through. Single player and
// the shell are still 0 and 4, so the enum did not move under them, but there
// are two the reference does not have: 7, which is where GAME_NONE lands once
// one mode is inserted ahead of it, and 6, the inserted mode itself, which
// this function answers true for. What that mode is is not visible here, so it
// is named for its number rather than guessed at.
//
// The mode is loaded once and compared four times, and the two exits are laid
// out true first: that ordering only comes out when the function has a single
// `return false` at the end with the mode tests folded into one guarded block,
// not the reference's chain of early returns, which lays the exits out the
// other way round for otherwise identical code.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { MAX_SLOTS = 8 };

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD = 0,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

enum
{
	GAME_SINGLE_PLAYER = 0,
	GAME_LAN,
	GAME_SKIRMISH,
	GAME_REPLAY,
	GAME_SHELL,
	GAME_INTERNET,
	GAME_BFME_MODE_SIX,				// no reference twin; multiplayer as far as this body is concerned
	GAME_NONE
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isOccupied(void) const;			// ILT 0x00040593
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot(Int which);			// ILT 0x0001EC18

private:
	char m_bfme_body[4];
};

extern GameInfo *TheSkirmishGameInfo;			// 0x012F7094

class Network;
extern Network *TheNetwork;				// 0x012F7714

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Int getGameMode(void) { return m_gameMode; }

private:
	char m_slice_pad[0x10C];			// retail this+0x00 .. +0x10B, untouched
	Int m_gameMode;					// this+0x10C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	Bool isMultiplayer(void);

private:
	char m_slice_padA[0x18];			// retail this+0x00 .. +0x17, untouched
	RecorderModeType m_mode;			// this+0x18
	char m_slice_padB[0x20 - 0x1C];			// this+0x1C, untouched
	GameInfo m_gameInfo;				// this+0x20
};

Bool RecorderClass::isMultiplayer( void )
{
	if (m_mode == RECORDERMODETYPE_PLAYBACK)
	{
		GameSlot *slot;
		for (int i = 0; i < MAX_SLOTS; ++i)
		{
			slot = m_gameInfo.getSlot(i);
			if (slot && slot->isOccupied())	///< slots default to closed for non-networked games
				return true;
		}
	}
	Int mode = TheGameLogic->getGameMode();
	if (mode != GAME_SINGLE_PLAYER && mode != GAME_NONE && mode != GAME_SHELL)
	{
		if (mode == GAME_BFME_MODE_SIX || TheNetwork || TheSkirmishGameInfo)
			return true;
	}

	return false;
}
