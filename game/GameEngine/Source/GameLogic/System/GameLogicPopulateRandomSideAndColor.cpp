// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/multiplayer /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00390A50, 1071 bytes through RET at +0x42E: populateRandomSideAndColor.
// Identity: Zero Hour's static populateRandomSideAndColor (GameLogic.cpp) is
// the same algorithm: collect playable player templates, then for each
// occupied slot replace a random side (discard GetGameLogicRandomSeed()%7
// values, pick GameLogicRandomValue(0,1000)%size) and a random color
// (getNumColors, isColorTaken). Its only caller is the matched
// GameLogic::startNewGame (0x00394260), which calls it right after
// populateRandomStartPosition (0x00390F90, the next function in the image,
// as in Zero Hour's source order). BFME swapped the two calls because the
// side is now filtered by the slot's start position: the map's per-position
// record (20 bytes from MapMetaData+0x54, a faction set at +8) limits the
// candidates to the templates named in that set.
// BFME tests PlayerTemplate::isPlayableSide() (+0xBD m_playableSide) where
// Zero Hour tested the starting building. The seed getter is the matched
// 6-byte global getter Rva00096A50Get, which sits directly before
// GetGameLogicRandomSeedCRC as GetGameLogicRandomSeed does in Zero Hour.
// GetGameLogicRandomValue receives retail's __FILE__ literal and lines.
#include "PreRTS.h"
#include "Common/PlayerTemplate.h"
#include "Common/MultiplayerSettings.h"
#include "GameClient/MapUtil.h"
#include "GameLogic/LogicRandomValue.h"
#include "GameNetwork/GameInfo.h"
#include <vector>
#include <set>

#define GAMELOGIC_SOURCE_FILE "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\System\\GameLogic.cpp"

extern Int Rva00096A50Get(void);

// BFME's MapMetaData keeps one 20-byte record per start position from +0x54;
// only the faction set at +8 of a record is read here.
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

// BFME's PlayerTemplate keeps m_playableSide at +0xBD (witnessed; the Zero Hour
// layout in the included header places it four bytes earlier).
struct Rva00390A50PlayableSideView
{
	UnsignedByte m_beforePlayableSide[0xBD];
	Bool m_playableSide;
};

static inline Bool isPlayableSide(const PlayerTemplate *pt)
{
	return reinterpret_cast<const Rva00390A50PlayableSideView *>(pt)->m_playableSide;
}

void populateRandomSideAndColor( GameInfo *game )
{
	if(!game)
		return;
	Int i;

	std::vector<Int> startSlots;
	for (i = 0; i < ThePlayerTemplateStore->getPlayerTemplateCount(); ++i)
	{
		const PlayerTemplate* ptTest = ThePlayerTemplateStore->getNthPlayerTemplate(i);
		if (!ptTest || !isPlayableSide(ptTest))
			continue;

		startSlots.push_back(i);
	}

	for (i=0; i<MAX_SLOTS; ++i)
	{
		GameSlot *slot = game->getSlot(i);

		if (!slot || !slot->isOccupied())
			continue;

		// clean up random factions
		Int playerTemplateIdx = slot->getPlayerTemplate();
		while (playerTemplateIdx != PLAYERTEMPLATE_OBSERVER && (playerTemplateIdx < 0 || playerTemplateIdx >= ThePlayerTemplateStore->getPlayerTemplateCount()))
		{
			UnsignedInt silly = (UnsignedInt)Rva00096A50Get() % 7;
			for (Int poo = 0; poo < silly; ++poo)
			{
				GetGameLogicRandomValue(0, 1, GAMELOGIC_SOURCE_FILE, 1573);	// ignore result
			}

			const MapMetaData *md = TheMapCache->findMap(game->getMap());
			if (md)
			{
				const Rva00390A50PlayerPosition &position =
					static_cast<const Rva00390A50MapMetaData *>(static_cast<const void *>(md))->m_positions[slot->getStartPos()];
				// Retail reads the count through the record, then turns the same
				// register into the set pointer (add eax,8) and spills it before
				// the test: the count is taken first, the set bound second.
				Int numFactions = position.m_factions.size();
				const std::set<AsciiString> &factions = position.m_factions;
				if (numFactions != 0)
				{
					std::vector<Int> possibleSlots;
					for (std::vector<Int>::iterator it = startSlots.begin(); it != startSlots.end(); ++it)
					{
						AsciiString name = ThePlayerTemplateStore->getNthPlayerTemplate(*it)->getName();
						if (factions.find(name) != factions.end())
							possibleSlots.push_back(*it);
					}
					playerTemplateIdx = possibleSlots[GetGameLogicRandomValue(0, 1000, GAMELOGIC_SOURCE_FILE, 1595) % possibleSlots.size()];
				}
			}

			if (playerTemplateIdx < 0 || playerTemplateIdx >= ThePlayerTemplateStore->getPlayerTemplateCount())
			{
				Int idxIdx = GetGameLogicRandomValue(0, 1000, GAMELOGIC_SOURCE_FILE, 1602) % startSlots.size();
				playerTemplateIdx = startSlots[idxIdx];
			}

			const PlayerTemplate* pt = ThePlayerTemplateStore->getNthPlayerTemplate(playerTemplateIdx);
			if (!pt || !isPlayableSide(pt))
			{
				playerTemplateIdx = -1; // only pick playable factions
			}
			else
			{
				slot->setPlayerTemplate(playerTemplateIdx);
			}
		}

		Int colorIdx = slot->getColor();
		if (colorIdx < 0 || colorIdx >= TheMultiplayerSettings->getNumColors())
		{
			while (colorIdx == -1)
			{
				colorIdx = GetGameLogicRandomValue(0, TheMultiplayerSettings->getNumColors()-1, GAMELOGIC_SOURCE_FILE, 1630);
				if (game->isColorTaken(colorIdx))
					colorIdx = -1;
			}
			slot->setColor(colorIdx);
		}
	}
}
