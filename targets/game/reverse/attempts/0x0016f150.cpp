// ?method@Rva0016F150@@QAE_NPAUCoord3D@@PAVObject@@PAX@Z
// partial score=0.4631 date=2026-10-09
// cl: /DNDEBUG /MD /Igame/Libraries/Include
#include <math.h>
#include "Lib/Coord3D.h"
class Rva0016F150Vector : public Coord3D {
public:
    Rva0016F150Vector() {}
    Rva0016F150Vector(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
    void copy(const Coord3D &p) { struct Raw {unsigned x,y,z;}; *(Raw*)this=*(const Raw*)&p; }
    void copyTo(Coord3D *p) const { struct Raw {unsigned x,y,z;}; *(Raw*)p=*(const Raw*)this; }
    void sub(const Coord3D *p) { x-=p->x; y-=p->y; z-=p->z; }
    void scale(float s) { x*=s; y*=s; z*=s; }
    float length2D() const { float a=x,b=y; return (float)sqrt(a*a+b*b); }
    float length() const { float a=x,b=y,c=z; return (float)sqrt(a*a+b*b+c*c); }
    void normalize() { float len=length(); float inv=1.0f/len; x*=inv; y*=inv; z*=inv; }
};
class Object { public: int getLayer() const; };
enum PathfindLayerEnum { LAYER_INVALID=0, LAYER_GROUND=1 };
class Rva0016F150CallReceiver {};
extern void j_000432a2();
template<class T> __forceinline T member(void (*raw)()) { union { void (*raw)(); T m; } u; u.raw=raw; return u.m; }
#define CALL(T,p,f) (((Rva0016F150CallReceiver*)(p))->*member<T>(f))
typedef int (Rva0016F150CallReceiver::*LineClear)(Object*,int,PathfindLayerEnum,const Coord3D*,const Coord3D*);
class AI;
extern AI *TheAI;
class Rva0016F150 {
public: bool method(Coord3D *destination, Object *object, void *unused);
};
bool Rva0016F150::method(Coord3D *destination, Object *object, void *unused)
{
    void *ai=*(void**)((char*)object+0x204);
    if(!ai) return false;
    Rva0016F150Vector direction=*destination;
    Rva0016F150Vector candidate; candidate.copy(*destination);
    direction.sub((Coord3D*)((char*)object+0x38));
    direction.z=0.0f;
    int count=-(int)(direction.length2D()*-0.05f)-1;
    direction.normalize();
    direction.scale(10.0f);
    for(int i=0;i<count;++i) {
        void *pathfinder=*(void**)((char*)TheAI+0x0c);
        int queryValue=*(int*)((char*)ai+0x1b8);
        if((unsigned char)CALL(LineClear,pathfinder,j_000432a2)(object,queryValue,(PathfindLayerEnum)object->getLayer(),&candidate,&candidate)) {
            candidate.copyTo(destination);
            return true;
        }
        candidate.sub(&direction);
    }
    return false;
}
