// ?d_005082d0@@YAXXZ
// partial score=0.33 date=2026-09-26
// ?populateQMSideComboBox@Rva005082D0PopulateSide@@QAEXHPBVLadderInfo@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameInfo.h"
#include "GameNetwork/GameSpy/LadderDefs.h"

#include <algorithm>
#include <set>

extern void j_00007004(void);
extern void j_00021ec2(void);
extern void j_0002f338(void);
extern void j_0001d01b(void);
extern void j_00037bd2(void);
extern void j_000439c3(void);
extern void j_0004a1fb(void);

union GetColorThunk
{
    void (*function)(void);
    MultiplayerColorDefinition * (MultiplayerSettings::*member)(Int);
};

union GetNthThunk
{
    void (*function)(void);
    const PlayerTemplate * (PlayerTemplateStore::*member)(Int) const;
};

union WinEnableThunk
{
    void (*function)(void);
    Int (GameWindow::*member)(Bool);
};

class Rva005082D0PopulateSide
{
public:
    void populateQMSideComboBox(Int favSide, const LadderInfo *li = NULL);

private:
    char m_unmodelled[0x254];
    GameWindow *m_side;
};

class Rva005082D0PlayerTemplateView
{
public:
    const AsciiString &getSide() const
    {
        return *(const AsciiString *)((const char *)this + 8);
    }

    Bool isPlayableSide() const
    {
        return *(const Bool *)((const char *)this + 0xbd);
    }
};

void Rva005082D0PopulateSide::populateQMSideComboBox(Int favSide, const LadderInfo *li)
{
    Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
    UnicodeString playerTemplateName;

    ((void (__cdecl *)(GameWindow *))j_00007004)(m_side);

    GetColorThunk getColor;
    getColor.function = j_00021ec2;
    MultiplayerColorDefinition *def = (TheMultiplayerSettings->*getColor.member)(PLAYERTEMPLATE_RANDOM);
    Int newIndex = ((Int (__cdecl *)(GameWindow *, UnicodeString, Int))j_0002f338)(m_side, TheGameText->fetch("GUI:Random"), def->getColor());
    ((void (__cdecl *)(GameWindow *, Int, void *))j_0001d01b)(m_side, newIndex, (void *)PLAYERTEMPLATE_RANDOM);

    std::set<AsciiString> seenSides;

    Int entryToSelect = 0;
    GetNthThunk getNth;
    getNth.function = j_00037bd2;
    Int c;

    for (c = 0; c < numPlayerTemplates; ++c)
    {
        const PlayerTemplate *fac = (ThePlayerTemplateStore->*getNth.member)(c);
        if (!fac)
            continue;

        const Rva005082D0PlayerTemplateView *bfmeFac = (const Rva005082D0PlayerTemplateView *)fac;
        if (!bfmeFac->isPlayableSide())
            continue;

        {
            AsciiString side;
            const AsciiString &facSide = bfmeFac->getSide();
            side.format("SIDE:%s", facSide.str());
            if (seenSides.find(side) != seenSides.end())
                continue;

            if (li)
            {
                if (std::find(li->validFactions.begin(), li->validFactions.end(), facSide) == li->validFactions.end())
                    continue;
            }

            seenSides.insert(side);

            newIndex = ((Int (__cdecl *)(GameWindow *, UnicodeString, Int))j_0002f338)(m_side, TheGameText->fetch(side), def->getColor());
            ((void (__cdecl *)(GameWindow *, Int, void *))j_0001d01b)(m_side, newIndex, (void *)c);

            if (c == favSide)
                entryToSelect = newIndex;
        }
    }
    seenSides.clear();

    ((void (__cdecl *)(GameWindow *, Int, Bool))j_000439c3)(m_side, entryToSelect, TRUE);
    if (li && li->randomFactions)
    {
        WinEnableThunk winEnable;
        winEnable.function = j_0004a1fb;
        (m_side->*winEnable.member)(FALSE);
    }
    else
    {
        WinEnableThunk winEnable;
        winEnable.function = j_0004a1fb;
        (m_side->*winEnable.member)(TRUE);
    }
}
