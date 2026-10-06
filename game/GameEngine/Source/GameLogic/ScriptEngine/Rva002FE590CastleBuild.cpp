// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

struct Coord3D { float x,y,z; };
class Object;
class PartitionManager;
class NameKeyGenerator { public: int nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_000022bb();
extern void j_0001b185();
extern void j_0002ae23();
extern void j_0002c471();
extern void j_0003add7();

class Rva002FE590Calls {};
template<class R> __forceinline R call0(void (*p)(), void *self) {
 typedef R (Rva002FE590Calls::*F)(); union {void (*p)(); F f;} u; u.p=p;
 return (((Rva002FE590Calls*)self)->*u.f)();
}
template<class R,class A> __forceinline R call1(void (*p)(), void *self,A a) {
 typedef R (Rva002FE590Calls::*F)(A); union {void (*p)(); F f;} u; u.p=p;
 return (((Rva002FE590Calls*)self)->*u.f)(a);
}
struct Rva002FE590Player {char pad00[0x295]; bool flag295;};
class Object {public: char pad00[0x38]; Coord3D m_position;};
class ScriptEngine { public:
 virtual void slot00()=0; virtual void slot01()=0; virtual void slot02()=0;
 virtual void slot03()=0; virtual void slot04()=0; virtual void slot05()=0;
 virtual void slot06()=0; virtual void slot07()=0; virtual void slot08()=0;
 virtual void slot09()=0; virtual void slot10()=0; virtual void slot11()=0;
 virtual void slot12()=0; virtual void slot13()=0; virtual void slot14()=0;
 virtual void slot15()=0; virtual void slot16()=0; virtual void slot17()=0;
 virtual void slot18()=0; virtual Rva002FE590Player *getPlayer()=0; virtual void slot20()=0;
 virtual void slot21()=0; virtual void slot22()=0; virtual void slot23()=0;
 virtual void slot24()=0; virtual void slot25()=0;
 virtual Object *getUnitNamed(const AsciiString&)=0; virtual void slot27()=0; virtual void slot28()=0; virtual void setName(Object*,const AsciiString&)=0;
};

extern void j_00020824(); extern void j_00028560(); extern void j_00009453(); extern void j_00019074();
extern void j_0002fb80(); extern void j_00017a12(); extern void j_00015d7a(); extern void j_00026deb();
extern void j_0002d015(); extern void j_0000983b(); extern void j_0000c752(); extern void j_0003d663();
extern void Rva009EBAC0(int);
// TU-local view of the 0x012EF1D8 template singleton; the global takes the
// canonical spelling, defined once in Common/Thing/ThingFactory.cpp.
class ThingFactory; extern ThingFactory *TheThingFactory;
struct Rva002FE590Globals {char pad00[0x11fc]; bool flag11fc;};
// GlobalData.cpp owns the 0x012ED5C8 pointer (data_rows.csv); TheGlobalData is its const view.
class GlobalData; extern GlobalData *TheWritableGlobalData;
#define TheGlobalData (reinterpret_cast<const Rva002FE590Globals *>(TheWritableGlobalData))
struct Rva002FE590Parameter {char pad00[8]; int value08;};
struct Rva002FE590List { char storage[20]; Rva002FE590List(){call0<void>(j_0002fb80,this);} ~Rva002FE590List(){call0<void>(j_00015d7a,this);} };
template<class R,class A,class B> __forceinline R call2(void (*p)(), void *self,A a,B b) {
 typedef R (Rva002FE590Calls::*F)(A,B); union {void (*p)(); F f;} u;u.p=p;
 return (((Rva002FE590Calls*)self)->*u.f)(a,b);
}
template<class R,class A,class B,class C> __forceinline R call3(void (*p)(), void *self,A a,B b,C c) {
 typedef R (Rva002FE590Calls::*F)(A,B,C); union {void (*p)(); F f;} u;u.p=p;
 return (((Rva002FE590Calls*)self)->*u.f)(a,b,c);
}
extern ScriptEngine *TheScriptEngine;
class Rva002FE590ScriptActions {public: void apply(const AsciiString&,Rva002FE590Parameter*,const AsciiString&,const AsciiString&,const AsciiString&);};
void Rva002FE590ScriptActions::apply(const AsciiString &type,Rva002FE590Parameter *option,const AsciiString &slot,const AsciiString &unitName,const AsciiString &newName) {
 Object *unit=TheScriptEngine->getUnitNamed(unitName); if(!unit)return;
 Rva002FE590Player *player=call0<Rva002FE590Player*>(j_00020824,unit);
 if(!player || !player->flag295 || player!=TheScriptEngine->getPlayer())return;
 void *thing=call1<void*>(j_00028560,TheThingFactory,&type); if(!thing)return;
 static int key=call1<int>(j_0003add7,TheNameKeyGenerator,(const char*)"CastleBehavior");
 void *castle=call1<void*>(j_0002ae23,unit,key); if(!castle)return;
 if(!call1<bool>(j_00009453,castle,thing))return;
 if(!call1<bool>(j_00019074,player,thing))return;
 if(!TheGlobalData->flag11fc) {
  bool flag=false; Rva002FE590List list;
  call2<void>(j_00017a12,thing,&list,&flag); Rva009EBAC0((int)&list);
 }
 Object *site=call1<Object*>(j_00026deb,castle,&slot);
 Object *built;
 if(site) {
  Coord3D position; position.x=site->m_position.x;position.y=site->m_position.y;position.z=site->m_position.z;
  built=call3<Object*>(j_0002d015,castle,thing,&position,option->value08);
 } else built=call3<Object*>(j_0000983b,castle,thing,-2,0);
 if(built && !call0<bool>(j_0000c752,(void*)&newName)) {
  call2<void>(j_0003d663,TheScriptEngine,&newName,built);
  TheScriptEngine->setName(built,newName);
 }
}
