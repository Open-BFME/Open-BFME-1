// ?GadgetComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "Common/Language.h"
#include "Common/AudioEventRTS.h"
#include "Common/GameAudio.h"
#include "Common/Debug.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameWindowGlobal.h"

void HideListBox(GameWindow *window);

WindowMsgHandledType GadgetComboBoxSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	WinInstanceData *instData = window->winGetInstanceData();
	ComboBoxData *comboData = (ComboBoxData *)window->winGetUserData();
	switch (msg)
	{
		case GGM_SET_LABEL:
			instData->setText(*(UnicodeString *)mData1);
			break;
		case GCM_GET_TEXT:
			if (comboData->editBox)
				*(UnicodeString *)mData2 = GadgetTextEntryGetText(comboData->editBox);
			break;
		case GCM_SET_TEXT:
			if (comboData->editBox)
				GadgetTextEntrySetText(comboData->editBox, *(const UnicodeString *)mData1);
			break;
		case GEM_UPDATE_TEXT:
			TheWindowManager->winSendSystemMsg(window->winGetOwner(), GCM_UPDATE_TEXT,
				(WindowMsgData)window, 0);
			if (comboData->listBox)
			{
				GadgetListBoxSetSelected(comboData->listBox, -1);
				HideListBox(window);
			}
			break;
		case GEM_EDIT_DONE:
			if ((GameWindow *)mData1 == comboData->editBox)
			{
				HideListBox(window);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(), GCM_SELECTED,
					(WindowMsgData)window, 0);
			}
			break;
		case GCM_SET_SELECTION:
		{
			GameWindow *listBox = GadgetComboBoxGetListBox(window);
			if (listBox)
			{
				if (!listBox->winIsHidden() && mData2 == TRUE)
					comboData->dontHide = TRUE;
				GadgetListBoxSetSelected(listBox, (Int)mData1);
			}
			break;
		}
		case GCM_GET_SELECTION:
			if (comboData->listBox)
				GadgetListBoxGetSelected(comboData->listBox, (Int *)mData2);
			else
			{
				DEBUG_ASSERTCRASH(0, ("We don't have a listbox as part of the combo box"));
				*(Int *)mData2 = -1;
			}
			break;
		case GCM_SET_ITEM_DATA:
			if (comboData->listBox)
				GadgetListBoxSetItemData(comboData->listBox, (void *)mData2, (Int)mData1);
			break;
		case GCM_GET_ITEM_DATA:
			if (comboData->listBox)
				*(void **)mData2 = GadgetListBoxGetItemData(comboData->listBox, (Int)mData1, 0);
			break;
		case GLM_SELECTED:
			if ((GameWindow *)mData1 == comboData->listBox)
			{
				if (comboData->dontHide == TRUE)
					comboData->dontHide = FALSE;
				else
					HideListBox(window);
				if (mData2 == -1)
					break;
				UnicodeString tempUString;
				Color color;
				tempUString = GadgetListBoxGetTextAndColor(comboData->listBox, &color, mData2, 0);
				GadgetTextEntrySetTextColor(comboData->editBox, color);
				GadgetTextEntrySetText(comboData->editBox, tempUString);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(), GCM_SELECTED,
					(WindowMsgData)window, 0);
			}
			break;
		case GGM_LEFT_DRAG:
			break;
		case GCM_DEL_ALL:
			if (comboData->listBox)
				GadgetListBoxReset(comboData->listBox);
			if (comboData->editBox)
				GadgetTextEntrySetText(comboData->editBox, UnicodeString.TheEmptyString);
			comboData->entryCount = 0;
			break;
		case GCM_DEL_ENTRY:
			break;
		case GGM_CLOSE:
			HideListBox(window);
			break;
		case GCM_ADD_ENTRY:
		{
			GameWindow *listBox = GadgetComboBoxGetListBox(window);
			ListboxData *listData = (ListboxData *)listBox->winGetUserData();
			Int addedIndex = -1;
			if (listBox)
			{
				comboData->entryCount++;
				if (comboData->entryCount >= listData->listLength)
					GadgetListBoxSetListLength(listBox, listData->listLength * 2);
				addedIndex = GadgetListBoxAddEntryText(listBox, *(UnicodeString *)mData1, mData2, -1, 0);
				ICoord2D winSize;
				ICoord2D newSize;
				ICoord2D editBoxSize;
				Int listX;
				Int multiplier;
				WinInstanceData *listInstData = listBox->winGetInstanceData();
				GameWindow *editBox = GadgetComboBoxGetEditBox(window);
				window->winGetSize(&winSize.x, &winSize.y);
				editBox->winGetSize(&editBoxSize.x, &editBoxSize.y);
				if (comboData->entryCount <= comboData->maxDisplay)
				{
					multiplier = comboData->entryCount;
					listX = winSize.x + 16;
					if (listData->upButton) listData->upButton->winHide(TRUE);
					if (listData->downButton) listData->downButton->winHide(TRUE);
					if (listData->slider) listData->slider->winHide(TRUE);
				}
				else
				{
					multiplier = comboData->maxDisplay;
					listX = winSize.x;
					if (listData->upButton) listData->upButton->winHide(FALSE);
					if (listData->downButton) listData->downButton->winHide(FALSE);
					if (listData->slider) listData->slider->winHide(FALSE);
				}
				newSize.y = TheWindowManager->winFontHeight(listInstData->getFont()) * multiplier + multiplier * 2 + 4;
				listBox->winSetPosition(0, editBoxSize.y);
				listBox->winSetSize(listX, newSize.y);
			}
			return (WindowMsgHandledType)addedIndex;
		}
		case GWM_CREATE:
			break;
		case GGM_RESIZED:
		{
			Int width = (Int)mData1;
			Int height = (Int)mData2;
			ICoord2D dropDownSize;
			comboData->dropDownButton->winGetSize(&dropDownSize.x, &dropDownSize.y);
			GameWindow *listBox = GadgetComboBoxGetListBox(window);
			if (listBox->winIsHidden())
			{
				if (listBox) listBox->winSetSize(width, height);
				if (comboData->dropDownButton)
					comboData->dropDownButton->winSetPosition(width - dropDownSize.x, 0);
				if (comboData->editBox)
				{
					comboData->editBox->winSetPosition(0, 0);
					comboData->editBox->winSetSize(width - dropDownSize.x, height);
				}
			}
			break;
		}
		case GWM_DESTROY:
			TheWindowManager->winSetLoneWindow(NULL);
			if (comboData)
			{
				delete comboData;
				comboData = NULL;
			}
			break;
		case GWM_INPUT_FOCUS:
		{
			if (mData1 == FALSE)
				BitClear(instData->m_state, WIN_STATE_HILITED);
			else
				BitSet(instData->m_state, WIN_STATE_HILITED);
			TheWindowManager->winSendSystemMsg(window->winGetOwner(), GGM_FOCUS_CHANGE,
				mData1, window->winGetWindowId());
			Bool wantsFocus = FALSE;
			GameWindow *editBox = GadgetComboBoxGetEditBox(window);
			TheWindowManager->winSendSystemMsg(editBox, GWM_INPUT_FOCUS, mData1,
				(WindowMsgData)&wantsFocus);
			*(Bool *)mData2 = TRUE;
			break;
		}
		case GBM_SELECTED:
			if ((GameWindow *)mData1 == comboData->dropDownButton)
			{
				ICoord2D winSize;
				ICoord2D newSize;
				Int listX = 0;
				Int multiplier;
				comboData->dontHide = FALSE;
				GameWindow *listBox = GadgetComboBoxGetListBox(window);
				if (listBox)
				{
					TheWindowManager->winSetLoneWindow(window);
					if (listBox->winIsHidden())
					{
						listBox->winHide(FALSE);
						window->winGetSize(&winSize.x, &winSize.y);
						WinInstanceData *listInstData = listBox->winGetInstanceData();
						ListboxData *listData = (ListboxData *)listBox->winGetUserData();
						if (comboData->entryCount <= comboData->maxDisplay)
						{
							multiplier = comboData->entryCount;
							listX = winSize.x;
							if (listData->upButton) listData->upButton->winHide(TRUE);
							if (listData->downButton) listData->downButton->winHide(TRUE);
							if (listData->slider) listData->slider->winHide(TRUE);
						}
						else
						{
							multiplier = comboData->maxDisplay;
							listX = winSize.x;
							if (listData->upButton) listData->upButton->winHide(FALSE);
							if (listData->downButton) listData->downButton->winHide(FALSE);
							if (listData->slider) listData->slider->winHide(FALSE);
						}
						newSize.y = TheWindowManager->winFontHeight(listInstData->getFont()) * multiplier + multiplier * 2 + 4;
						window->winSetSize(winSize.x, winSize.y + newSize.y);
						listBox->winSetPosition(0, winSize.y);
						listBox->winSetSize(listX, newSize.y);
					}
					else
						HideListBox(window);
				}
			}
			break;
		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
