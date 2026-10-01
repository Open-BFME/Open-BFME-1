// cl: /DNDEBUG /MD /EHsc
// GadgetListboxCreateScrollbar, retail 0x004B7350 / 879 bytes (ret +0x36E).
// The matched listbox factory at 0x0047D150 calls it through ILT 0x000194A7
// only when the listbox scrollbar flag is set; the body is the Zero Hour
// routine (GadgetListBox.cpp) on BFME's window-manager API, whose push-button
// and slider factories take one creation record instead of six arguments,
// and whose button sizes scale with the display resolution.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameFont;
class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();
	void init();

	UnsignedInt m_id;						// +0x04
	UnsignedInt m_state;					// +0x08
	UnsignedInt m_style;					// +0x0c
	UnsignedInt m_status;					// +0x10
	GameWindow *m_owner;					// +0x14
	unsigned char m_unmodelled018[0x1a8 - 0x18];
};

// The forwarding thunk the retail body calls for init().
class WinInstanceDataInitThunk
{
public:
	void forward();
};

class Rva00478520
{
public:
	Int call();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData();
	UnsignedInt winGetStatus();
	Int winGetSize(Int *width, Int *height);
	GameFont *winGetFont();
	UnsignedInt winGetStyle();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetListBox.h
struct ListboxData
{
	unsigned char m_unmodelled00[0xa];
	Bool scrollBar;						// +0x0a
	unsigned char m_unmodelled0b[0x1c - 0xb];
	GameWindow *upButton;					// +0x1c
	GameWindow *downButton;					// +0x20
	GameWindow *slider;					// +0x24
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetSlider.h
struct SliderData
{
	Int minVal;
	Int maxVal;
	float numTicks;
	Int position;
};

// BFME gadget creation record: ZH's six leading factory arguments, six
// unwitnessed words, then the instance data.
struct GadgetCreate004B7350
{
	GameWindow *parent;					// +0x00
	UnsignedInt status;					// +0x04
	Int x;							// +0x08
	Int y;							// +0x0c
	Int width;						// +0x10
	Int height;						// +0x14
	Int unwitnessed18[6];					// +0x18
	WinInstanceData *instData;				// +0x30

	GadgetCreate004B7350(Int w, Int h)
	{
		width = w;
		parent = 0;
		status = 0;
		x = 0;
		y = 0;
		unwitnessed18[0] = 0;
		unwitnessed18[1] = 0;
		unwitnessed18[2] = 0;
		unwitnessed18[3] = 0;
		unwitnessed18[4] = 0;
		unwitnessed18[5] = 0;
		instData = 0;
		height = h;
	}
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual GameWindow *slot14PushButton(GadgetCreate004B7350 *create, void *data, Bool defaultVisual);
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual GameWindow *slot20Slider(GadgetCreate004B7350 *create, SliderData *data, void *unused, Bool defaultVisual);
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59(); virtual void slot60();
	virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66();
	virtual Int winFontHeight(GameFont *font);
};
extern GameWindowManager *TheWindowManager;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva004BCB20GlobalDataView
{
	unsigned char m_unmodelled00[0x2c];
	Int m_xResolution;					// +0x2c
	Int m_yResolution;					// +0x30
};

static inline const Rva004BCB20GlobalDataView *scrollbarGlobalData()
{
	return (const Rva004BCB20GlobalDataView *)TheWritableGlobalData;
}

void Rva004BCB20(GameWindow *window, Int value);

enum
{
	WIN_STATUS_ACTIVE = 0x1,
	WIN_STATUS_ENABLED = 0x8,
	WIN_STATUS_HIDDEN = 0x10,
	WIN_STATUS_IMAGE = 0x80,
	WIN_STATUS_BORDER = 0x200,
	WIN_STATUS_NO_INPUT = 0x1000,
	GWS_PUSH_BUTTON = 0x1,
	GWS_VERT_SLIDER = 0x8,
	GWS_MOUSE_TRACK = 0x400,
};

void GadgetListboxCreateScrollbar(GameWindow *listbox)
{
	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	WinInstanceData winInstData;
	SliderData sData = { 0 };
	Int fontHeight;
	Int top;
	Int bottom;
	UnsignedInt status = listbox->winGetStatus();
	Bool title = false;
	Int width, height;

	listbox->winGetSize(&width, &height);
	if (((Rva00478520 *)listbox)->call())
		title = true;

	status &= ~(WIN_STATUS_BORDER | WIN_STATUS_HIDDEN | WIN_STATUS_NO_INPUT);

	fontHeight = TheWindowManager->winFontHeight(listbox->winGetFont());
	top = title ? (fontHeight + 1) : 0;
	bottom = title ? (height - (fontHeight + 1)) : height;

	((WinInstanceDataInitThunk *)&winInstData)->forward();

	GadgetCreate004B7350 button(21, 22);
	const Rva004BCB20GlobalDataView *gd = scrollbarGlobalData();
	button.width = gd->m_xResolution * 21 / 1024;
	button.height = gd->m_yResolution * 22 / 768;

	status |= WIN_STATUS_IMAGE;
	winInstData.m_owner = listbox;
	winInstData.m_style = GWS_PUSH_BUTTON;
	if (listbox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	button.parent = listbox;
	button.status = status |= WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED;
	button.x = width - button.width - 2;
	button.y = top + 2;
	button.instData = &winInstData;
	listData->upButton = TheWindowManager->slot14PushButton(&button, 0, true);

	((WinInstanceDataInitThunk *)&winInstData)->forward();
	winInstData.m_style = GWS_PUSH_BUTTON;
	winInstData.m_owner = listbox;
	if (listbox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	button.y = top + bottom - button.height - 2;
	listData->downButton = TheWindowManager->slot14PushButton(&button, 0, true);

	GadgetCreate004B7350 slide(button.width, 0);
	slide.height = bottom - (2 * button.height) - 6;
	((WinInstanceDataInitThunk *)&winInstData)->forward();
	winInstData.m_style = GWS_VERT_SLIDER;
	winInstData.m_owner = listbox;
	if (listbox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	memset(&sData, 0, sizeof(SliderData));

	slide.parent = listbox;
	slide.status = status;
	slide.x = width - slide.width - 2;
	slide.y = top + button.height + 3;
	slide.instData = &winInstData;
	listData->slider = TheWindowManager->slot20Slider(&slide, &sData, 0, true);

	Rva004BCB20(listData->upButton, 150);
	Rva004BCB20(listData->downButton, 150);

	listData->scrollBar = true;
}
