// ?adjust@PathSample002A5FB0@@QAE_NPAVCoord3D@@M@Z
// partial score=0.5967 date=2026-11-06
// ?adjust@PathSample002A5FB0@@QAE_NPAVCoord3D@@M@Z
// s560 bank: sibling Rva0016EE00 idiom (WWMath coord3d.h, raw direction=*dest copy,
// copy-constructed candidate, sub/z=0/Normalize/scale(10), sub at loop top).
// 366/367 B, shape 0.983: only the callee-saved register rotation differs
// (retail object ESI, destination EDI, position EBX, count EBP; ours EBX/ESI/EBP/EDI
// with a late EDI save), which also turns retail's 6-byte mov edx,[TheAI] into
// our 5-byte mov eax,[TheAI].
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath
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
inline float Coord3D::GetLength() const {return (float)sqrt(x*x+y*y+z*z);}
__forceinline void Coord3D::normalize() {float len=(float)sqrt(x*x+y*y+z*z);if(len!=0.0f){float inv=1.0f/len;x*=inv;y*=inv;z*=inv;}}
inline float Coord3D::Normalize() {float len=GetLength();float inv=1.0f/len;x*=inv;y*=inv;z*=inv;return len;}
class Receiver {};
extern void j_0001c675();
extern void j_0004a327();
template<class T> __forceinline T member(void (*raw)()) {union {void (*raw)(); T m;} u;u.raw=raw;return u.m;}
#define CALL(T,p,f) (((Receiver*)(p))->*member<T>(f))
class Object;
typedef int (Receiver::*Layer)(Object*,const Coord3D*);
typedef bool (Receiver::*Check)(Object*,const Coord3D*,Coord3D*,int);
class Object {
public:
 int getLayer() const;
 const Coord3D *getPosition() const { return &m_position; }
 void *getAI() const { return m_ai; }
private:
 char m_pad000[0x38];
 Coord3D m_position;
 char m_pad044[0x204-0x44];
 void *m_ai;
};
class AI {public: char pad0[12];void *pathfinder;};
extern AI *TheAI;
extern void *TheTerrainLogic;
class PathSample002A5FB0 {
public: bool adjust(Coord3D *destination, float range);
 Object *getObject() const { return m_object; }
 char pad0[8];
 Object *m_object;
};
bool PathSample002A5FB0::adjust(Coord3D *destination, float range)
{
 Object *object=getObject();
 if(object->getLayer()>1) return true;
 if(!object->getAI()) return false;
 Coord3D direction;direction=*destination;
 Coord3D candidate=*destination;
 const Coord3D *position=object->getPosition();
 direction.sub(position);
 direction.z=0.0f;
 int count=-(int)(range*-0.1f)-1;
 direction.Normalize();
 direction.scale(10.0f);
 int i;
 for(i=0;i<count;++i) {
  candidate.sub(&direction);
  if(CALL(Layer,TheTerrainLogic,j_0001c675)(object,&candidate)==1 && CALL(Check,TheAI->pathfinder,j_0004a327)(object,position,&candidate,0)) {
   *destination=candidate;
   return true;
  }
 }
 return false;
}
