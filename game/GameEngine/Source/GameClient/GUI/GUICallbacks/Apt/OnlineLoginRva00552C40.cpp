// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00552C40 (1137 bytes): BfmeAptScreenOnlineLogin bool tail shared by
// the matched OnlineLogin callers (_bfme_login 0x00553520, rva005536F0 and
// _bfme_acceptLocale 0x005533F0), which call it through ILT 0x00049E1D under the
// pinned address-keeping name.  true: the delete-nickname OK/Cancel box
// (GUI:SureDeleteNickname, callbacks 0x00551DB0 and ILT 0x00548D00).  false: the
// ZH WOLLoginMenu login branch as BFME ships it, the same request build as the
// matched neighbour OnlineLoginSubmit00551620.cpp (declarations copied from it),
// ending in one GSMessageBoxOk whose message label is picked by the ZH chain.
#include "ascii_string.h"
#include <wchar.h>
#include <string.h>
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
template<class T> inline bool StringBase<T>::isEmpty() const { return m_data==0 || m_data->length==0; }
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
bool GetStringFromRegistry(AsciiString,AsciiString,AsciiString&);
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)()=0);
class BuddyRequest {
public:
 enum { BUDDYREQUEST_LOGIN=0 };
 int buddyRequestType;
 union {
  struct { char nick[31]; char email[51]; char password[31]; bool hasFirewall; char field076[0x200]; char field276[65]; bool field2B7; } login;
  char extent[0x2b4];
 } arg;
};
class GameSpyBuddyMessageQueueInterface { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void addRequest(const BuddyRequest&);
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
class GameSpyInfoInterface { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6c();
 virtual void slot70();
 virtual void slot74();
 virtual void setLocalEmail(AsciiString);
 virtual void slot7c();
 virtual void setLocalPassword(AsciiString);
 virtual void setLocalBaseName(AsciiString);
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameTextInterface { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual UnicodeString fetch(const char*,bool * = 0);
};
extern GameTextInterface *TheGameText;
class Rva00548D30WindowGroup { public: void winEnable(bool); };
class Rva00550500Target;
namespace Rva00550500 { void startPings(); }
class WindowManager { public:
};
class BfmeLevelAN { public:
 char *bfmeBuildAN(unsigned int,int,int,int,int,int,int,int);
};
extern WindowManager *g_rva012F19E8WindowManager;
class GameWindow;
GameWindow *MessageBoxOkCancel(UnicodeString,UnicodeString,void (*)(),void (*)());
void d_00551db0();
void j_00548d00();
struct LoginContext00552C40 { char field000[0x250]; unsigned int field250; };
class BfmeAptScreenOnlineLogin { public:
 void rva00552C40(bool argument);
 UnicodeString bfmeGetTextAt74() const;
 UnicodeString bfmeGetTextAt78() const;
 UnicodeString bfmeGetTextAt7C() const;
 char field00[0x34]; LoginContext00552C40 *field34; char field38[0x60]; unsigned long field98;
};
void BfmeAptScreenOnlineLogin::rva00552C40(bool argument) {
 if(argument) {
  MessageBoxOkCancel(UnicodeString(L""),TheGameText->fetch("GUI:SureDeleteNickname"),d_00551db0,j_00548d00);
  return;
 }
 AsciiString login,password;
 AsciiString email(bfmeGetTextAt74());
 login.translate(bfmeGetTextAt78());
 password.translate(bfmeGetTextAt7C());
 if(!email.isEmpty() && !login.isEmpty() && !password.isEmpty()) {
  field98=timeGetTime();
  BuddyRequest req;
  req.buddyRequestType=BuddyRequest::BUDDYREQUEST_LOGIN;
  strcpy(req.arg.login.nick,login.str());
  strcpy(req.arg.login.email,email.str());
  strcpy(req.arg.login.password,password.str());
  req.arg.login.hasFirewall=true;
  AsciiString registryValue;
  GetStringFromRegistry("\\ergc","",registryValue);
  strcpy(req.arg.login.field276,registryValue.str());
  TheGameSpyInfo->setLocalBaseName(login);
  TheGameSpyInfo->setLocalEmail(email);
  TheGameSpyInfo->setLocalPassword(password);
  req.arg.login.field2B7=false;
  TheGameSpyBuddyMessageQueue->addRequest(req);
  ((Rva00548D30WindowGroup*)this)->winEnable(false);
  { unsigned int level=field34->field250; ((BfmeLevelAN*)g_rva012F19E8WindowManager)->bfmeBuildAN(level,(int)"CallChild",1,(int)"DisableButtonLogin",0,0,0,0); }
  { unsigned int level=field34->field250; ((BfmeLevelAN*)g_rva012F19E8WindowManager)->bfmeBuildAN(level,(int)"CallChild",1,(int)"DisableButtonDeleteNickname",0,0,0,0); }
  ((void (__fastcall *)(Rva00550500Target *))&Rva00550500::startPings)((Rva00550500Target*)this);
 } else {
  const char *message;
  if(email.isEmpty() && login.isEmpty() && password.isEmpty()) message="GUI:GSNoLoginInfoAll";
  else if(email.isEmpty() && login.isEmpty()) message="GUI:GSNoLoginInfoEmailNickname";
  else if(email.isEmpty() && password.isEmpty()) message="GUI:GSNoLoginInfoEmailPassword";
  else if(login.isEmpty() && password.isEmpty()) message="GUI:GSNoLoginInfoNicknamePassword";
  else if(email.isEmpty()) message="GUI:GSNoLoginInfoEmail";
  else if(password.isEmpty()) message="GUI:GSNoLoginInfoPassword";
  else if(login.isEmpty()) message="GUI:GSNoLoginInfoNickname";
  else message="GUI:GSNoLoginInfoAll";
  GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"),TheGameText->fetch(message));
 }
}
