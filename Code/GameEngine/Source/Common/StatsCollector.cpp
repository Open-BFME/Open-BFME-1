// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled

#include "PreRTS.h"
#include <time.h>

#pragma intrinsic( memcmp )

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	const char *str() const { return m_data ? m_data + 8 : ""; }
	Int compare( const char *other ) const
	{
		Int otherLength = strlen( other );
		Int thisLength = m_data ? *reinterpret_cast<const UnsignedShort *>( m_data + 4 ) : 0;
		const char *thisData = str();
		Int length = thisLength < otherLength ? thisLength : otherLength;
		Int result = memcmp( thisData, other, length );
		return result ? result : thisLength - otherLength;
	}

private:
	char *m_data;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *getFirstObject();

private:
	unsigned char m_unmodelled00[ 0x3C ];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled00[ 8 ];
	AsciiString m_mapName;
	unsigned char m_unmodelled0C[ 0xCCC - 0x0C ];
	Int m_playStats;
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt countMoney() const { return m_money; }

private:
	void *m_vtable;
	UnsignedInt m_money;
	Int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ScoreKeeper.h
class ScoreKeeper
{
public:
	Int getTotalMoneyEarned() const { return m_totalMoneyEarned; }
	Int getTotalMoneySpent() const { return m_totalMoneySpent; }
	Int getTotalUnitsDestroyed();
	Int getTotalUnitsBuilt() const { return m_totalUnitsBuilt; }
	Int getTotalUnitsLost() const { return m_totalUnitsLost; }
	Int getTotalBuildingsDestroyed();
	Int getTotalBuildingsBuilt() const { return m_totalBuildingsBuilt; }
	Int getTotalBuildingsLost() const { return m_totalBuildingsLost; }

private:
	void *m_vtable;
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[ 32 ];
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[ 32 ];
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf( Int kind ) const { return (m_kindOf & (1U << kind)) != 0; }

	unsigned char m_unmodelled08[ 0xC0 ];
	UnsignedInt m_kindOf;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
	const AsciiString &getSide() const { return m_side; }
	Money *getMoney() { return &m_money; }
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
	Bool isLocalPlayer() const;

private:
	unsigned char m_unmodelled00[ 0x24 ];
	Int m_playerIndex;
	AsciiString m_side;
	unsigned char m_unmodelled2C[ 0x48 - 0x2C ];
	Money m_money;
	unsigned char m_unmodelled54[ 0x348 - 0x54 ];
	ScoreKeeper m_scoreKeeper;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

private:
	unsigned char m_unmodelled00[ 0x0C ];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thing = m_thingTemplate;
		if( thing && thing->m_nextOverride )
			thing = static_cast<const ThingTemplate *>( thing->m_nextOverride->getFinalOverride() );
		return thing;
	}

	Bool isKindOf( Int kind ) const { return getTemplate()->isKindOf( kind ); }
	Bool isNeutralControlled() const;
	Player *getControllingPlayer() const;
	Object *getNextObject() const { return m_nextObject; }

private:
	unsigned char m_unmodelled00[ 4 ];
	ThingTemplate *m_thingTemplate;
	unsigned char m_unmodelled08[ 0x88 - 8 ];
	Object *m_nextObject;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	Int getType() const { return m_type; }
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unmodelled00[ 0x10 ];
	Int m_type;
	Int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
