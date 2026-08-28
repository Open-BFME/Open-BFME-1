// cl: /DNDEBUG /DWIN32 /MD /O2
// Open-BFME5: update the live DisconnectScreen.apt layout when present.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void destroy();
	virtual void hide(bool hidden);
	virtual void runUpdate(void *context);
};

extern WindowLayout *_disconnectMenuLayout;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	void _bfme_updateScreen();
};

// @?_bfme_updateScreen@DisconnectMenu@@QAEXXZ 0x0050E5F0
void DisconnectMenu::_bfme_updateScreen()
{
	if (_disconnectMenuLayout != 0)
		_disconnectMenuLayout->runUpdate(0);
}
