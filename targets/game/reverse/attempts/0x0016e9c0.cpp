// ?d_0016e9c0@@YAXXZ
// partial score=0.9910313901345291 date=2026-09-28
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath
// Banked reconstruction of retail RVA 0x0016E9C0, extent 669, ret 8.
// Emitter: ?find@DestinationSearch0016E9C0@@QAE_NPAVCoord3D@@PAX@Z
// Intended home: game/GameEngine/Source/GameLogic/AI/.
// Identity is deliberately address-derived. Matched Rva00173620State::computePath
// (0x00173680) calls this through ILT 0x0003BC05 with destination
// and owner on the stack. ECX is the state, but this body never reads it.
// The 0x0016EE00 sibling is identical except for REL32 call displacements.
//
// Best probe: 669 bytes; six differing bytes, solely the adjacent instruction
// order at +0x3D/+0x40. Retail: FLD [ESI+4]; LEA EDI,[EBX+38h]. Ours reverses
// those two instructions. All later bytes and relocation locations agree.
// The barrier is a compiler-ordering experiment, not an original-source claim.
// It fixes the x87 initial load order but does not finish the adjacent swap.
// GetLength's sequential accumulator preserves retail's two separate sums
// around __ftol2. A local pathfinder copy fixes the ECX/EDX rotation in the loop.
//
// Calls use existing address-only ILT symbols with witnessed thiscall ABIs:
// 0003A391 -> 001BEC20: no stack arguments, integer layer result.
// 0004A327 -> 003EDF90: object, start coordinate, end coordinate, zero; AL result.
// 00011252 -> 003EAC80: object, embedded AI+1A8 set, mutable coordinate.
// 00027FFC -> 003F6090: adjustDestination with the same triple and null group.
// No pins were added. AI+0C/+14 are independently used in the matched caller.
// Object+BC and AI-data+D0 lack a witnessed semantic member name, so remain
// explicit offsets. The 20.0 and -0.05 constants were read from retail.
#include <math.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &p) {x=p.x;y=p.y;z=p.z;}
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &p) {struct Raw {unsigned x,y,z;};*(Raw*)this=*(const Raw*)&p;return *this;}
inline Coord3D &Coord3D::operator=(const Coord3D &p) {Coord3DBase *base=this;*base=p;return *this;}
inline void Coord3D::set(const Coord3DBase *p) {x=p->x;y=p->y;z=p->z;}
inline void Coord3D::sub(const Coord3DBase *p) {x-=p->x;y-=p->y;z-=p->z;}
inline void Coord3D::scale(float s) {x*=s;y*=s;z*=s;}
inline float Coord3D::GetLength2D() const {float a=x,b=y;return (float)sqrt(a*a+b*b);}
inline float Coord3D::GetLength() const {float a=x*x; a+=y*y;a+=z*z;return (float)sqrt(a);}
__forceinline void Coord3D::normalize() {float len=(float)sqrt(x*x+y*y+z*z);if(len!=0.0f){float inv=1.0f/len;x*=inv;y*=inv;z*=inv;}}
inline float Coord3D::Normalize() {float len=GetLength();float inv=1.0f/len;x*=inv;y*=inv;z*=inv;return len;}
class Receiver {};
extern void j_0003a391();
extern void j_0004a327();
extern void j_00011252();
extern void j_00027ffc();
template<class T> __forceinline T member(void (*raw)()) {union {void (*raw)(); T m;} u;u.raw=raw;return u.m;}
#define CALL(T,p,f) (((Receiver*)(p))->*member<T>(f))
typedef int (Receiver::*Query)();
typedef bool (Receiver::*Check)(void*,const Coord3D*,Coord3D*,int);
typedef unsigned (Receiver::*Prepare)(void*,void*,Coord3D*);
typedef bool (Receiver::*Adjust)(void*,void*,Coord3D*,const Coord3D*);
class AI {public: char pad0[12];void *pathfinder;char pad10[4];void *data;};
extern AI *TheAI;
class DestinationSearch0016E9C0 {
public: bool find(Coord3D *destination, void *object);
};
bool DestinationSearch0016E9C0::find(Coord3D *destination, void *object)
{
 if(CALL(Query,object,j_0003a391)()>1) return true;
 void *ai=*(void**)((char*)object+0x204);
 if(!ai) return false;
 const Coord3D *position=(Coord3D*)((char*)object+0x38);
 Coord3D delta; delta.x=destination->x; _ReadWriteBarrier(); delta.y=destination->y; delta.z=destination->z; delta.sub(position); float distance=delta.GetLength2D();
 Coord3D direction;direction=*destination;
 Coord3D candidate=*destination;
 direction.sub(position);
 direction.z=0.0f;
 int count=-(int)(direction.GetLength2D()*-0.05f)-1;
 direction.Normalize();
 direction.scale(20.0f);
 int i;
 for(i=0;i<count;++i) {
  candidate.sub(&direction);
  void *pathfinder=TheAI->pathfinder;
  if(CALL(Check,pathfinder,j_0004a327)(object,position,&candidate,0)) {
 float clearance=*(float*)((char*)TheAI->data+0xd0)+*(float*)((char*)object+0xbc);
 direction.normalize();
 direction.scale(clearance);
 candidate.sub(&direction);
 direction=*destination;
 direction.sub(&candidate);
 if(direction.GetLength2D()+20.0f>distance) return false;
 CALL(Prepare,TheAI->pathfinder,j_00011252)(object,(char*)ai+0x1a8,&candidate);
 CALL(Adjust,TheAI->pathfinder,j_00027ffc)(object,(char*)ai+0x1a8,&candidate,0);
 *destination=candidate;
 return true;
  }
 }
 return false;
}
