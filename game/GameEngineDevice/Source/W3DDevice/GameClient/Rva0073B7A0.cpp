// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /I. /DNDEBUG /DWIN32 /MD /EHsc /Igame/GameEngine/Include /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "GameLogic/TerrainLogic.h"
#include "GameClient/View.h"

// Retail 0x0073B7A0, 179 bytes; opaque identity, no original owner asserted.
// Native RET at0x0073B852 followed by INT3 establishes the end. ILT24E6F
// jumps to the entry. See identity_evidence/0073b7a0-waypoint-abi.md.
// Address-qualified ABI views: native links begin20, count4C, view slot2C.
// These are deliberately distinct from the donor Waypoint and View layouts.
struct Rva0073B7A0Waypoint {
 char rva00[12];
 Coord3D rva0C;
 char rva18[4];
 Rva0073B7A0Waypoint *rva1C;
 Rva0073B7A0Waypoint *rva20[8];
 char rva40[12];
 int rva4C;
 const Coord3D *location() const {return &rva0C;}
 Rva0073B7A0Waypoint *link(int i)const {return i>=0 && i<8 ? rva20[i]:0;}
};
struct Rva0073B7A0Terrain {
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
 virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
 virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
 virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
 virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
 virtual void slot28(); virtual void slot29();
 virtual Rva0073B7A0Waypoint *rva78();
};
struct Rva0073B7A0View {
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual void slot08(); virtual void slot09(); virtual void slot10();
 virtual void rva2C(const Coord3D*,const Coord3D*,unsigned,bool);
};
#include <stddef.h>
typedef char Rva0073B7A0PositionOffset[(offsetof(Rva0073B7A0Waypoint,rva0C)==0x0c)?1:-1];
typedef char Rva0073B7A0NextOffset[(offsetof(Rva0073B7A0Waypoint,rva1C)==0x1c)?1:-1];
typedef char Rva0073B7A0LinksOffset[(offsetof(Rva0073B7A0Waypoint,rva20)==0x20)?1:-1];
typedef char Rva0073B7A0CountOffset[(offsetof(Rva0073B7A0Waypoint,rva4C)==0x4c)?1:-1];

void Rva0073B7A0()
{
 Coord3D top;
 for(Rva0073B7A0Waypoint *w=((Rva0073B7A0Terrain*)TheTerrainLogic)->rva78();w;w=w->rva1C) {
  const Coord3D *loc=w->location();
  top.x=loc->x;
  top.y=loc->y;
  top.z=loc->z+10.0f;
  ((Rva0073B7A0View*)TheTacticalView)->rva2C(loc,&top,0xffffff00,false);
  int count=w->rva4C;
  for(int i=0;i<count;++i) {
   Rva0073B7A0Waypoint *next=w->link(i);
   if(next)((Rva0073B7A0View*)TheTacticalView)->rva2C(loc,next->location(),0xff646400,false);
  }
 }
}
