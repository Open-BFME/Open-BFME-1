// cl: /DNDEBUG /MD /EHsc

// What the control bar shows for the object the player has selected, and the
// command-button grid it shows it in:
//
//   updateContextOCLTimer          0x004AA980  188 B  AAE (private)
//   updateContextUnderConstruction 0x004AF660   48 B  IAE (protected)
//   resetContainData               0x004A3B00   59 B  IAE (protected)
//   doTransportInventoryUI         0x004A3E90  401 B  IAE (protected)
//   commandSetButtonWalk           0x004A0370   68 B  QAE (public)
//
// Five files, five ControlBars, each described from its own member outwards:
// one padded to +0x68 for the construct percent, one to +0x6C for the OCL
// timer seconds, one to +0x70 for the inventory count, one to +0x100 for the
// command windows, and one declared no members at all. None of them was wrong
// and none of them could show what the merged run shows -- that the three
// "what the user was last shown" fields are adjacent at +0x68, +0x6C and
// +0x70, updated by the same shape of test, and that the twenty command
// windows the transport UI fills are the same twenty resetContainData hides.
//
// Access is load-bearing here, and it is why the sections below are split
// three ways rather than tidied into one: the access letter is part of the
// mangled name the ledger pins. updateContextOCLTimer is AAE, private;
// updateContextUnderConstruction, resetContainData and doTransportInventoryUI
// are IAE, protected; commandSetButtonWalk is QAE, public. So are the callees
// -- findNonConstCommandSet is private and setControlCommand is public --
// because the call sites name them the same way.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { LOGICFRAMES_PER_SECOND = 5 };
enum { MAX_COMMANDS_PER_SET = 20 };

class BfmeTargetJB
{
public:
	bool bfmeTailJB(void);
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class Object;
class Image;
class ThingTemplate;
class ThingTemplatePortraitShim;
class OpenContain;

template <class Type>
class StringBase
{
private:
	StringBase(const char *s);
	StringBase(const StringBase &that);
	friend class UnicodeString;
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:

	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	AsciiString(const AsciiString &that);
	~AsciiString();

private:

	void *m_text;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

// Retail's inventory callback uses the matched BFME image selector with a
// ThingTemplate view and the contained Object view as its two arguments.
class ThingTemplate : public Overridable
{
};

const Image *_bfme_getSelectedPortraitImage(const ThingTemplatePortraitShim *portraitTemplate,
	const ThingTemplatePortraitShim *objectTemplate);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	void Rva0049B240();

	Int getCommandType() const
	{
		return *(const Int *)((const char *)this + 0x10);
	}

