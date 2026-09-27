// ?populateLadderList@BfmeQuickMatchLadderPanel@@QAEXXZ
// partial score=0.82 date=2026-09-27
// ?populateLadderList@BfmeQuickMatchLadderPanel@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

#include "PreRTS.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/LadderPreferences.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetComboBox.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include <set>

class GameSpyProfileDispatch00508C80
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual Int getLocalProfileID();
};

extern GameSpyProfileDispatch00508C80 *TheGameSpyInfo;
extern int GameSpyColor[];
extern LadderList *TheLadderList;

class RvaLadderValidity00508C80
{
public:
    Bool check();
};

class Rva005082D0PopulateSide
{
public:
    void populateQMSideComboBox(Int side, const LadderInfo *ladder);
};

extern void j_0003b75a();
extern void j_0003b971();
extern void j_00028e93();

static __forceinline const LadderInfo *getLadderInfo(GameWindow *window)
{
    Int selected;
    ((void (__cdecl *)(GameWindow *, Int *))j_0003b75a)(window, &selected);
    Int index = (Int)((void *(__cdecl *)(GameWindow *, Int))j_0003b971)(window, selected);
    union
    {
        void (*raw)(void);
        const LadderInfo *(LadderList::*member)(Int);
    } call;
    call.raw = j_00028e93;
    return (TheLadderList->*call.member)(index);
}

class BfmeQuickMatchLadderPanel
{
public:
    void populateLadderList();

private:
    char m_beforeNumPlayers[0x23c];
    GameWindow *m_numPlayers;
    char m_betweenCombos[4];
    GameWindow *m_ladder;
};

void BfmeQuickMatchLadderPanel::populateLadderList()
{
    if (!m_ladder)
        return;

    *(unsigned char *)0x012F4814 = TRUE;
    QuickMatchPreferences pref;
    Int localProfile = ((GameSpyProfileDispatch00508C80 *)TheGameSpyInfo)->getLocalProfileID();
    Color specialColor = GameSpyColor[25];
    Color normalColor = GameSpyColor[26];
    Int index;
    GadgetComboBoxReset(m_ladder);
    index = GadgetComboBoxAddEntry(m_ladder, TheGameText->fetch("GUI:NoLadder"), normalColor);
    GadgetComboBoxSetItemData(m_ladder, index, 0);

    std::set<const LadderInfo *> usedLadders;
    Int selectedPos = 0;
    AsciiString lastLadderAddr = pref.getLastLadderAddr();
    UnsignedShort lastLadderPort = pref.getLastLadderPort();
    LadderList *ladderList = TheLadderList;
    const LadderInfo *info = ladderList->findLadder(lastLadderAddr, lastLadderPort);
    if (info && ((RvaLadderValidity00508C80 *)info)->check())
    {
        usedLadders.insert(info);
        index = GadgetComboBoxAddEntry(m_ladder, info->name, specialColor);
        GadgetComboBoxSetItemData(m_ladder, index, (void *)info->index);
        selectedPos = index;
        GadgetComboBoxSetSelectedPos(m_numPlayers, info->playersPerTeam - 1);
        m_numPlayers->winEnable(FALSE);
    }
    else
    {
        m_numPlayers->winEnable(TRUE);
    }

    LadderPreferences ladPref;
    ladPref.loadProfile(localProfile);
    const LadderPrefMap recentLadders = ladPref.getRecentLadders();
    for (LadderPrefMap::const_iterator cit = recentLadders.begin(); cit != recentLadders.end(); ++cit)
    {
        AsciiString addr = cit->second.address;
        UnsignedShort port = cit->second.port;
        if (addr == lastLadderAddr && port == lastLadderPort)
            continue;
        LadderList *ladderList = TheLadderList;
        const LadderInfo *info = ladderList->findLadder(addr, port);
        if (info && ((RvaLadderValidity00508C80 *)info)->check()
            && usedLadders.find(info) == usedLadders.end())
        {
            usedLadders.insert(info);
            index = GadgetComboBoxAddEntry(m_ladder, info->name, normalColor);
            GadgetComboBoxSetItemData(m_ladder, index, (void *)info->index);
        }
    }

    index = GadgetComboBoxAddEntry(m_ladder, TheGameText->fetch("GUI:ChooseLadder"), normalColor);
    GadgetComboBoxSetItemData(m_ladder, index, (void *)-1);
    GadgetComboBoxSetSelectedPos(m_ladder, selectedPos);
    *(unsigned char *)0x012F4814 = FALSE;
    ((Rva005082D0PopulateSide *)this)->populateQMSideComboBox(
        pref.getSide(), getLadderInfo(m_ladder));
}
