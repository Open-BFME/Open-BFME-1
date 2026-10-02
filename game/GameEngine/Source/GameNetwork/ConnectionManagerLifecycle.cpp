// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// BFME ConnectionManager complete destructor and virtual init.
// Identity: matched Network teardown / Network::init and vtable 0x0111A2B0.
// Field names and offsets retained from native_connection_timing.cpp;
// ConnectionManager layout witness confirms connections and routing fields.
// The BFME object is 0x12190 bytes. Owning strings and STL member lifetimes
// produce the native EH cleanup; there is no manually encoded frame.
// ZH ConnectionManager.cpp supplies the teardown/init sequence; BFME merges
// the frame/connection delete loop and carries its file maps as members.
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "StringInline.h"
void __cdecl operator delete(void *) throw();
class Transport { public: void reset(); ~Transport() { reset(); } };
class NetCommandList { public: NetCommandList(); virtual ~NetCommandList(); void reset(); void *first,*last,*lastInserted; };
class NetCommandWrapperList { public: NetCommandWrapperList(); virtual ~NetCommandWrapperList(); void init(); void *first; };
class FrameDataManager { public: virtual ~FrameDataManager(); };
class DisconnectManager { public: DisconnectManager(); virtual ~DisconnectManager(); void init(); char unknown04[0x288]; };
class Connection {
public:
 ~Connection() { delete m_netCommandList; }
 char unknown00[0x14];
 UnicodeString unknown14;
 NetCommandList *m_netCommandList;
};
void HideDisconnectWindow();
// Tag the three local comparator types by their witnessed erase bodies.
// Retail has separate non-ICF copies of these template helpers; reusing the
// generic map type would alias an already pinned helper in another TU.
template<unsigned int Address> struct FileIDLess {
 bool operator()(unsigned short left,unsigned short right) const { return left<right; }
};
typedef std::map<unsigned short,AsciiString,FileIDLess<0x00667B50> > FileCommandMap;
typedef std::map<unsigned short,unsigned char,FileIDLess<0x00665120> > FileMaskMap;
typedef std::map<unsigned short,int,FileIDLess<0x00665170> > FileProgressMap;
class ConnectionManager {
public:
 ConnectionManager();
 ~ConnectionManager();
 virtual void init();
 virtual void reset();
 virtual void update(bool isInGame);
 Connection *m_connections[8];
 char m_commandHistoryStorage[0x12000];
 Transport *m_transport;
 int m_localSlot;
 unsigned int m_packetRouterSlot;
 unsigned int m_packetRouterFallback[8];
 unsigned int m_unknown12050;
 unsigned short m_unknown12054;
 UnicodeString m_localPlayerName;
 unsigned int m_frameCeiling;
 unsigned int m_playerLatestFrame[8];
 unsigned int m_playerState[8];
 unsigned int m_playerClientFrame[8];
 unsigned int m_unknown120C0[8];
 DisconnectManager *m_disconnectManager;
 FrameDataManager *m_frameData[8];
 NetCommandList *m_pendingCommands;
 NetCommandList *m_pendingRelays;
 NetCommandWrapperList *m_wrapperList;
 unsigned int m_localLeaveStarted;
 bool m_unknown12114,m_unknown12115;
 FileCommandMap m_fileCommandMap;
 FileMaskMap m_fileRecipientMaskMap;
 FileProgressMap m_fileProgressMap[8];
};
typedef char ConnectionManagerSizeCheck[sizeof(ConnectionManager) == 0x12190 ? 1 : -1];
typedef char NetCommandListSizeCheck[sizeof(NetCommandList) == 0x10 ? 1 : -1];
typedef char NetCommandWrapperListSizeCheck[sizeof(NetCommandWrapperList) == 8 ? 1 : -1];
typedef char DisconnectManagerSizeCheck[sizeof(DisconnectManager) == 0x28c ? 1 : -1];

ConnectionManager::~ConnectionManager()
{
 delete m_transport;
 for(int i=0;i<8;++i) {
  if(m_frameData[i]) delete m_frameData[i];
  if(m_connections[i]) delete m_connections[i];
 }
 HideDisconnectWindow();
 delete m_disconnectManager;
 delete m_pendingCommands;
 delete m_pendingRelays;
 delete m_wrapperList;
 m_fileCommandMap.clear();
 m_fileRecipientMaskMap.clear();
 for(i=0;i<8;++i) m_fileProgressMap[i].clear();
}

void ConnectionManager::init()
{
 for(unsigned int i=0;i<8;++i) m_connections[i]=0;
 if(!m_pendingCommands) { m_pendingCommands=new NetCommandList; m_pendingCommands->reset(); }
 m_pendingCommands->reset();
 if(!m_pendingRelays) { m_pendingRelays=new NetCommandList; m_pendingRelays->reset(); }
 m_pendingRelays->reset();
 m_localSlot=-1;
 m_frameCeiling=0;
 m_packetRouterSlot=0;
 for(i=0;i<8;++i) {
  m_packetRouterFallback[i]=-1;
  m_playerLatestFrame[i]=0;
  m_playerClientFrame[i]=0;
  m_unknown120C0[i]=0;
  // Retail also repeats this store each iteration in the loop at RVA 0x00669140.
  m_playerClientFrame[0]=0;
 }
 for(i=0;i<8;++i) {
  if(m_frameData[i]) { delete m_frameData[i]; m_frameData[i]=0; }
 }
 m_disconnectManager=new DisconnectManager;
 m_disconnectManager->init();
 m_wrapperList=new NetCommandWrapperList;
 m_wrapperList->init();
 m_fileCommandMap.clear();
 m_fileRecipientMaskMap.clear();
 for(i=0;i<8;++i) m_fileProgressMap[i].clear();
 m_localLeaveStarted=0;
 m_unknown12114=false;
 m_unknown12115=true;
}
