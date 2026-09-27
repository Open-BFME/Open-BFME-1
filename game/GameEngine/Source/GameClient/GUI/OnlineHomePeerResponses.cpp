// Retail 0x00547160 (1093 bytes). OnlineHome vtable 0x01107B70 slot +0x14
// points through ILT 0x0002BAA3 to this response pump. Owner is established;
// method spelling retains the address because the original name is unproved.
// PeerResponse size 0x330 and payload +0xF4 agree with PeerResponseCopies.cpp.
// GameSpyGroupRoom copy at 0x004F97B0 consumes 0x20 bytes; +0x1C is unnamed.
// Group-room and disconnect arms follow ZH WOLWelcomeMenuUpdate.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
#pragma intrinsic(strlen)

template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template <typename T> inline const T *StringBase<T>::str() const {
    static const T TheNullChr = 0;
    return m_data ? m_data->data : &TheNullChr;
}
template <typename T> inline void StringBase<T>::set(const T *s) { set(s, s ? strlen((const char*)s) : 0); }
template <typename T> inline void StringBase<T>::concat(const StringBase<T>& s) {
    concat(s.m_data ? s.m_data->data : (const T*)"", s.m_data ? s.m_data->length : 0);
}
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::~StringBase(); }


template<class T> inline int StringBase<T>::getLength() const {return m_data?m_data->length:0;}
template<class T> inline T StringBase<T>::getCharAt(int i) const {return m_data?m_data->data[i]:0;}
template<class T> inline bool StringBase<T>::isEmpty() const {return !m_data || m_data->length==0;}
template<> inline bool StringBase<char>::startsWith(const char *s) const {return startsWith(s,strlen(s));}
inline AsciiString &AsciiString::operator=(const char *s) {StringBase<char>::set(s); return *this;}
inline UnicodeString::UnicodeString(const wchar_t* s) {
 ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase((const unsigned short*)s);
}
inline UnicodeString& UnicodeString::operator=(const UnicodeString& s) {
 ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this;
}

class PeerResponse {
public:
 PeerResponse();
 ~PeerResponse();
 int field00;
 const char *field04;
 unsigned char field08[0xec];
 int fieldF4[143];
};
class GameSpyGroupRoom {
public:
 GameSpyGroupRoom();
 GameSpyGroupRoom(const GameSpyGroupRoom&);
 AsciiString m_name;
 UnicodeString m_translatedName;
 int m_groupID, m_numWaiting, m_maxWaiting, m_numGames, m_numPlaying;
 int m_field1c;
};
class GameSpyInfo {public:
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00C();
virtual void addGroupRoom(GameSpyGroupRoom);
virtual void slot014();
virtual void slot018();
virtual void slot01C();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02C();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03C();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04C();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05C();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06C();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual void slot07C();
virtual void slot080();
virtual void slot084();
virtual void slot088();
virtual void slot08C();
virtual void slot090();
virtual void slot094();
virtual void slot098();
virtual void slot09C();
virtual void slot0A0();
virtual void slot0A4();
virtual void slot0A8();
virtual void slot0AC();
virtual void slot0B0();
virtual void slot0B4();
virtual void slot0B8();
virtual void slot0BC();
virtual void slot0C0();
virtual void slot0C4();
virtual void slot0C8();
virtual void slot0CC();
virtual void slot0D0();
virtual void slot0D4();
virtual void slot0D8();
virtual void slot0DC();
virtual void slot0E0();
virtual void slot0E4();
virtual void slot0E8();
virtual void slot0EC();
virtual void slot0F0();
virtual void slot0F4();
virtual void slot0F8();
virtual void slot0FC();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10C();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11C();
virtual void slot120();
virtual void slot124();
virtual void slot128();
virtual void slot12C();
virtual void slot130();
virtual void slot134();
virtual void slot138();
virtual void slot13C();
virtual void slot140();
virtual void slot144();
virtual void slot148();
virtual void slot14C();
virtual void slot150();
virtual void slot154();
virtual void slot158();
virtual void slot15C();
virtual void slot160();
virtual void slot164();
virtual void slot168();
 virtual int getMaxMessagesPerUpdate();
};
extern GameSpyInfo *TheGameSpyInfo;
class GameSpyPeerMessageQueueInterface {public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
 virtual bool getResponse(PeerResponse&);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class WindowManager {public: void bfme_setAptText(const AsciiString&,const AsciiString&);};
extern WindowManager *g_theWindowManager;
class GameTextInterface {public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
 virtual UnicodeString fetch(const char*,bool* = 0);
 virtual UnicodeString fetch(AsciiString,bool* = 0);
};
extern GameTextInterface *TheGameText;
class Shell { public: void pop(); };
extern Shell *TheShell;
void HandleBuddyResponses();
void HandlePersistentStorageResponses();
void GameSpyCloseAllOverlays();
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)() = 0);
void TearDownGameSpy();
class BfmeAptScreenOnlineHome {public: virtual void updatePeerResponses00547160();};
void BfmeAptScreenOnlineHome::updatePeerResponses00547160() {
 if(TheGameSpyPeerMessageQueue) {
  HandleBuddyResponses();
  HandlePersistentStorageResponses();
  int allowedMessages=TheGameSpyInfo->getMaxMessagesPerUpdate();
  bool sawImportantMessage=false;
  PeerResponse resp;
  while(allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse(resp)) {
   switch(resp.field00) {
   case 3: {
    GameSpyGroupRoom room;
    room.m_groupID=resp.fieldF4[0];
    room.m_maxWaiting=resp.fieldF4[2];
    room.m_name=resp.field04;
    room.m_translatedName=UnicodeString(L"TEST");
    room.m_numGames=resp.fieldF4[3];
    room.m_numPlaying=resp.fieldF4[4];
    room.m_numWaiting=resp.fieldF4[1];
    room.m_field1c=resp.fieldF4[5];
    TheGameSpyInfo->addGroupRoom(room);
   } break;
   case 21: {
    AsciiString games;
    games.format(AsciiString("%d"),resp.fieldF4[6]);
    { AsciiString name("APT:GamesInProgressNum"); AsciiString copy(games); g_theWindowManager->bfme_setAptText(name,copy); }
    int players=resp.fieldF4[7];
    if(players<=0) players=1;
    games.format(AsciiString("%d"),players);
    { AsciiString name("APT:PlayersOnlineNum"); AsciiString copy(games); g_theWindowManager->bfme_setAptText(name,copy); }
   } break;
   case 1: {
    sawImportantMessage=true;
    UnicodeString title,body;
    AsciiString disconMunkee;
    disconMunkee.format(AsciiString("GUI:GSDisconReason%d"),resp.fieldF4[0]);
    title=TheGameText->fetch("GUI:GSErrorTitle");
    body=TheGameText->fetch(disconMunkee);
    GameSpyCloseAllOverlays();
    GSMessageBoxOk(title,body);
    TheShell->pop();
    TearDownGameSpy();
   } break;
   }
  }
 }
}



