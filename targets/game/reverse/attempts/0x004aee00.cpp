// ?populateStructureInventory@ControlBar@@IAEXPAVObject@@_N@Z
// partial score=0.2382 date=2026-11-02
// ?populateStructureInventory@ControlBar@@IAEXPAVObject@@_N@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ControlBar::populateStructureInventory(Object *building, bool contested),
// retail 0x004AEE00, 1188 B. Its ledger row is the misnamed __emit lift
// ControlBarUpdateSlotExitImageThunk.cpp (?updateSlotExitImage, which
// tools/ilt_oracle.py CONTRADICTS at ILT 0x0001DF4D); symbols.csv pins this
// name at that ILT and ilt_oracle CONFIRMS it. Semantics follow the BFME 2
// donor Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp
// (45afcff3/59e3f8f8, BFME2 0x0053E783) with BFME 1 offsets: 20 command
// windows at +0x100, evacuate at +0x12C, sink at +0x2F0, mode at
// TheControlBar+0x2EC, count stored at +0x70; images 0 = portrait, 5/6 = NULL;
// populateButtonProc is pushed through ILT 0x00049549 (body 0x004AEC90).
// Callee pins used: reserve via ?call@Rva004A4090 (ILT 0x46F4C), the vector
// insert_overflow pin (ILT 0x56CD), ?call@Rva000DF810 (isLocalAlliedWith,
// ILT 0x3A85), ?isSet@Rva004A8F10Gate (ILT 0x330DC). Landing still needs
// route pins for GadgetButtonDrawOverlayImage (ILT 0xBC49), resetContainData
// (ILT 0x1A73F) and populateButtonProc (ILT 0x49549 + dir32 record).
#include <vector>
#include "string_base.h"
#include "ascii_string.h"

class Image;
class CommandButton;

class GameWindow
{
public:
	int winHide(bool hide);
	int winEnable(bool enable);
	void winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
	unsigned int winGetStatus();
	int winSetEnabledImage(int index, const Image *image);
};

void GadgetButtonDrawOverlayImage(GameWindow *g, const Image *image);

// GadgetPushButton.h: the enabled image, with the two end-cap images cleared.
inline void GadgetButtonSetEnabledImage(GameWindow *g, const Image *image)
{
	g->winSetEnabledImage(0, image);
	g->winSetEnabledImage(5, 0);
	g->winSetEnabledImage(6, 0);
}

class Overridable
{
public:
	virtual ~Overridable();
	// Zero Hour Override.h: one level inline, the rest through the out-of-line
	// body (ILT 0x000022BB -> 0x00087A80).
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	Overridable *m_overridable;
};

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage() const;
};

typedef void (*ContainIterateFunc)(class Object *obj, void *userData);

class ContainModuleInterface
{
public:
#define S(n) virtual void slot##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11)
	S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22)
	virtual int getContainMax() const;							// +0x5C
	S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35)
	S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47)
	S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62)
	virtual void iterateContained(ContainIterateFunc func, void *userData, int mode);	// +0xFC
	virtual int getContainCount(bool flag) const;				// +0x100
	S(65) S(66) S(67) S(68)
	virtual int getContestedContainMax() const;					// +0x114
	virtual int getContestedContainCount() const;				// +0x118
#undef S
};

class Object
{
public:
	const OVERRIDE<ThingTemplatePortraitShim> &getTemplate() const { return m_template; }
	ContainModuleInterface *getContain() const { return m_contain; }

	unsigned char m_pad000[4];
	OVERRIDE<ThingTemplatePortraitShim> m_template;			// +0x04
	unsigned char m_pad008[0x1fc - 0x08];
	ContainModuleInterface *m_contain;							// +0x1FC
};

class SubsystemReset
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void reset();										// +0x10
};

class HotKeyManager : public SubsystemReset {};
extern HotKeyManager *TheHotKeyManager;

class Rva004B19E0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void reset();										// +0x10
	void apply(void *windows);
};

class Rva004A4090
{
public:
	void call(unsigned int count);
};

class PlayerList;
extern PlayerList *ThePlayerList;
class Rva000DF810 { public: unsigned char call(Object *obj); };
class Rva004A8F10Gate { public: bool isSet(); };

class ControlBar;
extern ControlBar *TheControlBar;

struct PopulateButtonInfo
{
	Object *source;
	int buttonIndex;
	ControlBar *self;
	GameWindow **inventoryButtons;
};

