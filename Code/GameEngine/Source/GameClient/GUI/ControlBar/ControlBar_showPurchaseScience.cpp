// cl: /DNDEBUG /MD /EHsc
// readable body of ?showPurchaseScience@ControlBar@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// ControlBar::showPurchaseScience, retail 0x004A2290. Tail-jumps the window
// show helper after populatePurchaseScience.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool hasPurchaseScience( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer( void ) { return m_localPlayer; }

private:
	unsigned char m_pad[ 0x0C ];
	Player *m_localPlayer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	Bool isGameEnding( void ) const { return m_endGameTimer >= 0; }

private:
	unsigned char m_pad[ 0x17080 ];
	Int m_endGameTimer;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void finishShowPurchaseScience( void );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void showPurchaseScience( void );

protected:
	void populatePurchaseScience( Player *player );

private:
	unsigned char m_pad[ 0x2C8 ];
	Bool m_genStarFlash;
};

void ControlBar::showPurchaseScience( void )
{
	if ( TheScriptEngine->isGameEnding() )
		return;
	Player *player = ThePlayerList->getLocalPlayer();
	if ( !player )
		return;
	if ( !player->hasPurchaseScience() )
		return;
	populatePurchaseScience( player );
	m_genStarFlash = 0;
	finishShowPurchaseScience();
}
