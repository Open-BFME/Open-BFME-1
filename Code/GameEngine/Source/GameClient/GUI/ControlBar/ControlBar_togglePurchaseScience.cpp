// cl: /DNDEBUG /MD /EHsc
// readable body of ?togglePurchaseScience@ControlBar@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// ControlBar::togglePurchaseScience, retail 0x004A22F0. Visible window at
// 0x012F4C38+0x259 hides; otherwise the showPurchaseScience body.

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

struct PurchaseScienceWindow
{
	unsigned char m_pad[ 0x259 ];
	unsigned char m_visible;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern PurchaseScienceWindow *g_purchaseScienceWindow;

void finishShowPurchaseScience( void );
void hidePurchaseScience( void );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void togglePurchaseScience( void );

protected:
	void populatePurchaseScience( Player *player );

private:
	unsigned char m_pad[ 0x2C8 ];
	Bool m_genStarFlash;
};

void ControlBar::togglePurchaseScience( void )
{
	if ( g_purchaseScienceWindow && g_purchaseScienceWindow->m_visible )
	{
		hidePurchaseScience();
		return;
	}
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
