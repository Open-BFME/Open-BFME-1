// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// InGameUI::reset, retail 0x0044B3F0 (716 B).
// Identity: vtable 0x010F5B38, installed by the matched InGameUI constructor
// (0x0044B800), holds this body in slot 4 (+0x10, SubsystemInterface::reset)
// through ILT 0x000015A5; the body follows GeneralsMD InGameUI::reset. BFME
// adds three more subsystem resets, the +0x81c helper reset and the hint flag.
// Offsets follow the constructor TU's measured 0x13ac layout; virtual slots:
// 21 removeMilitarySubtitle, 40 setScrolling, 46 setGUICommand,
// 48 placeBuildAvailable, 107 resetIdleWorker (matched bodies); slot 78
// (0x0043CE70) keeps an address-derived name.
#include "ascii_string.h"
#include <map>
#include <list>
#include <stddef.h>

typedef bool Bool;

class SuperweaponInfo
{
public:
	virtual ~SuperweaponInfo();
};

class DisplayString;

class NamedTimerInfo
{
protected:
	virtual ~NamedTimerInfo();
public:
	void deleteInstance() { delete this; }
	int m_timerName;
	int m_timerText;
	DisplayString *displayString;
};

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;
typedef _STL::map<AsciiString, NamedTimerInfo *> NamedTimerMap;

class WindowLayout;
class CommandButton;
class ThingTemplate;
class Drawable;

// Receivers reset through the retail SubsystemInterface slot 4 (+0x10).
#define BFME_SUBSYSTEM_RESET_VIEW(T) \
	class T { public: virtual ~T(); virtual void init(); virtual void slot08(); \
	virtual void slot0c(); virtual void reset(); };
BFME_SUBSYSTEM_RESET_VIEW(ControlBar)
BFME_SUBSYSTEM_RESET_VIEW(Glo012F4B78Type)
BFME_SUBSYSTEM_RESET_VIEW(Glo012F4B98Type)
BFME_SUBSYSTEM_RESET_VIEW(BannerUI)
BFME_SUBSYSTEM_RESET_VIEW(Subsystem0048F090CallView)

class View
{
public:
#define BFME_VIEW_SLOT(n) virtual void slot##n();
	BFME_VIEW_SLOT(00) BFME_VIEW_SLOT(01) BFME_VIEW_SLOT(02) BFME_VIEW_SLOT(03)
	BFME_VIEW_SLOT(04) BFME_VIEW_SLOT(05) BFME_VIEW_SLOT(06) BFME_VIEW_SLOT(07)
	BFME_VIEW_SLOT(08) BFME_VIEW_SLOT(09) BFME_VIEW_SLOT(10) BFME_VIEW_SLOT(11)
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13) BFME_VIEW_SLOT(14) BFME_VIEW_SLOT(15)
	BFME_VIEW_SLOT(16) BFME_VIEW_SLOT(17) BFME_VIEW_SLOT(18) BFME_VIEW_SLOT(19)
	BFME_VIEW_SLOT(20) BFME_VIEW_SLOT(21) BFME_VIEW_SLOT(22) BFME_VIEW_SLOT(23)
	BFME_VIEW_SLOT(24) BFME_VIEW_SLOT(25) BFME_VIEW_SLOT(26) BFME_VIEW_SLOT(27)
	BFME_VIEW_SLOT(28) BFME_VIEW_SLOT(29) BFME_VIEW_SLOT(30) BFME_VIEW_SLOT(31)
	BFME_VIEW_SLOT(32) BFME_VIEW_SLOT(33) BFME_VIEW_SLOT(34) BFME_VIEW_SLOT(35)
	BFME_VIEW_SLOT(36) BFME_VIEW_SLOT(37) BFME_VIEW_SLOT(38) BFME_VIEW_SLOT(39)
	BFME_VIEW_SLOT(40) BFME_VIEW_SLOT(41) BFME_VIEW_SLOT(42) BFME_VIEW_SLOT(43)
	BFME_VIEW_SLOT(44) BFME_VIEW_SLOT(45) BFME_VIEW_SLOT(46) BFME_VIEW_SLOT(47)
	BFME_VIEW_SLOT(48) BFME_VIEW_SLOT(49) BFME_VIEW_SLOT(50) BFME_VIEW_SLOT(51)
	BFME_VIEW_SLOT(52) BFME_VIEW_SLOT(53) BFME_VIEW_SLOT(54) BFME_VIEW_SLOT(55)
#undef BFME_VIEW_SLOT
	virtual void setDefaultView(float pitch, float angle, float maxHeight); // +0xe0
};

// The 0x012F12CC singleton is DisplayStringManager *TheDisplayStringManager,
// defined once in DisplayStringManager.cpp.  This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class Rva0048EC80Manager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(DisplayString *string); // +0x28, frees a display string
};

extern ControlBar *TheControlBar;
extern Glo012F4B78Type *Glo012F4B78;
extern Glo012F4B98Type *Glo012F4B98;
extern BannerUI *TheBannerUI;
extern View *TheTacticalView;
extern DisplayStringManager *TheDisplayStringManager;
static inline Rva0048EC80Manager *theDisplayStringManagerView()
{
	return (Rva0048EC80Manager *)TheDisplayStringManager;
}
extern const AsciiString Rva01336E50EmptyString;

