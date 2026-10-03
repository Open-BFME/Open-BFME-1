// ?rva002C3E00@Rva002C3FE0Owner@@QAEXPAUCoord3D@@PA_N_N@Z
// partial score=0.8953 date=2026-10-03
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "Lib/BaseType.h"
#include "matrix3d.h"
struct Rva002C3E00Data { char field00[0x74]; float field74,field78,field7C; };
struct Rva002C3E00Loco { char field00[4]; Rva002C3E00Data *field04; };
struct Rva002C3E00Object { char field00[8]; Matrix3D field08; Coord3D field38; char field44[0x204-0x44]; Rva002C3E00Loco *field204; };
struct Rva002C3E00Context { char field00[0x10]; Rva002C3E00Object *field10; };
class Rva002C3FE0Owner { char field00[0x1c]; Rva002C3E00Context *field1C;
public: void rva002C3E00(Coord3D *,bool *,bool); bool method(const Coord3D *,float); };
void Rva002C3FE0Owner::rva002C3E00(Coord3D *out,bool *shortened,bool doubled) {
 Rva002C3E00Object *object=field1C->field10;
 Coord3D last; last.x=object->field38.x; last.y=object->field38.y; last.z=object->field38.z;
 float achieved=0.0f;
 if(object->field204) {
  const Rva002C3E00Data *data=object->field204->field04;
  float height=object->field38.z;
  Vector3 direction=object->field08.Get_X_Vector();
  float limit=data->field74;
  float step=data->field78;
  float slope=data->field7C;
  if(doubled)limit+=limit;
  for(float distance=step;distance<=limit;distance+=step) {
   Vector3 scaled=distance*direction;
   Coord3D delta; delta.x=scaled.X;delta.y=scaled.Y;delta.z=scaled.Z;
   Coord3D candidate; candidate.x=object->field38.x; candidate.y=object->field38.y; candidate.z=object->field38.z;
   candidate.add(&delta);
   if(!method(&candidate,distance*slope+height))break;
   achieved=distance;
   last=candidate;
  }
  if(achieved<limit*0.5f)*shortened=true;else *shortened=false;
 }
 out->x=last.x;out->y=last.y;out->z=last.z;
}