#define BFME_DISPLAY_SLOT( n ) virtual void unused##n();
	BFME_DISPLAY_SLOT( 00 ) BFME_DISPLAY_SLOT( 01 ) BFME_DISPLAY_SLOT( 02 ) BFME_DISPLAY_SLOT( 03 )
	BFME_DISPLAY_SLOT( 04 ) BFME_DISPLAY_SLOT( 05 ) BFME_DISPLAY_SLOT( 06 ) BFME_DISPLAY_SLOT( 07 )
	BFME_DISPLAY_SLOT( 08 ) BFME_DISPLAY_SLOT( 09 ) BFME_DISPLAY_SLOT( 10 ) BFME_DISPLAY_SLOT( 11 )
	BFME_DISPLAY_SLOT( 12 ) BFME_DISPLAY_SLOT( 13 ) BFME_DISPLAY_SLOT( 14 ) BFME_DISPLAY_SLOT( 15 )
	BFME_DISPLAY_SLOT( 16 ) BFME_DISPLAY_SLOT( 17 ) BFME_DISPLAY_SLOT( 18 ) BFME_DISPLAY_SLOT( 19 )
	BFME_DISPLAY_SLOT( 20 ) BFME_DISPLAY_SLOT( 21 ) BFME_DISPLAY_SLOT( 22 ) BFME_DISPLAY_SLOT( 23 )
	BFME_DISPLAY_SLOT( 24 ) BFME_DISPLAY_SLOT( 25 ) BFME_DISPLAY_SLOT( 26 ) BFME_DISPLAY_SLOT( 27 )
	BFME_DISPLAY_SLOT( 28 ) BFME_DISPLAY_SLOT( 29 ) BFME_DISPLAY_SLOT( 30 ) BFME_DISPLAY_SLOT( 31 )
	BFME_DISPLAY_SLOT( 32 ) BFME_DISPLAY_SLOT( 33 ) BFME_DISPLAY_SLOT( 34 ) BFME_DISPLAY_SLOT( 35 )
	BFME_DISPLAY_SLOT( 36 ) BFME_DISPLAY_SLOT( 37 ) BFME_DISPLAY_SLOT( 38 ) BFME_DISPLAY_SLOT( 39 )
	BFME_DISPLAY_SLOT( 40 ) BFME_DISPLAY_SLOT( 41 ) BFME_DISPLAY_SLOT( 42 ) BFME_DISPLAY_SLOT( 43 )
	BFME_DISPLAY_SLOT( 44 ) BFME_DISPLAY_SLOT( 45 ) BFME_DISPLAY_SLOT( 46 ) BFME_DISPLAY_SLOT( 47 )
	BFME_DISPLAY_SLOT( 48 ) BFME_DISPLAY_SLOT( 49 ) BFME_DISPLAY_SLOT( 50 ) BFME_DISPLAY_SLOT( 51 )
	BFME_DISPLAY_SLOT( 52 ) BFME_DISPLAY_SLOT( 53 ) BFME_DISPLAY_SLOT( 54 ) BFME_DISPLAY_SLOT( 55 )
	BFME_DISPLAY_SLOT( 56 ) BFME_DISPLAY_SLOT( 57 ) BFME_DISPLAY_SLOT( 58 ) BFME_DISPLAY_SLOT( 59 )
	BFME_DISPLAY_SLOT( 60 ) BFME_DISPLAY_SLOT( 61 ) BFME_DISPLAY_SLOT( 62 ) BFME_DISPLAY_SLOT( 63 )
	BFME_DISPLAY_SLOT( 64 ) BFME_DISPLAY_SLOT( 65 ) BFME_DISPLAY_SLOT( 66 ) BFME_DISPLAY_SLOT( 67 )
	BFME_DISPLAY_SLOT( 68 ) BFME_DISPLAY_SLOT( 69 ) BFME_DISPLAY_SLOT( 70 ) BFME_DISPLAY_SLOT( 71 )
	BFME_DISPLAY_SLOT( 72 ) BFME_DISPLAY_SLOT( 73 ) BFME_DISPLAY_SLOT( 74 ) BFME_DISPLAY_SLOT( 75 )
	BFME_DISPLAY_SLOT( 76 ) BFME_DISPLAY_SLOT( 77 ) BFME_DISPLAY_SLOT( 78 ) BFME_DISPLAY_SLOT( 79 )
	BFME_DISPLAY_SLOT( 80 ) BFME_DISPLAY_SLOT( 81 )
