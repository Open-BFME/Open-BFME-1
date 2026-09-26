// cl: /O2 /Ob0

// Five small BFME-only gadget helpers, all of which do the same thing: take a
// GameWindow, pull its user data with winGetUserData, and poke one field.
//
//   GadgetListBoxSetColumnWidths        0x004B83B0  187 B
//   Rva004B7A10SetScrollButtonsHidden   0x004B7A10  130 B
//   Rva004BCB20                         0x004BCB20   60 B
//   gen004BC7E0                         0x004BC7E0  114 B
//   Rva004B5B30::set                    0x004B5B30   50 B
//
// Five files, five GameWindows, each declaring only the accessors its own body
// called -- winGetUserData in all five, and then winSetUserData and
// winSetStatus in one, winGetStatus in another, winIsHidden and winHide in a
// third. One declaration carries all six now, at the same signatures each file
// had proved.
//
// The listbox user data was two structs in two files and is one here: the
// column setter knew the count at +2 and the width buffer at +4, the scroll
// helper knew the three child windows at +0x1c, +0x20 and +0x24, and neither
// contradicted the other.
//
// The other three user-data views stay separate types on purpose -- they are
// not the same object. Rva004BCB20 builds PUSH BUTTON data (it calls
// getNewPushButtonData when the window has none), gen004BC7E0 reads a nested
// pointer at +0x14 with its flag word at +0x18, and Rva004B5B30::set works on
// a window it owns rather than one it is handed. Same accessor, different
// records behind it.
//
// The file is /O2 /Ob0 like every body in it: inline expansion is off, which
// is what keeps the five bodies from folding into each other now that they
// share a translation unit.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
	void winSetUserData(void *data);
	unsigned int winGetStatus(void);
	void winSetStatus(unsigned int status);
	bool winIsHidden(void);
	int winHide(bool hide);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetListBox.h
struct GadgetListboxData
{
	unsigned char m_prefix[2];
	unsigned short m_columns;				// +0x02
	int *m_columnWidth;					// +0x04
	char m_pad08[0x1c - 8];
	GameWindow *m_upButton;					// +0x1c
	GameWindow *m_downButton;				// +0x20
	GameWindow *m_slider;					// +0x24
};

// Push-button data: the same accessor, a different record.
struct _PushButtonData
{
};

extern _PushButtonData *getNewPushButtonData(void);

struct Rva004BCB20Data
{
	char m_prefix[0x24];
	int m_value;						// +0x24
};

struct Rva004BC7E0NestedData
{
	char m_prefix[0x18];
	int m_value;						// +0x18
};

struct Rva004BC7E0UserData
{
	char m_prefix[0x14];
	Rva004BC7E0NestedData *m_nested;			// +0x14
};

struct Rva004B5B30GlobalData
{
	char m_prefix[0x30];
	int m_scale;						// +0x30
};

extern Rva004B5B30GlobalData *TheGlobalData;

struct Rva004B5B30UserData
{
	int m_value;
};

class Rva004B5B30
{
	GameWindow *m_window;

public:
	void set(int value);
};

void f_00881ef0(void *memory);
extern void *__cdecl operator new[](unsigned int size);

void j_000272fa(void);
void j_00002e0f(void);
void j_00011f54(void);
typedef void (__cdecl *Rva004BC7E0StringCall)(void *stringData);
typedef void (__cdecl *Rva004BC7E0ForwardCall)(void *self, void *event,
	void *arg2, void *arg3);