	Bool hasOverlayStatus() const
	{
		return *(const unsigned char *)((const char *)this + 0x14d) != 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet : public Overridable
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
// winHide and bfmeClose take the same argument and do the same job to the same
// window; each body names the one its own call site pins, and nothing here
// proves they are one function, so both stand.
class GameWindow
{
public:
	int winHide(bool hide);
	void bfmeClose(Bool hide);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
	Int winSetEnabledImage(Int index, const Image *image);
	Int winEnable(Bool enable);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
struct ContainEntry
{
	GameWindow *control;
	unsigned int objectID;
};

typedef void (*ContainIterateFunc)(Object *, void *);

class ContainModuleInterface
{
public:
	virtual OpenContain *asOpenContain() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
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
	virtual Int getContainMax() const = 0;			// slot 23, vtable+0x5c
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
	virtual Int getExtraSlotsInUse() = 0;			// slot 46, vtable+0xb8
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63(ContainIterateFunc, void *, Bool) = 0;
	virtual Int getContainCount(Bool countRiders) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdate
{
public:
	UnsignedInt getRemainingFrames(void);			// ILT 0x00032AA6
	Real getCountdownPercent(void);				// ILT 0x00047069
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	OCLUpdate *findUpdateModule(NameKeyType key);		// ILT 0x0002AE23

	const ThingTemplate *getTemplate(void) const
	{
		return *(const ThingTemplate *const *)((const char *)this + 4);
	}

	UnsignedInt getID(void) const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}

	Real getConstructionPercent(void) const
	{
		return *(const Real *)((const char *)this + 0x220);
	}

	bool testUnderConstruction(void) const
	{
		return (*(const unsigned char *)((const char *)this + 0x90) & 4) != 0;
	}

	ContainModuleInterface *getContain() const
	{
		return *(ContainModuleInterface *const *)((const char *)this + 0x1fc);
	}

	Bool isDisabledByType(Int type) const
	{
		return (*(const unsigned char *)((const char *)this + 0x1a4) & (1 << type)) != 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject(void) { return m_object; }

private:
	char m_slice_pad[0xFC];					// retail this+0x00 .. +0xFB, untouched
	Object *m_object;					// this+0xFC
};

enum Relationship { RELATIONSHIP_INVALID = 0 };

class Team;

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
};

class Rva002EE330PlayerList
{
private:
	char m_slice_pad[0x0C];

public:
	Player *m_localPlayer;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class BfmeStructureInventoryObject
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual Drawable *getDrawable(void) = 0;

	Team *getTeam(void) const
	{
		return *(Team *const *)((const char *)this + 0x23C);
	}

	ContainModuleInterface *getContain(void) const
	{
		return *(ContainModuleInterface *const *)((const char *)this + 0x1FC);
	}

	UnsignedInt getID(void) const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}
};

class GameMessage
{
public:
	enum Type { MSG_INVALID = 0, MSG_CONTEXT = 0x3EC };

	void appendObjectIDArgument(UnsignedInt objectID);
};

class MessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual GameMessage *appendMessage(GameMessage::Type type) = 0;
};

extern MessageStream *TheMessageStream;

class InGameUI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
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
	virtual void deselectDrawable(Drawable *draw) = 0;
};

extern InGameUI *TheInGameUI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			// 0x012ED600

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:

	UnicodeString() { m_text = 0; }

	// Visible delegation, so the by-value temporary is scheduled retail's way.
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}

	~UnicodeString();

	// Variadic member: MSVC compiles these __cdecl with this pushed first, and
	// the format string is a UnicodeString BY VALUE.
	void __cdecl format(UnicodeString fmt, ...);

private:

	void *m_text;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot000() = 0; virtual void slot001() = 0; virtual void slot002() = 0;
	virtual void slot003() = 0; virtual void slot004() = 0; virtual void slot005() = 0;
	virtual void slot006() = 0; virtual void slot007() = 0; virtual void slot008() = 0;
	virtual void slot009() = 0; virtual void slot010() = 0; virtual void slot011() = 0;
	virtual void slot012() = 0; virtual void slot013() = 0; virtual void slot014() = 0;
	virtual void slot015() = 0; virtual void slot016() = 0; virtual void slot017() = 0;
	virtual void slot018() = 0; virtual void slot019() = 0; virtual void slot020() = 0;
	virtual void slot021() = 0; virtual void slot022() = 0; virtual void slot023() = 0;
	virtual void slot024() = 0; virtual void slot025() = 0; virtual void slot026() = 0;
	virtual void slot027() = 0; virtual void slot028() = 0; virtual void slot029() = 0;
	virtual void slot030() = 0; virtual void slot031() = 0; virtual void slot032() = 0;
	virtual void slot033() = 0; virtual void slot034() = 0; virtual void slot035() = 0;
	virtual void slot036() = 0; virtual void slot037() = 0; virtual void slot038() = 0;
	virtual void slot039() = 0; virtual void slot040() = 0; virtual void slot041() = 0;
	virtual void slot042() = 0; virtual void slot043() = 0; virtual void slot044() = 0;
	virtual void slot045() = 0; virtual void slot046() = 0; virtual void slot047() = 0;
	virtual void slot048() = 0; virtual void slot049() = 0; virtual void slot050() = 0;
	virtual void slot051() = 0; virtual void slot052() = 0; virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *window, NameKeyType id ) = 0;	// slot 55, vtable+0xdc
};

class GameText
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;	// slot 10, vtable+0x28
};

extern GameWindowManager *TheWindowManager;
extern GameText *TheGameText;

void GadgetStaticTextSetText( GameWindow *window, UnicodeString text );
void GadgetProgressBarSetProgress( GameWindow *window, Int percent );

