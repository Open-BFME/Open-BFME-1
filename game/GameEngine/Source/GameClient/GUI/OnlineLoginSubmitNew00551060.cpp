// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00551060, 1172 bytes. New-login request flow from the ZH
// WOLLoginMenu.cpp create-account branch, with BFME's registry payload and
// OnlineLogin text getters. The method name is unproven; retain the address.
// BuddyRequest's login prefix is the ZH layout; the matched WOLLoginMenuSystem
// proves BFME's 0x2B8 extent and extra registry text at request+0x276.
// Preserve the retail call order, string temporary lifetimes and each distinct
// error expression: they control both EH states and the cached empty tests.
// this+0x98 is written with timeGetTime; no aligned field-name witness exists.
// Rva00550500Target is only a receiver-preserving callable view of the existing
// startPings body. Call 0x005512C3 -> ILT 0x00042B7C -> body 0x00550500;
// retail reloads ECX at 0x005512C1. The independently matched body ignores ECX.
#include "ascii_string.h"
#include <wchar.h>
#include <string.h>
#include "Common/UnicodeString.h"
template<class T> inline StringBase<T>::StringBase() : m_data(0) {}
template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
template<class T> inline bool StringBase<T>::isEmpty() const { return m_data==0 || m_data->length==0; }
template<class T> inline const T *StringBase<T>::str() const { return m_data?m_data->data:(const T*)""; }
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
bool GetStringFromRegistry(AsciiString,AsciiString,AsciiString&);
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)()=0);
class BuddyRequest {
public:
 enum { BUDDYREQUEST_LOGINNEW=4 };
 int buddyRequestType;
 union {
  struct { char nick[31]; char email[51]; char password[31]; bool hasFirewall; char field076[0x200]; char field276[66]; } login;
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
class Rva00550500Target { public: void startPings(); };
class BfmeAptScreenOnlineLogin { public:
 void submitNewLogin00551060();
 UnicodeString bfmeGetTextAt74() const;
 UnicodeString bfmeGetTextAt78() const;
 UnicodeString bfmeGetTextAt7C() const;
 char field00[0x98]; unsigned long field98;
};
void BfmeAptScreenOnlineLogin::submitNewLogin00551060() {
 AsciiString login,password,email;
 email.translate(bfmeGetTextAt74());
 login.translate(bfmeGetTextAt78());
 password.translate(bfmeGetTextAt7C());
 if(!email.isEmpty() && !login.isEmpty() && !password.isEmpty()) {
  field98=timeGetTime();
  BuddyRequest req;
  req.buddyRequestType=BuddyRequest::BUDDYREQUEST_LOGINNEW;
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
  TheGameSpyBuddyMessageQueue->addRequest(req);
  ((Rva00548D30WindowGroup*)this)->winEnable(false);
  ((Rva00550500Target*)this)->startPings();
 } else {
  if(email.isEmpty() && login.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoAll"));
  else if(email.isEmpty() && login.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmailNickname"));
  else if(email.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmailPassword"));
  else if(login.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoNicknamePassword"));
  else if(email.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmail"));
  else if(password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoPassword"));
  else if(login.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoNickname"));
  else GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoAll"));
 }
}