#undef BFME_DISPLAY_SLOT
	virtual Real getAverageFPS();
};

extern Display *TheDisplay;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0C();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void unused1C();
	virtual void unused20();
	virtual void unused24();
	virtual void unused28();
	virtual void unused2C();
	virtual Int getFramesPerSecondLimit();

	Real getInstantFPS() const { return m_instantFPS; }

private:
	unsigned char m_unmodelled04[ 0x54 - 4 ];
	Real m_instantFPS;
};

extern GameEngine *TheGameEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StatsCollector.h
class StatsCollector
{
public:
	StatsCollector();
	void writeFileEnd();
	void startScrollTime();
	void endScrollTime();
	void collectMsgStats( const GameMessage *msg );
	void collectUnitCountStats();
	void update();

private:
	void writeInitialFileInfo();
	void writeStatInfo();
	void collectScoreKeeperStats();
	AsciiString m_statsFileName;
	UnsignedInt m_moneyWithdrawn;
	UnsignedInt m_moneyDeposited;
	UnsignedInt m_buildCommands;
	UnsignedInt m_moveCommands;
	UnsignedInt m_attackCommands;
	UnsignedInt m_scrollMapCommands;
	UnsignedInt m_aiUnits;
	UnsignedInt m_playerUnits;
	UnsignedInt m_alliesKilled;
	UnsignedInt m_neutralsKilled;
	UnsignedInt m_enemiesKilled;
	UnsignedInt m_scoreKeeperMoneySpent;
	UnsignedInt m_scoreKeeperMoneyEarned;
	UnsignedInt m_scoreKeeperUnitsDestroyed;
	UnsignedInt m_scoreKeeperUnitsBuilt;
	UnsignedInt m_scoreKeeperUnitsLost;
	UnsignedInt m_scoreKeeperBuildingsDestroyed;
	UnsignedInt m_scoreKeeperBuildingsBuilt;
	UnsignedInt m_scoreKeeperBuildingsLost;
	UnsignedInt m_scrollBeginTime;
	UnsignedInt m_scrollTime;
	Bool m_isScrolling;
	Int m_timeCount;
	Int m_lastUpdate;
	Int m_startFrame;
};

StatsCollector::StatsCollector()
{
	m_moneyWithdrawn = 0;
	m_moneyDeposited = 0;
	m_buildCommands = 0;
	m_moveCommands = 0;
	m_attackCommands = 0;
	m_scrollMapCommands = 0;
	m_aiUnits = 0;
	m_playerUnits = 0;
	m_alliesKilled = 0;
	m_neutralsKilled = 0;
	m_enemiesKilled = 0;
	m_scoreKeeperMoneySpent = 0;
	m_scoreKeeperMoneyEarned = 0;
	m_scoreKeeperUnitsDestroyed = 0;
	m_scoreKeeperUnitsBuilt = 0;
	m_scoreKeeperUnitsLost = 0;
	m_scoreKeeperBuildingsDestroyed = 0;
	m_scoreKeeperBuildingsBuilt = 0;
	m_scoreKeeperBuildingsLost = 0;
	m_scrollBeginTime = 0;
	m_scrollTime = 0;
	m_isScrolling = FALSE;
	m_timeCount = 0;
	m_lastUpdate = 0;
	m_startFrame = TheGameLogic->getFrame();
}

