// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00551620: login request flow. Address retained: original method name unproven.
// Layout: three matched OnlineLogin getters; screen context +0x34; saved ASCII nickname +0xA8.
// ZH WOLLoginMenu login branch and matched neighbor 0x00551060 supply the request prefix.
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
class Rva00550500Target { public: void startPings(); };
class WindowManager { public:
 void *_bfme_callAptFunction(unsigned int,const char*,int,const char*,const char*,const char*,const char*,const char*);
};
extern WindowManager *g_rva012F19E8WindowManager;
struct LoginContext00551620 { char field000[0x250]; unsigned int field250; };
class BfmeAptScreenOnlineLogin { public:
 void submitLogin00551620();
 UnicodeString bfmeGetTextAt74() const;
 UnicodeString bfmeGetTextAt78() const;
 UnicodeString bfmeGetTextAt7C() const;
 char field00[0x34]; LoginContext00551620 *field34; char field38[0x60]; unsigned long field98; char field9C[0xC]; AsciiString fieldA8;
};
void BfmeAptScreenOnlineLogin::submitLogin00551620() {
 AsciiString login,password,email;
 email.translate(bfmeGetTextAt74());
 login.translate(bfmeGetTextAt78());
 password.translate(bfmeGetTextAt7C());
 { unsigned int level=field34->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction(level,"CallChild",1,"DisableButtonDeleteNickname",0,0,0,0); }
 { unsigned int level=field34->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction(level,"CallChild",1,"DisableButtonLogin",0,0,0,0); }
 { unsigned int level=field34->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction(level,"CallChild",1,"DisableButtonServiceTerms",0,0,0,0); }
 if(!email.isEmpty() && !login.isEmpty() && !password.isEmpty()) {
  fieldA8=login;
  field98=timeGetTime();
  BuddyRequest req;
  req.buddyRequestType=BuddyRequest::BUDDYREQUEST_LOGIN;
  req.arg.login.field2B7=true;
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
// Opaque address token for retail 0x00551DB0 (21 B): DeleteNickname
// message-box OK callback. Evidence: DeleteNickname arm at 0x00552C40
// (rva00552C40) passes VA 0x00951DB0 as the MessageBoxOkCancel OK callback
// with cancel 0x00948D00 (-> ILT 0x42A50 -> Rva004C5490); no direct callers,
// ledger refs=0, no ILT thunk. Calls Rva004C5490 (0x004C5490 via ILT
// 0x42A50), then tail-jumps to TheBfmeOnlineLogin-gated submitLogin00551620
// (ECX-gated je/jmp E9 to ILT 0x7FB3 -> 0x00551620). Calls by address take
// (TheBfmeOnlineLogin, 0x012F4AAC) live here only as an opaque pointer.
// ?Rva00551DB0@@YAXXZ
extern void Rva004C5490();
extern BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin;
void Rva00551DB0()
{
	Rva004C5490();
	if (TheBfmeOnlineLogin)
		TheBfmeOnlineLogin->submitLogin00551620();
}
