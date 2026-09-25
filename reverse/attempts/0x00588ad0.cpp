// ?select@Rva00588AD0Selection@@QAEXH@Z
// partial score=0.26241135 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Source/GameClient

// The dump boundary and indexed record layout are known, but the owning class
// is not. Keep the address in the type so this implementation makes no owner
// identity claim.

typedef unsigned int WindowMsgData;

#include "game_window.h"

// The retail helper at 0x00478CA0 is a thiscall getter: mov eax,[ecx+34]; ret.
class Rva00478CA0Window
{
public:
	int getId();
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

class Rva00579160Manager
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

extern Rva00579160Manager *Rva00579160TheManager;
extern GameWindowManager *TheWindowManager;
extern ControlBar *TheControlBar;
extern void __cdecl bfmeNamedAudio0046F1A0(const char *name);
extern const char Rva0110BA90[];
extern const char Rva0110BAC0[];

class Rva00588AD0Selection
{
public:
	void select(int index);

private:
	char m_unmodelled00[0x2c];
	GameWindow *m_window;
	char m_unmodelled30[0x8];
	int m_mode;
};

// Retail @ 0x00588AD0; the sole explicit argument is thiscall index.
void Rva00588AD0Selection::select(int index)
{
	Rva00588AD0Selection *record = (Rva00588AD0Selection *)
		(index * 0x20 + (unsigned int)this);
	GameWindow *window = record->m_window;
	if (window == 0)
		return;

	char *data = *(char **)((char *)record + 0x30);
	if (data == 0)
		return;

	int mode = record->m_mode;
	if (mode == 1 || mode == 2)
	{
		Rva00579160Manager *manager = Rva00579160TheManager;
		if (manager->m_windowMode != 2 || (*(unsigned int *)(data + 0x18) & 0x80000000) == 0)
		{
			bfmeNamedAudio0046F1A0(Rva0110BA90);
			return;
		}
	}

	WinInstanceData *instance = window->winGetInstanceData();
	if (instance == 0)
		return;

	TheControlBar->hideBuildTooltipLayout();
	GameWindow *owner = *(GameWindow **)((char *)instance + 0x14);
	int managerMode = Rva00579160TheManager->m_windowMode;
	TheWindowManager->winSendSystemMsg(owner, 0x4008 + (managerMode == 2),
		(WindowMsgData)window, (WindowMsgData)((Rva00478CA0Window *)window)->getId());

	// winSendSystemMsg is an unknown callback boundary. Retail reloads the
	// record fields after it returns instead of trusting the pre-call values.
	mode = record->m_mode;
	if (mode == 4)
	{
		managerMode = Rva00579160TheManager->m_windowMode;
		data = *(char **)((char *)record + 0x30);
		const char *sound = Rva0110BA90;
		if (managerMode == 2 && *(unsigned char *)(data + 0x158) != 0)
			sound = Rva0110BAC0;
		else
			sound = Rva0110BA90;
		bfmeNamedAudio0046F1A0(sound);
	}
	else if (mode == 1 || mode == 2)
	{
		bfmeNamedAudio0046F1A0(Rva0110BAC0);
	}
}