enum { MAX_STRUCTURE_INVENTORY_BUTTONS = 20, EVACUATE_ID = 11 };

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
protected:
	void resetContainData();
	void populateStructureInventory(Object *building, bool contested);
	static void populateButtonProc(Object *obj, void *userData);
private:
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);

public:
	unsigned char m_pad000[0x70];
	int m_lastRecordedInventoryCount;							// +0x70
	unsigned char m_pad074[0x100 - 0x74];
	GameWindow *m_commandWindows[MAX_STRUCTURE_INVENTORY_BUTTONS];	// +0x100
	unsigned char m_pad150[0x2ec - 0x150];
	int m_inventoryMode;										// +0x2EC
	Rva004B19E0 *m_inventorySink;								// +0x2F0
};

void ControlBar::populateStructureInventory(Object *building, bool contested)
{
	if (!building)
		return;

	m_inventorySink->reset();
	resetContainData();
	if (TheHotKeyManager)
		TheHotKeyManager->reset();

	ContainModuleInterface *contain = building->getContain();
	if (!contain)
		return;

	const CommandButton *evacuateCommand;
	if (contested)
		evacuateCommand = findCommandButton("Command_Evacuate_Contested");
	else
		evacuateCommand = findCommandButton("Command_Evacuate");
	setControlCommand(m_commandWindows[EVACUATE_ID], evacuateCommand);
	m_commandWindows[EVACUATE_ID]->winEnable(false);

	const CommandButton *exitCommand = findCommandButton("Command_StructureExit");

	int containMax;
	int containCount;
	if (contested)
	{
		containMax = contain->getContestedContainMax();
		containCount = contain->getContestedContainCount();
	}
	else
	{
		containMax = contain->getContainMax();
		containCount = contain->getContainCount(false);
	}

	bool overlay = TheControlBar->m_inventoryMode == 1;
	const Image *buttonImage = building->getTemplate()->getSelectedPortraitImage();
	std::vector<GameWindow *> windows;
	((Rva004A4090 *)&windows)->call(MAX_STRUCTURE_INVENTORY_BUTTONS);
	unsigned char ally = ((Rva000DF810 *)ThePlayerList)->call(building);
	bool disableUnavailable = !((Rva004A8F10Gate *)ThePlayerList)->isSet();

	AsciiString windowName;
	int i;
	for (i = 0; i < containMax; i++)
	{
		m_commandWindows[i]->winHide(false);
		if (overlay && ally)
		{
			m_commandWindows[i]->winSetStatus(0x4000000);
			windows.push_back(m_commandWindows[i]);
		}
		else
			m_commandWindows[i]->winClearStatus(0x4000000);
		m_commandWindows[i]->winEnable(false);
		m_commandWindows[i]->winSetStatus(0x1000000);
		m_commandWindows[i]->winClearStatus(0x400000);
		m_commandWindows[i]->winClearStatus(0x80000000);
		setControlCommand(m_commandWindows[i], exitCommand);
		if (buttonImage)
			GadgetButtonSetEnabledImage(m_commandWindows[i], buttonImage);
		GadgetButtonDrawOverlayImage(m_commandWindows[i], 0);
		if (disableUnavailable && (m_commandWindows[i]->winGetStatus() & 8))
		{
			m_commandWindows[i]->winEnable(false);
			m_commandWindows[i]->winSetStatus(0x40000000);
		}
	}
	for (i = containMax; i < MAX_STRUCTURE_INVENTORY_BUTTONS; i++)
	{
		if (m_commandWindows[i])
			m_commandWindows[i]->winHide(true);
	}

	m_commandWindows[EVACUATE_ID]->winHide(false);
	if (overlay && ally)
	{
		m_commandWindows[EVACUATE_ID]->winSetStatus(0x4000000);
		windows.push_back(m_commandWindows[EVACUATE_ID]);
		if (disableUnavailable && (m_commandWindows[EVACUATE_ID]->winGetStatus() & 8))
		{
			m_commandWindows[EVACUATE_ID]->winEnable(false);
			m_commandWindows[EVACUATE_ID]->winSetStatus(0x40000000);
		}
	}
	else
		m_commandWindows[EVACUATE_ID]->winClearStatus(0x4000000);

	if (ally)
		m_inventorySink->apply(&windows);

	if (containCount)
		m_commandWindows[EVACUATE_ID]->winEnable(true);

	PopulateButtonInfo info;
	info.source = building;
	info.buttonIndex = 0;
	info.self = this;
	info.inventoryButtons = m_commandWindows;
	contain->iterateContained(populateButtonProc, &info, contested ? 2 : 1);

	m_lastRecordedInventoryCount = containCount;
}
