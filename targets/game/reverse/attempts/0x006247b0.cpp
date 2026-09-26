// ?PopulatePlayerTemplateComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z
// partial score=0.54 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
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