void StatsCollector::update()
{
	if( m_lastUpdate + TheWritableGlobalData->m_playStats * 5 > TheGameLogic->getFrame() )
		return;

	collectUnitCountStats();

	if( m_isScrolling )
	{
		m_scrollTime += TheGameLogic->getFrame() - m_scrollBeginTime;
		m_scrollBeginTime = TheGameLogic->getFrame();
	}

	m_timeCount += TheWritableGlobalData->m_playStats;
	writeStatInfo();
	m_buildCommands = 0;
	m_moveCommands = 0;
	m_attackCommands = 0;
	m_scrollMapCommands = 0;
	m_aiUnits = 0;
	m_playerUnits = 0;
	m_scrollTime = 0;
	m_moneyDeposited = 0;
	m_moneyWithdrawn = 0;
	m_scoreKeeperMoneySpent = 0;
	m_scoreKeeperMoneyEarned = 0;
	m_scoreKeeperUnitsDestroyed = 0;
	m_scoreKeeperUnitsBuilt = 0;
	m_scoreKeeperUnitsLost = 0;
	m_scoreKeeperBuildingsDestroyed = 0;
	m_scoreKeeperBuildingsBuilt = 0;
	m_scoreKeeperBuildingsLost = 0;
	m_alliesKilled = 0;
	m_neutralsKilled = 0;
	m_enemiesKilled = 0;
	collectScoreKeeperStats();
	m_lastUpdate = TheGameLogic->getFrame();
}

void StatsCollector::writeInitialFileInfo()
{
	FILE *f = fopen( m_statsFileName.str(), "w" );
	if( !f )
		return;

	fprintf( f, "---------------------------------------------------\n" );
	time_t aclock;
	time( &aclock );
	struct tm *newTime = localtime( &aclock );
	fprintf( f, "Date:\t%s", asctime( newTime ) );
	fprintf( f, "Map:\t%s\n", TheWritableGlobalData->m_mapName.str() );
	fprintf( f, "Side:\t%s\n", ThePlayerList->getLocalPlayer()->getSide().str() );
	fprintf( f, "---------------------------------------------------\n\n" );

	fprintf( f, "Time*\t" );
	fprintf( f, "Instant_Average_FPS\t" );
	fprintf( f, "Instant_Net_FPS\t" );
	fprintf( f, "Build_Commands\t" );
	fprintf( f, "Move_Commands\t" );
	fprintf( f, "Attack_Commands\t" );
	fprintf( f, "Scroll_Map_Commands\t" );
	fprintf( f, "Scroll_Time_in_Seconds\t" );
	fprintf( f, "Other_Commands_(N/A)\t" );
	fprintf( f, "Player_Money_Amount\t" );
	fprintf( f, "Player_Money_Withdrawn\t" );
	fprintf( f, "Player_Money_Deposited\t" );
	fprintf( f, "Player_Units\t" );
	fprintf( f, "AI_Units\t" );
	fprintf( f, "Allies_Killed\t" );
	fprintf( f, "Enemies_Killed\t" );
	fprintf( f, "Neutrals_Killed\t" );
	fprintf( f, "ScoreKeeper_MoneySpent\t" );
	fprintf( f, "ScoreKeeper_MoneyEarned\t" );
	fprintf( f, "ScoreKeeper_UnitsDestroyed\t" );
	fprintf( f, "ScoreKeeper_UnitsBuilt\t" );
	fprintf( f, "ScoreKeeper_UnitsLost\t" );
	fprintf( f, "ScoreKeeper_BuildingsDestroyed\t" );
	fprintf( f, "ScoreKeeper_BuildingsBuilt\t" );
	fprintf( f, "ScoreKeeper_BuildingsLost\t" );
	fprintf( f, "\n" );

	fclose( f );
}

