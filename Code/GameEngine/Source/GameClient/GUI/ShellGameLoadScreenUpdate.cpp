// cl: /DNDEBUG /MD
// readable body of ?update@ShellGameLoadScreen@@UAEXH@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
//
// Retail 0x00491550: ShellGameLoadScreen::update(Int percent).  Named by
// vtable 0x010F9B0C slot 1 beside the already-matched
// ?init@ShellGameLoadScreen@@ at slot 2 (0x004920E0).  The same vtable
// cluster holds LoadScreen / MultiPlayer / GameSpy / MapTransfer, each
// with update(Int) at +0x04.  Body is ZH LoadScreen.cpp:1275 without the
// tooltip (LoadScreen::update already clears it) and with m_progressBar
// at +0x10 on BFME's 0x10-byte LoadScreen base.
//
// 0x00491550 was previously claimed as W3DTerrainLogic::newMap by pinning
// ILT 0x00021B7A as bfme_loadRoadsAndBridges and ILT 0x00003FE4 as
// TerrainLogic::newMap.  Those ILTs are GadgetProgressBarSetProgress and
// LoadScreen::update.

class GameWindow;

void GadgetProgressBarSetProgress( GameWindow *g, int progress );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class LoadScreen
{
public:
	virtual void update( int percent );

private:
	unsigned char m_unmodelled_04[0x0C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class ShellGameLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );

private:
	GameWindow *m_progressBar;						// this+0x10
};

void ShellGameLoadScreen::update( int percent )
{
	GadgetProgressBarSetProgress( m_progressBar, percent );
	LoadScreen::update( percent );
}
