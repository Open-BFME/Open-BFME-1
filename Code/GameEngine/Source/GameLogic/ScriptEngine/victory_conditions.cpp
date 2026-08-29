// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?cachePlayerPtrs@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?hasAchievedVictory@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?hasBeenDefeated@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?hasSinglePlayerBeenDefeated@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?isLocalAlliedDefeat@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?isLocalAlliedVictory@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?isLocalDefeat@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// readable body of ?reset@VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// victory_conditions.cpp -- BFME's VictoryConditions subsystem as clean C++.
//
// Retail keeps the whole family in one TU around 0x0035F150-0x0035FED0 with the
// concrete vtable at VA 0x010E8D90 (22 slots). Identity comes from the ZH source
// (GameEngine/Source/GameLogic/System/VictoryConditions.cpp): slot 5 is the
// matched ?update@VictoryConditions@@ body, slot 12 walks ThePlayerList against
// the "FactionCivilian" template exactly like ZH's cachePlayerPtrs, and the
// factory at 0x0035F810 news 0xC4 bytes through the ctor at 0x0035F430.
//
// BFME deltas against ZH, read off the retail bodies:
//  - SubsystemInterface has nine virtual slots (see subsystem_interface.h); the
//    interface virtuals therefore start at slot 9, and BFME appends four new
//    ones (slots 18-21: the ShowEndGame/HideEndGame banner machinery and an
//    m_isDefeated getter).
//  - MAX_PLAYER_COUNT is 32 (every loop runs to 0x20).
//  - Three new members: m_endGameShowing (+0x0C) and m_endGameShowTime (+0x10),
//    zeroed only in the ctor and driven by the banner methods, and a defeat
//    counter at +0xC0 zeroed in reset() and bumped by every true return of
//    hasSinglePlayerBeenDefeated.
//  - reset() picks the victory mask from TheGameLogic's mode word (+0x10C):
//    mode 6 keeps ZH's NOBUILDINGS|NOUNITS, everything else NOBUILDINGS only.
// sizeof(VictoryConditions) == 0xC4, asserted below.

// Real ZH type stack: BitFlags + STLTypedefs bring AsciiString, Bool/Int and
// the Relationship enum this file needs.
#include "Common/BitFlags.h"

// BFME plays 32 slots; ZH's GameCommon enumerator says 16. Shadow the
// enumerator for the rest of this TU (every retail loop here runs to 0x20).
#define MAX_PLAYER_COUNT 32

// KindOfMaskType, width-only: BFME's KINDOF_COUNT sits in (160,192] so the
// mask is six 32-bit words (KindOfMaskCountThunk.cpp pins the STLport
// _Base_bitset Nw=6 helpers); 192 follows the CrateSystem.cpp precedent.
// Retail's one use here sets bit 175 -- the check ZH spells
// mask.set(KINDOF_MP_COUNT_FOR_VICTORY) -- so that index gets ZH's name;
// every other BFME enumerator stays unmodeled.
enum { KINDOF_COUNT = 192 };
enum { KINDOF_MP_COUNT_FOR_VICTORY = 175 };
typedef BitFlags<KINDOF_COUNT> KindOfMaskType;

// Player as far as this TU touches it. Methods resolve out-of-line through
// reverse/symbols.csv; the two members model the retail offsets areAllies and
// cachePlayerPtrs read inline (getPlayerTemplate at +0x04, getDefaultTeam at
// +0x230).
class Team;
class PlayerTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Relationship getRelationship( const Team *that ) const;
	Bool isPlayerObserver() const;
	Bool isLocalPlayer() const;
	Bool hasAnyUnits() const;
	Bool hasAnyObjects(Bool b) const;
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool b) const;

private:
	void					*m_vptrPad;								// +0x00 retail vptr
	PlayerTemplate *m_playerTemplate;				// +0x04
	char					 m_pad[ 0x230 - 8 ];
	Team					*m_defaultTeam;						// +0x230
};

// BFME's nine-slot subsystem base -- the retail truth this TU dispatches
// against (the shared subsystem_interface.h stops at six slots and keeps
// reset/update one slot early, which these bodies cannot afford: init() must
// tail-jump through [vptr+0x10]).
//   0 ~SubsystemInterface (body 0x009A1A40)   1 init
//   2 loadIniFilesFromLegend (0x009A1A50)     3 unidentified, empty (0x00067930)
//   4 reset                                   5 update
//   6 unidentified Bool(arg){false} (0x00067940)
//   7 unidentified, empty (0x009A16C0)        8 unidentified, empty-with-arg (0x009A16D0)
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void unidentifiedSlot03();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual Bool unidentifiedSlot06(Int arg);
	virtual void unidentifiedSlot07();
	virtual void unidentifiedSlot08(Int arg);
