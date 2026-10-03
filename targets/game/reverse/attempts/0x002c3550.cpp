// ?method@Rva002C3550State@@QAEHXZ
// partial score=0.9608 date=2026-10-03
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Complete experimental body, not a production implementation or verified binding.
// Extent: 002C3550..002C3801, RET at 002C3800; retail EH handler C13CE8,
// FuncInfo E0337C, sole unwind action C13CE0 -> ILT4309F4 -> FFCA0.
// State table 010C7868 slot6 -> ILT446A92 -> body; matched ctor2BE230
// (AIGiantBirdSwoopState) installs it. Opaque name retained pending full audit.
// The 5C geometry owns native vectors at 2C/38, with native AsciiString
// elements (24B/name1C and 10B/name0C). Copy/destructor DECLARATIONS below
// are deliberately UNBOUND. Integrate the canonical BFME geometry layout
// and authentic FFD10/FFCA0 lifetime bindings before any production claim.
// Probe: 689/689B,27 differing nonrelocation bytes,all28 sites aligned,
// shape .990. Remaining differences are load/store scheduling at +1E2..+20C.
// Baseline681B/353diff; explicit distance-call-left and inline length helper,
// ID local and two radius accessor reads fix the earlier x87/register drift.
// Direct Coord3D copy or by-value accessor685B/161diff; out-ref copy and
// aggregate initializer unchanged689B/27diff; copy before range689B/28diff;
// scalar square693B/202diff; double radius691B/194diff. No assembly added.
// Calls use existing address thunks through checked 4B member pointers;
// semantic ABI/layout audit and actual strict relocation verification remain.
// 2BC9C0 independently reads second argument byte and RET8, returns EAX0/1/2.
// D3F10 independently computes EAX0/1 from owner flags and RET4 (AL consumed).
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <vector>

