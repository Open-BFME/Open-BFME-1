// ?rva006DC0D0@Rva006DED60RoadBuffer@@QAEXPAVMeshClass@@PAURva006DC0D0RenderView@@HAAU?$_Rb_tree_iterator@PAURva006DC0D0Instance@@U?$_Const_traits@PAURva006DC0D0Instance@@@_STL@@@_STL@@@Z
// partial score=0.0438 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /I. /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#include "game/Libraries/Source/WWVegas/WW3D2/mesh.h"
#include "game/Libraries/Source/WWVegas/WW3D2/meshmdl.h"
#include "game/Libraries/Source/WWVegas/WW3D2/vertmaterial.h"
#include "game/Libraries/Source/WWVegas/WWMath/color.h"
#include <set>
struct Rva006DB2F0Vec;
class Rva006DB2F0 { public: void set(const Rva006DB2F0Vec *); };
class Rva006DAC80Fade { public: void update(); };
class Bfme5ShroudedThing { public: char bfmeIsShrouded(int); };
struct Rva006DC0D0Instance {
 char gap00[0xC]; float value0c; bool flag10; char gap11[3]; Matrix3D matrix;
 bool flag44; char gap45[3]; Vector3 position; float scale;
};
struct Rva006DC0D0Vertex { float x,y,z; unsigned color; float u,v; };
struct Rva006DC0D0Array { char gap[0xC]; void *data; };
struct Rva006DC0D0Model {
 char gap00[0x18]; unsigned flags; char gap1c[8]; int triangles,vertices;
 Rva006DC0D0Array *indices,*positions; char gap34[0x68]; MeshMatDescClass *materials;
};
struct Rva006DC0D0MatInfo {
 void **vptr; int refs; int unused; VertexMaterialClass **materials;
 void release(){if(--refs==0){typedef void (__fastcall *F)(void *);((F)vptr[0])(this);}}
};
struct Rva006DC0D0RenderView {
 void **vptr; char gap04[0x14]; Matrix3D transform;
 char gap48[0x80]; Rva006DC0D0Model *model;
 Vector3 position()const {
  typedef void (__fastcall *F)(const void *);((F)vptr[20])(this);
  return transform.Get_Translation();
 }
 Rva006DC0D0MatInfo *materialInfo(){typedef Rva006DC0D0MatInfo *(__fastcall *F)(void *);return ((F)vptr[84])(this);}
};
struct Rva006DC0D0Com {
 void **vptr;
 void lock(unsigned offset,unsigned size,void **out,unsigned flags) {
  typedef long (__stdcall *F)(void *,unsigned,unsigned,void **,unsigned);
  ((F)vptr[11])(this,offset,size,out,flags);
 }
 void unlock(){typedef long (__stdcall *F)(void *);((F)vptr[12])(this);}
};
struct Rva006DC0D0FVF {unsigned unused,stride;};
struct Rva006DC0D0VB {char gap[0x14];Rva006DC0D0FVF *fvf;unsigned unused;Rva006DC0D0Com *buffer;};
struct Rva006DC0D0IB {char gap[0x14];Rva006DC0D0Com *buffer;};
struct Rva006DC0D0Player {char gap[0x24];int index;};
struct Rva006DC0D0Players {char gap[0xC];Rva006DC0D0Player *player;};
extern Rva006DC0D0Players *Rva012ED748;
struct Rva006DC0D0Clock {void **vptr;unsigned frame(){typedef unsigned (__fastcall *F)(void *);return ((F)vptr[26])(this);}};
extern Rva006DC0D0Clock *Rva012F1464;
typedef std::set<Rva006DC0D0Instance*> Rva006DC0D0Set;
class Rva006DED60RoadBuffer {
public:
 void rva006DC0D0(MeshClass *,Rva006DC0D0RenderView *,int,Rva006DC0D0Set::iterator &);
 Rva006DC0D0VB *vb;Rva006DC0D0IB *ib;int usedVertices,usedIndices,baseVertex,baseIndex;
 char gap18[0x7C];Rva006DC0D0Set sets[10];bool enabled;
};
void Rva006DED60RoadBuffer::rva006DC0D0(MeshClass *mesh,Rva006DC0D0RenderView *camera,int index,Rva006DC0D0Set::iterator &it) {
 if(!ib||!vb||!enabled)return;
 if(!mesh||!camera)return;
 usedVertices=0;usedIndices=0;

 if(it==sets[index].end())return;
 Rva006DC0D0RenderView *render=(Rva006DC0D0RenderView *)mesh;
 Vector3 *positions=(Vector3 *)render->model->positions->data;
 int nverts=render->model->vertices;
 int ntris=render->model->triangles;
 unsigned short *triangles=(unsigned short *)render->model->indices->data;
 Vector2 *uv=render->model->materials->Get_UV_Array_By_Index(0,false);
 unsigned *colors=render->model->materials->Get_Color_Array(0,false);
 Vector3 emissive(0,0,0);
 Rva006DC0D0MatInfo *info=render->materialInfo();
 if(info){info->materials[0]->Get_Emissive(&emissive);info->release();}
 RGBColor light;light.red=emissive.X;light.green=emissive.Y;light.blue=emissive.Z;
 Rva006DC0D0Vertex *vertices;
 unsigned short *indices;
 int total=sets[index].size()*nverts;
 int stride=vb->fvf->stride;
 if(baseVertex+total+2>=30000){baseVertex=0;vb->buffer->lock(0,total*stride,(void**)&vertices,0x2000);}
 else vb->buffer->lock(baseVertex*stride,total*stride,(void**)&vertices,0x1000);
 total=sets[index].size()*ntris*3;
 if(baseIndex+total+6>=60000){baseIndex=0;ib->buffer->lock(0,total*2,(void**)&indices,0x2000);}
 else ib->buffer->lock(baseIndex*2,total*2,(void**)&indices,0x1000);
 int player=Rva012ED748?Rva012ED748->player->index:0;
 for(;it!=sets[index].end();++it) {
  Rva006DC0D0Instance *instance=*it;
  if(!instance)continue;
  if(!instance->flag44||((Bfme5ShroudedThing*)instance)->bfmeIsShrouded(player)) {((Rva006DAC80Fade*)instance)->update();continue;}
  Vector3 pos=instance->position;
  float scale=instance->scale;
  int start=baseVertex+usedVertices;
  pos+=render->position();
  bool useMatrix=false;
  if(!instance->flag10) {
   if(render->model->flags&0x800) {
    Matrix3D matrix;
    matrix.Obj_Look_At(pos,camera->position(),0);
    matrix.Set_Translation(Vector3(0,0,0));
    ((Rva006DB2F0*)instance)->set((const Rva006DB2F0Vec*)&matrix);
    useMatrix=true;
   }
   instance->flag10=true;
  }
  if(render->model->flags&0x800) {
   if(Rva012F1464->frame()%10==0) {
    Matrix3D matrix;
    matrix.Obj_Look_At(pos,camera->position(),0);
    matrix.Set_Translation(Vector3(0,0,0));
    ((Rva006DB2F0*)instance)->set((const Rva006DB2F0Vec*)&matrix);
   }
   useMatrix=true;
  }
  for(int i=0;i<nverts;++i) {
   vertices->u=uv[i].X;vertices->v=uv[i].Y;
   Vector3 original=positions[i];
   Vector3 p=original*scale;
   if(useMatrix)Matrix3D::Transform_Vector(instance->matrix,original,&p);
   p+=pos;
   vertices->x=p.X;vertices->y=p.Y;vertices->z=p.Z;
   RGBColor color=light;
   if(colors&&colors[i]!=0xffffffff) {
    unsigned c=colors[i];
    color.blue=float(c&255)*color.blue*(1.0f/255.0f);
    color.green=float((c>>8)&255)*color.green*(1.0f/255.0f);
    color.red=float((c>>16)&255)*color.red*(1.0f/255.0f);
   }
   color.red*=instance->value0c;color.green*=instance->value0c;color.blue*=instance->value0c;
   vertices->color=color.getAsInt();++vertices;++usedVertices;
  }
  for(int j=0;j<ntris;++j) {
   *indices++=triangles[j*3]+start;*indices++=triangles[j*3+1]+start;*indices++=triangles[j*3+2]+start;
   usedIndices+=3;
  }
  ((Rva006DAC80Fade*)instance)->update();
 }
 vb->buffer->unlock();ib->buffer->unlock();
}
