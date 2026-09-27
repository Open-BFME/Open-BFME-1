// ?d_007a4b40@@YAXXZ
// partial score=0.9895833333 date=2026-09-27
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "W3DDevice/GameClient/W3DWater.h"
#include <list>
#include <math.h>
struct ICoord3D;
class PolygonTrigger;
struct WaterHandle { PolygonTrigger* m_polygon; };
class PolygonTrigger {
 char pad00[4]; PolygonTrigger* m_next;
 char pad08[8]; ICoord3D* m_points; int m_numPoints;
 char pad18[0x1a]; bool waterAt0032;
public:
 bool pointInTrigger(ICoord3D&) const;
 const WaterHandle* getWaterHandle() const;
 PolygonTrigger* getNext(){return m_next;}
 bool isWaterArea(){return waterAt0032;}
 ICoord3D* getPoint(int i){if(i<0)i=0; if(i>=m_numPoints)i=m_numPoints-1; return m_points+i;}
};
extern "C" PolygonTrigger** g_bfmePolygonTriggerTable;
struct Rva0079E560Point2 {float x,y;};
struct Rva0079E560Point3 {float x,y,z;};
class Rva0079E560Polygon {
 char pad00[0x54];
public:
 Rva0079E560Point3* m_points;
 bool containsPoint(const Rva0079E560Point2*);
};
float WaterRenderObjClass::getWaterHeight(float x,float y)
{
 const WaterHandle* waterHandle=0;
 float waterZ=0.0f;
 ICoord3D iLoc;
 iLoc.x=fast_float2long_round((float)floor(x+0.5f));
 iLoc.y=fast_float2long_round((float)floor(y+0.5f));
 iLoc.z=0;
 for(PolygonTrigger* pTrig=*g_bfmePolygonTriggerTable;pTrig;pTrig=pTrig->getNext()) {
  if(!pTrig->isWaterArea())continue;
  if(pTrig->pointInTrigger(iLoc)) {
   if(pTrig->getPoint(0)->z>=waterZ){waterZ=pTrig->getPoint(0)->z;waterHandle=pTrig->getWaterHandle();}
  }
 }
 if(waterHandle) waterZ=waterHandle->m_polygon->getPoint(0)->z;
 else waterZ=0.0f;
 Coord3D pos;
 struct Node { Node* next; Node* previous; Rva0079E560Polygon* value; };
 struct List { Node* volatile sentinel; };
 List* polygons=(List*)((char*)this+0x2ac);
 unsigned yCopy=*(volatile unsigned*)&y;
 Node* firstEnd=polygons->sentinel;
 unsigned xCopy=*(volatile unsigned*)&x;
 *(unsigned*)&pos.y=yCopy;
 Node* n=firstEnd->next;
 bool empty=n==firstEnd;
 *(unsigned*)&pos.x=xCopy;pos.z=0;
 if(!empty) { do { n=n->next; } while(n!=firstEnd); }
 Node* end=polygons->sentinel;
 for(Node* it=end->next;it!=end;it=it->next){
  Rva0079E560Polygon* poly=it->value;
  if(poly->containsPoint((Rva0079E560Point2*)&pos)){
   if(waterZ==poly->m_points[0].z) return waterZ-0.01f;
   break;
  }
 }
 return waterZ;
}
