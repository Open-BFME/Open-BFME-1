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

// Own TU rather than an edit to the 83 KB GadgetListBox.cpp, which carries
// many matched rows and whose $L labels other gen-funclet rows depend on.
//
// Retail inlines GadgetListBoxGetBottomVisibleEntry into this body: the outer
// null check on `window` folds away, but the inner winGetUserData() call is
// re-issued (0x004B8564) and its null branch duplicates the whole
// adjustDisplay tail with `sub ecx, eax` against a zero eax. That duplicated
// tail is what identifies the inlined helper.

struct _ListboxData;
typedef struct _ListboxData ListboxData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData();
};

// 0x004B6BA0 opens with `movsx eax, word ptr [ecx+0x2c]`, and this call site
// is `mov ecx, eax` / `call` with no push and no stack cleanup: the helper is
// static in retail's GadgetListBox.cpp and MSVC 7.1 gave it a register
// convention. __fastcall is the only spelling that reproduces that, so the pin
// carries the __fastcall decoration (YI) of the same 0x004B6BA0 body the
// existing ?getListboxBottomEntry@@YAHPAU_ListboxData@@@Z row already claims.
int __fastcall getListboxBottomEntry(ListboxData *listData);

// The general 3-argument overload at 0x004B7CA0 (3 pushes + `add esp, 0xc`),
// distinct from the BFME-only 2-argument ?adjustDisplay@@YAXPAVGameWindow@@_N@Z
// at 0x004B7B20.
void adjustDisplay(GameWindow *window, int adjustment, bool useSlider);

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
