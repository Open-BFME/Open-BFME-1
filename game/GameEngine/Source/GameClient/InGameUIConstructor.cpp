// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// This TU has BFME's complete 0x13ac layout. InGameUI.cpp retains the ZH
// readable body and flags; editing its layout would affect 43 unrelated rows.
// BFME constructor RVA 0x0044B800. Layout measured from retail constructor and
// its 31-state unwind map, compared with GeneralsMD InGameUI.cpp/InGameUI.h.
// W3DInGameUI's matched constructor calls this base constructor through ILT.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include <new>
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include "snapshot.h"

// Array element entry points remain opaque where the ledger has no real identity.
// Retail constructor/destructor pointer pairs (RVA, reached via ILT):
// MoveHint0043AAD0: 0000602D / 0004454E -> 0043AAD0 / 0043AAE0
// Message0043DBA0: 0002AA81 / 000376AA -> 0043DBA0 / 0043DBB0
// Map0044B780:     0002254D / 00038BBD -> 0044B780 / 0044AE60
// List00442C90:    00026A8A / 00018949 -> 00442C90 / 000CEBD0
// RadiusDecalTemplate: 00029C71 / 00023B41 -> 00458830 / 001D6450
// The cleanup table corroborates each array's start, stride and count.
struct MoveHint0043AAD0 {
    MoveHint0043AAD0();
    ~MoveHint0043AAD0();
    unsigned int field_00, field_04, field_08, field_0c;
    bool field_10;
};
struct Message0043DBA0 {
    Message0043DBA0();
    ~Message0043DBA0();
    unsigned int text, displayString, timestamp, color;
};
struct Map0044B780 {
    Map0044B780();
    ~Map0044B780();
    unsigned int storage[3];
};
struct List00442C90 {
    List00442C90();
    ~List00442C90();
    void *head;
};
class RadiusDecalTemplate {
public:
    RadiusDecalTemplate();
    ~RadiusDecalTemplate();
    unsigned int storage[12]; // complete 0x30-byte BFME template
};
class RadiusDecal {
public:
    RadiusDecal();
    ~RadiusDecal();
    unsigned int storage[4]; // BFME includes the +0x0c extension
};
class Rva00449790Owner {
public:
    Rva00449790Owner();
    ~Rva00449790Owner();
    unsigned int storage[15];
};
// ILT RVA 0x00011AD1 jumps to the 38-byte body at 0x0048F090.
// Independent evidence: the body calls SubsystemInterface::SubsystemInterface,
// installs vtable 0x010F9AAC (whose slot 2 is loadIniFilesFromLegend), zeros
// +0x08..+0x1c, returns this in EAX, and has a plain ret (no stack arguments).
// Retail allocates 0x24 bytes here; the last dword is not initialized by it.
// Use the existing BfmeThingCCF::bfmeInitCCF entry without introducing an alias.
// The scoped storage guard gives raw allocation the same delete-on-throw
// behavior as the retail new expression and preserves its returned receiver.
struct BfmeThingCCF {
    BfmeThingCCF *bfmeInitCCF();
};
struct Subsystem0048F090CallView {
    virtual ~Subsystem0048F090CallView();
    virtual void init();
};
class AllocationGuard0044B800 {
public:
    void *memory;
    AllocationGuard0044B800(void *p) : memory(p) {}
    ~AllocationGuard0044B800() { if (memory) ::operator delete(memory); }
};
struct BfmeOwnerVNY {
    void bfmeResetVNY();
};
class WindowLayout;
class Drawable;
struct Payload0044B800_1304 { unsigned int first, second; };
extern "C" void *g_bfmeReplayControlAR;

