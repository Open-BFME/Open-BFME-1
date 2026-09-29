// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/nat /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// GameSpyInfo::sendChat -- retail RVA 0x00626230, 1102 bytes.
// Identity: GameSpyInfo vtable 0x011188D0 slot 62 (+0xF8), adjacent to
// independently identified addChat/handleText; ZH GameNetwork/GameSpy/Chat.cpp
// supplies the public/private message flow and PeerRequest types 3/2.
// BFME omits the ZH previous-message cache and resolves recipient names through
// vslot +0x4C. Its result is viewed only as the AsciiString at offset zero;
// no identity or complete layout is asserted for the returned record.
// The receiver view below contains only the witnessed virtual slots, no fields.
// PeerRequest's existing nat header gives nick +4, text +0x10, message +0xE4,
// and sizeof 0x194, independently visible in this body's stack accesses.
// Retail's compareNoCase call has no EH state transition: the specialization
// is nonthrowing. This reproduces the original EH and register allocation.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include <new>
#include "string_base.h"
template<typename T> inline bool StringBase<T>::isEmpty() const { return !m_data || m_data->length == 0; }
template<> int StringBase<char>::compareNoCase(const StringBase<char>&) const throw();
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
#include "GameNetwork/GameSpy/PeerThread.h"
class GameWindow;
int GadgetListBoxGetListLength(GameWindow*);
void GadgetListBoxGetSelected(GameWindow*,int*);
int GadgetListBoxGetNumColumns(GameWindow*);
UnicodeString GadgetListBoxGetText(GameWindow*,int,int);
class GameSpyInfo {
public:
virtual void slot0() = 0;
virtual void slot1() = 0;
virtual void slot2() = 0;
virtual void slot3() = 0;
virtual void slot4() = 0;
virtual void slot5() = 0;
virtual void slot6() = 0;
virtual void slot7() = 0;
virtual void slot8() = 0;
virtual void slot9() = 0;
virtual void slot10() = 0;
virtual int getCurrentGroupRoom() = 0;
virtual void slot12() = 0;
virtual void slot13() = 0;
virtual void slot14() = 0;
virtual void slot15() = 0;
virtual void slot16() = 0;
virtual void slot17() = 0;
virtual void slot18() = 0;
virtual AsciiString* slot004c(const char*) = 0;
virtual void slot20() = 0;
virtual void slot21() = 0;
virtual void slot22() = 0;
virtual void slot23() = 0;
virtual void slot24() = 0;
virtual void slot25() = 0;
virtual AsciiString getLocalName() = 0;
virtual void slot27() = 0;
virtual void slot28() = 0;
virtual void slot29() = 0;
virtual void slot30() = 0;
virtual void slot31() = 0;
virtual void slot32() = 0;
virtual void slot33() = 0;
virtual void slot34() = 0;
virtual void slot35() = 0;
virtual void slot36() = 0;
virtual void slot37() = 0;
virtual void slot38() = 0;
virtual void slot39() = 0;
virtual void slot40() = 0;
virtual void slot41() = 0;
virtual void slot42() = 0;
virtual void slot43() = 0;
virtual void slot44() = 0;
virtual void slot45() = 0;
virtual void slot46() = 0;
virtual void slot47() = 0;
virtual void slot48() = 0;
virtual void slot49() = 0;
virtual void slot50() = 0;
virtual void slot51() = 0;
virtual void slot52() = 0;
virtual void slot53() = 0;
virtual void slot54() = 0;
virtual void slot55() = 0;
virtual void slot56() = 0;
virtual void slot57() = 0;
virtual void slot58() = 0;
virtual void slot59() = 0;
virtual void slot60() = 0;
virtual void slot61() = 0;
virtual bool sendChat(UnicodeString message, bool isAction, GameWindow* playerListbox);
};
extern GameSpyInfo* TheGameSpyInfo;
// Retail 0x00626230: ZH Chat.cpp sendChat with BFME player lookup and without duplicate suppression.
bool GameSpyInfo::sendChat(UnicodeString message, bool isAction, GameWindow* playerListbox) {
 getCurrentGroupRoom();
 PeerRequest req;
 req.text = message.str();
 message.trim();
 if (!message.isEmpty()) {
  if (!playerListbox) {
   req.message.isAction = isAction;
   req.peerRequestType = PeerRequest::PEERREQUEST_MESSAGEROOM;
   TheGameSpyPeerMessageQueue->addRequest(req);
   return false;
  }
  int maxSel = GadgetListBoxGetListLength(playerListbox);
  int* selections;
  GadgetListBoxGetSelected(playerListbox, (int*)&selections);
  if (selections == (int*)-1) return false;
  if (selections[0] == -1) {
   req.message.isAction = isAction;
   req.peerRequestType = PeerRequest::PEERREQUEST_MESSAGEROOM;
   TheGameSpyPeerMessageQueue->addRequest(req);
   return false;
  } else {
   AsciiString names = AsciiString::TheEmptyString;
   AsciiString tmp = AsciiString::TheEmptyString;
   AsciiString aStr;
   AsciiString* player = TheGameSpyInfo->slot004c(TheGameSpyInfo->getLocalName().str());
   if (player) names.format("%s", player->str());
   else names.format("%s", TheGameSpyInfo->getLocalName().str());
   for (int i=0;i<maxSel;++i) {
    if (selections[i] != -1) {
     aStr.translate(GadgetListBoxGetText(playerListbox,selections[i],GadgetListBoxGetNumColumns(playerListbox)-1));
     if (aStr.compareNoCase(TheGameSpyInfo->getLocalName())) {
      AsciiString* other = TheGameSpyInfo->slot004c(aStr.str());
      if (other) tmp.format(",%s",other->str());
      else tmp.format(",%s",aStr.str());
      names.concat(tmp);
     }
    } else break;
   }
   if (!names.isEmpty()) {
    req.nick = names.str();
    req.message.isAction = isAction;
    req.peerRequestType = PeerRequest::PEERREQUEST_MESSAGEPLAYER;
    TheGameSpyPeerMessageQueue->addRequest(req);
   }
   return true;
  }
 }
 return false;
}
