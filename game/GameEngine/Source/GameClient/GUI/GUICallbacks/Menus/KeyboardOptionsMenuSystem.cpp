// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "../../../../../../inputs/reference/shims/displaystring/GameClient/DisplayString.h"

#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameText.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/Shell.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

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
extern NameKeyType g_012F3AAC;
extern NameKeyType g_012F3ABC;
extern GameWindow *g_012F3AC0;
extern NameKeyType g_012F3AC4;
extern GameWindow *g_012F3AC8;
extern GameWindow *g_012F3AD0;
extern GameWindow *g_012F3AD8;
extern NameKeyType g_012F3ADC;
extern GameWindow *g_012F3AE8;
extern NameKeyType g_012F3AEC;
extern UnicodeString alt;
extern UnicodeString ctrl;
extern UnicodeString shift;
extern const BfmeKeyboardSystemLookupListRec g_010FE7E0[];
extern const BfmeKeyboardSystemLookupListRec g_010FE828[];

#define kButtonBackID g_012F3AAC
#define kComboBoxCategoryListID g_012F3ABC
#define kComboBoxCategoryList g_012F3AC0
#define kListBoxCommandListID g_012F3AC4
#define kListBoxCommandList g_012F3AC8
#define kStaticTextDescription g_012F3AD0
#define kStaticTextCurrentHotkey g_012F3AD8
#define kButtonResetAllID g_012F3ADC
#define kTextEntryAssignHotkey g_012F3AE8
#define kButtonAssignID g_012F3AEC
#define kAlt alt
#define kCtrl ctrl
#define kShift shift
#define kTheEmptyString UnicodeString::TheEmptyString
#define kGuiNull "GUI:NULL"
#define kCategoryList g_010FE7E0
#define kKeyNames g_010FE828

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

extern const BfmeKeyboardSystemLookupListRec g_010FE7E0[9];
extern "C" const BfmeKeyboardSystemLookupListRec
	__identifier("?g_010FE7E0@@3QBUBfmeKeyboardSystemLookupListRec@@B")[9] =
{
	{ "CONTROL", 0 },
	{ "INFORMATION", 1 },
	{ "INTERFACE", 2 },
	{ "SELECTION", 3 },
	{ "TAUNT", 4 },
	{ "TEAM", 5 },
	{ "MISC", 6 },
	{ "DEBUG", 7 },
	{ 0, 0 },
};

extern const BfmeKeyboardSystemLookupListRec g_010FE828[87];
extern "C" const BfmeKeyboardSystemLookupListRec
	__identifier("?g_010FE828@@3QBUBfmeKeyboardSystemLookupListRec@@B")[87] =
{
	{ "KEY_ESC", 1 },
	{ "KEY_BACKSPACE", 14 },
	{ "KEY_ENTER", 28 },
	{ "KEY_SPACE", 57 },
	{ "KEY_TAB", 15 },
	{ "KEY_F1", 59 },
	{ "KEY_F2", 60 },
	{ "KEY_F3", 61 },
	{ "KEY_F4", 62 },
	{ "KEY_F5", 63 },
	{ "KEY_F6", 64 },
	{ "KEY_F7", 65 },
	{ "KEY_F8", 66 },
	{ "KEY_F9", 67 },
	{ "KEY_F10", 68 },
	{ "KEY_F11", 87 },
	{ "KEY_F12", 88 },
	{ "KEY_A", 30 },
	{ "KEY_B", 48 },
	{ "KEY_C", 46 },
	{ "KEY_D", 32 },
	{ "KEY_E", 18 },
	{ "KEY_F", 33 },
	{ "KEY_G", 34 },
	{ "KEY_H", 35 },
	{ "KEY_I", 23 },
	{ "KEY_J", 36 },
	{ "KEY_K", 37 },
	{ "KEY_L", 38 },
	{ "KEY_M", 50 },
	{ "KEY_N", 49 },
	{ "KEY_O", 24 },
	{ "KEY_P", 25 },
	{ "KEY_Q", 16 },
	{ "KEY_R", 19 },
	{ "KEY_S", 31 },
	{ "KEY_T", 20 },
	{ "KEY_U", 22 },
	{ "KEY_V", 47 },
	{ "KEY_W", 17 },
	{ "KEY_X", 45 },
	{ "KEY_Y", 21 },
	{ "KEY_Z", 44 },
	{ "KEY_1", 2 },
	{ "KEY_2", 3 },
	{ "KEY_3", 4 },
	{ "KEY_4", 5 },
	{ "KEY_5", 6 },
	{ "KEY_6", 7 },
	{ "KEY_7", 8 },
	{ "KEY_8", 9 },
	{ "KEY_9", 10 },
	{ "KEY_0", 11 },
	{ "KEY_KP1", 79 },
	{ "KEY_KP2", 80 },
	{ "KEY_KP3", 81 },
	{ "KEY_KP4", 75 },
	{ "KEY_KP5", 76 },
	{ "KEY_KP6", 77 },
	{ "KEY_KP7", 71 },
	{ "KEY_KP8", 72 },
	{ "KEY_KP9", 73 },
	{ "KEY_KP0", 82 },
	{ "KEY_MINUS", 12 },
	{ "KEY_EQUAL", 13 },
	{ "KEY_LBRACKET", 26 },
	{ "KEY_RBRACKET", 27 },
	{ "KEY_SEMICOLON", 39 },
	{ "KEY_APOSTROPHE", 40 },
	{ "KEY_TICK", 41 },
	{ "KEY_BACKSLASH", 43 },
	{ "KEY_COMMA", 51 },
	{ "KEY_PERIOD", 52 },
	{ "KEY_SLASH", 53 },
	{ "KEY_UP", 200 },
	{ "KEY_DOWN", 208 },
	{ "KEY_LEFT", 203 },
	{ "KEY_RIGHT", 205 },
	{ "KEY_HOME", 199 },
	{ "KEY_END", 207 },
	{ "KEY_PGUP", 201 },
	{ "KEY_PGDN", 209 },
	{ "KEY_INS", 210 },
	{ "KEY_DEL", 211 },
	{ "KEY_KPSLASH", 181 },
	{ "KEY_NONE", 0 },
	{ 0, 0 },
};