struct Coord2D0044B800 { float x, y; };
struct ICoord2D0044B800 { unsigned int x, y; };
struct RGBA0044B800 { unsigned int red, green, blue, alpha; };
struct BuildProgress { unsigned int thingTemplate, percentComplete, control; };
class InGameUI : public SubsystemInterface, public Snapshot {
public:
    InGameUI();
    virtual ~InGameUI();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &);
    bool m_superweaponHiddenByScript; // +0xc
    bool m_inputEnabled; // +0xd
    bool m_field_00e; // +0xe
    unsigned char m_unreconstructed_00f[0x1];
    _STL::list<WindowLayout *> m_windowLayouts; // +0x10
    AsciiString m_currentlyPlayingMovie; // +0x14
    _STL::list<Drawable *> m_selectedDrawables; // +0x18
    _STL::list<Drawable *> m_selectedLocalDrawables; // +0x1c
    bool m_isDragSelecting; // +0x20
    unsigned char m_unreconstructed_021[3];
    unsigned int m_dragSelectRegion[4]; // +0x24
    bool m_displayedMaxWarning; // +0x34
    unsigned char m_unreconstructed_035[0x3];
    MoveHint0043AAD0 m_moveHint[25]; // +0x38
    unsigned int m_nextMoveHint; // +0x22c
    unsigned int m_pendingGUICommand; // +0x230
    BuildProgress m_buildProgress[64]; // +0x234
    unsigned int m_pendingPlaceType; // +0x534
    unsigned int m_pendingPlaceSourceObjectID; // +0x538
    unsigned int * m_placeIcon; // +0x53c
    bool m_placeAnchorInProgress; // +0x540
    unsigned char m_unreconstructed_541[0x3];
    ICoord2D0044B800 m_placeAnchorStart; // +0x544
    ICoord2D0044B800 m_placeAnchorEnd; // +0x54c
    unsigned int m_selectCount; // +0x554
    unsigned int m_maxSelectCount; // +0x558
    unsigned int m_frameSelectionChanged; // +0x55c
    unsigned int m_videoStream; // +0x560
    unsigned char m_unreconstructed_564[0x4];
    unsigned int m_videoBuffer; // +0x568
    Message0043DBA0 m_uiMessages[6]; // +0x56c
    Map0044B780 m_superweapons[32]; // +0x5cc
    Coord2D0044B800 m_superweaponPosition; // +0x74c
    float m_superweaponFlashDuration; // +0x754
    AsciiString m_superweaponNormalFont; // +0x758
    unsigned int m_superweaponNormalPointSize; // +0x75c
    bool m_superweaponNormalBold; // +0x760
    unsigned char m_unreconstructed_761[0x3];
    AsciiString m_superweaponReadyFont; // +0x764
    unsigned int m_superweaponReadyPointSize; // +0x768
    bool m_superweaponReadyBold; // +0x76c
    unsigned char m_unreconstructed_76d[0x3];
    unsigned int m_superweaponLastFlashFrame; // +0x770
    unsigned int m_superweaponFlashColor; // +0x774
    bool m_superweaponUsedFlashColor; // +0x778
    unsigned char m_unreconstructed_779[0x3];
    _STL::map<AsciiString, void *> m_namedTimers; // +0x77c
    Coord2D0044B800 m_namedTimerPosition; // +0x788
    bool m_field_790; // +0x790
    unsigned char m_unreconstructed_791[0x3];
    float m_namedTimerFlashDuration; // +0x794
    unsigned int m_namedTimerLastFlashFrame; // +0x798
    unsigned int m_namedTimerFlashColor; // +0x79c
    bool m_namedTimerUsedFlashColor; // +0x7a0
    bool m_showNamedTimers; // +0x7a1
    unsigned char m_unreconstructed_7a2[0x2];
    AsciiString m_namedTimerNormalFont; // +0x7a4
    unsigned int m_namedTimerNormalPointSize; // +0x7a8
    bool m_namedTimerNormalBold; // +0x7ac
    unsigned char m_unreconstructed_7ad[0x3];
    unsigned int m_namedTimerNormalColor; // +0x7b0
    AsciiString m_namedTimerReadyFont; // +0x7b4
    unsigned int m_namedTimerReadyPointSize; // +0x7b8
    bool m_namedTimerReadyBold; // +0x7bc
    unsigned char m_unreconstructed_7bd[0x3];
    unsigned int m_namedTimerReadyColor; // +0x7c0
    AsciiString m_drawableCaptionFont; // +0x7c4
    unsigned int m_drawableCaptionPointSize; // +0x7c8
    bool m_drawableCaptionBold; // +0x7cc
    unsigned char m_unreconstructed_7cd[0x3];
    unsigned int m_drawableCaptionColor; // +0x7d0
    AsciiString m_field_7d4; // +0x7d4
    unsigned int m_field_7d8; // +0x7d8
    bool m_field_7dc; // +0x7dc
    unsigned char m_unreconstructed_7dd[0x3];
    unsigned int m_field_7e0; // +0x7e0
    AsciiString m_field_7e4; // +0x7e4
    unsigned int m_field_7e8; // +0x7e8
    bool m_field_7ec; // +0x7ec
    unsigned char m_unreconstructed_7ed[0x3];
    unsigned int m_field_7f0; // +0x7f0
    AsciiString m_field_7f4; // +0x7f4
    unsigned int m_field_7f8; // +0x7f8
    bool m_field_7fc; // +0x7fc
    unsigned char m_unreconstructed_7fd[0x3];
    unsigned int m_field_800; // +0x800
    AsciiString m_field_804; // +0x804
    unsigned int m_field_808; // +0x808
    bool m_field_80c; // +0x80c
    unsigned char m_unreconstructed_80d[0x3];
    unsigned int m_field_810; // +0x810
    unsigned int m_tooltipsDisabledUntil; // +0x814
    unsigned int m_militarySubtitle; // +0x818
    Subsystem0048F090CallView * m_field_81c; // +0x81c
    bool m_isScrolling; // +0x820
    bool m_isSelecting; // +0x821
    unsigned char m_unreconstructed_822[0x2];
    unsigned int m_mouseMode; // +0x824
    unsigned int m_mouseModeCursor; // +0x828
    unsigned int m_mousedOverDrawableID; // +0x82c
    unsigned char m_unreconstructed_830[0x9];
    bool m_messagesOn; // +0x839
    unsigned char m_unreconstructed_83a[0x2];
    unsigned int m_messageColor1; // +0x83c
    unsigned int m_messageColor2; // +0x840
    ICoord2D0044B800 m_messagePosition; // +0x844
    AsciiString m_messageFont; // +0x84c
    unsigned int m_messagePointSize; // +0x850
    bool m_messageBold; // +0x854
    unsigned char m_unreconstructed_855[0x3];
    unsigned int m_messageDelayMS; // +0x858
    RGBA0044B800 m_militaryCaptionColor; // +0x85c
    Coord2D0044B800 m_militaryCaptionPosition; // +0x86c
    bool m_field_874; // +0x874
    unsigned char m_unreconstructed_875[0x3];
    AsciiString m_militaryCaptionTitleFont; // +0x878
    unsigned int m_militaryCaptionTitlePointSize; // +0x87c
    bool m_militaryCaptionTitleBold; // +0x880
    unsigned char m_unreconstructed_881[0x3];
    AsciiString m_militaryCaptionFont; // +0x884
    unsigned int m_militaryCaptionPointSize; // +0x888
    bool m_militaryCaptionBold; // +0x88c
    unsigned char m_unreconstructed_88d[0x3];
    unsigned int m_militaryCaptionDelayMS; // +0x890
    RadiusDecalTemplate m_radiusCursors[53]; // +0x894
    RadiusDecal m_curRadiusCursor; // +0x1284
    unsigned int m_curRcType; // +0x1294
    _STL::list<void *> m_list_1298; // +0x1298
    float m_floatingTextTimeOut; // +0x129c
    float m_floatingTextMoveUpSpeed; // +0x12a0
    float m_floatingTextMoveVanishRate; // +0x12a4
    unsigned int m_popupMessageData; // +0x12a8
    unsigned int m_popupMessageColor; // +0x12ac
    bool m_field_12b0; // +0x12b0
    bool m_field_12b1; // +0x12b1
    bool m_field_12b2; // +0x12b2
    bool m_field_12b3; // +0x12b3
    bool m_field_12b4; // +0x12b4
    bool m_field_12b5; // +0x12b5
    bool m_field_12b6; // +0x12b6
    bool m_field_12b7; // +0x12b7
    bool m_field_12b8; // +0x12b8
    bool m_field_12b9; // +0x12b9
    bool m_field_12ba; // +0x12ba
    bool m_field_12bb; // +0x12bb
    bool m_drawRMBScrollAnchor; // +0x12bc
    bool m_moveRMBScrollAnchor; // +0x12bd
    bool m_field_12be; // +0x12be
    unsigned char m_unreconstructed_12bf[0x1];
    _STL::list<void *> m_list_12c0; // +0x12c0
    _STL::list<void *> m_list_12c4; // +0x12c4
    Rva00449790Owner m_field_12c8; // +0x12c8
    _STL::list<Payload0044B800_1304> m_list_1304; // +0x1304
    unsigned int m_field_1308; // +0x1308
    unsigned int m_field_130c; // +0x130c
    unsigned int m_field_1310; // +0x1310
    unsigned int m_field_1314; // +0x1314
    bool m_field_1318; // +0x1318
    unsigned char m_unreconstructed_1319[0x3];
    List00442C90 m_idleWorkers[32]; // +0x131c
    unsigned int m_idleWorkerWin; // +0x139c
    unsigned int m_currentIdleWorkerDisplay; // +0x13a0
    unsigned int m_soloNexusSelectedDrawableID; // +0x13a4
    unsigned int m_field_13a8; // +0x13a8
};

