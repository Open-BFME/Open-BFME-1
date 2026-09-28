// ?select@SelectProjectile00373090@@QAEHPAXPBMH@Z
// partial score=0.265432 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x00372E40, 280B. Identity: not a matched caller, but the string
// literal at the nameToKey call site reads "CastleMemberBehavior" (retail
// .rdata 0x01090D8C), and one callee is pinned to CastleBehavior::
// isPendingObjectUnavailable (0x00372090), matching the same
// local-static-key module lookup idiom already landed in
// CastleMemberBehaviorFind.cpp. Address-derived name kept per naming rules
// since no caller/vtable/name-key proves the enclosing function's own
// identity.

typedef bool Bool;

// -- pinned wrapper stubs; each class/method reproduces one retail REL32 pin --

class BfmeX1011;
class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011(int id);
};
extern BfmeLook1011 *TheBfmeGameLogic;

class BfmeSubBIA
{
public:
	int ask();
};

class BfmeQ1060
{
public:
	int bfmeConv1060(int name);
};
extern BfmeQ1060 *TheNameKeyGenerator;

class BfmeItemDJ;
class BfmeThingDJ
{
public:
	BfmeItemDJ *bfmeFindDJ(int key);
};

class BfmeItemE63
{
public:
	Bool checkValid();
};

class BfmeY982
{
public:
	BfmeY982 *bfmeConv982B();
};

class BfmeR1094;
class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
};

// -- real-layout views of the same retail objects, for field access / vcalls --

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xd0];
	unsigned int m_kindOf0xd8;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x30];
};

class ProjectileUpdateInterfaceView
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual Bool queryStatus();
 virtual int fireAt(Object *object,int cArg,void *posAddr,int zero,void *player,bool flag);
};

class FireShimBase
{
public:
	int fireAt(Object *object, int cArg, void *posAddr, int zero,
		void *player, int flag);
};
typedef int (FireShimBase::*FireMember)(Object *, int, void *, int, void *,
	int);


int Rva00372E40(void*,int,int,bool);
struct Range00373090 {int *begin,*end;};
class SelectProjectile00373090 {public: int select(void *arg,const float *pos,int mode);};
int SelectProjectile00373090::select(void *arg,const float *pos,int mode) {
 if(!arg) return 0;
 float best;
 switch(mode) {case 0:best=9999999.0f;break;case 1:best=0.0f;break;default:return 0;}
 int kind=*(int*)((char*)arg+0xcc);
 int id=0;
 Range00373090 *range=(Range00373090*)((char*)this+0xb8);
 if(kind & 0x80000000) range=(Range00373090*)((char*)this+0xdc);
 for(int *it=range->begin;it!=range->end;++it) {
  Object *object=(Object*)TheBfmeGameLogic->bfmeFind1011(*it);
  if(!object) continue;
  ThingTemplate *tmpl=object->m_template;
  if(tmpl && tmpl->m_nextOverride) tmpl=(ThingTemplate*)((BfmeSubBIA*)tmpl->m_nextOverride)->ask();
  if(tmpl->m_kindOf0xd8 & 0x200000) continue;
  ProjectileUpdateInterfaceView *iface=(ProjectileUpdateInterfaceView*)((BfmeY982*)object)->bfmeConv982B();
  if(!iface || iface->queryStatus()) continue;
  float x=*(float*)((char*)object+0x38)-pos[0];
  float y=*(float*)((char*)object+0x3c)-pos[1];
  float d=x*x+y*y;
  switch(mode) {
  case 0: if(best>=d) {id=*(int*)((char*)object+0x74);best=d;} break;
  case 1: if(best<d) {id=*(int*)((char*)object+0x74);best=d;} break;
  }
 }
 return Rva00372E40(*(void**)((char*)this+0xa0),id,(int)arg,false);
}