// ?GadgetListBoxSetColumnWidths@@YAXPAVGameWindow@@HPAH@Z
// BFME's column-width setter is an additive listbox helper: it replaces the
// width buffer, and with no widths supplied it spreads 100 across the columns
// and gives the remainder to the first few.
void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count, int *widths)
{
	if (count <= 0)
		return;
	if (listbox == 0)
		return;

	GadgetListboxData *data =
		(GadgetListboxData *)listbox->winGetUserData();
	if (data == 0)
		return;

	data->m_columns = (unsigned short)count;
	f_00881ef0(data->m_columnWidth);
	data->m_columnWidth = new int[count];

	if (widths != 0)
	{
		for (int i = 0; i < count; ++i)
			data->m_columnWidth[i] = widths[i];
	}
	else
	{
		int each = 100 / count;
		int extra = 100 % count;
		for (int i = 0; i < count; ++i)
		{
			if (extra != 0)
			{
				--extra;
				data->m_columnWidth[i] = each + 1;
			}
			else
			{
				data->m_columnWidth[i] = each;
			}
		}
	}

	((void (__cdecl *)(GameWindow *))j_000272fa)(listbox);
}

// ?Rva004B7A10SetScrollButtonsHidden@@YAXPAVGameWindow@@_N@Z
void Rva004B7A10SetScrollButtonsHidden(GameWindow *window, bool hide)
{
	if (window != 0)
	{
		GadgetListboxData *data =
			(GadgetListboxData *)window->winGetUserData();
		GameWindow *child = data != 0 ? data->m_slider : 0;
		if (child != 0 && child->winIsHidden() != hide)
			child->winHide(hide);

		data = (GadgetListboxData *)window->winGetUserData();
		child = data != 0 ? data->m_upButton : 0;
		if (child != 0 && child->winIsHidden() != hide)
			child->winHide(hide);

		data = (GadgetListboxData *)window->winGetUserData();
		child = data != 0 ? data->m_downButton : 0;
		if (child != 0 && child->winIsHidden() != hide)
			child->winHide(hide);
	}
}

// ?Rva004BCB20@@YAXPAVGameWindow@@H@Z
// The one helper that CREATES the user data rather than assuming it: a window
// with none gets fresh push-button data before the field is written.
void Rva004BCB20(GameWindow *window, int value)
{
	if (window != 0)
	{
		Rva004BCB20Data *data =
			(Rva004BCB20Data *)window->winGetUserData();
		if (data == 0)
		{
			data = (Rva004BCB20Data *)getNewPushButtonData();
			window->winSetUserData(data);
		}
		data->m_value = value;
		window->winSetStatus(0x02000000);
	}
}

// ?gen004BC7E0@@YAXPAX000@Z
// Retail 0x004BC7E0 is the explicit-this event body used by the forwarder at
// 0x00793E20. The event values and the two display-string constants are the
// only identity recovered for this address; the forwarded call remains the
// existing incremental-link thunk.
void gen004BC7E0(void *self, void *event, void *arg2, void *arg3)
{
	GameWindow *window = (GameWindow *)self;
	int eventCode = (int)event;
	if (window != 0)
	{
		switch (eventCode)
		{
		case 13:
			{
				if ((window->winGetStatus() & 8) != 0)
					((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8D4);
				else
				{
					Rva004BC7E0UserData *data =
						(Rva004BC7E0UserData *)window->winGetUserData();
					if (data != 0 && data->m_nested != 0)
					{
						if ((data->m_nested->m_value & 0x80000000) == 0)
							((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8A4);
						else
							((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8D4);
					}
					else
						((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8A4);
				}
				break;
			}
		case 5:
			if ((window->winGetStatus() & 8) != 0)
				((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8D4);
			else
				((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8A4);
			break;
		}
	}

forward:
	((Rva004BC7E0ForwardCall)j_00011f54)(self, event, arg2, arg3);
}

// ?set@Rva004B5B30@@QAEXH@Z
// Scales by the global at +0x30 over 768 -- a resolution-independent position
// written into the window this object owns.
void Rva004B5B30::set(int value)
{
	if (m_window != 0)
	{
		Rva004B5B30UserData *data =
			(Rva004B5B30UserData *)m_window->winGetUserData();
		data->m_value = (TheGlobalData->m_scale * value) / 768;
	}
}