protected:
	AsciiString m_name;
};

enum VictoryType
{
	VICTORY_NOBUILDINGS = 1,
	VICTORY_NOUNITS = 2,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/VictoryConditions.h
class VictoryConditionsInterface : public SubsystemInterface
{
public:
	VictoryConditionsInterface() { m_victoryConditions = 0; }

	virtual Bool hasAchievedVictory(Player *player) = 0;					// slot 9
	virtual Bool hasBeenDefeated(Player *player) = 0;							// slot 10
	virtual Bool hasSinglePlayerBeenDefeated(Player *player) = 0;	// slot 11
	virtual void cachePlayerPtrs( void ) = 0;											// slot 12
	virtual Bool isLocalAlliedVictory( void ) = 0;								// slot 13
	virtual Bool isLocalAlliedDefeat( void ) = 0;									// slot 14
	virtual Bool isLocalDefeat( void ) = 0;												// slot 15
	virtual Bool amIObserver( void ) = 0;													// slot 16
	virtual UnsignedInt getEndFrame( void ) = 0;									// slot 17
	// BFME-only banner machinery; descriptive names from the "ShowEndGame" /
	// "HideEndGame" event literals the retail bodies push (VA 0x010E8E10 /
	// 0x010E8E58), not from any symbol.
	virtual void showEndGame(void *a, void *b, void *c, void *d) = 0;	// slot 18 (0x0035F600)
	virtual void hideEndGame( void ) = 0;													// slot 19 (0x0035F770)
	virtual Bool isPlayerDefeated(Int index) = 0;									// slot 20 (0x0035F4C0)
	virtual void updateEndGame( void ) = 0;												// slot 21 (0x0035F1A0)

protected:
	Int m_victoryConditions;	// +0x08
};

// TheGameLogic as far as reset() needs it: the game-mode word retail keeps at
// +0x10C (the same field the matched update body compares against 1/2/5/6).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Int getGameMode( void ) const { return m_gameMode; }
private:
	char m_pad[ 0x10c ];
	Int m_gameMode;					// +0x10C
};

extern GameLogic *TheGameLogic;			///< retail [0x012F0898]

// TheGameInfo as far as isLocalAlliedVictory needs it: retail queries virtual
// slot 12 ([vptr+0x30]) as a Bool predicate before trusting the local slot.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Bool unidentifiedSlot12() = 0;
};

extern GameInfo *TheGameInfo;				///< retail [0x012F708C]

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char* keyName );
};

extern NameKeyGenerator *TheNameKeyGenerator;	///< retail [0x012ED600]

#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate( NameKeyType nameKey ) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;	///< retail [0x012ED750]

// PlayerList as far as cachePlayerPtrs needs it: getNthPlayer resolves
// out-of-line, getNeutralPlayer inlines to the +0x14 member read retail shows.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getNeutralPlayer() { return m_neutralPlayer; }
	Player *getNthPlayer( Int i );

private:
	void		*m_vptrPad;					// +0x00 retail vptr
	char		 m_pad[ 0x10 ];
	Player	*m_neutralPlayer;		// +0x14
};

extern PlayerList *ThePlayerList;			///< retail [0x012ED748]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	Bool isMultiplayer( void );
};

extern RecorderClass *TheRecorder;		///< retail [0x012ED62C]

// Radar as far as cachePlayerPtrs needs it: forceOn inlines to the +0x0D byte
// store retail shows.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
public:
	void forceOn( Bool force ) { m_radarForceOn = force; }

private:
	void	*m_vptrPad;							// +0x00 retail vptr
	char	 m_pad[ 9 ];
	Bool	 m_radarForceOn;				// +0x0D
};

extern Radar *TheRadar;								///< retail [0x012EF0E4]

// hasSinglePlayerBeenDefeated seeds its result from a Player byte getter at
// +0x680 (ILT 0x00012EEA -> body 0x000C9D00), a BFME-only pre-check with no ZH
// counterpart. Address-derived shim name, identity open.
class PlayerShim
{
public:
	Bool unidentified_00012eea() const;
};

// WindowManager as far as the banner methods need it: the eight-dword
// scripted-UI event dispatcher (ILT 0x00015235, body 0x004675F0) is a
// __thiscall member -- retail loads [0x012F19E8] into ecx for the call --
// invoked as (0xB, eventName, argCount, up to five args...). Address-derived
// name, identity open.
class WindowManager
{
public:
	void unidentified_00015235(Int a, const char *eventName, Int argCount,
		const void *p1, const void *p2, const void *p3, const void *p4, const void *p5);
};

extern WindowManager *g_theWindowManager;	///< retail [0x012F19E8]

