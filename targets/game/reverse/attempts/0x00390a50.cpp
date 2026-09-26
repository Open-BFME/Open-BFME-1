// ?Rva00390A50PopulateRandomSideAndColor@@YAXPAVGameInfo@@@Z
// partial score=0.2082 date=2026-09-26
// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/multiplayer /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/PlayerTemplate.h"
#include "Common/MultiplayerSettings.h"
#include "Common/RandomValue.h"
#include "GameClient/MapUtil.h"
#include "GameNetwork/GameInfo.h"
#include <vector>
#include <set>

struct Rva00390A50PlayerPosition
{
    char m_flags[8];
    std::set<AsciiString> m_factions;
};

struct Rva00390A50MapMetaData
{
    char m_prefix[0x54];
    Rva00390A50PlayerPosition m_positions[8];
};

void Rva00390A50PopulateRandomSideAndColor( GameInfo *game )
{
    if (!game)
        return;

    Int i;
    std::vector<Int> startSlots;
    for (i = 0; i < ThePlayerTemplateStore->getPlayerTemplateCount(); ++i)
    {
        const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(i);
        if (pt && reinterpret_cast<const unsigned char *>(pt)[0xBD])
            startSlots.push_back(i);
    }

    for (i = 0; i < MAX_SLOTS; ++i)
    {
        GameSlot *slot = game->getSlot(i);
        if (!slot || !slot->isOccupied())
            continue;

        Int playerTemplateIdx = slot->getPlayerTemplate();
        while (playerTemplateIdx != PLAYERTEMPLATE_OBSERVER &&
               (playerTemplateIdx < 0 || playerTemplateIdx >= ThePlayerTemplateStore->getPlayerTemplateCount()))
        {
            UnsignedInt silly = GetGameLogicRandomSeed() % 7;
            for (Int n = 0; n < silly; ++n)
                GameLogicRandomValue(0, 1);

            const MapMetaData *md = TheMapCache->findMap(game->getMap());
            const std::set<AsciiString> *factions = md ?
                &static_cast<const Rva00390A50MapMetaData *>(static_cast<const void *>(md))->m_positions[slot->getStartPos()].m_factions : 0;
            if (factions && factions->size())
            {
                std::vector<Int> possibleSlots;
                for (std::vector<Int>::const_iterator it = startSlots.begin(); it != startSlots.end(); ++it)
                {
                    const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(*it);
                    AsciiString name = pt->getName();
                    if ((*factions).find(name) != (*factions).end())
                        possibleSlots.push_back(*it);
                }
                playerTemplateIdx = possibleSlots[GameLogicRandomValue(0, 1000) % possibleSlots.size()];
            }
            else
            {
                playerTemplateIdx = startSlots[GameLogicRandomValue(0, 1000) % startSlots.size()];
            }

            const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(playerTemplateIdx);
            if (!pt || !reinterpret_cast<const unsigned char *>(pt)[0xBD])
                playerTemplateIdx = -1;
            else
                slot->setPlayerTemplate(playerTemplateIdx);
        }

        Int colorIdx = slot->getColor();
        if (colorIdx < 0 || colorIdx >= TheMultiplayerSettings->getNumColors())
        {
            while (colorIdx == -1)
            {
                colorIdx = GameLogicRandomValue(0, TheMultiplayerSettings->getNumColors() - 1);
                if (game->isColorTaken(colorIdx))
                    colorIdx = -1;
            }
            slot->setColor(colorIdx);
        }
    }
}