void ResetInGameChat();
void UpdateDiplomacyBriefingText(const AsciiString &text, bool clear);

// Callee entry points under their ledger names; each is called with this.
struct BfmeOwnerVNY { void bfmeResetVNY(); };
struct BfmeOwnerVOK { void bfmeClearVOK(); };
struct Gen_0043F5D0 { void bfmeClear(); };
struct Gen_0043FBB0 { void bfmeClear(); };

struct Coord3D
{
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

struct MoveHint0043AAD0
{
	Coord3D pos;
	unsigned int field_0c;
	bool field_10;
};

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n();
	virtual ~InGameUI();
	virtual void init();
	virtual Bool loadIniFilesFromLegend();
	virtual void slot03();
	virtual void reset(); // slot 4
	BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07) BFME_UI_SLOT(08) BFME_UI_SLOT(09)
	BFME_UI_SLOT(10) BFME_UI_SLOT(11) BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14)
	BFME_UI_SLOT(15) BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20)
	virtual void removeMilitarySubtitle(); // slot 21
	BFME_UI_SLOT(22) BFME_UI_SLOT(23) BFME_UI_SLOT(24)
	BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27) BFME_UI_SLOT(28) BFME_UI_SLOT(29)
	BFME_UI_SLOT(30) BFME_UI_SLOT(31) BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34)
	BFME_UI_SLOT(35) BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	virtual void setScrolling(Bool isScrolling); // slot 40
	BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43) BFME_UI_SLOT(44) BFME_UI_SLOT(45)
	virtual void setGUICommand(const CommandButton *command); // slot 46
	BFME_UI_SLOT(47)
	virtual void placeBuildAvailable(const ThingTemplate *build, Drawable *buildDrawable); // slot 48
	BFME_UI_SLOT(49)
	BFME_UI_SLOT(50) BFME_UI_SLOT(51) BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54)
	BFME_UI_SLOT(55) BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62) BFME_UI_SLOT(63) BFME_UI_SLOT(64)
	BFME_UI_SLOT(65) BFME_UI_SLOT(66) BFME_UI_SLOT(67) BFME_UI_SLOT(68) BFME_UI_SLOT(69)
	BFME_UI_SLOT(70) BFME_UI_SLOT(71) BFME_UI_SLOT(72) BFME_UI_SLOT(73) BFME_UI_SLOT(74)
	BFME_UI_SLOT(75) BFME_UI_SLOT(76) BFME_UI_SLOT(77)
	virtual void rva0043CE70Slot78(); // slot 78
	BFME_UI_SLOT(79)
	BFME_UI_SLOT(80) BFME_UI_SLOT(81) BFME_UI_SLOT(82) BFME_UI_SLOT(83) BFME_UI_SLOT(84)
	BFME_UI_SLOT(85) BFME_UI_SLOT(86) BFME_UI_SLOT(87) BFME_UI_SLOT(88) BFME_UI_SLOT(89)
	BFME_UI_SLOT(90) BFME_UI_SLOT(91) BFME_UI_SLOT(92) BFME_UI_SLOT(93) BFME_UI_SLOT(94)
	BFME_UI_SLOT(95) BFME_UI_SLOT(96) BFME_UI_SLOT(97) BFME_UI_SLOT(98) BFME_UI_SLOT(99)
	BFME_UI_SLOT(100) BFME_UI_SLOT(101) BFME_UI_SLOT(102) BFME_UI_SLOT(103) BFME_UI_SLOT(104)
	BFME_UI_SLOT(105) BFME_UI_SLOT(106)
	virtual void resetIdleWorker(); // slot 107
