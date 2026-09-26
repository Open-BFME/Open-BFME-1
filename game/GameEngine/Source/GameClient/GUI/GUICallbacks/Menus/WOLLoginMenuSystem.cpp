// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native WOLLoginMenuSystem at 00501B90, 7088 bytes.
// Derived from the Zero Hour source; Copyright 2025 Electronic Arts Inc.
// GPL-3.0-or-later. BFME identity and layout witnesses:
// targets/game/reverse/identity_evidence/00501b90-login-system.md.
// Retail calls the CRT iswspace import directly, without the header's iswctype wrapper.
#define _WCTYPE_INLINE_DEFINED
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}
template <> inline const unsigned short *StringBase<unsigned short>::str() const
{
	return m_data ? m_data->data : (const unsigned short *)L"";
}

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
#define UnicodeString Rva00501B90HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
// BFME File slots are independently witnessed by File.cpp and its seven vtables.
class File {
public:
 enum { READ=1 };
 virtual ~File();
 virtual bool open(const char*,int=0);
 virtual void close();
 virtual int read(void*,int);
 virtual int write(const void*,int);
 virtual int seek(int,int);
 virtual void nextLine(char*,int);
 virtual bool scanInt(int&);
 virtual bool scanReal(float&);
 virtual bool scanString(AsciiString&);
 virtual bool print(const char*,...);
 virtual int size();
};

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
#include "GameNetwork/GameSpy/ThreadUtils.h"
class GameSpyInfoInterface {
public:
virtual void rva501b90_slot00() = 0;
virtual void rva501b90_slot04() = 0;
virtual void rva501b90_slot08() = 0;
virtual void rva501b90_slot0C() = 0;
virtual void rva501b90_slot10() = 0;
virtual void rva501b90_slot14() = 0;
virtual void rva501b90_slot18() = 0;
virtual void rva501b90_slot1C() = 0;
virtual void rva501b90_slot20() = 0;
virtual void rva501b90_slot24() = 0;
virtual void rva501b90_slot28() = 0;
virtual void rva501b90_slot2C() = 0;
virtual void rva501b90_slot30() = 0;
virtual void rva501b90_slot34() = 0;
virtual void rva501b90_slot38() = 0;
virtual void rva501b90_slot3C() = 0;
virtual void rva501b90_slot40() = 0;
virtual void rva501b90_slot44() = 0;
virtual void rva501b90_slot48() = 0;
virtual void rva501b90_slot4C() = 0;
virtual void rva501b90_slot50() = 0;
virtual void rva501b90_slot54() = 0;
virtual void rva501b90_slot58() = 0;
virtual void rva501b90_slot5C() = 0;
virtual void rva501b90_slot60() = 0;
virtual void rva501b90_slot64() = 0;
virtual void rva501b90_slot68() = 0;
virtual void rva501b90_slot6C() = 0;
virtual void rva501b90_slot70() = 0;
virtual void rva501b90_slot74() = 0;
virtual void setLocalEmail(AsciiString) = 0;
virtual void rva501b90_slot7C() = 0;
virtual void setLocalPassword(AsciiString) = 0;
virtual void setLocalBaseName(AsciiString) = 0;
};
extern GameSpyInfoInterface*TheGameSpyInfo;
void TearDownGameSpy();
extern Color GameSpyColor[];
enum {GSCOLOR_DEFAULT=0};
class BuddyRequest {
public:
 enum {BUDDYREQUEST_LOGIN=0,BUDDYREQUEST_LOGINNEW=4};
 int buddyRequestType;
 union {
  struct { char nick[31]; char email[51]; char password[31]; bool hasFirewall; char rva00501b90_076[0x200]; char rva00501b90_276[66]; } login;
  char extent[0x2b4];
 }arg;
};
class GameSpyBuddyMessageQueueInterface {
public:
 virtual void rva_slot0()=0;virtual void rva_slot4()=0;virtual void rva_slot8()=0;virtual void rva_slotC()=0;virtual void rva_slot10()=0;virtual void rva_slot14()=0;
 virtual void addRequest(const BuddyRequest&)=0;
};
extern GameSpyBuddyMessageQueueInterface*TheGameSpyBuddyMessageQueue;


