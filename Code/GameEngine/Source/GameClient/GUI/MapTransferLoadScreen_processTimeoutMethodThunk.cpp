// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/languagefilter /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME5: lift processTimeout to clean C++.

#include "GameClient/LoadScreen.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetStaticText.h"

struct BFMERetailMapTransferFields
{
	unsigned char m_unreconstructed_00[0xB4];
	GameWindow *m_timeoutText;
	Int m_oldTimeout;
};

// ?processTimeout@MapTransferLoadScreen@@QAEXH@Z
void MapTransferLoadScreen::processTimeout(Int secondsLeft)
{
	BFMERetailMapTransferFields *retail = (BFMERetailMapTransferFields *)this;

	if (retail->m_oldTimeout == secondsLeft)
		return;
	retail->m_oldTimeout = secondsLeft;

	if (retail->m_timeoutText)
	{
		UnicodeString text;
		text.format(TheGameText->fetch("MapTransfer:Timeout"), secondsLeft / 60, secondsLeft % 60);
		GadgetStaticTextSetText(retail->m_timeoutText, text);
	}
}
