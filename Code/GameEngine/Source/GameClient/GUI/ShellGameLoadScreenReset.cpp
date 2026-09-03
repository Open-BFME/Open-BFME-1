// cl: /DNDEBUG /MD
// readable body of ?reset@ShellGameLoadScreen@@UAEXXZ: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
//
// Retail 0x00490570: ShellGameLoadScreen::reset.  Named by vtable 0x010F9B0C
// slot 3 beside landed init (slot 2, 0x004920E0) and update (slot 1,
// 0x00491550).  Slot 3 is reset on the MultiPlayer/GameSpy/MapTransfer
// siblings too.  ZH LoadScreen.cpp:1269: setLoadScreen(NULL) and
// m_progressBar = NULL.  BFME stores those pointers at +0x08 and +0x10.

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class LoadScreen
{
public:
	virtual void reset();

protected:
	unsigned char m_unmodelled_04[4];
	GameWindow *m_loadScreen;					// this+0x08
	unsigned char m_ready;						// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class ShellGameLoadScreen : public LoadScreen
{
public:
	virtual void reset();

private:
	GameWindow *m_progressBar;					// this+0x10
};

void ShellGameLoadScreen::reset()
{
	m_loadScreen = 0;
	m_progressBar = 0;
}
