// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/languagefilter /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