// Compile-time checks keep the measured BFME layout explicit.
#include <stddef.h>
typedef char CheckInGameUISize[(sizeof(InGameUI) == 0x13ac) ? 1 : -1];
typedef char CheckHintsOffset[(offsetof(InGameUI, m_moveHint) == 0x38) ? 1 : -1];
typedef char CheckMessagesOffset[(offsetof(InGameUI, m_uiMessages) == 0x56c) ? 1 : -1];
typedef char CheckMapsOffset[(offsetof(InGameUI, m_superweapons) == 0x5cc) ? 1 : -1];
typedef char CheckTimerMapOffset[(offsetof(InGameUI, m_namedTimers) == 0x77c) ? 1 : -1];
typedef char CheckRadiusOffset[(offsetof(InGameUI, m_radiusCursors) == 0x894) ? 1 : -1];
typedef char CheckIdleWorkersOffset[(offsetof(InGameUI, m_idleWorkers) == 0x131c) ? 1 : -1];

// clear() is inlined to the actual StringBase releaseBuffer entry in retail.
template<class T> inline void StringBase<T>::clear() { releaseBuffer(); }

InGameUI::InGameUI()
{
  m_inputEnabled = true;
  m_field_00e = true;
  m_isDragSelecting = false;
  m_nextMoveHint = 0;
  m_selectCount = 0;
  m_frameSelectionChanged = 0;
  m_maxSelectCount = 0xffffffff;
  m_isScrolling = false;
  m_isSelecting = false;
  m_mouseMode = 0;
  m_mouseModeCursor = 2;
  m_mousedOverDrawableID = 0;
  m_currentlyPlayingMovie.clear();
  m_militarySubtitle = 0;
  {
    AllocationGuard0044B800 storage(::operator new(0x24));
    m_field_81c = storage.memory ? (Subsystem0048F090CallView*)((BfmeThingCCF*)storage.memory)->bfmeInitCCF() : 0;
    storage.memory = 0;
  }
  m_field_81c->init();
  m_popupMessageData = 0;
  m_field_12b0 = false;
  m_field_12be = false;
  m_messageColor1 = 0xffffffff;
  m_messageColor2 = 0xffb4b4b4;
  m_messagePosition.x = 10;
  m_messagePosition.y = 10;
  m_messageFont.StringBase<char>::set("Arial",5);
  m_messagePointSize = 10;
  m_messageBold = false;
  m_messageDelayMS = 5000;
  m_militaryCaptionColor.red = 200;
  m_militaryCaptionColor.green = 200;
  m_militaryCaptionColor.blue = 0x1e;
  m_militaryCaptionColor.alpha = 0xff;
  m_militaryCaptionPosition.x = 0.5f;
  m_militaryCaptionPosition.y = 0.01f;
  m_field_874 = true;
  m_militaryCaptionTitleFont.StringBase<char>::set("Courier",7);
  m_militaryCaptionTitlePointSize = 0xc;
  m_militaryCaptionTitleBold = true;
  m_militaryCaptionFont.StringBase<char>::set("Courier",7);
  m_militaryCaptionPointSize = 0xc;
  m_militaryCaptionBold = false;
  m_militaryCaptionDelayMS = 0x2ee;
  m_popupMessageColor = 0xffffffff;
  m_tooltipsDisabledUntil = 0;
  // Keep the cursor at the middle dword: this is retail's loop addressing.
  unsigned int *hint = &m_moveHint[0].field_08;
  for (int i = 0; i < 25; ++i, hint += 5) {
    hint[-2] = 0;
    hint[-1] = 0;
    hint[0] = 0;
    hint[1] = 0;
    *(bool *)(hint + 2) = false;
  }
  for (int j = 0; j < 64; ++j) {
    m_buildProgress[j].thingTemplate = 0;
    m_buildProgress[j].percentComplete = 0;
    m_buildProgress[j].control = 0;
  }
  m_pendingGUICommand = 0;
  m_placeIcon = new unsigned int[1];
  m_placeIcon[0] = 0;
  m_pendingPlaceType = 0;
  m_pendingPlaceSourceObjectID = 0;
  m_placeAnchorStart.y = 0;
  m_placeAnchorStart.x = 0;
  m_placeAnchorEnd.y = 0;
  m_placeAnchorEnd.x = 0;
  m_placeAnchorInProgress = false;
  m_videoStream = 0;
  m_videoBuffer = 0;
  for (int k = 0; k < 6; ++k) {
    ((StringBase<unsigned short>*)&m_uiMessages[k].text)->clear();
    m_uiMessages[k].displayString = 0;
    m_uiMessages[k].timestamp = 0;
    m_uiMessages[k].color = 0;
  }
  g_bfmeReplayControlAR = 0;
  m_messagesOn = true;
  m_superweaponPosition.x = 0.7f;
  m_superweaponPosition.y = 0.7f;
  m_superweaponFlashDuration = 1.0f;
  m_superweaponNormalFont.StringBase<char>::set("Arial",5);
  m_superweaponNormalPointSize = 10;
  m_superweaponNormalBold = false;
  m_superweaponReadyFont.StringBase<char>::set("Arial",5);
  m_superweaponReadyPointSize = 10;
  m_superweaponReadyBold = false;
  m_superweaponFlashColor = 0xffffffff;
  m_superweaponLastFlashFrame = 0;
  m_superweaponUsedFlashColor = true;
  m_superweaponHiddenByScript = false;
  m_namedTimerPosition.x = 0.5f;
  m_namedTimerPosition.y = 0.01f;
  m_field_790 = false;
  m_namedTimerFlashDuration = 1.0f;
  m_namedTimerNormalFont.StringBase<char>::set("Arial",5);
  m_namedTimerNormalPointSize = 10;
  m_namedTimerNormalBold = false;
  m_namedTimerReadyFont.StringBase<char>::set("Arial",5);
  m_namedTimerReadyPointSize = 10;
  m_namedTimerReadyBold = false;
  m_namedTimerNormalColor = 0xffffff00;
  m_namedTimerReadyColor = 0xffff00ff;
  m_namedTimerFlashColor = 0xff00ffff;
  m_namedTimerLastFlashFrame = 0;
  m_namedTimerUsedFlashColor = true;
  m_showNamedTimers = true;
  m_floatingTextTimeOut = 10.0f;
  m_floatingTextMoveUpSpeed = 1.0f;
  m_floatingTextMoveVanishRate = 0.1f;
  m_drawableCaptionFont.StringBase<char>::set("Arial",5);
  m_drawableCaptionPointSize = 10;
  m_drawableCaptionBold = false;
  m_drawableCaptionColor = 0xffffffff;
  m_field_7d4.StringBase<char>::set("Albertus MT",0xb);
  m_field_7d8 = 0x10;
  m_field_7dc = false;
  m_field_7e0 = 0xffffffff;
  m_field_7e4.StringBase<char>::set("Albertus MT",0xb);
  m_field_7e8 = 0xe;
  m_field_7ec = false;
  m_field_7f0 = 0xffffcc00;
  m_field_7f4.StringBase<char>::set("Albertus MT",0xb);
  m_field_7f8 = 0xe;
  m_field_7fc = false;
  m_field_800 = 0xffffcc00;
  m_field_804.StringBase<char>::set("Albertus MT",0xb);
  m_field_808 = 0xe;
  m_field_80c = false;
  m_field_810 = 0xffffcc00;
  m_drawRMBScrollAnchor = false;
  m_moveRMBScrollAnchor = false;
  m_displayedMaxWarning = false;
  m_idleWorkerWin = 0;
  m_currentIdleWorkerDisplay = 0xffffffff;
  m_field_12b0 = false;
  m_field_12b1 = false;
  m_field_12b2 = false;
  m_field_12b3 = false;
  m_curRcType = 0;
  m_soloNexusSelectedDrawableID = 0;
  ((BfmeOwnerVNY*)this)->bfmeResetVNY();
  m_field_1318 = false;
  m_field_1308 = 0;
  m_field_130c = 0;
  m_field_1310 = 0;
  m_field_1314 = 0;
  m_field_12b8 = false;
  m_field_12b9 = false;
  m_field_12ba = false;
  m_field_12bb = false;
  m_field_12b4 = false;
  m_field_12b5 = false;
  m_field_12b6 = false;
  m_field_12b7 = false;
  m_field_13a8 = 0;

}
