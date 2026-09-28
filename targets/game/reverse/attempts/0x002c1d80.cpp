// ?update@Rva002C1D80@@QAEHXZ
// partial score=0.898 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
// Opaque secondary-interface update; retail start is ILT target 000133D6.
#include "../../../command_source_type.h"
struct Coord3D { float x,y,z; float GetLengthEstimate() const; void normalize(); };
enum AICommandType { COMMAND_INVALID=-1 };
class Gen_000D7330 { public: void bfmeClear(); };
struct AICommandParms {
 char field00[0x9c];
 AICommandParms(AICommandType,CommandSourceType);
 ~AICommandParms() { ((Gen_000D7330*)this)->bfmeClear(); }
};
class AICommandParmsStorage { public: void reconstitute(AICommandParms&) const; int field00; char field04[0xa0-4]; };
class AICommandInterface { public: virtual void slot00(const AICommandParms*)=0; };
template<int N> class BitFlags { public: enum Init{kInit}; _STL::bitset<N> data; BitFlags(Init,int n){data.set(n);} };
class Thing { public: float getHeightAboveTerrain() const; float bfmeRelativeAngleTo(const Coord3D*) const; void setOrientation(float); void setPositionZ(float); };
class Object { public: void setStatus(const BitFlags<86>&,bool); void notifyModelConditionChanged(); char field00[0x38]; Coord3D field38; float field44; char field48[0x11c-0x48]; union { unsigned field11C; unsigned char byte11C; }; char field120[0x344-0x120]; unsigned char field344; };
class Overridable { public: virtual ~Overridable(); const Overridable* getFinalOverride() const { if(next) return next->getFinalOverride();return this; } Overridable* next; };
class Rva002C1D80Template:public Overridable { public: char field08[0xbc-8]; int fieldBC; };
template<class T> class OVERRIDE { public: const T* ptr; const T* value() const { if(!ptr)return 0;return (T*)ptr->getFinalOverride(); } };
struct Rva002C1D80Loco { void* field00; OVERRIDE<Rva002C1D80Template> field04; const Rva002C1D80Template* value()const { return field04.value(); } };
class Rva002BC260Owner { public: void run(void*,void*,void*,void*); };
class Rva002C1480 { public: void invoke(); };
struct Rva002C1D80State { int field00; unsigned field04; };
class Rva002C1D80Machine { public: virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual int v10(); char field04[0x18]; Rva002C1D80State* field1C; unsigned state()const { if(field1C)return field1C->field04;return 999999;} };
class Rva002C1D80Root { public:
 virtual void slot000();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual int slot214();
};
extern char rva012F02D8;
float normalizeAngle(float);
class Rva002C1D80 {
public:
 int update();
 char field00[0x20]; Rva002C1D80Machine* field20;
 char field24[0x1bc-0x24]; Rva002C1D80Loco* field1BC;
 char field1C0[0x33c-0x1c0]; AICommandParmsStorage field33C;
 char field3DC[0x450-0x3dc]; int field450;
 char field454[0x460-0x454]; float field460,field464; char field468[0x18];
 unsigned char field480; char field481[7]; Coord3D field488,field494; bool field4A0;
 Object* object() { return *(Object**)((char*)this-8); }
};
int Rva002C1D80::update() {
 if(!field480 && field33C.field00!=-1) {
  AICommandParms parms(COMMAND_INVALID,(CommandSourceType)2);
  field33C.reconstitute(parms);
  ((AICommandInterface*)((char*)this+0x10))->slot00(&parms);
  field33C.field00=-1;
 }
 Rva002C1D80Root* root=(Rva002C1D80Root*)((char*)this-0x10);
 ((Rva002C1480*)root)->invoke();
 field464*=0.8f;
 field460*=0.9f;
 Object* obj=object();
 int height=field1BC->value()->fieldBC;
 if(((Thing*)obj)->getHeightAboveTerrain()>height) object()->setStatus(BitFlags<86>(BitFlags<86>::kInit,6),true);
 else object()->setStatus(BitFlags<86>(BitFlags<86>::kInit,6),false);
 int sleep=2;
 int next=field20->v10();
 if(next>0) { if(next<sleep)sleep=next; } else sleep=1;
 if(object()->field344&1)return 1;
 Coord3D* direction=&field494;
 if(direction->GetLengthEstimate()>0.0f) {
  direction->normalize();
  Coord3D goal; goal.x=field488.x; goal.y=field488.y; goal.z=field488.z+4.0f;
  obj=object(); if(!(obj->byte11C&0x40)){obj->field11C|=0x40;obj->notifyModelConditionChanged();}
  float orient=object()->field44;
  float delta=((Thing*)object())->bfmeRelativeAngleTo(&goal)-orient;
#define BMIN(a,b) ((a)<(b)?(a):(b))
#define BMAX(a,b) ((a)>(b)?(a):(b))
  float angle=normalizeAngle(orient+BMIN(-0.2f,BMAX(0.2f,normalizeAngle(delta))));
  ((Thing*)object())->setOrientation(angle);
  ((Thing*)object())->setPositionZ(goal.z);
  direction->x=0;direction->y=0;direction->z=0;
  field460*=0.5f;
  field488=object()->field38;
  field4A0=true;
  return 1;
 }
 if(field4A0){field4A0=false;((Rva002BC260Owner*)root)->run((char*)this+0x46c,&rva012F02D8,0,0);}
 field488=object()->field38;
 unsigned state=field20->state();
 switch(state) {
 case 0: field450=3;
 case 1001:case 1002:case 1003:case 1004:case 1006:case 1007:case 1009:case 1010:case 1011:case 1013:case 1014:case 1019:
  next=root->slot214();if(next<sleep)sleep=next;break;
 case 16:case 17:case 23:case 31:case 1015:case 1016:case 1017:case 1018:
  field450=1;next=root->slot214();if(next<sleep)sleep=next;break;
 case 1005:case 1012:sleep=1;break;
 }
 return sleep;
}