struct PopulateInvButtonData
{
	Int currIndex;
	Int maxIndex;
	GameWindow **controls;
	Object *transport;
};

class BfmeUnit1013
{
public:
	void bfmeStop1013(char enable);
};

void GadgetButtonDrawOverlayImage(GameWindow *window, const Image *image);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void commandSetButtonWalk(const AsciiString &name);
	void setControlCommand(GameWindow *window, const CommandButton *commandButton);
	void updateConstructionTextDisplay(Object *obj);
	void populateOCLTimer(Object *creatorObject);

private:
	void updateContextOCLTimer(void);
	CommandSet *findNonConstCommandSet(const AsciiString &name);
	const CommandButton *findCommandButton(const AsciiString &name);
	void setPortraitByObject(Object *obj);

protected:
	void updateOCLTimerTextDisplay(UnsignedInt secondsLeft, Real percentDone);
	void updateContextUnderConstruction(void);
	void updateContextStructureInventory(void);
	static void populateButtonProc(Object *obj, void *userData);
	static void populateInvDataCallback(Object *obj, void *userData);
	void populateStructureInventory(Object *building, Bool refresh);
	void evaluateContextUI(void);
	void resetContainData(void);
	void doTransportInventoryUI(Object *transport, const CommandSet *commandSet);
	static const Image *calculateVeterancyOverlayForObject(const Object *obj);

	char m_slice_pad[0x54];					// retail this+0x00 .. +0x53, untouched
	GameWindow *m_bfmeContextParentOclTimer;		// this+0x54, m_contextParent[CP_OCL_TIMER]
	char m_slice_padA[0x5C - 0x58];				// this+0x58 .. +0x5B, untouched
	Drawable *m_currentSelectedDrawable;			// this+0x5C
	char m_slice_padB[0x68 - 0x60];				// this+0x60 .. +0x67, untouched
	Real m_displayedConstructPercent;			// this+0x68
	UnsignedInt m_displayedOCLTimerSeconds;			// this+0x6C
	UnsignedInt m_lastRecordedInventoryCount;		// this+0x70
	char m_slice_padC[0x100 - 0x74];			// this+0x74 .. +0xFF, untouched
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];	// this+0x100

	static ContainEntry m_containData[MAX_COMMANDS_PER_SET];
};

#pragma comment(linker, "/alternatename:?populateStructureInventory@ControlBar@@IAEXPAVObject@@_N@Z=?j_0001df4d@@YAXXZ")

ContainEntry ControlBar::m_containData[MAX_COMMANDS_PER_SET];

// Retail registers this callback from populateStructureInventory at
// 0x004AEE00 through the 0x00049549 ILT.  The callback receives the contained
// Object first and the four-field iterator record second; its static table is
// the same 0x012F3448 table resetContainData/findContainedObject use.
struct PopulateButtonInfo
{
	Object *source;
	Int buttonIndex;
	ControlBar *self;
	GameWindow **inventoryButtons;
};

// ?populateButtonProc@ControlBar@@KAXPAVObject@@PAX@Z
void ControlBar::populateButtonProc(Object *obj, void *userData)
{
	PopulateButtonInfo *info = (PopulateButtonInfo *)userData;

	info->self->m_containData[info->buttonIndex].control =
		info->inventoryButtons[info->buttonIndex];
	info->self->m_containData[info->buttonIndex].objectID = obj->getID();

	const ThingTemplate *thingTemplate = obj->getTemplate();
	if (thingTemplate && thingTemplate->m_nextOverride)
	{
		thingTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
	}

	const Image *image = _bfme_getSelectedPortraitImage(
		(const ThingTemplatePortraitShim *)thingTemplate,
		(const ThingTemplatePortraitShim *)obj);
	GameWindow *control = info->inventoryButtons[info->buttonIndex];
	control->winSetEnabledImage(0, image);
	control->winSetEnabledImage(5, 0);
	control->winSetEnabledImage(6, 0);

	image = calculateVeterancyOverlayForObject(obj);
	GadgetButtonDrawOverlayImage(info->inventoryButtons[info->buttonIndex], image);
	info->inventoryButtons[info->buttonIndex]->winEnable(true);
	info->buttonIndex++;
}

