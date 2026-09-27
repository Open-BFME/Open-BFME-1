// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x003DC190, 716 bytes. The matched GameLogic::update call through
// ILT 0x000313A9 and the Zero Hour processPathfindQueue body establish identity.
// BFME adds incremental zone refresh, a 512-entry request ring, STLport object
// lookup, and the performance-counter threshold. Layouts below are slices
// witnessed by this body and the existing zone/lookup conversions.
// Coordinate rounding uses the original BaseType.h helper; no lifted assembly.
// The byte at this+8 is accessed by offset because the layout oracle labels it
// as a pointer member, conflicting with the byte test in this retail body.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *);
#include "Lib/BaseType.h"
__forceinline int floorCell(float f) { return fast_float2long_round((float)floor((double)f)); }
class PathfindCell;
class PathfindLayer { char pad[0x44]; };
class Pathfinder;
class Gen_00403850 { public: void m(int); };
class PathfindZoneManager {
friend class Pathfinder;
private: void calculateZonesIncremental(PathfindCell **,PathfindLayer [],const IRegion2D &);
public:
 char m_unreconstructed[0x243f4-0xc9c];
 bool m_at243f4,m_at243f5;
};
class TerrainLogic { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void getExtent(Region3D *);
};
extern TerrainLogic *TheTerrainLogic;
// Retail calls the AI update interface through vtable slot +0x1f8.
#define QUEUE_AI_SLOT(n) virtual void slot##n();
class AIUpdateInterface { public:
 QUEUE_AI_SLOT(0) QUEUE_AI_SLOT(1) QUEUE_AI_SLOT(2) QUEUE_AI_SLOT(3) QUEUE_AI_SLOT(4) QUEUE_AI_SLOT(5) QUEUE_AI_SLOT(6) QUEUE_AI_SLOT(7)
 QUEUE_AI_SLOT(8) QUEUE_AI_SLOT(9) QUEUE_AI_SLOT(10) QUEUE_AI_SLOT(11) QUEUE_AI_SLOT(12) QUEUE_AI_SLOT(13) QUEUE_AI_SLOT(14) QUEUE_AI_SLOT(15)
 QUEUE_AI_SLOT(16) QUEUE_AI_SLOT(17) QUEUE_AI_SLOT(18) QUEUE_AI_SLOT(19) QUEUE_AI_SLOT(20) QUEUE_AI_SLOT(21) QUEUE_AI_SLOT(22) QUEUE_AI_SLOT(23)
 QUEUE_AI_SLOT(24) QUEUE_AI_SLOT(25) QUEUE_AI_SLOT(26) QUEUE_AI_SLOT(27) QUEUE_AI_SLOT(28) QUEUE_AI_SLOT(29) QUEUE_AI_SLOT(30) QUEUE_AI_SLOT(31)
 QUEUE_AI_SLOT(32) QUEUE_AI_SLOT(33) QUEUE_AI_SLOT(34) QUEUE_AI_SLOT(35) QUEUE_AI_SLOT(36) QUEUE_AI_SLOT(37) QUEUE_AI_SLOT(38) QUEUE_AI_SLOT(39)
 QUEUE_AI_SLOT(40) QUEUE_AI_SLOT(41) QUEUE_AI_SLOT(42) QUEUE_AI_SLOT(43) QUEUE_AI_SLOT(44) QUEUE_AI_SLOT(45) QUEUE_AI_SLOT(46) QUEUE_AI_SLOT(47)
 QUEUE_AI_SLOT(48) QUEUE_AI_SLOT(49) QUEUE_AI_SLOT(50) QUEUE_AI_SLOT(51) QUEUE_AI_SLOT(52) QUEUE_AI_SLOT(53) QUEUE_AI_SLOT(54) QUEUE_AI_SLOT(55)
 QUEUE_AI_SLOT(56) QUEUE_AI_SLOT(57) QUEUE_AI_SLOT(58) QUEUE_AI_SLOT(59) QUEUE_AI_SLOT(60) QUEUE_AI_SLOT(61) QUEUE_AI_SLOT(62) QUEUE_AI_SLOT(63)
 QUEUE_AI_SLOT(64) QUEUE_AI_SLOT(65) QUEUE_AI_SLOT(66) QUEUE_AI_SLOT(67) QUEUE_AI_SLOT(68) QUEUE_AI_SLOT(69) QUEUE_AI_SLOT(70) QUEUE_AI_SLOT(71)
 QUEUE_AI_SLOT(72) QUEUE_AI_SLOT(73) QUEUE_AI_SLOT(74) QUEUE_AI_SLOT(75) QUEUE_AI_SLOT(76) QUEUE_AI_SLOT(77) QUEUE_AI_SLOT(78) QUEUE_AI_SLOT(79)
 QUEUE_AI_SLOT(80) QUEUE_AI_SLOT(81) QUEUE_AI_SLOT(82) QUEUE_AI_SLOT(83) QUEUE_AI_SLOT(84) QUEUE_AI_SLOT(85) QUEUE_AI_SLOT(86) QUEUE_AI_SLOT(87)
 QUEUE_AI_SLOT(88) QUEUE_AI_SLOT(89) QUEUE_AI_SLOT(90) QUEUE_AI_SLOT(91) QUEUE_AI_SLOT(92) QUEUE_AI_SLOT(93) QUEUE_AI_SLOT(94) QUEUE_AI_SLOT(95)
 QUEUE_AI_SLOT(96) QUEUE_AI_SLOT(97) QUEUE_AI_SLOT(98) QUEUE_AI_SLOT(99) QUEUE_AI_SLOT(100) QUEUE_AI_SLOT(101) QUEUE_AI_SLOT(102) QUEUE_AI_SLOT(103)
 QUEUE_AI_SLOT(104) QUEUE_AI_SLOT(105) QUEUE_AI_SLOT(106) QUEUE_AI_SLOT(107) QUEUE_AI_SLOT(108) QUEUE_AI_SLOT(109) QUEUE_AI_SLOT(110) QUEUE_AI_SLOT(111)
 QUEUE_AI_SLOT(112) QUEUE_AI_SLOT(113) QUEUE_AI_SLOT(114) QUEUE_AI_SLOT(115) QUEUE_AI_SLOT(116) QUEUE_AI_SLOT(117) QUEUE_AI_SLOT(118) QUEUE_AI_SLOT(119)
 QUEUE_AI_SLOT(120) QUEUE_AI_SLOT(121) QUEUE_AI_SLOT(122) QUEUE_AI_SLOT(123) QUEUE_AI_SLOT(124) QUEUE_AI_SLOT(125)
 virtual void doPathfind(Pathfinder *);
};
#undef QUEUE_AI_SLOT
class Object { public: char m_pad00[0x204]; AIUpdateInterface *m_at204; };
typedef _STL::hash_map<int,Object *,_STL::hash<int>,_STL::equal_to<int> > ObjectPtrHash;
class GameLogic {
public:
 char m_pad00[0x3c]; unsigned int m_frame;
 char m_pad40[0xb0-0x40]; ObjectPtrHash m_objHash;
 __forceinline Object *findObjectByID(int id) {
  if(id==0) return 0;
  ObjectPtrHash::iterator it=m_objHash.find(id);
  if(it==m_objHash.end()) return 0;
  return (*it).second;
 }
};
extern GameLogic *TheGameLogic;
class GlobalData { public: char m_pad00[0x1270]; unsigned int m_at1270; };
extern GlobalData *TheWritableGlobalData;
void bfmeTintSlowPathfindObject(Object *);
class Pathfinder {
public:
 void processPathfindQueue();
 void bfmePrepareRefresh();
 char m_pad00[0x10];
 PathfindCell **m_map;
 IRegion2D m_extent;
 IRegion2D m_at24;
 char m_pad34[0x840-0x34]; int m_at840;
 char m_pad844[0x85c-0x844]; PathfindLayer m_layers[16];
 PathfindZoneManager m_zoneManager;
 char m_pad243f6[0x24718-0x243f6];
 int m_at24718[512]; int m_queuePRHead,m_queuePRTail;
};
void Pathfinder::processPathfindQueue() {
 ((Gen_00403850 *)&m_zoneManager)->m(0);
 if(!*((bool *)this+8)) return;
 if(m_zoneManager.m_at243f4 || m_zoneManager.m_at243f5) { bfmePrepareRefresh(); return; }
 m_zoneManager.calculateZonesIncremental(m_map,m_layers,m_extent);
 Region3D terrainExtent;
 TheTerrainLogic->getExtent(&terrainExtent);
 IRegion2D bounds;
 bounds.lo.x=floorCell(terrainExtent.lo.x/10.0f);
 bounds.hi.x=floorCell(terrainExtent.hi.x/10.0f);
 bounds.lo.y=floorCell(terrainExtent.lo.y/10.0f);
 bounds.hi.y=floorCell(terrainExtent.hi.y/10.0f);
 bounds.hi.x--; bounds.hi.y--;
 m_at24=bounds;
 m_at840=0;
 // Retail retains the stack budget read at the initial and subsequent loop tests.
 volatile int budget=4000;
 if(TheGameLogic->m_frame<25) budget=400000;
 while(m_at840<budget && m_queuePRTail!=m_queuePRHead) {
  Object *obj=TheGameLogic->findObjectByID(m_at24718[m_queuePRHead]);
  m_at24718[m_queuePRHead]=0;
  if(obj) {
   AIUpdateInterface *ai=obj->m_at204;
   if(ai) {
    __int64 start,end,frequency;
    if(TheWritableGlobalData->m_at1270) {
     QueryPerformanceFrequency(&frequency);
     QueryPerformanceCounter(&start);
    }
    ai->doPathfind(this);
    if(TheWritableGlobalData->m_at1270) {
     QueryPerformanceCounter(&end);
     double elapsed=(double)(end-start)*1000.0/(double)frequency;
     if(elapsed>=TheWritableGlobalData->m_at1270) bfmeTintSlowPathfindObject(obj);
    }
   }
  }
  m_queuePRHead=m_queuePRHead+1;
  if(m_queuePRHead>=512) m_queuePRHead=0;
 }
}




