// cl: /DNDEBUG /MD /EHsc
// readable body of ??0VictoryConditions@@: Code/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp
// victory_conditions_create.cpp -- the EH-framed VictoryConditions bodies.
//
// Split from victory_conditions.cpp deliberately: retail's constructor,
// destructor and createVictoryConditions all carry fs:[0] EH frames whose only
// throwing points are calls to reset() / hideEndGame(). MSVC 7.1 proves an
// intra-TU callee of pure stores nothrow and deletes the whole frame, so the
// bodies that must KEEP their frames live here, where those callees are only
// declared. The class declaration is a verbatim copy of the one in
// victory_conditions.cpp -- see that file for the layout evidence.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	char *m_data;
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/VictoryConditions.h
class VictoryConditionsInterface : public SubsystemInterface
{
public:
	VictoryConditionsInterface() { m_victoryConditions = 0; }

	virtual Bool hasAchievedVictory(Player *player) = 0;
	virtual Bool hasBeenDefeated(Player *player) = 0;
	virtual Bool hasSinglePlayerBeenDefeated(Player *player) = 0;
	virtual void cachePlayerPtrs( void ) = 0;
	virtual Bool isLocalAlliedVictory( void ) = 0;
	virtual Bool isLocalAlliedDefeat( void ) = 0;
	virtual Bool isLocalDefeat( void ) = 0;
	virtual Bool amIObserver( void ) = 0;
	virtual UnsignedInt getEndFrame( void ) = 0;
	virtual void showEndGame(void *a, void *b, void *c, void *d) = 0;
	virtual void hideEndGame( void ) = 0;
	virtual Bool isPlayerDefeated(Int index) = 0;
	virtual void updateEndGame( void ) = 0;

protected:
	Int m_victoryConditions;
};

enum { MAX_PLAYER_COUNT = 32 };

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

//-------------------------------------------------------------------------------------------------
VictoryConditionsInterface * createVictoryConditions( void )
{
	// only one created, so no MemoryPool usage
	return new VictoryConditions;
}

//-------------------------------------------------------------------------------------------------
VictoryConditions::VictoryConditions()
: m_endGameShowing(false), m_endGameShowTime(0)
{
	reset();
}
