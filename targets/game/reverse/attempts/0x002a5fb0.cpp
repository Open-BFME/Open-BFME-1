// ?d_002a5fb0@@YAXXZ
// partial score=0.3869209809264305 date=2026-09-28
// Retail 0x002A5FB0 path sampling helper. Address-qualified owner; identity unproved.
#include <math.h>
struct Coord3D { float x,y,z; };
class BfmeHolderNS {public:int bfmeQueryNS();};
class Object {public:char pad000[0x38];Coord3D position;char pad044[0x204-0x44];void *field204;};
enum PathfindLayerEnum {Layer002A5FB0};
class TerrainLogic {public:PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);};
class BfmeE1081;
class BfmeD1081 {public:char bfmeDo1081(BfmeE1081*,char*,char*,int);};
class AI {public:char pad[12];BfmeD1081 *path;};
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
class PathSample002A5FB0 {public:char pad[8];Object *object;bool adjust(Coord3D *destination,float range);};
bool PathSample002A5FB0::adjust(Coord3D *destination,float range) {
 Object *self=object;
 if (((BfmeHolderNS*)self)->bfmeQueryNS()>1) return true;
 if (!self->field204) return false;
 Coord3D delta=*destination;
 Coord3D current=*destination;
 const Coord3D *position=&self->position;
 delta.x-=position->x;delta.y-=position->y;delta.z=0.0f;
 int count=-1-(int)(range*-0.1f);
 float inverse=1.0f/(float)sqrt(delta.x*delta.x+delta.y*delta.y);
 delta.x*=inverse;delta.y*=inverse;delta.z*=inverse;
 delta.x*=10.0f;delta.y*=10.0f;delta.z*=10.0f;
 int i=0;while(i++<count) {
  current.x-=delta.x;current.y-=delta.y;current.z-=delta.z;
  if (TheTerrainLogic->getLayerForDestination(self,&current)==1 && TheAI->path->bfmeDo1081((BfmeE1081*)self,(char*)position,(char*)&current,0)) {
   *destination=current;return true;
  }
 }
 return false;
}
