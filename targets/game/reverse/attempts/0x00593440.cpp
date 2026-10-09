// ?rva00593440@@YA?AURva00593440Record@@PAVObject@@@Z
// partial score=0.527 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/GameEngine/Source
#include "GameLogic/Object/object.h"
class NameKeyGenerator; class GameLogic; class ExperienceLevelSystem;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
extern void j_0003add7(); extern void j_0002ae23(); extern void j_0002bf85(); extern void j_000022bb();
extern void j_000012a8(); extern void j_0000bc21(); extern void j_0000dfc1(); extern void j_0000edc7();
extern void j_0001e64b(); extern void j_00031471(); extern void j_00041295();
class Rva00593440Calls {};
struct Rva0058B610Pair { void *first; void *second; Rva0058B610Pair() {} Rva0058B610Pair(const Rva0058B610Pair &o):first(o.first),second(o.second) {} };
class ExperienceLevelSystem {
public:
 void rva0037F190(Rva0058B610Pair*,Object*);
 bool rva0037E810(Rva0058B610Pair);
 int rva0037D810(Rva0058B610Pair);
 int rva0037D840(Rva0058B610Pair);
 Rva0058B610Pair rva0037F220(Rva0058B610Pair);
 bool rva00381200(Object*);
};
class Rva0058B610TrackerCalls {public: bool rva001B2030(int*);};
#define ROUTE0(tag,ret) typedef ret(Rva00593440Calls::*M##tag)(); __forceinline M##tag m##tag(){ union {void(*raw)();M##tag m;} c;c.raw=j_##tag;return c.m;}
#define ROUTE1(tag,ret,a) typedef ret(Rva00593440Calls::*M##tag)(a); __forceinline M##tag m##tag(){ union {void(*raw)();M##tag m;} c;c.raw=j_##tag;return c.m;}
#define ROUTE2(tag,ret,a,b) typedef ret(Rva00593440Calls::*M##tag)(a,b); __forceinline M##tag m##tag(){ union {void(*raw)();M##tag m;} c;c.raw=j_##tag;return c.m;}
ROUTE1(0003add7,int,const char*)
ROUTE1(0002ae23,void*,int)
ROUTE0(0002bf85,void*)
ROUTE0(000022bb,void*)
ROUTE1(000012a8,int,Rva0058B610Pair)
ROUTE1(0000bc21,int,Rva0058B610Pair)
ROUTE1(0000dfc1,bool,Rva0058B610Pair)
ROUTE2(0000edc7,void,Rva0058B610Pair*,Object*)
ROUTE1(0001e64b,bool,Object*)
ROUTE1(00031471,bool,int*)
ROUTE1(00041295,Rva0058B610Pair,Rva0058B610Pair)
#define CALL(p,tag) (((Rva00593440Calls*)(p))->*m##tag())
static bool rva0058b610(Object *object,int *rank,float *progress)
{
 Rva0058B610Pair level;
 TheExperienceLevelSystem->rva0037F190(&level,object);
 bool valid=TheExperienceLevelSystem->rva0037E810(level);
 if(!valid) return valid;
 *rank=TheExperienceLevelSystem->rva0037D810(level);
 Rva0058B610Pair next=TheExperienceLevelSystem->rva0037F220(level);
 if(TheExperienceLevelSystem->rva0037E810(next) && TheExperienceLevelSystem->rva00381200(object)) {
  int maxRank;
  if(!((Rva0058B610TrackerCalls*)object->m_experienceTracker)->rva001B2030(&maxRank) || *rank<maxRank) {
   float experience=*(float*)((char*)object->m_experienceTracker+12);
   float before=(float)TheExperienceLevelSystem->rva0037D840(level);
   float after=(float)TheExperienceLevelSystem->rva0037D840(next);
   if(before<after) {
    *progress=(experience-before)/(after-before);
    if(*progress<0.0f) *progress=0.0f;
    else if(*progress>1.0f) *progress=1.0f;
    goto done;
   }
  }
 }
 *progress=-1.0f;
done:
 return *rank>1 || *progress>=0.0f;
}
struct Rva00593440Record {
 int dword_0,dword_4; float float_8;
 Rva00593440Record() {dword_4=0;float_8=0;dword_0=0;}
};
Rva00593440Record rva00593440(Object *object)
{
 Rva00593440Record result;
 static int lifeKey=CALL(TheNameKeyGenerator,0003add7)("LifetimeUpdate");
 void *life=CALL(object,0002ae23)(lifeKey);
 unsigned start,end;
 if(life && !*(bool*)(*(char**)((char*)life+4)+0x10)) {
  start=*(const volatile unsigned*)((char*)life+0x24);end=*(const volatile unsigned*)((char*)life+0x20);
  goto lifetime;
 }
 if(object->m_status[1]&0x20000000) {
  static int defectKey=CALL(TheNameKeyGenerator,0003add7)("TemporarilyDefectUpdate");
  void *defect=CALL(object,0002ae23)(defectKey);
  if(defect) {
   end=*(const volatile unsigned*)((char*)defect+0x20);
   if(end>0) {
    start=*(const volatile unsigned*)((char*)defect+0x24);
    goto lifetime;
   }
  }
 }
 goto rank;
lifetime:
 result.dword_0=1;
 if(end>start) {
  result.float_8=float(end-*(unsigned*)((char*)TheGameLogic+0x3c))/float(end-start);
  if(result.float_8<0.0f) result.float_8=0.0f;
  else if(result.float_8>1.0f) result.float_8=1.0f;
 } else result.dword_0=2;
 goto finish;
rank:
 {
  bool alternate=false;
  void *t=CALL(object,0002bf85)();
  if(t) alternate=true;
  else {
   t=object->m_template;
   if(!t) t=0;
   else if(*(void**)((char*)t+4)) t=CALL(*(void**)((char*)t+4),000022bb)();
  }
  if(*(bool*)((char*)t+0x487) && rva0058b610(object,&result.dword_4,&result.float_8)) {
   if(alternate) result.dword_4=1;
   goto finish;
  }
 }
 result.dword_0=2;
finish:
 return result;

}
