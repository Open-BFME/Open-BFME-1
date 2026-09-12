// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/controlbarvtables /Ireference/shims/controlbarlayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Full retail body: RVA 0x0049E780, 1254 bytes through ret 8.
// The 46-byte COFF trailer contains hotpatch padding and 11 switch targets.
// ILT 0x000329D4 names this entry; the retired 0x0049E901 row was interior.
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ControlBar.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Context sensitive command interface
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:
#define DEFINE_GUI_COMMMAND_NAMES
#define DEFINE_COMMAND_OPTION_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES
#define DEFINE_RADIUSCURSOR_NAMES

#include "Common/ActionManager.h"
#include "Common/GameType.h"
#include "Common/MultiplayerSettings.h"
#include "Common/NameKeyGenerator.h"
#include "Common/OVERRIDE.h"
#include "Common/PlayerTemplate.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Upgrade.h"
#include "Common/Recorder.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/ScriptEngine.h"

#include "GameClient/AnimateWindowManager.h"
#include "GameClient/ControlBar.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/Drawable.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/InGameUI.h"
#include "GameClient/WindowVideoManager.h"
#include "GameClient/ControlBarResizer.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/HotKey.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GUICallbacks.h"

#include "GameNetwork/GameInfo.h"

// BFME's InGameUI vtable puts setGUICommand at slot 46; the ZH header lands it
// at 37, so the tail call comes out [eax+0x94] instead of [eax+0xb8]. Only the
// one slot is named; the rest stay anonymous because nothing here needs them.
class BFMERetailInGameUIVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void setGUICommand(const void *cmd) = 0;
};


// The BFME object grew two context-parent slots and moved the selected-draw
// state one word past the Zero Hour layout.  Keep this view local to the
// reconstruction so the real ControlBar header remains untouched.
struct BfmeContextSwitchControlBarView
{
	char pad00[0x34];
	GameWindow *contextParent[10];
	Drawable *currentSelectedDrawable;
	ControlBarContext currContext;
	char pad64[0x9c];
	GameWindow *commandWindows[20];
	char pad150[0x1a0];
	void *contextOverlay;
};

struct BfmeContextSwitchSelectionState
{
	void *chat;
	Drawable *oldSelected;
};

class BfmeSourceCB
{
public:
	char m_bfmeHead[0x74];
	int m_bfmeValue;
};

class Gen_004AFA80
{
public:
	void bfmeTake(BfmeSourceCB *source);

private:
	int m_bfmeHead[7];
	int m_bfmeValue;
};

struct BfmeContextSwitchDrawableView
{
	char pad00[0xfc];
	BfmeSourceCB *object;
};

// Calls in the context arms are deliberately declaration-only.  This keeps
// each retail call boundary visible to the compiler instead of inlining an
// already-converted sibling body into this large dispatcher.
extern void j_0000d495(void);
extern void j_0000efe8(void);
extern void j_0001df4d(void);
extern void j_00034581(void);
class Rva0049E780Calls {
public:
    void commandSignature(Object *, Bool);
    void multiSignature(void);
    __forceinline void populateCommand(Object *object, Bool refresh) {
        typedef void (Rva0049E780Calls::*Method)(Object *, Bool);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_0000d495;
        (this->*call.member)(object, refresh);
    }
    __forceinline void populateStructureInventory(Object *object, Bool refresh) {
        typedef void (Rva0049E780Calls::*Method)(Object *, Bool);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_0001df4d;
        (this->*call.member)(object, refresh);
    }
    __forceinline void populateOCLTimer(Object *object) {
        typedef void (Rva0049E780Calls::*Method)(Object *);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_00034581;
        (this->*call.member)(object);
    }
    __forceinline void populateMultiSelect(void) {
        typedef void (Rva0049E780Calls::*Method)(void);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_0000efe8;
        (this->*call.member)();
    }
};

class BfmeContextSwitchBfmeTransitionMD
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
};

