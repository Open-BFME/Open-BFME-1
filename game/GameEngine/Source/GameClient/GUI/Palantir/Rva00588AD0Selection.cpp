// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail 0x00588AD0 (282 bytes, ret 4) handles a click on one of the
// Palantir command-button records.  Its only caller is the offset tail thunk
// Rva005896F0::invoke, so the owner and method keep address-derived names.

typedef unsigned int WindowMsgData;

class GameWindow;

class WinInstanceData
{
public:
	char m_pad[0x14];
	GameWindow *m_owner;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	int winGetWindowId();
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52();
	virtual int winSendSystemMsg(GameWindow *window, unsigned int message,
		WindowMsgData data1, WindowMsgData data2);
};

struct Rva00579160Manager
{
public:
	char m_unmodelled[0x1b4];
	int m_windowMode;
};

class ControlBar
{
public:
	void hideBuildTooltipLayout();
};

class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
extern GameWindowManager *TheWindowManager;
extern ControlBar *TheControlBar;
extern void __cdecl bfmeNamedAudio0046F1A0(const char *name);

struct Rva00588AD0Record
{
	GameWindow *m_window;
	char *m_data;
	int m_unknown08;
	int m_mode;
	char m_unknown10[0x10];
};

class Rva00588AD0Selection
{
public:
	void select(int index);

private:
	char m_unmodelled00[0x2c];
	Rva00588AD0Record m_records[1];
};

void Rva00588AD0Selection::select(int index)
{
	GameWindow *window = m_records[index].m_window;
	if (window == 0)
		return;

	char *data = m_records[index].m_data;
	if (data == 0)
		return;

	int mode = m_records[index].m_mode;
	if (mode == 1 || mode == 2)
	{
		Rva00579160Manager *manager = reinterpret_cast<Rva00579160Manager *>(g_rva012F19E8WindowManager);
		if (manager->m_windowMode != 2 || (*(unsigned int *)(data + 0x18) & 0x80000000) == 0)
		{
			bfmeNamedAudio0046F1A0("Gui_PalantirCommandButtonDisabledClick");
			return;
		}
	}

	WinInstanceData *instance = window->winGetInstanceData();
	if (instance == 0)
		return;

	TheControlBar->hideBuildTooltipLayout();
	int managerMode = reinterpret_cast<Rva00579160Manager *>(g_rva012F19E8WindowManager)->m_windowMode;
	GameWindow *owner = instance->m_owner;
	TheWindowManager->winSendSystemMsg(owner, 0x4008 + (managerMode == 2),
		(WindowMsgData)window, (WindowMsgData)window->winGetWindowId());

	// winSendSystemMsg can change the records, so retail reloads them.
	mode = m_records[index].m_mode;
	if (mode == 4)
	{
		const char *sound;
		if (reinterpret_cast<Rva00579160Manager *>(g_rva012F19E8WindowManager)->m_windowMode == 2 &&
			*(unsigned char *)(m_records[index].m_data + 0x158) != 0)
			sound = "Gui_PalantirCommandButtonClick";
		else
			sound = "Gui_PalantirCommandButtonDisabledClick";
		bfmeNamedAudio0046F1A0(sound);
	}
	else if (mode == 1 || mode == 2)
	{
		bfmeNamedAudio0046F1A0("Gui_PalantirCommandButtonClick");
	}
}
