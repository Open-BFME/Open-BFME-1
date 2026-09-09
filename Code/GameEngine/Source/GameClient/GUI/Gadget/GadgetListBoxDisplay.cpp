// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

// The listbox display position: the setter that moves it and the adjuster it
// moves it with.
//
//   adjustDisplay (3 arguments)         0x004B7CA0  135 B
//   GadgetListBoxSetBottomVisibleEntry  0x004B8550   80 B
//
// Caller and callee, in two files. Both are kept out of the 83 KB
// GadgetListBox.cpp, which carries many matched rows and whose $L labels other
// gen-funclet rows depend on -- that is why they are their own TU rather than
// an edit to it, and it is why they are ONE TU rather than two.
//
// Merging them is safe to do here because ?adjustDisplay@@YAXPAVGameWindow@@H_N@Z
// has exactly one pin, the body at 0x004B7CA0, with no thunk under a second
// spelling: the call resolves to the same address whether or not the callee
// shares the translation unit. (Where that is not true, a callee cannot join
// its caller -- see the findGroup note in
// Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsHandler.cpp.)
//
// The two files described the user data from opposite ends and neither
// contradicted the other: the adjuster knows the row array at +0x18, the entry
// count at +0x2c and the display height and position at +0x3c and +0x44, while
// the setter never opens the record at all and takes it as an opaque
// _ListboxData. Both spellings are kept, because the opaque one is what the
// __fastcall helper's pin is written against.
//

// Retail inlines GadgetListBoxGetBottomVisibleEntry into this body: the outer
// null check on `window` folds away, but the inner winGetUserData() call is
// re-issued (0x004B8564) and its null branch duplicates the whole
// adjustDisplay tail with `sub ecx, eax` against a zero eax. That duplicated
// tail is what identifies the inlined helper.


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData();
};

struct ListEntryRowBFME
{
	int listHeight;
	short rowTop;
	short unused6;
	void *cell;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetListBox.h
struct ListboxDataBFME
{
	char unused00[0x18];
	ListEntryRowBFME *listData;				// +0x18
	char unused1c[0x10];
	short endPos;						// +0x2c
	char unused2e[0x0e];
	short displayHeight;					// +0x3c
	char unused3e[6];
	short displayPos;					// +0x44
};

// The helper's static/private call convention is selected by its real callers,
// so keep the retail record spelling while opening only the fields it reads.
struct _ListboxData
{
	char unused00[0x18];
	ListEntryRowBFME *listData;
	char unused1c[0x10];
	short endPos;
	char unused2e[0x0e];
	short displayHeight;
	char unused3e[6];
	short displayPos;
};
typedef struct _ListboxData ListboxData;

// 0x004B6BA0 opens with `movsx eax, word ptr [ecx+0x2c]`, and the call site is
// `mov ecx, eax` / `call` with no push and no stack cleanup: the helper is
// static in retail's GadgetListBox.cpp and MSVC 7.1 gave it a register
// convention. A TU-local static definition lets the compiler select that
// convention from the actual callers, as it does for getListboxTopEntry.
static int getListboxBottomEntry(ListboxData *list)
{
	int entry;

	for (entry = list->endPos - 1; ; entry--)
	{
		if (entry < 0)
			return 0;
		if (list->listData[entry].listHeight == list->displayPos + list->displayHeight)
			return entry;
		if (list->listData[entry].listHeight < list->displayPos + list->displayHeight)
		{
			if (entry != list->endPos - 1)
				return entry + 1;
			return entry;
		}
	}
}

// The BFME-only 2-argument overload at 0x004B7B20, distinct from the general
// 3-argument one defined below.
void adjustDisplay(GameWindow *window, bool updateSlider);

void adjustDisplay(GameWindow *window, int adjustment, bool useSlider);

static int getListboxTopEntry(ListboxDataBFME *list)
{
	int entry;
	for (entry = 0; ; ++entry)
	{
		if (list->listData[entry].listHeight > list->displayPos)
			return entry;
		if (entry >= list->endPos)
			return 0;
	}
}

void adjustDisplay(GameWindow *window, int adjustment, bool updateSlider)
{
	ListboxDataBFME *list = (ListboxDataBFME *)window->winGetUserData();

	if (updateSlider)
	{
		int entry = getListboxTopEntry(list) + adjustment;
		if (entry < 0)
			entry = 0;
		else if (entry >= list->endPos)
			entry = list->endPos - 1;

		list->displayPos = list->listData[entry].listHeight - list->listData[entry].rowTop;
	}

	adjustDisplay(window, updateSlider);
}

static int GadgetListBoxGetBottomVisibleEntry(GameWindow *window)
{
	if (!window)
		return 0;

	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return 0;

	return getListboxBottomEntry(listData);
}

void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, int newPos)
{
	if (!window)
		return;

	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return;

	int prevPos = GadgetListBoxGetBottomVisibleEntry(window);

	adjustDisplay(window, newPos - prevPos + 1, true);
}