#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/WOLBrowser/WebBrowser.h"
template <> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template <> inline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <> inline unsigned short StringBase<unsigned short>::getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
template <> inline int StringBase<unsigned short>::getLength() const { return m_data ? m_data->length : 0; }
#undef iswspace
extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short);

class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences() { m_emailPasswordMap.clear(); m_emailNickMap.clear(); }
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
void startPings();
Bool isAgeOkay(AsciiString&,AsciiString&,AsciiString);
WindowMsgHandledType WOLLoginMenuSystem( GameWindow *window, UnsignedInt msg,
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;

	switch( msg )
	{


		case GWM_CREATE:
			{
				break;
			} // case GWM_DESTROY:

		case GWM_DESTROY:
			{
				break;
			} // case GWM_DESTROY:

		case GWM_INPUT_FOCUS:
			{
				// if we're givin the opportunity to take the keyboard focus we must say we want it
				if( mData1 == TRUE )
					*(Bool *)mData2 = TRUE;

				return MSG_HANDLED;
			}//case GWM_INPUT_FOCUS:

		// someone typed in a combo box.  Clear password (or fill it in if the typed name matches a known login name)
		case GCM_UPDATE_TEXT:
			{
				UnicodeString uNick = GadgetComboBoxGetText(comboBoxLoginName);
				UnicodeString uEmail = GadgetComboBoxGetText(comboBoxEmail);
				AsciiString nick, email;
				nick.translate(uNick);
				email.translate(uEmail);
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				UnicodeString trimmedNick = uNick, trimmedEmail = uEmail;
				((StringBase<unsigned short>*)&trimmedNick)->trim();
				((StringBase<unsigned short>*)&trimmedEmail)->trim();
				if (!trimmedNick.isEmpty())
				{
					if (((const StringBase<unsigned short>*)&trimmedNick)->getCharAt(trimmedNick.getLength()-1) == L'\\')
						((StringBase<unsigned short>*)&trimmedNick)->removeLastChar();
					if (((const StringBase<unsigned short>*)&trimmedNick)->getCharAt(trimmedNick.getLength()-1) == L'/')
						((StringBase<unsigned short>*)&trimmedNick)->removeLastChar();
				}
				if (!trimmedEmail.isEmpty())
				{
					if (((const StringBase<unsigned short>*)&trimmedEmail)->getCharAt(trimmedEmail.getLength()-1) == L'\\')
						((StringBase<unsigned short>*)&trimmedEmail)->removeLastChar();
					if (((const StringBase<unsigned short>*)&trimmedEmail)->getCharAt(trimmedEmail.getLength()-1) == L'/')
						((StringBase<unsigned short>*)&trimmedEmail)->removeLastChar();
				}
				if (trimmedEmail.getLength() != uEmail.getLength())
				{
					// we just trimmed a space.  set the text back and bail
					GadgetComboBoxSetText(comboBoxEmail, trimmedEmail);
					break;
				}
				if (trimmedNick.getLength() != nick.getLength())
				{
					// we just trimmed a space.  set the text back and bail
					GadgetComboBoxSetText(comboBoxLoginName, trimmedNick);
					break;
				}

				if (controlID == comboBoxEmailID)
				{
					// email changed.  look up password, and choose new login names

					// fill in the password for the selected email
					UnicodeString pass;
					pass.translate(loginPref->getPasswordForEmail(email));
					GadgetTextEntrySetText(textEntryPassword, pass);

					// fill in list of nicks for selected email, selecting the first
					AsciiStringList cachedNicks = loginPref->getNicksForEmail(email);
					AsciiStringListIterator nIt = cachedNicks.begin();
					Int selectedPos = -1;
					GadgetComboBoxReset(comboBoxLoginName);
					while (nIt != cachedNicks.end())
					{
						UnicodeString uniNick;
						uniNick.translate(*nIt);
						GadgetComboBoxAddEntry(comboBoxLoginName, uniNick, GameSpyColor[GSCOLOR_DEFAULT]);
						selectedPos = 0;
						++nIt;
					}
					if (selectedPos >= 0)
					{
						GadgetComboBoxSetSelectedPos(comboBoxLoginName, selectedPos);
						GadgetCheckBoxSetChecked(checkBoxRememberPassword, true);
						AsciiString month,day,year;
						loginPref->getDateForEmail(email, month, day, year);
						pass.translate(month);
						GadgetTextEntrySetText(textEntryMonth, pass);
						pass.translate(day);
						GadgetTextEntrySetText(textEntryDay, pass);
						pass.translate(year);
						GadgetTextEntrySetText(textEntryYear, pass);

					}
					else
					{
						GadgetCheckBoxSetChecked(checkBoxRememberPassword, false);
						GadgetTextEntrySetText(textEntryMonth, BFMEEmptyPlayerName);
						GadgetTextEntrySetText(textEntryDay, BFMEEmptyPlayerName);
						GadgetTextEntrySetText(textEntryYear, BFMEEmptyPlayerName);

					}
				}
				else if (controlID == comboBoxLoginNameID)
				{
					// they typed a new login name.  Email & pass shouldn't change
				}

				break;
			}

		case GCM_SELECTED:
			{
				if (buttonPushed)
					break;
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if (controlID == comboBoxEmailID)
				{
					// email changed.  look up password, and choose new login names
					UnicodeString uEmail = GadgetComboBoxGetText(comboBoxEmail);
					AsciiString email;
					email.translate(uEmail);

					// fill in the password for the selected email
					UnicodeString pass;
					pass.translate(loginPref->getPasswordForEmail(email));
					GadgetTextEntrySetText(textEntryPassword, pass);

					// fill in list of nicks for selected email, selecting the first
					AsciiStringList cachedNicks = loginPref->getNicksForEmail(email);
					AsciiStringListIterator nIt = cachedNicks.begin();
					Int selectedPos = -1;
					GadgetComboBoxReset(comboBoxLoginName);
					while (nIt != cachedNicks.end())
					{
						UnicodeString uniNick;
						uniNick.translate(*nIt);
						GadgetComboBoxAddEntry(comboBoxLoginName, uniNick, GameSpyColor[GSCOLOR_DEFAULT]);
						selectedPos = 0;
						++nIt;
					}
					if (selectedPos >= 0)
					{
						GadgetComboBoxSetSelectedPos(comboBoxLoginName, selectedPos);
						GadgetCheckBoxSetChecked(checkBoxRememberPassword, true);
						AsciiString month,day,year;
						loginPref->getDateForEmail(email, month, day, year);
						pass.translate(month);
						GadgetTextEntrySetText(textEntryMonth, pass);
						pass.translate(day);
						GadgetTextEntrySetText(textEntryDay, pass);
						pass.translate(year);
						GadgetTextEntrySetText(textEntryYear, pass);

					}
					else
					{
						GadgetCheckBoxSetChecked(checkBoxRememberPassword, false);
						GadgetTextEntrySetText(textEntryMonth, BFMEEmptyPlayerName);
						GadgetTextEntrySetText(textEntryDay, BFMEEmptyPlayerName);
						GadgetTextEntrySetText(textEntryYear, BFMEEmptyPlayerName);
					}

				}
				else if (controlID == comboBoxLoginNameID)
				{
					// they typed a new login name.  Email & pass shouldn't change
				}
				break;
			}

		case GBM_SELECTED:
			{
				if (buttonPushed)
					break;
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				// If we back out, just bail - we haven't gotten far enough to need to log out
				if ( controlID == buttonBackID )
				{
					buttonPushed = true;
					TearDownGameSpy();
					TheShell->pop();
				} //if ( controlID == buttonBack )
				else if ( controlID == buttonCreateAccountID )
				{
						// actually attempt to create an account based on info entered
						AsciiString month, day, year;
						month.translate( GadgetTextEntryGetText(textEntryMonth) );
						day.translate( GadgetTextEntryGetText(textEntryDay) );
						year.translate( GadgetTextEntryGetText(textEntryYear) );

						if(!isAgeOkay(month, day, year))
						{
							GSMessageBoxOk(TheGameText->fetch("GUI:AgeFailedTitle"), TheGameText->fetch("GUI:AgeFailed"));
							break;
						}

						AsciiString login, password, email;
						email.translate( GadgetComboBoxGetText(comboBoxEmail) );
						login.translate( GadgetComboBoxGetText(comboBoxLoginName) );
						password.translate( GadgetTextEntryGetText(textEntryPassword) );

						if ( !email.isEmpty() && !login.isEmpty() && !password.isEmpty() )
						{
							loginAttemptTime = timeGetTime();
							BuddyRequest req;
							req.buddyRequestType = BuddyRequest::BUDDYREQUEST_LOGINNEW;
							strcpy(req.arg.login.nick, login.str());
							strcpy(req.arg.login.email, email.str());
							strcpy(req.arg.login.password, password.str());
							req.arg.login.hasFirewall = TRUE;
AsciiString registryValue;
							GetStringFromRegistry("\\ergc", "", registryValue);
							strcpy(req.arg.login.rva00501b90_276, registryValue.str());

							TheGameSpyInfo->setLocalBaseName( login );
							//TheGameSpyInfo->setLocalProfileID( resp.player.profileID );
							TheGameSpyInfo->setLocalEmail( email );
							TheGameSpyInfo->setLocalPassword( password );
							DEBUG_LOG(("before create: TheGameSpyInfo->stuff(%s/%s/%s)\n", TheGameSpyInfo->getLocalBaseName().str(), TheGameSpyInfo->getLocalEmail().str(), TheGameSpyInfo->getLocalPassword().str()));

							TheGameSpyBuddyMessageQueue->addRequest( req );
							if(checkBoxRememberPassword && GadgetCheckBoxIsChecked(checkBoxRememberPassword))
							{
								(*loginPref)["lastName"] = login;
								(*loginPref)["lastEmail"] = email;
								(*loginPref)["useProfiles"] = "yes";
								AsciiString date;
								date = month;
								date.concat(day);
								date.concat(year);

								loginPref->addLogin(email, login, password, date);
							}

							EnableLoginControls( FALSE );

							// fire off some pings
							startPings();
						}
						else
						{
							// user didn't fill in all info.  prompt him.
							if(email.isEmpty() && login.isEmpty() && password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoAll"));
							else if( email.isEmpty() && login.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoEmailNickname"));
							else if( email.isEmpty() && password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoEmailPassword"));
							else if( login.isEmpty() && password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoNicknamePassword"));
							else if( email.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoEmail"));
							else if( password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoPassword"));
							else if( login.isEmpty() )
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoNickname"));
							else
								GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSNoLoginInfoAll"));
						}
				} //if ( controlID == buttonCreateAccount )
				else if ( controlID == buttonLoginID )
				{
					AsciiString login, password, email;

						AsciiString month, day, year;
						month.translate( GadgetTextEntryGetText(textEntryMonth) );
						day.translate( GadgetTextEntryGetText(textEntryDay) );
						year.translate( GadgetTextEntryGetText(textEntryYear) );

						if(!isAgeOkay(month, day, year))
						{
							GSMessageBoxOk(TheGameText->fetch("GUI:AgeFailedTitle"), TheGameText->fetch("GUI:AgeFailed"));
							break;
						}

						email.translate( GadgetComboBoxGetText(comboBoxEmail) );
						login.translate( GadgetComboBoxGetText(comboBoxLoginName) );
						password.translate( GadgetTextEntryGetText(textEntryPassword) );

						if ( !email.isEmpty() && !login.isEmpty() && !password.isEmpty() )
						{
							loginAttemptTime = timeGetTime();
							BuddyRequest req;
							req.buddyRequestType = BuddyRequest::BUDDYREQUEST_LOGIN;
							strcpy(req.arg.login.nick, login.str());
							strcpy(req.arg.login.email, email.str());
							strcpy(req.arg.login.password, password.str());
							req.arg.login.hasFirewall = true;

							TheGameSpyInfo->setLocalBaseName( login );
							//TheGameSpyInfo->setLocalProfileID( resp.player.profileID );
							TheGameSpyInfo->setLocalEmail( email );
							TheGameSpyInfo->setLocalPassword( password );
							DEBUG_LOG(("before login: TheGameSpyInfo->stuff(%s/%s/%s)\n", TheGameSpyInfo->getLocalBaseName().str(), TheGameSpyInfo->getLocalEmail().str(), TheGameSpyInfo->getLocalPassword().str()));

							TheGameSpyBuddyMessageQueue->addRequest( req );
							if(checkBoxRememberPassword && GadgetCheckBoxIsChecked(checkBoxRememberPassword))
							{
								(*loginPref)["lastName"] = login;
								(*loginPref)["lastEmail"] = email;
								(*loginPref)["useProfiles"] = "yes";
								AsciiString date;
								date = month;
								date.concat(day);
								date.concat(year);

								loginPref->addLogin(email, login, password,date);
							}
							else
							{
								loginPref->forgetLogin(email);
							}
							EnableLoginControls( FALSE );

							// fire off some pings
							startPings();
						}
						else
						{
							// user didn't fill in all info.  prompt him.
							if(email.isEmpty() && login.isEmpty() && password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoAll"));
							else if( email.isEmpty() && login.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoEmailNickname"));
							else if( email.isEmpty() && password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoEmailPassword"));
							else if( login.isEmpty() && password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoNicknamePassword"));
							else if( email.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoEmail"));
							else if( password.isEmpty())
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoPassword"));
							else if( login.isEmpty() )
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoNickname"));
							else
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSNoLoginInfoAll"));
						}

				} //if ( controlID == buttonLogin )
				else if ( controlID == buttonTOSID )
				{
					parentTOS->winHide(FALSE);
					{
						// Okay, no web browser.  This means we're looking at a UTF-8 text file.
						GadgetListBoxReset(listboxTOS);
						AsciiString fileName;
						fileName.format("Lang\\%s\\TOS.txt", GetRegistryLanguage().str());
						File *theFile = TheFileSystem->openFile(fileName.str(), File::READ);
						if (theFile)
						{
							Int size = theFile->size();

							char *fileBuf = new char[size];
							Color tosColor = GameMakeColor(255, 255, 255, 255);

							Int bytesRead = theFile->read(fileBuf, size);
							if (bytesRead == size && size > 2)
							{
								fileBuf[size-1] = 0; // just to be safe
								AsciiString asciiBuf = fileBuf+2;
								AsciiString asciiLine;
								while (asciiBuf.nextToken(&asciiLine, "\r\n"))
								{
									UnicodeString uniLine;
									uniLine = UnicodeString(MultiByteToWideCharSingleLine(asciiLine.str()).c_str());
									int len = uniLine.getLength();
									for (int index = len-1; index >= 0; index--)
									{
										if ((::iswspace)(((const StringBase<unsigned short>*)&uniLine)->getCharAt(index)))
										{
											((StringBase<unsigned short>*)&uniLine)->removeLastChar();
										}
										else
										{
											break;
										}
									}
									//((StringBase<unsigned short>*)&uniLine)->trim();
									DEBUG_LOG(("adding TOS line: [%ls]\n", uniLine.str()));
									GadgetListBoxAddEntryText(listboxTOS, uniLine, tosColor, -1);
								}

							}

							delete fileBuf;
							fileBuf = NULL;

							theFile->close();
							theFile = NULL;
						}
					}
					EnableLoginControls( FALSE );
					buttonBack->winEnable(FALSE);

				}
				else if ( controlID == buttonTOSOKID )
				{
					EnableLoginControls( TRUE );

					parentTOS->winHide(TRUE);
					OptionPreferences optionPref;
					optionPref["SawTOS"] = "yes";
					optionPref.write();

					buttonBack->winEnable(TRUE);
				}
				break;
			}// case GBM_SELECTED:

		case GEM_EDIT_DONE:
			{
				break;
			}
			/*
		case GEM_UPDATE_TEXT:
			{
				if (buttonPushed)
					break;
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if ( controlID == textEntryLoginNameID )
				{
					UnicodeString munkee = GadgetTextEntryGetText( textEntryLoginName );
					if ( !isNickOkay( munkee ) )
					{
						((StringBase<unsigned short>*)&munkee)->removeLastChar();
						GadgetTextEntrySetText( textEntryLoginName, munkee );
					}
				}// if ( controlID == textEntryLoginNameID )
				break;
			}//case GEM_UPDATE_TEXT:
			*/
		default:
			return MSG_IGNORED;

	}//Switch

	return MSG_HANDLED;
}// WOLLoginMenuSystem
