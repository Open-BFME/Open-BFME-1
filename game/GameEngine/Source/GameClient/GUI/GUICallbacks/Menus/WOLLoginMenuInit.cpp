// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native WOLLoginMenuInit at 00500A20, 3164 bytes.
// Derived from the Zero Hour source; Copyright 2025 Electronic Arts Inc.
// GPL-3.0-or-later. BFME identity and layout witnesses:
// targets/game/reverse/identity_evidence/00500a20-login-init.md.
#define _WCTYPE_INLINE_DEFINED
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a, const AsciiString &b)const {return a.compare(b)<0;} }; }

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

// The legacy window header embeds its own UnicodeString in unused inline
// accessors. Give that header-only view a distinct name while preserving the
// canonical native strings used by this body.
#undef UNICODESTRING_H
#define UnicodeString Rva00500A20HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
#include "Common/FileSystem.h"
#include "Common/Registry.h"
#include "Common/UserPreferences.h"
#include "GameClient/GameText.h"
#include "GameClient/Shell.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/MessageBox.h"
extern Color GameSpyColor[];
enum {GSCOLOR_DEFAULT=0};
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/WOLBrowser/WebBrowser.h"
template <> inline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <> inline unsigned short StringBase<unsigned short>::getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
#undef iswspace
extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short);

class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences() {}

	virtual Bool load(AsciiString fname);
	virtual Bool write(void);

	AsciiString getPasswordForEmail( AsciiString email );
	AsciiString getDateForEmail( AsciiString email, AsciiString &month, AsciiString &date, AsciiString &year  );
	AsciiStringList getNicksForEmail( AsciiString email );
	void addLogin( AsciiString email, AsciiString nick, AsciiString password, AsciiString date );
	void forgetLogin( AsciiString email );
	AsciiStringList getEmails( void );

private:
	typedef std::map<AsciiString, AsciiString> PassMap;
	typedef std::map<AsciiString, AsciiString> DateMap;
	typedef std::map<AsciiString, AsciiStringList> NickMap;
	PassMap m_emailPasswordMap;
	NickMap m_emailNickMap;
	DateMap m_emailDateMap;
};

static Bool webBrowserActive = FALSE;
static Bool useWebBrowserForTOS = FALSE;

static Bool isShuttingDown = false;
static Bool buttonPushed = false;
static char *nextScreen = NULL;

static const UnsignedInt loginTimeoutInMS = 10000;
static UnsignedInt loginAttemptTime = 0;

static NameKeyType parentWOLLoginID =						NAMEKEY_INVALID;
static NameKeyType buttonBackID =								NAMEKEY_INVALID;	// profile, quick
static NameKeyType buttonLoginID =							NAMEKEY_INVALID;	// profile, quick
static NameKeyType buttonCreateAccountID =			NAMEKEY_INVALID;	// profile, quick
static NameKeyType buttonUseAccountID =					NAMEKEY_INVALID;	// quick
static NameKeyType buttonDontUseAccountID =			NAMEKEY_INVALID;	// profile
static NameKeyType buttonTOSID =								NAMEKEY_INVALID;	// TOS
static NameKeyType parentTOSID =								NAMEKEY_INVALID;	// TOS Parent
static NameKeyType buttonTOSOKID =							NAMEKEY_INVALID;	// TOS
static NameKeyType listboxTOSID =								NAMEKEY_INVALID;	// TOS
static NameKeyType comboBoxEmailID =						NAMEKEY_INVALID;	// profile
static NameKeyType comboBoxLoginNameID =				NAMEKEY_INVALID;	// profile
static NameKeyType textEntryLoginNameID =				NAMEKEY_INVALID;	// quick
static NameKeyType textEntryPasswordID =				NAMEKEY_INVALID;	// profile
static NameKeyType checkBoxRememberPasswordID =	NAMEKEY_INVALID;	// checkbox to remember information or not
static NameKeyType textEntryMonthID =				NAMEKEY_INVALID;	// profile
static NameKeyType textEntryDayID =				NAMEKEY_INVALID;	// profile
static NameKeyType textEntryYearID =				NAMEKEY_INVALID;	// profile