// Display as far as the banner methods need it: they flip a byte at +0x13C
// (1 on hide, 0 on show). Member identity open.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	void setUnidentified13c( Bool b ) { m_unidentified13c = b; }

private:
	char	m_pad[ 0x13c ];
	Bool	m_unidentified13c;			// +0x13C
};

extern Display *TheDisplay;						///< retail [0x012F1270]

class TransitionHandler
{
public:
	void setGroup( AsciiString name, Int i );
};

extern TransitionHandler *TheTransitionHandler;	///< retail [0x012F3330]

// timeGetTime through the import slot retail reads at [0x01359544].
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

#define ISSET(x) (m_victoryConditions & VICTORY_##x)

// hasAchievedVictory reports the winning player index to TheGameLogic through
// the ILT thunk at 0x0000F5FB; the 35-byte body (0x00383C30) bounds the index
// to [0,8) and stamps TheGameLogic's frame counter (+0x3C) into the 0x1C-byte
// per-slot records at +0x1BC. hideEndGame gates the score-screen fade on the
// Bool at ILT 0x0001E0AB (body 0x00382C20: mode 1/2/5, or a replay of one).
// Address-derived shim names, identities open.
class GameLogicShim
{
public:
	void unidentified_0000f5fb(Int playerIndex);
	Bool unidentified_0001e0ab( void );
};


class VictoryConditions : public VictoryConditionsInterface
{
public:
	VictoryConditions();
	virtual ~VictoryConditions();

	virtual void init( void );
	virtual void reset( void );
	virtual void update( void );

	virtual Bool hasAchievedVictory(Player *player);
	virtual Bool hasBeenDefeated(Player *player);
	virtual Bool hasSinglePlayerBeenDefeated(Player *player);

	virtual void cachePlayerPtrs( void );

	virtual Bool isLocalAlliedVictory( void );
	virtual Bool isLocalAlliedDefeat( void );
	virtual Bool isLocalDefeat( void );
	virtual Bool amIObserver( void );
	virtual UnsignedInt getEndFrame( void );

	virtual void showEndGame(void *a, void *b, void *c, void *d);
	virtual void hideEndGame( void );
	virtual Bool isPlayerDefeated(Int index);
	virtual void updateEndGame( void );

private:
	Bool					m_endGameShowing;										// +0x0C
	UnsignedInt		m_endGameShowTime;									// +0x10
	Player*				m_players[MAX_PLAYER_COUNT];				// +0x14
	Int						m_localSlotNum;											// +0x94
	UnsignedInt		m_endFrame;													// +0x98
	Bool					m_isDefeated[MAX_PLAYER_COUNT];			// +0x9C
	Bool					m_localPlayerDefeated;							// +0xBC
	Bool					m_singleAllianceRemaining;					// +0xBD
	Bool					m_isObserver;												// +0xBE
	Int						m_defeatCount;											// +0xC0
};

typedef char BFMERetailVictoryConditionsSizeCheck[ sizeof( VictoryConditions ) == 0xc4 ? 1 : -1 ];

// The constructor, destructor and createVictoryConditions live in
// victory_conditions_create.cpp: their retail bodies carry EH frames, which
// MSVC only emits while their callees (reset, hideEndGame) stay undefined in
// the calling TU -- defined here, they are provably nothrow and the frame
// vanishes.

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::hasSinglePlayerBeenDefeated(Player *player)
{
	if (!player)
		return false;
	if (player->isPlayerObserver())
		return false;

	Bool defeated = ((const PlayerShim *)player)->unidentified_00012eea();

	KindOfMaskType mask;
	mask.set(KINDOF_MP_COUNT_FOR_VICTORY);

	if ( ISSET(NOUNITS) && ISSET(NOBUILDINGS) )
	{
		if ( !player->hasAnyObjects(false) )
		{
			defeated = true;
		}
	}
	else if ( ISSET(NOUNITS) )
	{
		if ( !player->hasAnyUnits() )
		{
			defeated = true;
		}
	}
	else if ( ISSET(NOBUILDINGS) )
	{
		if ( !player->hasAnyBuildings(mask, false) )
		{
			defeated = true;
		}
	}

	if (defeated)
		++m_defeatCount;

	return defeated;
}

