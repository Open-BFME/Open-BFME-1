// ?PopulatePlayerTemplateComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z
// partial score=0.53 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

// gap port rva=0x006247B0 size=756, zh_source=GUIUtil.cpp anchor="GUI:Observer"
// ?PopulatePlayerTemplateComboBox@@YAXHPAPAVGameWindow@@PAVGameInfo@@_N@Z

#include "PreRTS.h"
#include "GameNetwork/GUIUtil.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameInfo.h"
#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/ChallengeGenerals.h"

#include <set>

// BFME adds a re-entrancy guard not present in the Zero Hour source: retail
// reads a static flag before doing anything else and bails if it is set.
static int s_bfmePopulatingPlayerTemplateCombo = 0;

static const char *playerTemplateSideText(const PlayerTemplate *fac)
{
	const char *buffer = *(const char * const *)((const char *)fac + 8);
	return buffer ? buffer + 8 : (const char *)0x0107388B;
}

void PopulatePlayerTemplateComboBox(Int comboBox, GameWindow *comboArray[], GameInfo *myGame, Bool allowObservers)
{
	if (s_bfmePopulatingPlayerTemplateCombo)
		return;

	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	UnicodeString playerTemplateName;

	GadgetComboBoxReset(comboArray[comboBox]);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM);
	Int newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("GUI:Random"), def->getColor());
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)PLAYERTEMPLATE_RANDOM);

	std::set<AsciiString> seenSides;

	for (Int c = 0; c < numPlayerTemplates; ++c)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(c);
		if (!fac)
			continue;

		AsciiString side;
		side.format("SIDE:%s", playerTemplateSideText(fac));
		if (seenSides.find(side) != seenSides.end())
			continue;

		seenSides.insert(side);

		Bool sideExists;
		UnicodeString localizedSide = TheGameText->fetch(side, &sideExists);
		if (sideExists)
		{
			newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], localizedSide, def->getColor());
			GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
		}
	}
	seenSides.clear();

	if (allowObservers)
	{
		def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_OBSERVER);
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("GUI:Observer"), def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)PLAYERTEMPLATE_OBSERVER);
	}
	GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0);
}