// Window Pointers ------------------------------------------------------------------------
static GameWindow *parentWOLLogin =						NULL;
static GameWindow *buttonBack =								NULL;
static GameWindow *buttonLogin =							NULL;
static GameWindow *buttonCreateAccount =			NULL;
static GameWindow *buttonUseAccount =					NULL;
static GameWindow *buttonDontUseAccount =			NULL;
static GameWindow *buttonTOS						=			NULL;
static GameWindow *parentTOS						=			NULL;
static GameWindow *buttonTOSOK					=			NULL;
static GameWindow *listboxTOS						=			NULL;
static GameWindow *comboBoxEmail =						NULL;
static GameWindow *comboBoxLoginName =				NULL;
static GameWindow *textEntryLoginName =				NULL;
static GameWindow *textEntryPassword =				NULL;
static GameWindow *checkBoxRememberPassword =	NULL;
static GameWindow *textEntryMonth =				NULL;
static GameWindow *textEntryDay =				NULL;
static GameWindow *textEntryYear =				NULL;

static GameSpyLoginPreferences *loginPref;
extern const UnicodeString BFMEEmptyPlayerName;
void EnableLoginControls(Bool);
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameWindowTransitions.h"
// Slot +10 is independently proved by WindowLayout vtable VA010F7514
// and the matched implementation WindowLayout::hide at 00497A00.
class Rva00500A20Layout {
public:
 virtual void slot0();
 virtual void slot4();
 virtual void slot8();
 virtual void slotC();
 virtual void hide(int);
};

