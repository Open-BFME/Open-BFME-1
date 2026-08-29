// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void winHide(bool hide);
};

struct Rva505C80WindowVisibilityThunk
{
	void updateVisibility();
	void setState(bool enabled);

	unsigned char unused000[0x264];
	GameWindow *finalWindow;
	unsigned char unused268[0x24];
	GameWindow *firstWindow;
	void *unused290;
	GameWindow *secondWindow;
	void *unused298;
	GameWindow *fourthWindow;
	void *unused2a0;
	GameWindow *thirdWindow;
};

// ?updateVisibility@Rva505C80WindowVisibilityThunk@@ absent-from-retail
void Rva505C80WindowVisibilityThunk::updateVisibility()
{
	firstWindow->winHide(true);
	secondWindow->winHide(true);
	thirdWindow->winHide(true);
	fourthWindow->winHide(true);
	setState(false);
	finalWindow->winHide(false);
}
