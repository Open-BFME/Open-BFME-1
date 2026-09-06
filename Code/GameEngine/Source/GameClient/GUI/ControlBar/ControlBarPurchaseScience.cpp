// cl: /DNDEBUG /MD /EHsc
// readable body of ?showPurchaseScience@ControlBar@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// readable body of ?togglePurchaseScience@ControlBar@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
//
// Opening the purchase-science window, at 0x004A2290 and 0x004A22F0. The two
// bodies are the same six lines with one prefix between them -- toggle first
// asks whether the window is already up and hides it if so -- and they used to
// sit in two files with two copies of the four classes they read through.
//
// The refusals are what the merge makes legible: no science window while the
// game is ending, none without a local player, and none for a player who has
// no purchase science to spend. Only then is the window populated, the general
// star stops flashing because the player has now looked, and the window is
// shown.

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
	void showPurchaseScience( void );
	void togglePurchaseScience( void );

protected:
	void populatePurchaseScience( Player *player );

private:
	unsigned char m_pad[ 0x2C8 ];
	Bool m_genStarFlash;
};

// ?showPurchaseScience@ControlBar@@QAEXXZ
// Retail 0x004A2290. Tail-jumps the window show helper.
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

// ?togglePurchaseScience@ControlBar@@QAEXXZ
// Retail 0x004A22F0. The visible window lives at 0x012F4C38, its visible byte
// at +0x259.
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
