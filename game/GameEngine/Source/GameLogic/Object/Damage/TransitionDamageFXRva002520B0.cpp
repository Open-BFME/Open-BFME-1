// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Native source for retail002520B0 (407 bytes), ending RET00252246 then INT3.
// GeneralsMD TransitionDamageFX.cpp::getLocalEffectPos supplies the algorithm;
// retail literalCB2528 proves the BFME TU, including the random call line339.
// Inputs match FXLocInfo offsets00/04/08/0C, but this partial view keeps its
// address and offset names. Direct calls002526F5/0025277D/0025282E independently
// establish the compiler-private EDI/EBX/ESI input/result convention.
// Coord3D's canonical empty constructor/destructor and field-wise copy are
// visible here: scalar lifetimes optimize away, while the32-element array
// retains CRT construction/destruction and the native EH actionC0E7E0.
// Parent -> handlerC0E7F6 -> FuncInfoDFD604/mapDFD5FC state0/-1 owns that action.
// Preserve the same canonical coordinate layout with the struct key required
// by the independently matched six-argument bone-query ABI (PAUCoord3D).
#define class struct
#include "coord3d.h"
#undef class
#include "ascii_string.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &other) {x=other.x;y=other.y;z=other.z;}
class Matrix3D;
class BFMEDrawableBoneQuery {
public:
 int getPristineBonePositions(const char *,int,Coord3D *,Matrix3D *,int,int) const;
};
int GetGameLogicRandomValue(int,int,char *,int);
struct Rva002520B0Loc {
 char field00;
 AsciiString field04;
 bool field08;
 Coord3D field0C;
};
static __declspec(noinline) Coord3D rva002520B0(const Rva002520B0Loc *loc, BFMEDrawableBoneQuery *draw) {
 if(loc->field00==0 && draw) {
  if(!loc->field08) {
   Coord3D pos;
   int count=draw->getPristineBonePositions(loc->field04.str(),0,&pos,0,1,0);
   if(count==0) return loc->field0C;
   return pos;
  } else {
   Coord3D positions[32];
   int count=draw->getPristineBonePositions(loc->field04.str(),1,positions,0,32,0);
   if(count==0) return loc->field0C;
   int pick=GetGameLogicRandomValue(0,count-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Damage\\TransitionDamageFX.cpp",339);
   return positions[pick];
  }
 }
 return loc->field0C;
}
// absent-from-retail: emission anchor for the file-local helper. The real
// caller at 002525E0 passes loc in EDI, draw in EBX, and result storage in ESI;
// VC7.1 derives that exact private convention from this ordinary C++ call.
Coord3D emitRva002520B0(const Rva002520B0Loc *loc,BFMEDrawableBoneQuery *draw) {return rva002520B0(loc,draw);}
