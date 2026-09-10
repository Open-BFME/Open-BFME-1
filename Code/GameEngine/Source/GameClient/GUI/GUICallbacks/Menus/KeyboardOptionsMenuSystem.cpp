// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "../../../../../../reference/shims/displaystring/GameClient/DisplayString.h"

#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameText.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/Shell.h"

struct BfmeKeyboardSystemLookupListRec
{
	const char *name;
	Int value;
};

struct BfmeKeyboardSystemMetaMapRec
{
	BfmeKeyboardSystemMetaMapRec *m_next;
	UnsignedInt m_meta;
	UnsignedInt m_key;
	UnsignedInt m_transition;
	UnsignedInt m_modState;
	UnsignedInt m_usableIn;
	MappableKeyCategories m_category;
	UnicodeString m_description;
	UnicodeString m_displayName;
};

struct BfmeKeyboardSystemMetaMap
{
	unsigned char m_base[8];
	BfmeKeyboardSystemMetaMapRec *m_metaMaps;
};

struct BfmeKeyboardSystemEntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	Bool secretText;
	Bool numericalOnly;
	Bool alphaNumericalOnly;
	Bool aSCIIOnly;
	Short maxTextLen;
	Bool receivedUnichar;
	Bool drawTextFromStart;
	GameWindow *constructList;
	void *bfmeEntryPad;
	UnsignedShort charPos;
	UnsignedShort conCharPos;
};

// These are the private KeyboardOptionsMenu objects in the retail compiland.
#define kButtonBackID (*(NameKeyType *)0x012F3AAC)
#define kComboBoxCategoryListID (*(NameKeyType *)0x012F3ABC)
#define kComboBoxCategoryList (*(GameWindow **)0x012F3AC0)
#define kListBoxCommandListID (*(NameKeyType *)0x012F3AC4)
#define kListBoxCommandList (*(GameWindow **)0x012F3AC8)
#define kStaticTextDescription (*(GameWindow **)0x012F3AD0)
#define kStaticTextCurrentHotkey (*(GameWindow **)0x012F3AD8)
#define kButtonResetAllID (*(NameKeyType *)0x012F3ADC)
#define kTextEntryAssignHotkey (*(GameWindow **)0x012F3AE8)
#define kButtonAssignID (*(NameKeyType *)0x012F3AEC)
#define kAlt (*(UnicodeString *)0x012F3AF8)
#define kCtrl (*(UnicodeString *)0x012F3AFC)
#define kShift (*(UnicodeString *)0x012F3B00)
#define kTheEmptyString (*(UnicodeString *)0x01336E54)
#define kGuiNull ((const Char *)0x010FEF88)
#define kCategoryList ((const BfmeKeyboardSystemLookupListRec *)0x010FE7E0)
#define kKeyNames ((const BfmeKeyboardSystemLookupListRec *)0x010FE828)

extern void populateCategoryBox();
extern void fillCommandListBox(MappableKeyCategories cat);
extern void setKeyDown(UnicodeString mod, Bool down);

// ?KeyboardOptionsMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType KeyboardOptionsMenuSystem(GameWindow *window,
	UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	switch (msg)
	{
	case GWM_CREATE:
		break;

	case GWM_DESTROY:
		break;

	case GWM_INPUT_FOCUS:
		if (mData1 == TRUE)
			*(Bool *)mData2 = TRUE;
		return MSG_HANDLED;

	case 0x4008: // BFME GBM_SELECTED
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == kButtonBackID)
		{
			TheShell->pop();
		}
		else if (controlID == kButtonAssignID)
		{
		}
		else if (controlID == kButtonResetAllID)
		{
			populateCategoryBox();
			fillCommandListBox((MappableKeyCategories)0);
			GadgetStaticTextSetText(kStaticTextCurrentHotkey,
				TheGameText->fetch(kGuiNull));

			BfmeKeyboardSystemEntryData *e =
				(BfmeKeyboardSystemEntryData *)kTextEntryAssignHotkey->winGetUserData();
				e->text->setText(kTheEmptyString);
			e->charPos = e->text->getTextLength();
			setKeyDown(kAlt, false);
			setKeyDown(kCtrl, false);
			setKeyDown(kShift, false);
			kTextEntryAssignHotkey->winEnable(false);
		}
		break;
	}

	case 0x4025: // BFME GCM_SELECTED
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == kComboBoxCategoryListID)
		{
			Int selected;
			GadgetComboBoxGetSelectedPos(kComboBoxCategoryList, &selected);
			BfmeKeyboardSystemLookupListRec rec = kCategoryList[selected];
			MappableKeyCategories cat = (MappableKeyCategories)rec.value;
			fillCommandListBox(cat);
			GadgetStaticTextSetText(kStaticTextDescription,
				TheGameText->fetch(kGuiNull));
			GadgetStaticTextSetText(kStaticTextCurrentHotkey,
				TheGameText->fetch(kGuiNull));

			BfmeKeyboardSystemEntryData *e =
				(BfmeKeyboardSystemEntryData *)kTextEntryAssignHotkey->winGetUserData();
				e->text->setText(kTheEmptyString);
				UnsignedShort charPos = e->text->getTextLength();
				GameWindow *assignHotkey = kTextEntryAssignHotkey;
				e->charPos = charPos;
				assignHotkey->winEnable(false);
		}
		break;
	}

	case 0x4014: // BFME GLM_SELECTED
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == kListBoxCommandListID)
		{
			Int selected;
			GadgetListBoxGetSelected(kListBoxCommandList, &selected);
			UnicodeString str;
			str = GadgetListBoxGetText(kListBoxCommandList, selected);

			for (const BfmeKeyboardSystemMetaMapRec *rec =
				((BfmeKeyboardSystemMetaMap *)TheMetaMap)->m_metaMaps;
				rec; rec = rec->m_next)
			{
				if (((const StringBase<unsigned short> *)&rec->m_displayName)->compare(
					*(const StringBase<unsigned short> *)&str) == 0)
				{
					GadgetStaticTextSetText(kStaticTextDescription,
						rec->m_description);
					UnsignedInt type = rec->m_key;
					kTextEntryAssignHotkey->winEnable(true);

					const BfmeKeyboardSystemLookupListRec *keyName = kKeyNames;
					if (kKeyNames->name)
					{
						do
						{
							if ((UnsignedInt)keyName->value == type)
							{
								const char *cptr = keyName->name;
								AsciiString aStr;
								aStr.format(cptr);
								UnicodeString uStr;
								uStr.translate(aStr);
								GadgetStaticTextSetText(kStaticTextCurrentHotkey,
									uStr);
								break;
							}
							++keyName;
						} while (keyName->name);
					}
					break;
				}
			}
		}
		break;
	}

	default:
		return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
