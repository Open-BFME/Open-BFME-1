// cl: /DNDEBUG /MD /EHsc
// ControlBar::showPurchaseScience, retail 0x004A2290. Tail-jumps the window
// show helper after populatePurchaseScience.

typedef int Int;
typedef bool Bool;

class Player
{
public:
	Bool hasPurchaseScience( void );
};

class PlayerList
{
public:
	Player *getLocalPlayer( void ) { return m_localPlayer; }

private:
	unsigned char m_pad[ 0x0C ];
	Player *m_localPlayer;
};

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
