// ?method@Rva0016EE00@@QAE_NPAVCoord3D@@PAX@Z
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath
//
// Retail RVA 0x0016EE00, 669 bytes. The body returns with ret 8 at +0x29A,
// and INT3 padding starts at +0x29D.
//
// The byte-true AIAttackApproachTargetState::computePath body at 0x00182360
// calls ILT 0x0001041A with Coord3D* and Object*. Those arguments establish
// the ABI. The caller does not name the operation, so this body keeps the
// address-derived identity Rva0016EE00::method.
//
// The position pointer follows the destination X/Y copies. That source order
// reproduces retail's FLD destination Y before LEA object+0x38.
// Existing ILTs provide the query, path check, preparation, and adjustment
// calls. Object+0xBC and AI data+0xD0 remain address-derived field offsets.
#include <math.h>
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
class Rva0016EE00 {
public: bool method(Coord3D *destination, void *object);
};
bool Rva0016EE00::method(Coord3D *destination, void *object)
{
 if(CALL(Query,object,j_0003a391)()>1) return true;
 void *ai=*(void**)((char*)object+0x204);
 if(!ai) return false;
 Coord3D delta; delta.x=destination->x; delta.y=destination->y;
 const Coord3D *position=(Coord3D*)((char*)object+0x38);
 delta.z=destination->z; delta.sub(position); float distance=delta.GetLength2D();
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