//-------------------------------------------------------------------------------------------------
// Compiles as a TU-local helper with MSVC's custom register convention
// (p1 in eax, p2 in caller's esi), exactly the 53-byte body at 0x0035F150.
inline static Bool areAllies(const Player *p1, const Player *p2)
{
	if (p1 != p2 &&
		p1->getRelationship(p2->getDefaultTeam()) == ALLIES &&
		p2->getRelationship(p1->getDefaultTeam()) == ALLIES)
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::hasAchievedVictory(Player *player)
{
	if (!player)
		return false;
	if (player->isPlayerObserver())
		return false;

	if (m_singleAllianceRemaining && m_defeatCount > 0)
	{
		for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
		{
			if ( m_players[i] && !hasSinglePlayerBeenDefeated(m_players[i]) &&
				(player == m_players[i] || areAllies(m_players[i], player)) )
			{
				((GameLogicShim *)TheGameLogic)->unidentified_0000f5fb(i);
				return true;
			}
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
// ?hideEndGame@VictoryConditions@@UAEXXZ present-unmatched
// One instruction pair from the 119-byte retail body at 0x0035F770: retail
// emits `mov [esp+0xC],esp` (the /EHsc byval-temp stash) BEFORE `mov ecx,esp`
// at the setGroup AsciiString temp, this compiles them swapped. Every other
// byte matches; ||/nested-if, implicit conversion, defaulted-arg and
// /EHs//EHs-c- spellings all keep the swap.
void VictoryConditions::hideEndGame( void )
{
	if (!g_theWindowManager || !m_endGameShowing)
		return;

	g_theWindowManager->unidentified_00015235(0xb, "HideEndGame", 0, 0, 0, 0, 0, 0);
	m_endGameShowing = false;
	TheDisplay->setUnidentified13c(true);

	if (((GameLogicShim *)TheGameLogic)->unidentified_0001e0ab())
	{
		if (m_singleAllianceRemaining)
			TheTransitionHandler->setGroup("MPorSkirmishFadeToScoreScreen", 0);
	}
}

//-------------------------------------------------------------------------------------------------
void VictoryConditions::updateEndGame( void )
{
	if (m_endGameShowing)
	{
		if (timeGetTime() - m_endGameShowTime > 7000)
			hideEndGame();
	}
}

//-------------------------------------------------------------------------------------------------
void VictoryConditions::cachePlayerPtrs( void )
{
	if (!TheRecorder->isMultiplayer())
		return;

	Int playerCount = 0;
	const PlayerTemplate *civTemplate = ThePlayerTemplateStore->findPlayerTemplate( NAMEKEY("FactionCivilian") );
	for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
	{
		Player *player = ThePlayerList->getNthPlayer(i);
		if (player && player != ThePlayerList->getNeutralPlayer() && player->getPlayerTemplate() && player->getPlayerTemplate() != civTemplate && !player->isPlayerObserver())
		{
			m_players[playerCount] = player;
			if (m_players[playerCount]->isLocalPlayer())
				m_localSlotNum = playerCount;
			++playerCount;
		}
	}
	while (playerCount < MAX_PLAYER_COUNT)
	{
		m_players[playerCount++] = NULL;
	}

	if (m_localSlotNum < 0)
	{
		m_localPlayerDefeated = true;	// if we have no local player, don't check for defeat
		TheRadar->forceOn(TRUE);
		m_isObserver = true;
	}
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isLocalAlliedVictory( void )
{
	if (!m_isObserver)
	{
		GameInfo *info = TheGameInfo;
		if (!info || !info->unidentifiedSlot12())
			return (hasAchievedVictory(m_players[m_localSlotNum]));
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::hasBeenDefeated(Player *player)
{
	if (!player)
		return false;
	if (player->isPlayerObserver())
		return false;

	if (m_singleAllianceRemaining && m_defeatCount > 0 && !hasAchievedVictory(player))
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isLocalAlliedDefeat( void )
{
	if (m_isObserver)
	{
		if (m_defeatCount > 0)
			return m_singleAllianceRemaining;
		return false;
	}

	return (hasBeenDefeated(m_players[m_localSlotNum]));
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isLocalDefeat( void )
{
	if (m_isObserver)
		return FALSE;

	return (m_localPlayerDefeated);
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::amIObserver( void )
{
	return m_isObserver;
}

//-------------------------------------------------------------------------------------------------
// ?getEndFrame@VictoryConditions@@ present-unmatched
UnsignedInt VictoryConditions::getEndFrame( void )
{
	return m_endFrame;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isPlayerDefeated(Int index)
{
	return m_isDefeated[index];
}

//-------------------------------------------------------------------------------------------------
// ?init@VictoryConditions@@ present-unmatched
void VictoryConditions::init( void )
{
	reset();
}

//-------------------------------------------------------------------------------------------------
void VictoryConditions::reset( void )
{
	for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
	{
		m_players[i] = NULL;
		m_isDefeated[i] = false;
	}
	m_localPlayerDefeated = false;
	m_singleAllianceRemaining = false;
	m_isObserver = false;
	m_endFrame = 0;
	m_defeatCount = 0;
	m_localSlotNum = -1;

	m_victoryConditions = (TheGameLogic->getGameMode() == 6)
		? (VICTORY_NOBUILDINGS | VICTORY_NOUNITS)
		: VICTORY_NOBUILDINGS;
}
