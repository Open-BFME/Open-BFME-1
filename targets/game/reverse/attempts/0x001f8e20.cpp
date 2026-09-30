// ?method@Rva001F8E20Owner@@QAEXPAUCoord3D@@@Z
// partial score=0.5861 date=2026-09-30
// stlport
// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
#include "Common/Thing.h"
#include <math.h>
extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;
struct Rva001F8E20Data { char pad[0xcc]; Coord3D pos; };
class Rva001F8E20Owner {
public:
 void *vptr; Rva001F8E20Data *data; Thing *object;
 void method(Coord3D *out);
};
void Rva001F8E20Owner::method(Coord3D *out) {
 Rva001F8E20Data *d=data;
 Coord3D in = {1.0f,0.0f,0.0f};
 Coord3D delta;
 object->transformPoint(&in,&delta);
 delta.x -= object->getPosition()->x;
 delta.y -= object->getPosition()->y;
 float ay=(float)fabs(delta.y), ax=(float)fabs(delta.x);
 const float &maximum=ax>ay?ax:ay;
 float scale=g_bfmeDefaultBU/maximum;
 delta.x*=scale;
 delta.y*=scale;
 delta.z=BfmeZeroRange*scale;
 in=d->pos;
 float len=(float)sqrt(delta.z*delta.z+delta.x*delta.x+delta.y*delta.y);
 in.x*=len;
 in.y*=len;
 Coord3D result;
 object->transformPoint(&in,&result);
 out->x=result.x;
 out->y=result.y;
 out->z=result.z;
}
