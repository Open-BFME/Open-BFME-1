// cl: /DNDEBUG /MD /GX /Igame/Libraries/Source/WWVegas/WWLib
// ZH ConnectionManager::parseUserList, specialized to the BFME layout.
// Matched Network::parseUserList forwards GameInfo to this existing identity.
// GameSlot +0x30 is the address record passed to the independently matched
// Connection::bfmeConfigurePeer at 0x00661E00 (three stack arguments).
// The canonical wide string view needs inline destruction and assignment:
// retail calls StringBase<unsigned short> directly for both operations.
#include "ascii_string.h"
#include "unicode_string.h"
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
inline UnicodeString::~UnicodeString() { reinterpret_cast<StringBase<unsigned short> *>(this)->~StringBase(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other) {
 reinterpret_cast<StringBase<unsigned short> *>(this)->set(*reinterpret_cast<const StringBase<unsigned short> *>(&other)); return *this;
}
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
extern "C" bool g_bfmeFlagVSF;
extern "C" AsciiString g_bfmeHostVSF;
extern "C" AsciiString g_bfmeNameVSF;
unsigned int ResolveIP(AsciiString);
void SeedNextCommandIDFromPlayerCount(unsigned short);
struct NetPacketAddress { unsigned int ip; unsigned short port; NetPacketAddress(unsigned int i,unsigned short p):ip(i),port(p) {} };
class Transport;
class Connection {
public:
 Connection();
 void bfmeConfigurePeer(const NetPacketAddress &,const StringBase<unsigned short> &,Transport *);
 char unknown00[0x358];
};
class FrameDataManager {
public:
 FrameDataManager(bool);
 void init();
 void reset();
 char unknown00[0x10];
};
class GameSlot {
public:
 bool isHuman() const;
 UnicodeString getName() const;
 const NetPacketAddress &getConnectInfo() const { return m_connectInfo; }
 char unknown00[0x30];
 NetPacketAddress m_connectInfo;
};
class GameInfo {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual void slot10();
 virtual int getLocalSlotNum() const;
 const GameSlot *getConstSlot(int) const;
};
class BFMEConnectionManager {
public:
 void attachPlayersFromGameInfo(void *gameInfo);
 char unknown00[4];
 Connection *m_connections[8];
 char unknown24[0x12000];
 Transport *m_transport;
 int m_localSlot;
 unsigned int m_packetRouterSlot;
 unsigned int m_packetRouterFallback[8];
 char unknown12050[8];
 UnicodeString m_localPlayerName;
 char unknown1205c[0x88];
 FrameDataManager *m_frameData[8];
};
void BFMEConnectionManager::attachPlayersFromGameInfo(void *gameInfo)
{
 const GameInfo *game=static_cast<const GameInfo *>(gameInfo);
 if(!game) return;
 m_localSlot=game->getLocalSlotNum();
 SeedNextCommandIDFromPlayerCount((unsigned short)m_localSlot);
 int numUsers=0;
 for(int i=0;i<8;++i) {
  const GameSlot *slot=game->getConstSlot(i);
  if(slot && slot->isHuman()) {
   if(i==m_localSlot) {
    m_localPlayerName=slot->getName();
    m_frameData[i]=new FrameDataManager(true);
   } else {
    m_connections[i]=new Connection;
    m_connections[i]->bfmeConfigurePeer(slot->getConnectInfo(),*reinterpret_cast<const StringBase<unsigned short> *>(&slot->getName()),m_transport);
    if(g_bfmeFlagVSF) {
     m_connections[i]->bfmeConfigurePeer(NetPacketAddress(ResolveIP(g_bfmeNameVSF),(unsigned short)atoi(g_bfmeHostVSF.str())),*reinterpret_cast<const StringBase<unsigned short> *>(&slot->getName()),m_transport);
    }
    m_frameData[i]=new FrameDataManager(false);
   }
   m_frameData[i]->init();
   m_frameData[i]->reset();
   m_packetRouterFallback[numUsers++]=i;
  }
 }
}
