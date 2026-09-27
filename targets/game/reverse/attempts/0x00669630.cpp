// ?construct@BFMEConnectionManager@@QAEPAXXZ
// partial score=0.9860031104199067 date=2026-09-27
// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "StringInline.h"
void __cdecl operator delete(void *) throw();
class Transport { public: void reset(); ~Transport() { reset(); } };
class NetCommandList { public: virtual ~NetCommandList(); };
class NetCommandWrapperList { public: virtual ~NetCommandWrapperList(); };
class FrameDataManager { public: virtual ~FrameDataManager(); };
class DisconnectManager { public: virtual ~DisconnectManager(); };
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
#include <string.h>
struct CommandHistory00669630 {
 unsigned int words[0x800];
 CommandHistory00669630() { memset(words,0,sizeof(words)); words[0]=0; }
};
class ConnectionManager {
public:
 ConnectionManager();
 ~ConnectionManager();
 virtual void init();
 virtual void reset();
 virtual void update();
 Connection *m_connections[8];
 CommandHistory00669630 unknown24[9];
 Transport *m_transport;
 int m_localSlot;
 unsigned int m_packetRouterSlot;
 unsigned int m_packetRouterFallback[8];
 unsigned int unknown12050;
 unsigned short unknown12054;
 UnicodeString unknown12058;
 unsigned int unknown1205c;
 unsigned int unknown12060[8];
 unsigned int unknown12080[8];
 unsigned int unknown120a0[8];
 unsigned int unknown120c0[8];
 DisconnectManager *unknown120e0;
 FrameDataManager *unknown120e4[8];
 NetCommandList *unknown12104;
 NetCommandList *unknown12108;
 NetCommandWrapperList *unknown1210c;
 unsigned int unknown12110;
 bool unknown12114,unknown12115;
 FileCommandMap unknown12118;
 FileMaskMap unknown12124;
 FileProgressMap unknown12130[8];
};
ConnectionManager::~ConnectionManager()
{
 delete m_transport;
 for(int i=0;i<8;++i) {
  if(unknown120e4[i]) delete unknown120e4[i];
  if(m_connections[i]) delete m_connections[i];
 }
 HideDisconnectWindow();
 delete unknown120e0;
 delete unknown12104;
 delete unknown12108;
 delete unknown1210c;
 unknown12118.clear();
 unknown12124.clear();
 for(i=0;i<8;++i) unknown12130[i].clear();
}

ConnectionManager::ConnectionManager()
 : m_transport(0), m_localSlot(-1), m_packetRouterSlot(0),
 unknown12050(0), unknown12054(0), unknown1205c(0),
 unknown120e0(0), unknown12104(0), unknown12108(0), unknown1210c(0),
 unknown12110(0), unknown12114(false), unknown12115(true)
{
 for(int i=0;i<8;++i) {
  m_connections[i]=0;
  m_packetRouterFallback[i]=-1;
  unknown120e4[i]=0;
  unknown12060[i]=0;
  unknown120a0[i]=0;
  unknown120c0[i]=0;
  unknown12080[i]=0;
 }
}