void WOLLoginMenuInit( WindowLayout *layout, void *userData )
{
	nextScreen = NULL;
	buttonPushed = false;
	isShuttingDown = false;
	loginAttemptTime = 0;

	if (!loginPref)
	{
		loginPref = new GameSpyLoginPreferences;
	}

	// if the ESRB warning is blank (other country) hide the box
	GameWindow *esrbTitle = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("GameSpyLoginProfile.wnd:StaticTextESRBTop") );
	GameWindow *esrbParent = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("GameSpyLoginProfile.wnd:ParentESRB") );
	if (esrbTitle && esrbParent)
	{
		if ( GadgetStaticTextGetText( esrbTitle ).getLength() < 2 )
		{
			esrbParent->winHide(TRUE);
		}
	}

	parentWOLLoginID =						TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:WOLLoginMenuParent" );
	buttonBackID =								TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonBack" );
	buttonLoginID =								TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonLogin" );
	buttonCreateAccountID =				TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonCreateAccount" );
	buttonUseAccountID =					TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonUseAccount" );
	buttonDontUseAccountID =			TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonDontUseAccount" );
	buttonTOSID							=			TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonTOS" );
	parentTOSID							=			TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ParentTOS" );
	buttonTOSOKID						=			TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ButtonTOSOK" );
	listboxTOSID						=			TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ListboxTOS" );
	comboBoxEmailID =							TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ComboBoxEmail" );
	comboBoxLoginNameID =					TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:ComboBoxLoginName" );
	textEntryLoginNameID =				TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:TextEntryLoginName" );
	textEntryPasswordID =					TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:TextEntryPassword" );
	checkBoxRememberPasswordID =	TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:CheckBoxRememberInfo" );
	textEntryMonthID =					TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:TextEntryMonth" );
	textEntryDayID =					TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:TextEntryDay" );
	textEntryYearID =					TheNameKeyGenerator->nameToKey( "GameSpyLoginProfile.wnd:TextEntryYear" );

	parentWOLLogin =							TheWindowManager->winGetWindowFromId( NULL,  parentWOLLoginID );
	buttonBack =									TheWindowManager->winGetWindowFromId( NULL,  buttonBackID);
	buttonLogin =									TheWindowManager->winGetWindowFromId( NULL,  buttonLoginID);
	buttonCreateAccount =					TheWindowManager->winGetWindowFromId( NULL,  buttonCreateAccountID);
	buttonUseAccount =						TheWindowManager->winGetWindowFromId( NULL,  buttonUseAccountID);
	buttonDontUseAccount =				TheWindowManager->winGetWindowFromId( NULL,  buttonDontUseAccountID);
	buttonTOS =										TheWindowManager->winGetWindowFromId( NULL,  buttonTOSID);
	parentTOS =										TheWindowManager->winGetWindowFromId( NULL,  parentTOSID);
	buttonTOSOK =									TheWindowManager->winGetWindowFromId( NULL,  buttonTOSOKID);
	listboxTOS =									TheWindowManager->winGetWindowFromId( NULL,  listboxTOSID);
	comboBoxEmail =								TheWindowManager->winGetWindowFromId( NULL,  comboBoxEmailID);
	comboBoxLoginName =						TheWindowManager->winGetWindowFromId( NULL,  comboBoxLoginNameID);
	textEntryLoginName =					TheWindowManager->winGetWindowFromId( NULL,  textEntryLoginNameID);
	textEntryPassword =						TheWindowManager->winGetWindowFromId( NULL,  textEntryPasswordID);
	checkBoxRememberPassword =		TheWindowManager->winGetWindowFromId( NULL,  checkBoxRememberPasswordID);
	textEntryMonth =					TheWindowManager->winGetWindowFromId( NULL,  textEntryMonthID);
	textEntryDay =					TheWindowManager->winGetWindowFromId( NULL,  textEntryDayID);
	textEntryYear =					TheWindowManager->winGetWindowFromId( NULL,  textEntryYearID);

	GadgetTextEntrySetText(textEntryMonth, BFMEEmptyPlayerName);

	GadgetTextEntrySetText(textEntryDay, BFMEEmptyPlayerName);

	GadgetTextEntrySetText(textEntryYear, BFMEEmptyPlayerName);

	GameWindowList tabList;
	tabList.push_front(comboBoxEmail);
	tabList.push_back(comboBoxLoginName);
	tabList.push_back(textEntryPassword);
	tabList.push_back(textEntryMonth);
	tabList.push_back(textEntryDay);
	tabList.push_back(textEntryYear);
	tabList.push_back(checkBoxRememberPassword);
	tabList.push_back(buttonLogin);
	tabList.push_back(buttonCreateAccount);
	tabList.push_back(buttonTOS);
	tabList.push_back(buttonBack);
	TheWindowManager->clearTabList();
	TheWindowManager->registerTabList(tabList);
	TheWindowManager->winSetFocus( comboBoxEmail );
	// short form or long form?

		DEBUG_ASSERTCRASH(buttonBack,						("buttonBack missing!"));
		DEBUG_ASSERTCRASH(buttonLogin,					("buttonLogin missing!"));
		DEBUG_ASSERTCRASH(buttonCreateAccount,	("buttonCreateAccount missing!"));
		//DEBUG_ASSERTCRASH(buttonDontUseAccount,	("buttonDontUseAccount missing!"));
		DEBUG_ASSERTCRASH(comboBoxEmail,				("comboBoxEmail missing!"));
		DEBUG_ASSERTCRASH(comboBoxLoginName,		("comboBoxLoginName missing!"));
		DEBUG_ASSERTCRASH(textEntryPassword,		("textEntryPassword missing!"));

		//TheShell->registerWithAnimateManager(parentWOLLogin, WIN_ANIMATION_SLIDE_TOP, TRUE);
		/**/
//		TheShell->registerWithAnimateManager(buttonTOS, WIN_ANIMATION_SLIDE_BOTTOM, TRUE);
		//TheShell->registerWithAnimateManager(buttonCreateAccount, WIN_ANIMATION_SLIDE_LEFT, TRUE);
		//TheShell->registerWithAnimateManager(buttonDontUseAccount, WIN_ANIMATION_SLIDE_LEFT, TRUE);