// ControlBar::populateInvDataCallback, retail 0x004A3C70, 128 bytes.
// The transport iterator's retail thunk supplies the contained object first
// and the iterator record second.  The body reads the record before saving
// the object register, matching the callback ABI and retail stack shape.

// ?populateInvDataCallback@ControlBar@@KAXPAVObject@@PAX@Z
void ControlBar::populateInvDataCallback(Object *obj, void *userData)
{
	PopulateInvButtonData *data = (PopulateInvButtonData *)userData;

	if (data->currIndex > data->maxIndex)
		return;

	GameWindow *control = data->controls[data->currIndex];
	m_containData[data->currIndex].control = control;
	m_containData[data->currIndex].objectID = obj->getID();
	data->currIndex++;

	const ThingTemplate *thingTemplate = obj->getTemplate();
	if (thingTemplate && thingTemplate->m_nextOverride)
	{
		thingTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
	}

	const Image *image = _bfme_getSelectedPortraitImage(
		(const ThingTemplatePortraitShim *)thingTemplate,
		(const ThingTemplatePortraitShim *)obj);
	control->winSetEnabledImage(0, image);
	control->winSetEnabledImage(5, 0);
	control->winSetEnabledImage(6, 0);
	GadgetButtonDrawOverlayImage(control, 0);
	control->winEnable(true);
}

// Open-BFME: ControlBar::updateContextOCLTimer, retail 0x004AA980, 188 bytes.
//
// The reference's body with a guard around it: BFME checks that the selected
// drawable actually has an object before doing any of the work, which is what
// puts the function-local static's once-flag inside the test rather than at
// the top.
//
// The divisor is five, not the reference's thirty: the reciprocal multiply by
// 0xCCCCCCCD with a shift of two is a divide by five, and a shift of three
// would be the ten it looks like at a glance.
//
// The static key sits at 0x012F3624 behind the initialised-once bit at
// 0x012F3628.

// ?updateContextOCLTimer@ControlBar@@AAEXXZ
void ControlBar::updateContextOCLTimer( void )
{
	Object *obj = m_currentSelectedDrawable->getObject();

	if( obj )
	{
		static const NameKeyType key_OCLUpdate = NAMEKEY( "OCLUpdate" );
		OCLUpdate *update = (OCLUpdate*)obj->findUpdateModule( key_OCLUpdate );

		UnsignedInt frames = update->getRemainingFrames();
		UnsignedInt seconds = frames / LOGICFRAMES_PER_SECOND;

		Real percent = update->getCountdownPercent();

		// if the time has changed since what was last shown to the user update the text
		if( m_displayedOCLTimerSeconds != seconds )
			updateOCLTimerTextDisplay( seconds, percent );
	}

}  // end updateContextOCLTimer

// ?updateOCLTimerTextDisplay@ControlBar@@IAEXIM@Z
void ControlBar::updateOCLTimerTextDisplay( UnsignedInt totalSeconds, Real percent )
{
	UnicodeString text;
	static UnsignedInt descID = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:OCLTimerStaticText" );
	GameWindow *descWindow = TheWindowManager->winGetWindowFromId( 0, (NameKeyType)descID );

	static UnsignedInt barID = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:OCLTimerProgressBar" );
	GameWindow *barWindow = TheWindowManager->winGetWindowFromId( 0, (NameKeyType)barID );

	Int minutes = totalSeconds / 60;
	Int seconds = totalSeconds - (minutes * 60);
	if( seconds < 10 )
		text.format( TheGameText->fetch( "CONTROLBAR:OCLTimerDescWithPadding" ), minutes, seconds );
	else
		text.format( TheGameText->fetch( "CONTROLBAR:OCLTimerDesc" ), minutes, seconds );

	GadgetStaticTextSetText( descWindow, text );
	GadgetProgressBarSetProgress( barWindow, (Int)(percent * 100) );
	m_displayedOCLTimerSeconds = totalSeconds;
}

// ControlBar::updateContextUnderConstruction, retail 0x004AF660, 48 bytes.
// Twin: ControlBarUnderConstruction.cpp. BFME inlines the under-construction
// flag as a byte test at Object+0x90 bit 2, and the construction percent as
// the Real at Object+0x220.