#undef BFME_UI_SLOT

	void freeMessageResources();
	void clearPopupMessageData();

	unsigned char m_snapshotBase[0x8]; // +0x4 (Snapshot base in the full class)
	bool m_superweaponHiddenByScript; // +0xc
	bool m_inputEnabled; // +0xd
	bool m_field_00e; // +0xe
	unsigned char m_unreconstructed_00f[0x1];
	_STL::list<WindowLayout *> m_windowLayouts; // +0x10
	unsigned char m_unreconstructed_014[0xc];
	bool m_isDragSelecting; // +0x20
	unsigned char m_unreconstructed_021[0x17];
	MoveHint0043AAD0 m_moveHint[25]; // +0x38
	unsigned char m_unreconstructed_22c[0x3a0];
	SuperweaponMap m_superweapons[32]; // +0x5cc
	unsigned char m_unreconstructed_74c[0x24];
	unsigned int m_superweaponLastFlashFrame; // +0x770
	unsigned int m_superweaponFlashColor; // +0x774
	bool m_superweaponUsedFlashColor; // +0x778
	unsigned char m_unreconstructed_779[0x3];
	NamedTimerMap m_namedTimers; // +0x77c
	unsigned char m_unreconstructed_788[0x10];
	unsigned int m_namedTimerLastFlashFrame; // +0x798
	unsigned int m_namedTimerFlashColor; // +0x79c
	bool m_namedTimerUsedFlashColor; // +0x7a0
	bool m_showNamedTimers; // +0x7a1
	unsigned char m_unreconstructed_7a2[0x72];
	unsigned int m_tooltipsDisabledUntil; // +0x814
	unsigned int m_militarySubtitle; // +0x818
	Subsystem0048F090CallView *m_field_81c; // +0x81c
	bool m_isScrolling; // +0x820
	bool m_isSelecting; // +0x821
	unsigned char m_unreconstructed_822[0x16];
	bool m_field_838; // +0x838
	unsigned char m_unreconstructed_839[0xa77];
	bool m_field_12b0; // +0x12b0
	bool m_field_12b1; // +0x12b1
	bool m_field_12b2; // +0x12b2
	bool m_field_12b3; // +0x12b3
	unsigned char m_unreconstructed_12b4[0xa];
	bool m_field_12be; // +0x12be
	unsigned char m_unreconstructed_12bf[0x49];
	unsigned int m_field_1308; // +0x1308
	unsigned int m_field_130c; // +0x130c
	unsigned int m_field_1310; // +0x1310
	unsigned int m_field_1314; // +0x1314
	bool m_field_1318; // +0x1318
};

typedef char CheckWindowLayouts[(offsetof(InGameUI, m_windowLayouts) == 0x10) ? 1 : -1];
typedef char CheckHints[(offsetof(InGameUI, m_moveHint) == 0x38) ? 1 : -1];
typedef char CheckMaps[(offsetof(InGameUI, m_superweapons) == 0x5cc) ? 1 : -1];
typedef char CheckTimers[(offsetof(InGameUI, m_namedTimers) == 0x77c) ? 1 : -1];
typedef char CheckTooltips[(offsetof(InGameUI, m_tooltipsDisabledUntil) == 0x814) ? 1 : -1];
typedef char Check838[(offsetof(InGameUI, m_field_838) == 0x838) ? 1 : -1];
typedef char Check12b0[(offsetof(InGameUI, m_field_12b0) == 0x12b0) ? 1 : -1];
typedef char Check12be[(offsetof(InGameUI, m_field_12be) == 0x12be) ? 1 : -1];
typedef char Check1318[(offsetof(InGameUI, m_field_1318) == 0x1318) ? 1 : -1];

void InGameUI::reset()
{
	m_field_838 = false;
	m_inputEnabled = true;
	m_field_00e = true;

	TheControlBar->reset();
	Glo012F4B78->reset();
	Glo012F4B98->reset();
	TheBannerUI->reset();

	setScrolling(false);
	((BfmeOwnerVNY *)this)->bfmeResetVNY();
	m_field_1318 = false;
	m_field_1308 = 0;
	m_field_130c = 0;
	m_field_1310 = 0;
	m_field_1314 = 0;
	m_isSelecting = false;
	m_isDragSelecting = false;
	m_field_81c->reset();

	TheTacticalView->setDefaultView(0.0f, 0.0f, 1.0f);

	ResetInGameChat();

	rva0043CE70Slot78();
	setGUICommand(NULL);
	placeBuildAvailable(NULL, NULL);
	freeMessageResources();

	int i;
	for (i = 0; i < 32; ++i)
	{
		for (SuperweaponMap::iterator mapIt = m_superweapons[i].begin(); mapIt != m_superweapons[i].end(); ++mapIt)
		{
			for (SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt)
			{
				SuperweaponInfo *info = *listIt;
				delete info;
			}
			mapIt->second.clear();
		}
		m_superweapons[i].clear();
	}

	for (NamedTimerMap::iterator timerIt = m_namedTimers.begin(); timerIt != m_namedTimers.end(); ++timerIt)
	{
		NamedTimerInfo *info = timerIt->second;
		theDisplayStringManagerView()->slot28(info->displayString);
		info->deleteInstance();
	}
	m_namedTimers.clear();
	m_namedTimerLastFlashFrame = 0;
	m_namedTimerUsedFlashColor = true;
	m_showNamedTimers = true;

	removeMilitarySubtitle();
	clearPopupMessageData();
	m_superweaponLastFlashFrame = 0;
	m_superweaponUsedFlashColor = true;
	m_superweaponHiddenByScript = false;

	((BfmeOwnerVOK *)this)->bfmeClearVOK();
	((Gen_0043F5D0 *)this)->bfmeClear();
	((Gen_0043FBB0 *)this)->bfmeClear();
	resetIdleWorker();

	for (i = 0; i < 25; i++)
	{
		m_moveHint[i].pos.zero();
		m_moveHint[i].field_0c = 0;
		m_moveHint[i].field_10 = true;
	}

	m_field_12b0 = false;
	m_field_12b1 = false;
	m_field_12b2 = false;
	m_field_12b3 = false;
	m_field_12be = false;

	m_windowLayouts.clear();

	m_tooltipsDisabledUntil = 0;

	UpdateDiplomacyBriefingText(Rva01336E50EmptyString, true);
}