//		TheShell->registerWithAnimateManager(buttonBack, WIN_ANIMATION_SLIDE_BOTTOM, TRUE);
		/**/

		// Read login names from registry...
		GadgetComboBoxReset(comboBoxEmail);
		GadgetTextEntrySetText(textEntryPassword, BFMEEmptyPlayerName);

		// look for cached nicks to add
		AsciiString lastName;
		AsciiString lastEmail;
		Bool markCheckBox = FALSE;
		UserPreferences::const_iterator it = loginPref->find("lastName");
		if (it != loginPref->end())
		{
			lastName = it->second;
		}
		it = loginPref->find("lastEmail");
		if (it != loginPref->end())
		{
			lastEmail = it->second;
		}

		// fill in list of Emails, and select the most recent
		AsciiStringList cachedEmails = loginPref->getEmails();
		AsciiStringListIterator eIt = cachedEmails.begin();
		Int selectedPos = -1;
		while (eIt != cachedEmails.end())
		{
			UnicodeString uniEmail;
			uniEmail.translate(*eIt);
			Int pos = GadgetComboBoxAddEntry(comboBoxEmail, uniEmail, GameSpyColor[GSCOLOR_DEFAULT]);
			if (eIt->compare(lastEmail) == 0)
				selectedPos = pos;

			++eIt;
		}
		if (selectedPos >= 0)
		{
			GadgetComboBoxSetSelectedPos(comboBoxEmail, selectedPos);

			// fill in the password for the selected email
			UnicodeString pass;
			pass.translate(loginPref->getPasswordForEmail(lastEmail));
			GadgetTextEntrySetText(textEntryPassword, pass);

			AsciiString month,day,year;
			loginPref->getDateForEmail(lastEmail, month, day, year);
			pass.translate(month);
			GadgetTextEntrySetText(textEntryMonth, pass);
			pass.translate(day);
			GadgetTextEntrySetText(textEntryDay, pass);
			pass.translate(year);
			GadgetTextEntrySetText(textEntryYear, pass);

			markCheckBox = TRUE;
		}

		// fill in list of nicks for selected email, selecting the most recent
		GadgetComboBoxReset(comboBoxLoginName);
		AsciiStringList cachedNicks = loginPref->getNicksForEmail(lastEmail);
		AsciiStringListIterator nIt = cachedNicks.begin();
		selectedPos = -1;
		while (nIt != cachedNicks.end())
		{
			UnicodeString uniNick;
			uniNick.translate(*nIt);
			Int pos = GadgetComboBoxAddEntry(comboBoxLoginName, uniNick, GameSpyColor[GSCOLOR_DEFAULT]);
			if (nIt->compare(lastName) == 0)
				selectedPos = pos;

			++nIt;
		}
		if (selectedPos >= 0)
		{
			GadgetComboBoxSetSelectedPos(comboBoxLoginName, selectedPos);
			markCheckBox = TRUE;
		}
		// always start with not storing information
		if( markCheckBox)
			GadgetCheckBoxSetChecked(checkBoxRememberPassword, TRUE);
		else
			GadgetCheckBoxSetChecked(checkBoxRememberPassword, FALSE);

	EnableLoginControls(TRUE);

	// Show Menu
	((Rva00500A20Layout*)layout)->hide(0);

	// Set Keyboard to Main Parent

	RaiseGSMessageBox();

	OptionPreferences optionPref;
	if (!optionPref.getBool("SawTOS", TRUE))
	{
		TheWindowManager->winSendSystemMsg( parentWOLLogin, GBM_SELECTED,
																			(WindowMsgData)buttonTOS, buttonTOSID );
	}
	TheTransitionHandler->setGroup("GameSpyLoginProfileFade");

} // WOLLoginMenuInit