// ?updateContextUnderConstruction@ControlBar@@IAEXXZ
void ControlBar::updateContextUnderConstruction(void)
{
	Object *obj = m_currentSelectedDrawable->getObject();

	if (!obj->testUnderConstruction())
	{
		evaluateContextUI();
		return;
	}

	if (m_displayedConstructPercent != obj->getConstructionPercent())
		updateConstructionTextDisplay(obj);
}

// ControlBar::updateContextStructureInventory, retail 0x004AF3D0, 151 bytes.
// The selected object leaves the local player's relationship unless it is
// locally controlled. In that case the UI posts the context message, removes
// the drawable from selection, and otherwise refreshes the inventory count.

// ?updateContextStructureInventory@ControlBar@@IAEXXZ
void ControlBar::updateContextStructureInventory(void)
{
	BfmeStructureInventoryObject *source =
		reinterpret_cast<BfmeStructureInventoryObject *>(m_currentSelectedDrawable->getObject());
	Player *localPlayer = Rva002EE330ThePlayers->m_localPlayer;

	if (!reinterpret_cast<BfmeTargetJB *>(source)->bfmeTailJB() &&
		localPlayer->getRelationship(source->getTeam()) != (Relationship)1)
	{
		Drawable *draw = source->getDrawable();
		if (draw)
		{
			GameMessage *message = TheMessageStream->appendMessage(GameMessage::MSG_CONTEXT);
			message->appendObjectIDArgument(source->getID());
			TheInGameUI->deselectDrawable(draw);
		}
		return;
	}

	ContainModuleInterface *contain = source->getContain();
	if (!contain)
		return;

	if (m_lastRecordedInventoryCount != contain->getContainCount(false))
		populateStructureInventory(reinterpret_cast<Object *>(source), false);
}

// ControlBar::resetContainData, retail 0x004A3B00, 59 bytes.
// Twin: ControlBarCommand.cpp. BFME also hides each command window after
// clearing the matching static ContainEntry.

// ?resetContainData@ControlBar@@IAEXXZ
void ControlBar::resetContainData(void)
{
	int i;

	for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		m_containData[i].control = 0;
		m_containData[i].objectID = 0;

		if (m_commandWindows[i])
			m_commandWindows[i]->winHide(true);
	}
}

// ControlBar::doTransportInventoryUI, retail 0x004A3E90, 401 bytes.
// The inventory pass: every command of type 0xf in the set becomes one slot
// button, disabled if the transport is disabled or if it is past the contain
// maximum, and the occupants are then walked into those buttons through the
// contain module's iterate slot.

// ?doTransportInventoryUI@ControlBar@@IAEXPAVObject@@PBVCommandSet@@@Z
void ControlBar::doTransportInventoryUI(Object *transport, const CommandSet *commandSet)
{
	if (transport == 0 || commandSet == 0)
		return;

	ContainModuleInterface *contain = transport->getContain();
	if (contain == 0)
		return;

	OpenContain *openContain = contain->asOpenContain();
	if (openContain != 0 && !*(const unsigned char *)((const char *)openContain + 0xb6))
		return;

	Int transportMax = contain->getContainMax();
	transportMax -= contain->getExtraSlotsInUse();

	Int firstInventoryIndex = -1;
	Int lastInventoryIndex = -1;
	Int inventoryCommandCount = 0;

	for (Int i = 0; i < 20; ++i)
	{
		const CommandButton *commandButton = commandSet->getCommandButton(i);
		if (commandButton == 0 || commandButton->getCommandType() != 0xf)
			continue;

		if (firstInventoryIndex == -1)
			firstInventoryIndex = i;
		lastInventoryIndex = i;
		++inventoryCommandCount;

		if (m_commandWindows[i] == 0)
			continue;

		m_commandWindows[i]->bfmeClose(false);
		((BfmeUnit1013 *)m_commandWindows[i])->bfmeStop1013(0);
		GadgetButtonDrawOverlayImage(m_commandWindows[i], 0);

		if (transport->isDisabledByType(5))
			m_commandWindows[i]->bfmeClose(true);

		if (inventoryCommandCount > transportMax)
			m_commandWindows[i]->bfmeClose(true);

		setControlCommand(m_commandWindows[i], commandButton);
		if (commandButton->hasOverlayStatus())
			m_commandWindows[i]->winSetStatus(0x4000000);
		else
			m_commandWindows[i]->winClearStatus(0x4000000);
	}

	if (lastInventoryIndex >= 0)
	{
		PopulateInvButtonData data;
		data.controls = m_commandWindows;
		data.currIndex = firstInventoryIndex;
		data.maxIndex = lastInventoryIndex;
		data.transport = transport;
		contain->slot63((ContainIterateFunc)0x0043fd5f, &data, true);
	}

	m_lastRecordedInventoryCount = contain->getContainCount(false);
}

