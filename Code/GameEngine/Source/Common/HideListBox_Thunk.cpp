// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData();
	bool winIsHidden();
	int winHide(int hide);
	int winGetSize(int *width, int *height);
	int winSetSize(int width, int height);
};

struct ComboBoxData
{
	unsigned char m_pad[0x28];
	GameWindow *editBox;
	GameWindow *listBox;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46();
	virtual void winSetFocus(GameWindow *window);
	virtual GameWindow *winGetFocus();
};

extern GameWindowManager *TheWindowManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x, y;
};

static __forceinline GameWindow *getListBox(GameWindow *window)
{
	ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
	return data ? data->listBox : 0;
}

static __forceinline GameWindow *getEditBox(GameWindow *window)
{
	ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
	return data && data->editBox ? data->editBox : 0;
}

// ?HideListBox@@YAXPAVGameWindow@@@Z
void HideListBox(GameWindow *window)
{
	ICoord2D winSize;
	ICoord2D newSize;
	GameWindow *listBox = getListBox(window);
	if (!listBox)
		return;

	if (!listBox->winIsHidden())
	{
		listBox->winHide(1);
		GameWindow *editBox = getEditBox(window);
		editBox->winGetSize(&winSize.x, &winSize.y);
		window->winGetSize(&newSize.x, &newSize.y);
		window->winSetSize(newSize.x, winSize.y);
		if (TheWindowManager->winGetFocus() == window)
			TheWindowManager->winSetFocus(0);
	}
}
