// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
//
// Open-BFME5: convert d_0010d090 (dump Code/gen_asm/d_00104e40.asm) to standalone C++.
//
// Body-only identification: "this" is a save-info-shaped object (not proven to be
// GameState itself -- the field offsets below are 8 bytes lower than the verified
// GameState offsets used by GameState::friend_xferSaveDataForCRC at 0x00110CF0,
// which places pristineMapName/description/saveFileType/missionMapName at
// GameState+0x1c/0x3c/0x40/0x44. Here the same field family (date, campaignSide,
// missionNumber, description, saveFileType, missionMapName in identical relative
// order and sizes) sits 8 bytes earlier, so either "this" here is not GameState*,
// or GameState's layout differs by 8 bytes between this call site and the CRC
// helper. Left as an open question -- see the banked notes.
//
// Callees resolved from reverse/symbols.csv / reverse/functions.csv:
//   Xfer::Version1() (Code/GameEngine/Source/Common/System/Xfer.cpp) matches the
//     version-tag call exactly: Version{1,1} then operator==(Version&) at slot 0x28.
//   0x00048FAE -> Rva0010BFA0 (MidVirtualSlot90 xferUser-style forwarder,
//     Code/GameEngine/Source/Common/MidVirtualSlot90Forwarders.cpp), called on the
//     saveFileType-shaped field.
//   0x000044CB -> ultimately CampaignManager::getCurrentCampaign (0x005BB510, pinned
//     in reverse/symbols.csv).
//   0x0001D5A2 -> ultimately CampaignManager::getCurrentMissionNumber (0x005BBDB0,
//     matched in Code/GameEngine/Source/GameClient/System/CampaignManager.cpp).
//   0x01336E50 -> AsciiString::TheEmptyString (reverse/symbols.csv).
//   0x00887C90 -> UnicodeString::set(const UnicodeString&) (string_base.cpp); retail
//     folds AsciiString::set into the same address, so AsciiString-typed fields are
//     reinterpreted as UnicodeString for the .set() call only.
//   0x012F4CB0 -> TheCampaignManager.
//   __imp__GetLocalTime@4 -> 0x01358DB8.
//
// Xfer vtable slots (0x28 Version, 0x64 UnicodeString, 0x68 AsciiString, 0x78 int,
// 0x7c unsigned short) reused verbatim from the already-tracked
// Code/GameEngine/Source/Common/System/xfer.h shim -- its comment documents the same
// slot table, derived from this family's retail bodies.

#include <windows.h>
#include "xfer.h"

// ---- minimal string wrappers completing xfer.h's forward declarations ----
class UnicodeString {
public:
    char *m_text;
    void set(const UnicodeString &s);
};

class AsciiString {
public:
    char *m_text;
    static const AsciiString TheEmptyString;
};

// ---- MidVirtualSlot90 forwarder (already matched/pinned) ----
class MidVirtualSlot90Receiver;
void Rva0010BFA0(MidVirtualSlot90Receiver *receiver, void *context);

// ---- CampaignManager (already-matched methods this body calls) ----
class Campaign;
class CampaignManager {
public:
    Campaign *getCurrentCampaign();
    int getCurrentMissionNumber();
};
extern CampaignManager *TheCampaignManager;

// ---- the body's own object shape (fields only; base offset unresolved, see notes) ----
class Rva0010D090Obj {
public:
    char _pad[0x14];
    AsciiString srcLabel;        // +0x14
    AsciiString mapLabel;        // +0x18
    unsigned short date[8];      // +0x1c .. +0x2c (year,month,day,dow,hour,min,sec,ms)
    AsciiString campaignSide;    // +0x2c
    int missionNumber;           // +0x30
    UnicodeString description;   // +0x34
    int saveFileType;            // +0x38
    AsciiString missionMapName;  // +0x3c

    void xfer(Xfer *xfer);
};

void Rva0010D090Obj::xfer(Xfer *xfer)
{
    Xfer::Version version;
    version.data[0] = 1;
    version.data[1] = 1;
    *xfer == version;

    Rva0010BFA0((MidVirtualSlot90Receiver *)(void *)xfer, &saveFileType);
    *xfer == missionMapName;

    SYSTEMTIME st;
    GetLocalTime(&st);

    date[0] = st.wYear;
    *xfer == date[0];
    date[1] = st.wMonth;
    *xfer == date[1];
    date[2] = st.wDay;
    *xfer == date[2];
    date[3] = st.wDayOfWeek;
    *xfer == date[3];
    date[4] = st.wHour;
    *xfer == date[4];
    date[5] = st.wMinute;
    *xfer == date[5];
    date[6] = st.wSecond;
    *xfer == date[6];
    date[7] = st.wMilliseconds;
    *xfer == date[7];

    *xfer == description;

    ((UnicodeString *)&mapLabel)->set(*(const UnicodeString *)&srcLabel);
    *xfer == mapLabel;

    CampaignManager *cm = TheCampaignManager;
    Campaign *camp = cm->getCurrentCampaign();
    if (camp)
    {
        UnicodeString *name = (UnicodeString *)((char *)camp + 4);
        ((UnicodeString *)&campaignSide)->set(*name);
        *xfer == campaignSide;

        cm = TheCampaignManager;
        missionNumber = cm->getCurrentMissionNumber();
        *xfer == missionNumber;
    }
    else
    {
        ((UnicodeString *)&campaignSide)->set(*(const UnicodeString *)&AsciiString::TheEmptyString);
        *xfer == campaignSide;

        missionNumber = -1;
        *xfer == missionNumber;
    }
}