class BfmeContextSwitchInGameUI : public BFMERetailInGameUIVTable
{
public:
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void slot57(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot59(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot61(void) = 0;
	virtual void slot62(void) = 0;
	virtual void slot63(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot65(void) = 0;
	virtual void slot66(void) = 0;
	virtual void slot67(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot69(void) = 0;
	virtual void slot70(void) = 0;
	virtual void setRadiusCursorNone(void) = 0;
};

class BfmeContextSwitchOverlaySink
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
};

class BfmeContextSwitchGameLogicView
{
public:
	char pad00[0x10c];
	Int mode;
};

class Rva0058C040
{
public:
	void invoke(void);
};

extern void j_00018f2f(void);
extern void j_0003367c(void);

class BfmeTransitionMD;
class Rva005127A0InGameChat;
class Glo012F4B98Type;
extern BfmeTransitionMD *g_bfmeTransitionMD;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;
extern void *g_obj12F4C38;
extern Glo012F4B98Type *Glo012F4B98;
// No recovered source name exists for this retail selection cache.
extern volatile Drawable *g_Rva012F340C;
#define BFME_CONTEXT_TRANSITION ((BfmeContextSwitchBfmeTransitionMD *)g_bfmeTransitionMD)
#define BFME_CONTEXT_INGAME_UI ((BfmeContextSwitchInGameUI *)TheInGameUI)
#define BFME_CONTEXT_IN_GAME_CHAT g_Rva005127A0InGameChat
#define BFME_CONTEXT_OBJECT_12F4C38 g_obj12F4C38
#define BFME_CONTEXT_GAME_LOGIC ((BfmeContextSwitchGameLogicView *)TheGameLogic)
#define BFME_CONTEXT_GLO_12F4B98 ((Rva0058C040 *)Glo012F4B98)
#define BFME_CONTEXT_SELECTION_CACHE g_Rva012F340C

void ControlBar::switchToContext(ControlBarContext context, Drawable *draw)
{
	BfmeContextSwitchControlBarView *self = (BfmeContextSwitchControlBarView *)this;
	ControlBarContext incomingContext = context;
	Drawable *incomingDraw = draw;
	Bool changed;
	if (incomingContext == self->currContext)
	{
		changed = false;
		if (incomingDraw != self->currentSelectedDrawable)
			changed = true;
	}
	else
	{
		changed = true;
	}

	Object *drawObject = incomingDraw ? (Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object : 0;

	BfmeContextSwitchBfmeTransitionMD *transition = BFME_CONTEXT_TRANSITION;
	if (transition != 0)
		transition->slot04();
	BfmeContextSwitchInGameUI *inGameUI = BFME_CONTEXT_INGAME_UI;
	inGameUI->setRadiusCursorNone();

	if (incomingDraw != BFME_CONTEXT_SELECTION_CACHE &&
		incomingDraw != self->currentSelectedDrawable)
		((BfmeContextSwitchOverlaySink *)self->contextOverlay)->slot04();

	BfmeContextSwitchSelectionState state;
	state.oldSelected = self->currentSelectedDrawable;
	self->currentSelectedDrawable = incomingDraw;
	state.chat = BFME_CONTEXT_IN_GAME_CHAT;
	if (state.chat == 0)
	{
		BFME_CONTEXT_SELECTION_CACHE = state.oldSelected;
		if (BFME_CONTEXT_OBJECT_12F4C38 == 0 && BFME_CONTEXT_GAME_LOGIC != 0 &&
			BFME_CONTEXT_GAME_LOGIC->mode != 8 && BFME_CONTEXT_GAME_LOGIC->mode != 4)
			TheWindowManager->winSetFocus(0);
	}
	else
	{
		BFME_CONTEXT_SELECTION_CACHE = state.oldSelected;
	}

	((Gen_004AFA80 *)self->contextOverlay)->bfmeTake((BfmeSourceCB *)drawObject);
	showRallyPoint(0);

	switch ((Int)incomingContext)
	{
	case 0:
	case 4:
		if (BFME_CONTEXT_GLO_12F4B98 != 0)
			((Rva0058C040 *)BFME_CONTEXT_GLO_12F4B98)->invoke();
		self->contextParent[2]->winHide(true);
		self->contextParent[9]->winHide(true);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		{
			GameWindow **window = self->commandWindows;
			Int count = 20;
			do
			{
				if (*window != 0)
					(*window)->winClearStatus(0x800000);
				++window;
				--count;
			} while (count != 0);
		}
		break;

	case 1:
		self->contextParent[2]->winHide(false);
		self->contextParent[9]->winHide(false);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		((Rva0049E780Calls *)this)->populateCommand((Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object, changed);
		break;

	case 2:
		if (BFME_CONTEXT_GLO_12F4B98 != 0)
			((Rva0058C040 *)BFME_CONTEXT_GLO_12F4B98)->invoke();
		self->contextParent[2]->winHide(false);
		self->contextParent[9]->winHide(false);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		((Rva0049E780Calls *)this)->populateStructureInventory((Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object, false);
		break;
	case 3:
		if (BFME_CONTEXT_GLO_12F4B98 != 0)
			((Rva0058C040 *)BFME_CONTEXT_GLO_12F4B98)->invoke();
		self->contextParent[2]->winHide(false);
		self->contextParent[9]->winHide(false);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		((Rva0049E780Calls *)this)->populateStructureInventory((Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object, true);
		break;
	case 5:
		if (BFME_CONTEXT_GLO_12F4B98 != 0)
			((Rva0058C040 *)BFME_CONTEXT_GLO_12F4B98)->invoke();
		self->contextParent[2]->winHide(true);
		self->contextParent[9]->winHide(true);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(false);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		populateBeacon((Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object);
		break;
	case 6:
		self->contextParent[2]->winHide(true);
		self->contextParent[9]->winHide(false);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		populateUnderConstruction((Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object);
		break;
	case 10:
		if (BFME_CONTEXT_GLO_12F4B98 != 0)
			((Rva0058C040 *)BFME_CONTEXT_GLO_12F4B98)->invoke();
		self->contextParent[2]->winHide(true);
		self->contextParent[9]->winHide(true);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(false);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		((Rva0049E780Calls *)this)->populateOCLTimer((Object *)((BfmeContextSwitchDrawableView *)incomingDraw)->object);
		break;

	case 7:
		self->contextParent[2]->winHide(false);
		self->contextParent[9]->winHide(false);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(true);
		((Rva0049E780Calls *)this)->populateMultiSelect();
		break;
	case 9:
		if (BFME_CONTEXT_GLO_12F4B98 != 0)
			((Rva0058C040 *)BFME_CONTEXT_GLO_12F4B98)->invoke();
		self->contextParent[2]->winHide(true);
		self->contextParent[9]->winHide(true);
		self->contextParent[3]->winHide(true);
		self->contextParent[4]->winHide(true);
		self->contextParent[5]->winHide(true);
		self->contextParent[8]->winHide(true);
		self->contextParent[6]->winHide(true);
		self->contextParent[7]->winHide(false);
		populateObserverList();
		break;
	default:
		break;
	}

	self->currContext = incomingContext;
}