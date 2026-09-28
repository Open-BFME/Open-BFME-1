// ?d_00231c50@@YAXXZ
// partial score=0.939655 date=2026-09-28
// Retail 0x00231C50, 812 bytes through ret4 at 0x00231F79.
// AODHordeContain.cpp literal and primary-object layout establish the source family.
// The method identity is unproved; names retain its address. No guessed semantic pins.
// Module settings are witnessed float loads at +2F8/+300/+30C/+314.
// The primary vector at +12C has 16-byte entries; randomized vector at +224
// has six float words. Twenty 24-byte records occupy +614..+7F3; count is +7F4.
// Calls to reserve and insert need address-qualified ABI pins only after exactness;
// their retail targets are 2304B0 via 5835 and 231A00 via A47A respectively.
// BaseCall00245010 is a declaration-only thiscall view: ECX=this and ret4 ABI.
// append follows STLport push_back with its empty dispatch tag default-initialized.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
#include <vector>
#include <string.h>
struct Coord2D { float x,y; };
struct Coord3D { float x,y,z; void set(const Coord3D *p) {x=p->x;y=p->y;z=p->z;} };
#define BFME_HAVE_COORD3D 1
#include "object.h"
struct RandomRecord00231C50 { float values[6]; };
namespace _STL {
template<> void vector<RandomRecord00231C50>::reserve(size_type n);
template<> void vector<RandomRecord00231C50>::_M_insert_overflow(pointer,const RandomRecord00231C50&,const __false_type&,size_type,bool);
}
class RandomVector00231C50 : public _STL::vector<RandomRecord00231C50> {
public:
 void append(const RandomRecord00231C50 &r) {
  if(this->_M_finish!=this->_M_end_of_storage._M_data) {
   if(this->_M_finish) new(this->_M_finish) RandomRecord00231C50(r);
   ++this->_M_finish;
  } else { _STL::__false_type tag; this->_M_insert_overflow(this->_M_finish,r,tag,1,true); }
 }
};
class BfmePairDH { public: BfmePairDH(){} BfmePairDH(const BfmePairDH &v):m_bfmeFirst(v.m_bfmeFirst),m_bfmeSecond(v.m_bfmeSecond) {} int m_bfmeFirst,m_bfmeSecond; };
class Gen_002301A0 { public: BfmePairDH bfmeGet(int) const; };
struct Rva00233F30Offset { Rva00233F30Offset(){} Rva00233F30Offset(const Rva00233F30Offset&v):x(v.x),y(v.y){} float x,y; };
struct Rva00233F30 { Rva00233F30Offset rotatedOffset(const Coord2D *); };
class BfmeAODHordeContainOwner { public: void addPathPosition(const Coord3D *); };
class BaseCall00245010 { public: void apply(int); };
float Rva0002CCA5GetGameLogicRandomValueRealThunk(float,float,char*,int);
struct Data00231C50 { char prefix[0x2f8]; float f2f8; float f2fc; float f300; float f304; float f308; float f30c; float f310; float f314; };
struct Item00231C50 { unsigned words[4]; };
struct FlowPoint00231C50 { float key; float angle; Coord3D position; bool flag; };
class Formation00231C50 : public BaseCall00245010 {
public:
 void initialize(int);
 char prefix[4]; Data00231C50 *data; Object *object;
 char pad00c[0x120]; _STL::vector<Item00231C50> items;
 char pad138[0xec]; RandomVector00231C50 randoms;
 char pad230[0x3e4]; FlowPoint00231C50 points[20]; int count;
};
void Formation00231C50::initialize(int arg)
{
 Data00231C50 *settings=data;
 Object *owner=object;
 BaseCall00245010::apply(arg);
 int memberCount=items.size();
 randoms.reserve(memberCount);
 for(int i=0;i<memberCount;++i) {
  RandomRecord00231C50 r;
  { float angularRange=settings->f2f8 * 6.2831855f;
  r.values[1]=Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f-settings->f300,1.0f+settings->f300,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp",521);
  r.values[0]=Rva0002CCA5GetGameLogicRandomValueRealThunk(0.0f,angularRange,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp",522);
  r.values[2]=Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f-settings->f2f8,1.0f+settings->f2f8,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp",523);
  }
  { float secondAngularRange=settings->f30c * 6.2831855f;
  r.values[4]=Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f-settings->f314,1.0f+settings->f314,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp",526);
  r.values[3]=Rva0002CCA5GetGameLogicRandomValueRealThunk(0.0f,secondAngularRange,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp",527);
  r.values[5]=Rva0002CCA5GetGameLogicRandomValueRealThunk(1.0f-settings->f30c,1.0f+settings->f30c,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp",528);
  }
  randoms.append(r);
 }
 float firstOffset=0;
 for(int i=0;i<memberCount;++i) {
  BfmePairDH pair=((Gen_002301A0*)this)->bfmeGet(i);
  Coord2D &formationOffset=*(Coord2D *)&pair;
  bool found=false;
  for(int j=0;j<count;++j) if(formationOffset.x==points[j].key) {found=true;break;}
  if(found) continue;
  if(count>=20) break;
  points[count].key=formationOffset.x;
  if(count==0) firstOffset=formationOffset.x;
  formationOffset.x-=firstOffset; formationOffset.y=0;
  Rva00233F30Offset rotated=((Rva00233F30*)this)->rotatedOffset((Coord2D*)&formationOffset);
  points[count].flag=true;
  Coord3D position;
  position.set(&owner->m_cachedPos);
  position.x+=rotated.x;
  position.y+=rotated.y;
  points[count].position=position;
  points[count].angle=owner->m_cachedAngle;
  ++count;
 }
 for(int i=count-1;i>=0;--i) ((BfmeAODHordeContainOwner*)this)->addPathPosition(&points[i].position);
}