// ControlBar::commandSetButtonWalk, retail 0x004A0370, 68 bytes.
// Walk a named CommandSet's 20 buttons and run the +0x138 pointer walk on each.

// ?commandSetButtonWalk@ControlBar@@QAEXABVAsciiString@@@Z
void ControlBar::commandSetButtonWalk( const AsciiString &name )
{
	CommandSet *set = findNonConstCommandSet( name );
	if ( !set )
		return;
	if ( set->m_nextOverride )
		set = (CommandSet *)set->m_nextOverride->friend_getFinalOverride();
	if ( !set )
		return;
	for ( int i = 0; i < 20; ++i )
	{
		const CommandButton *btn = set->getCommandButton( i );
		if ( btn )
			( (CommandButton *)btn )->Rva0049B240();
	}
}

// ControlBar::updateConstructionTextDisplay, retail 0x004AF520, 245 bytes.
// No port of ControlBarUnderConstruction.cpp exists under Code/. Found by the
// literal it pushes: "ControlBar.wnd:UnderConstructionDesc" appears in exactly
// one reference source and inside exactly one function there. The body is Zero
// Hour's, minus the DEBUG_ASSERTCRASH that NDEBUG removes from both trees.
// NameKeyGenerator::nameToKey takes a const char * here, not an AsciiString:
// retail pushes the literal straight through and builds no temporary.

// ?updateConstructionTextDisplay@ControlBar@@QAEXPAVObject@@@Z
void ControlBar::updateConstructionTextDisplay( Object *obj )
{
	UnicodeString text;
	// descID keeps the UnsignedInt its own file gave it and the cast is the
	// no-op that costs nothing: this TU spells NameKeyType as the enum the
	// other bodies' nameToKey calls are pinned under.
	static UnsignedInt descID = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:UnderConstructionDesc" );
	GameWindow *descWindow = TheWindowManager->winGetWindowFromId( 0, (NameKeyType)descID );

	// format the message
	text.format( TheGameText->fetch( "CONTROLBAR:UnderConstructionDesc" ),
							 obj->getConstructionPercent() );
	GadgetStaticTextSetText( descWindow, text );

	// record this as the last percentage displayed
	m_displayedConstructPercent = obj->getConstructionPercent();

}  // end updateConstructionTextDisplay

// ControlBar::populateOCLTimer, retail 0x004AAA70, 182 bytes. BFME dropped the
// two KINDOF branches Zero Hour has -- there is no isKindOf call in these 182
// bytes at all -- and always sets the sell button. The order is the
// reference's only up to a point: retail builds and destroys the
// findCommandButton temporary BEFORE calling nameToKey, so that statement
// comes first here.

// ?populateOCLTimer@ControlBar@@QAEXPAVObject@@@Z
void ControlBar::populateOCLTimer( Object *creatorObject )
{

	// sanity
	if( creatorObject == 0 )
		return;

	// get our parent window
	GameWindow *parent = m_bfmeContextParentOclTimer;

	const CommandButton *commandButton = findCommandButton( "Command_Sell" );
	NameKeyType id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:OCLTimerSellButton" );
	GameWindow *win = TheWindowManager->winGetWindowFromId( parent, id );

	setControlCommand( win, commandButton );
	win->winSetStatus( 0x200000 );								// WIN_STATUS_USE_OVERLAY_STATES

	// set the text percent and bar of our timer we are displaying
	updateContextOCLTimer( );

	// set the portrait for the thing being constructed
	setPortraitByObject( creatorObject );

}  // end populateOCLTimer