void StatsCollector::writeStatInfo()
{
	FILE *f = fopen( m_statsFileName.str(), "a" );
	if( !f )
		return;

	Player *player = ThePlayerList->getLocalPlayer();
	Money *money = player->getMoney();
	fprintf( f, "%d\t", m_timeCount );
	fprintf( f, "%.1f\t", TheDisplay ? TheDisplay->getAverageFPS() : 0.0f );
	fprintf( f, "%.1f\t", TheGameEngine ? TheGameEngine->getInstantFPS() : 0.0f );
	fprintf( f, "%d\t", m_buildCommands );
	fprintf( f, "%d\t", m_moveCommands );
	fprintf( f, "%d\t", m_attackCommands );
	fprintf( f, "%d\t", m_scrollMapCommands );
	fprintf( f, "%d\t", m_scrollTime / 5 );
	fprintf( f, "%d\t", 0 );
	fprintf( f, "%d\t", money->countMoney() );
	fprintf( f, "%d\t", m_moneyWithdrawn );
	fprintf( f, "%d\t", m_moneyDeposited );
	fprintf( f, "%d\t", m_playerUnits );
	fprintf( f, "%d\t", m_aiUnits );
	fprintf( f, "%d\t", m_alliesKilled );
	fprintf( f, "%d\t", m_enemiesKilled );
	fprintf( f, "%d\t", m_neutralsKilled );

	player = ThePlayerList->getLocalPlayer();
	if( player )
	{
		ScoreKeeper *scoreKeeper = player->getScoreKeeper();
		if( scoreKeeper )
		{
			fprintf( f, "%d\t", scoreKeeper->getTotalMoneySpent() - m_scoreKeeperMoneySpent );
			fprintf( f, "%d\t", scoreKeeper->getTotalMoneyEarned() - m_scoreKeeperMoneyEarned );
			fprintf( f, "%d\t", scoreKeeper->getTotalUnitsDestroyed() - m_scoreKeeperUnitsDestroyed );
			fprintf( f, "%d\t", scoreKeeper->getTotalUnitsBuilt() - m_scoreKeeperUnitsBuilt );
			fprintf( f, "%d\t", scoreKeeper->getTotalUnitsLost() - m_scoreKeeperUnitsLost );
			fprintf( f, "%d\t", scoreKeeper->getTotalBuildingsDestroyed() - m_scoreKeeperBuildingsDestroyed );
			fprintf( f, "%d\t", scoreKeeper->getTotalBuildingsBuilt() - m_scoreKeeperBuildingsBuilt );
			fprintf( f, "%d\t", scoreKeeper->getTotalBuildingsLost() - m_scoreKeeperBuildingsLost );
		}
	}

	fprintf( f, "\n" );
	fclose( f );
}

void StatsCollector::writeFileEnd()
{
	FILE *f = fopen( m_statsFileName.str(), "a" );
	if( !f )
		return;

	m_timeCount += (TheGameLogic->getFrame() - m_lastUpdate) / 5;
	writeStatInfo();
	fprintf( f, "---------------------------------------------------\n" );

	time_t aclock;
	time( &aclock );
	struct tm *newTime = localtime( &aclock );
	fprintf( f, "End Time:\t%s\n", asctime( newTime ) );
	fprintf( f, "* Times are in Game Seconds which are based on logic FPS: current logic FPS is %d, max update FPS (game speed) is %d\n",
		5, TheGameEngine->getFramesPerSecondLimit() );

	fclose( f );
}

void StatsCollector::startScrollTime()
{
	m_isScrolling = TRUE;
	m_scrollBeginTime = TheGameLogic->getFrame();
	++m_scrollMapCommands;
}

void StatsCollector::endScrollTime()
{
	if( !m_isScrolling )
		return;

	m_isScrolling = FALSE;
	m_scrollTime += TheGameLogic->getFrame() - m_scrollBeginTime;
}

void StatsCollector::collectMsgStats( const GameMessage *msg )
{
	if( ThePlayerList->getLocalPlayer()->getPlayerIndex() != msg->getPlayerIndex() )
		return;

	switch( msg->getType() )
	{
		case 0x416:
		case 0x418:
			++m_buildCommands;
			break;
	}
}

void StatsCollector::collectUnitCountStats()
{
	for( Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject() )
	{
		if( !(obj->isKindOf( 8 ) || obj->isKindOf( 9 )) ||
			obj->isNeutralControlled() ||
			obj->getControllingPlayer()->getSide().compare( "Civilian" ) == 0 )
			continue;

		if( obj->getControllingPlayer()->isLocalPlayer() )
			++m_playerUnits;
		else
			++m_aiUnits;
	}
}
