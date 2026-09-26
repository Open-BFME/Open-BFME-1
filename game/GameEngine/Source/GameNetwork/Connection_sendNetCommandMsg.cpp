// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Connection::sendNetCommandMsg, RVA0x006624A0, 502 bytes through RET8.
// Matched ConnectionManager send paths call through ILT0x00026D3C.
// A reusable packet tests fit. Oversized commands become wrapper commands,
// each queued separately so retries do not resend the entire original message.
// NetCommandRef is de-pooled in BFME: message pointer+0, relay byte+0x0C,
// ordinary destructor/delete. Packet and command-list deletion is virtual.
// The reference is borrowed by addCommand and ConstructBigCommandPacketList;
// this function owns its two temporary references and the returned packet list.
#include <list>
class NetCommandMsg;
class NetCommandRef {
public:
 NetCommandRef(NetCommandMsg*); ~NetCommandRef();
 NetCommandMsg*getCommand(){return msg;}
 NetCommandRef*getNext(){return next;}
 void setRelay(unsigned char r){relay=r;}
 NetCommandMsg *msg;NetCommandRef *next,*prev;unsigned char relay;unsigned time;
};
class NetCommandList {
public:
 virtual ~NetCommandList();
 NetCommandRef*addMessage(NetCommandMsg*);
 NetCommandRef*getFirstMessage(){return first;}
 NetCommandRef *first,*last,*inserted;
};
class NetPacket;
typedef _STL::list<NetPacket*> NetPacketList;
class NetPacket {
public:
 NetPacket();virtual ~NetPacket();
 void reset();bool addCommand(NetCommandRef*);
 static NetPacketList ConstructBigCommandPacketList(NetCommandRef*);
 NetCommandList*getCommandList();
 char rest[0x1fc];
};
class Connection {
public:
 void sendNetCommandMsg(NetCommandMsg*,unsigned char);
 int quitFrame; // -1 until quitting
 char unknown[0x14];
 NetCommandList *commands; // +0x18
};
void Connection::sendNetCommandMsg(NetCommandMsg *msg,unsigned char relay){
 static NetPacket *packet=0;
 if(!packet)packet=new NetPacket;
 if(quitFrame!=-1)return;
 if(commands){
  packet->reset();
  NetCommandRef *tempref=new NetCommandRef(msg);
  bool fits=packet->addCommand(tempref);
  delete tempref;tempref=0;
  if(!fits){
   NetCommandRef *origref=new NetCommandRef(msg);
   origref->setRelay(relay);
   NetPacketList packetList=NetPacket::ConstructBigCommandPacketList(origref);
   NetPacketList::iterator it=packetList.begin();
   while(it!=packetList.end()){
    NetPacket *p=*it;
    NetCommandList *list=p->getCommandList();
    NetCommandRef *ref1=list->getFirstMessage();
    while(ref1){
     NetCommandRef *ref2=commands->addMessage(ref1->getCommand());
     ref2->setRelay(relay);
     ref1=ref1->getNext();
    }
    delete p;p=0;++it;
    delete list;list=0;
   }
   delete origref;origref=0;
   return;
  }
  NetCommandRef *ref=commands->addMessage(msg);
  if(ref)ref->setRelay(relay);
 }
}
