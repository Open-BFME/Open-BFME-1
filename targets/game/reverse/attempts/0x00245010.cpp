// ?build@FormationBuild00245010@@QAEXH@Z
// partial score=0.158845 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include "coord.h"
extern void j_00042898();extern void j_00034d24();extern void j_00033d39();
extern void j_0001476d();extern void j_0001de3a();extern void j_0001aacd();
extern void j_000128dc();extern void j_0000c5d6();extern void j_000178eb();extern void j_00038604();extern void j_0001d9d0();
extern int GetGameLogicRandomValue(int,int,char *,int);
class Record00245010 {public: int field000;float field004,field008,field00C;
 Record00245010() {union {void (*p)();void (Record00245010::*m)();} c;c.p=j_00033d39;(this->*c.m)();}
};
class Slot00245010 {public: char data[28];
 Slot00245010() {union {void (*p)();void (Slot00245010::*m)();} c;c.p=j_0001aacd;(this->*c.m)();}
};
template<class T> struct Vector00245010 {T *first,*last,*limit;
 unsigned size() const {return last-first;}
 T *begin() {return first;}
 void reserve(unsigned n, void (*route)()) {union {void (*p)();void (Vector00245010::*m)(unsigned);} c;c.p=route;(this->*c.m)(n);}
 void push(const T &value,void (*construct)(),void (*overflow)()) {
  if(last!=limit) {((void (*)(T *,const T &))construct)(last,value);++last;}
  else {char tag;union {void (*p)();void (Vector00245010::*m)(T *,const T &,const char &,unsigned,bool);} c;c.p=overflow;(this->*c.m)(last,value,tag,1,true);}
 }
};
struct Rank00245010 {int field000;int field004;Vector00245010<Coord3D> field008;};
struct Data00245010 {
 char pad000[0x224];Vector00245010<Rank00245010 *> field224;
 char pad230[0x268-0x230];float field268,field26C;
 char pad270[0x28c-0x270];Vector00245010<int> field28C;
 int field298[2];char pad2A0[0x2b0-0x2a0];Vector00245010<int> field2B0;
};
class FormationBuild00245010 {public:
 void *field000;Data00245010 *field004;
 char pad008[0x38-8];_STL::list<int> field038;
 char pad03C[0x118-0x38-sizeof(_STL::list<int>)];int field118;
 char pad11C[0x12c-0x11c];Vector00245010<Record00245010> field12C;
 _STL::list<int> field138;bool field13C;
 char pad13D[0x1b8-0x13d];int field1B8;
 char pad1BC[0x1d8-0x1bc];Vector00245010<Slot00245010> field1D8;
 void build(int arg);
 void add(int *input,int value,int *out) {union {void (*p)();void (FormationBuild00245010::*m)(int *,int,int *);} c;c.p=j_000178eb;(this->*c.m)(input,value,out);}
 void extra(Data00245010 *d) {union {void (*p)();void (FormationBuild00245010::*m)(Data00245010 *);} c;c.p=j_00038604;(this->*c.m)(d);}
 void finish() {union {void (*p)();void (FormationBuild00245010::*m)();} c;c.p=j_0001d9d0;(this->*c.m)();}
};
void FormationBuild00245010::build(int arg) {
 Data00245010 *data=field004;
 int total=0;
 Rank00245010 **rankIt=data->field224.begin();
 for(unsigned remaining=data->field224.size();remaining>0;--remaining,++rankIt) total+=(*rankIt)->field008.size();
 field12C.reserve(total,j_00042898);field1D8.reserve(total,j_00034d24);
 float jitterX=data->field268,jitterY=data->field26C;
 for(unsigned i=0;i<data->field224.size();++i) {
  Rank00245010 *rank=data->field224.first[i];
  int value=rank->field000;
  Coord3D *positions=rank->field008.begin();
  for(unsigned j=0;j<rank->field008.size();++j) {
   Record00245010 record;
   record.field004=positions[j].x;
   record.field008=positions[j].y;
   record.field000=value;
   if(jitterX>0.0f) record.field004+=GetGameLogicRandomValue((int)-jitterX,(int)jitterX,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x4fb);
   if(jitterY>0.0f) record.field008+=GetGameLogicRandomValue((int)-jitterY,(int)jitterY,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x4fe);
   record.field00C=rank->field008.first[j].z;
   field12C.push(record,j_0001476d,j_0001de3a);
   if(arg || (field038.empty() && !field118)) {
    field138.push_back(field12C.size()-1);
    Slot00245010 slot;
    field1D8.push(slot,j_000128dc,j_0000c5d6);
   }
   positions=rank->field008.begin();
  }
 }
 if(data->field28C.first!=data->field28C.last) add(data->field298,0,&field1B8);
 if(data->field2B0.first!=data->field2B0.last) extra(data);
 finish();field13C=true;
}

