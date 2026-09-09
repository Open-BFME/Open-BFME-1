// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/gamewindowlist /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Real source for the BFME radio-button system callback.  The callback table
// registration is in GameWindowManager::gogoGadgetRadioButton; the reference
// constants and RadioButtonData layout are in Gadget.h.

// The campaign AsciiString shim supplies the shared StringBase template.  Use
// the inline forwarding UnicodeString wrapper for the by-value label argument,
// then let the established BFME headers supply the complete window layouts.
#include "Common/AsciiString.h"
#define ASCIISTRING_H
#define UNICODESTRING_H

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

#define __PLACEMENT_VEC_NEW_INLINE
#include "GameClient/Gadget.h"

class GameWindowManager
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual void _bfme_pad_5C() = 0;
	virtual void _bfme_pad_60() = 0;
	virtual void _bfme_pad_64() = 0;
	virtual void _bfme_pad_68() = 0;
	virtual void _bfme_pad_6C() = 0;
	virtual void _bfme_pad_70() = 0;
	virtual void _bfme_pad_74() = 0;
	virtual void _bfme_pad_78() = 0;
	virtual void _bfme_pad_7C() = 0;
	virtual void _bfme_pad_80() = 0;
	virtual void _bfme_pad_84() = 0;
	virtual void _bfme_pad_88() = 0;
	virtual void _bfme_pad_8C() = 0;
	virtual void _bfme_pad_90() = 0;
	virtual void _bfme_pad_94() = 0;
	virtual void _bfme_pad_98() = 0;
	virtual void _bfme_pad_9C() = 0;
	virtual void _bfme_pad_A0() = 0;
	virtual void _bfme_pad_A4() = 0;
	virtual void _bfme_pad_A8() = 0;
	virtual void _bfme_pad_AC() = 0;
	virtual void _bfme_pad_B0() = 0;
	virtual void _bfme_pad_B4() = 0;
	virtual void _bfme_pad_B8() = 0;
	virtual void _bfme_pad_BC() = 0;
	virtual void _bfme_pad_C0() = 0;
	virtual void _bfme_pad_C4() = 0;
	virtual void _bfme_pad_C8() = 0;
	virtual void _bfme_pad_CC() = 0;
	virtual void _bfme_pad_D0() = 0;
	virtual void winSendSystemMsg(GameWindow *window, UnsignedInt msg,
		WindowMsgData mData1, WindowMsgData mData2) = 0;
	virtual GameWindow *winGetWindowList() = 0;
};

extern GameWindowManager *TheWindowManager;

static void doRadioUnselect(GameWindow *window, Int group, Int screen,
	GameWindow *except)
{
	if (window != except && BitTest(window->winGetStyle(), GWS_RADIO_BUTTON))
	{
		RadioButtonData *radioData = (RadioButtonData *)window->winGetUserData();
		if (radioData->group == group && radioData->screen == screen)
		{
			WinInstanceData *instData = window->winGetInstanceData();
			BitClear(instData->m_state, WIN_STATE_SELECTED);
		}
	}

	GameWindow *child;
	for (child = window->winGetChild(); child; child = child->winGetNext())
		doRadioUnselect(child, group, screen, except);
}

static void unselectOtherRadioOfGroup(Int group, Int screen, GameWindow *except)
{
	GameWindow *window = TheWindowManager->winGetWindowList();
	for (window = TheWindowManager->winGetWindowList(); window;
		window = window->winGetNext())
		doRadioUnselect(window, group, screen, except);
}

// ?GadgetRadioButtonSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType GadgetRadioButtonSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GBM_SET_SELECTION:
		{
			if (BitTest(instData->getState(), WIN_STATE_SELECTED) == FALSE)
			{
				if ((Bool)mData1 == TRUE)
				{
					TheWindowManager->winSendSystemMsg(window->winGetOwner(),
																					GBM_SELECTED,
																					(WindowMsgData)window,
																					0);
				}

				RadioButtonData *radioData = (RadioButtonData *)window->winGetUserData();
				if (radioData->group != 0)
					unselectOtherRadioOfGroup(radioData->group, radioData->screen, window);

				BitSet(instData->m_state, WIN_STATE_SELECTED);
			}

			break;

		}

		case GGM_SET_LABEL:
		{
			window->GameWindow::winSetText(*(UnicodeString *)mData1);
			break;

		}

		case GWM_CREATE:
			break;

		case GWM_DESTROY:
		{
			RadioButtonData *radioData = (RadioButtonData *)window->winGetUserData();

			delete radioData;

			break;

		}

		case GWM_INPUT_FOCUS:
		{
			if (mData1 == FALSE)
				BitClear(instData->m_state, WIN_STATE_HILITED);

			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
																			GGM_FOCUS_CHANGE,
																			mData1,
																			window->winGetWindowId());

			*(Bool *)mData2 = TRUE;
			break;

		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