struct Rva002C3550Shape { char field00[0x1c]; AsciiString name; bool enabled; char pad21[3]; };
struct Rva002C3550Record { int x,y,z; AsciiString name; };
class Rva002C3550Geometry {
public:
 Rva002C3550Geometry(const Rva002C3550Geometry&);
 ~Rva002C3550Geometry();
 char prefix[0x10]; float radius10;
 __forceinline float radius() const {return radius10;}
 char field14[0x18];
 std::vector<Rva002C3550Shape> shapes;
 std::vector<Rva002C3550Record> records;
 char cache44[0x18];
};
struct Rva002C3550AI {
 char pad0[0x3f8]; unsigned field3F8;
 char pad3FC[0x424-0x3fc]; bool field424;
 char pad425[0x46c-0x425]; unsigned char field46C;
 char pad46D[3]; float field470;
 char pad474[8]; Coord3D field47C;
};
struct Rva002C3550Object {
 char pad0[0x38]; Coord3D field38;
 char pad44[0x94-0x44]; unsigned field94;
 char pad98[0xac-0x98]; Rva002C3550Geometry geometryAC;
 char pad108[0x204-0x108]; Rva002C3550AI* field204;
 char pad208[0x344-0x208]; unsigned char field344;
};
struct Rva002C3550Machine {char pad0[0x10]; Rva002C3550Object* owner10;};
class GameLogic;
extern GameLogic *TheGameLogic;
extern void j_0001f253(); extern void j_000163d3(); extern void j_00018e8a();
extern void j_00017607(); extern void j_0003daa5(); extern void j_0003ab20();
extern void j_00029e88(); extern void j_00008a26(); extern void j_0003a1a7();
struct Rva002C3550Call {
 Rva002C3550Object *lookup(unsigned);
 void step(bool);
 int choose(float,bool);
 bool mobile() const;
 float speed();
 bool flag(int) const;
 void route(float,Coord3D*,int);
 float distance(const Coord3D*) const;
 void setPosition(const Coord3D*);
};
template<class T> static __forceinline T rva002C3550Member(void(*raw)()) {
 union {void(*p)(); T m;} u; u.p=raw; return u.m;
}
class Rva002C3550State {
public:
 int method();
 char pad0[0x1c]; Rva002C3550Machine* machine1C;
 char pad20[8]; Coord3D goal28;
 bool field34; char pad35[7]; float damping3C;
 void step(bool b) {
  typedef void(Rva002C3550Call::*M)(bool);
  ((Rva002C3550Call*)this->*rva002C3550Member<M>(j_000163d3))(b);
 }
};
static __forceinline float rva002C3550Length(const Coord3D &p) {return p.x*p.x+p.y*p.y+p.z*p.z;}
int Rva002C3550State::method()
{
 Rva002C3550Object* owner=machine1C->owner10;
 if(owner->field344 & 1) return -2;
 Rva002C3550AI* ai=owner->field204;
 if(!ai) return -2;
 typedef Rva002C3550Object*(Rva002C3550Call::*Lookup)(unsigned);
 unsigned objectID=ai->field3F8;
 Rva002C3550Object* target=((Rva002C3550Call*)TheGameLogic->*rva002C3550Member<Lookup>(j_0001f253))(objectID);
 if(target && !(target->field94 & 0x08000000)) {
  if(target->field344 & 1) return -1;
  float speed=(1.0f-damping3C)*ai->field470;
  damping3C*=0.8f;
  ai->field470=speed;
  step(false);
  if(field34) {
   typedef int(Rva002C3550Call::*Choose)(float,bool);
   if(((Rva002C3550Call*)ai->*rva002C3550Member<Choose>(j_00018e8a))(-5.0f,1)==1) return -1;
  } else {
   typedef bool(Rva002C3550Call::*Mobile)() const;
   typedef float(Rva002C3550Call::*Speed)();
   bool still=!((const Rva002C3550Call*)target->*rva002C3550Member<Mobile>(j_00017607))()
    || (target->field204 && ((Rva002C3550Call*)target->field204->*rva002C3550Member<Speed>(j_0003daa5))()<=0.0f);
   typedef bool(Rva002C3550Call::*Flag)(int) const;
   if(!((const Rva002C3550Call*)owner->*rva002C3550Member<Flag>(j_0003ab20))(0x91) || !still) {
    typedef void(Rva002C3550Call::*Route)(float,Coord3D*,int);
    ((Rva002C3550Call*)ai->*rva002C3550Member<Route>(j_00029e88))(5.0f,&goal28,0);
   }
  }
  if(!ai->field424) return -2;
  Rva002C3550Geometry geometry(owner->geometryAC);
  Coord3D delta;
  delta.x=goal28.x-owner->field38.x;
  delta.y=goal28.y-owner->field38.y;
  delta.z=goal28.z-owner->field38.z;
  float distanceSquared=rva002C3550Length(delta);
  float radius=geometry.radius();
  if(distanceSquared < radius*geometry.radius()*0.5f) step(true);
  float range=ai->field470;
  Coord3D next; next.x=ai->field47C.x; next.y=ai->field47C.y; next.z=ai->field47C.z;
  typedef float(Rva002C3550Call::*Distance)(const Coord3D*) const;
  bool close=((const Rva002C3550Call*)owner->*rva002C3550Member<Distance>(j_00008a26))(&next) < range*range;
  if((float)ai->field46C==0.0f && !close) return 0;
  typedef void(Rva002C3550Call::*Position)(const Coord3D*);
  ((Rva002C3550Call*)owner->*rva002C3550Member<Position>(j_0003a1a7))(&next);
 }
 return -1;
}

typedef char Rva002C3550GeometrySize[(sizeof(Rva002C3550Geometry)==0x5c)?1:-1];
typedef char Rva002C3550ShapeSize[(sizeof(Rva002C3550Shape)==0x24)?1:-1];
typedef char Rva002C3550RecordSize[(sizeof(Rva002C3550Record)==0x10)?1:-1];
typedef char Rva002C3550MemberSize[(sizeof(void(Rva002C3550Call::*)(bool))==4)?1:-1];
