// Retail 0x00290990 target eligibility callback. Owning filter identity unproved.
// Object/Thing ABI offsets witnessed in retail; unknown members remain address-derived.
struct Coord3D { float x,y,z; };
class Overridable { public: const Overridable* getFinalOverride() const; };
enum KindOfType { K2=2,K47=47,K53=53,K108=108 };
enum Relationship { ENEMY=0 };
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS Relationship getRelationship(const Object*) const; bool query(Object*,int);
#include "../object.h"
class BfmeHolderNS { public: int bfmeQueryNS(); };
class BfmeRvaA760Object;
class BfmeRvaA760ProbeInterface { public: bool accepts(BfmeRvaA760Object*,int); };
class Rva0037C310Owner { public: bool Rva0037C310(int,int,Object*); };
class Pathfinder { public: bool bfmeGroundCellThreshold(const Coord3D*,bool); bool worldLineNoHit(const Coord3D*,const Coord3D*); };
struct PathSystem00290990 { char pad00[12]; Pathfinder* at0c; Pathfinder* getPathfinder() { return at0c; } };
extern PathSystem00290990* g_path00290990;
struct Config00290990 { char pad00[0x10]; BfmeRvaA760ProbeInterface at10; };
struct Collection00290990 { char pad00[4]; Config00290990* at04; char pad08[0x78]; Rva0037C310Owner** at80; Rva0037C310Owner** at84; };
class TargetEligibility00290990 {
public: bool accepts(Object* target);
 char pad00[8]; Collection00290990* at08; Object* at0c; Object* at10; int at14,at18; Object* at1c; bool at20;
};
bool TargetEligibility00290990::accepts(Object* target) {
 Object* source=at0c;
 if(!source) return false;
 if(at1c) {
  void* container=*(void**)((char*)at1c+0x214);
  if(container && container==*(void**)((char*)target+0x214)) return true;
 }
 const char* templ=*(char**)((char*)target+4);
 if(templ && *(Overridable**)(templ+4)) templ=(const char*)(*(Overridable**)(templ+4))->getFinalOverride();
 if((*(unsigned char*)(templ+0xc8)&0x80)!=0) return false;
 if(target->isKindOf(K108) || target->isKindOf(K53) || target->isKindOf(K2) || target->isKindOf(K47)) return false;
 if(source->getRelationship(target)!=ENEMY) return false;
 if(*(unsigned char*)((char*)target+0x344)&1) return false;
 if(!target->query(at10,0)) return false;
 at20=true;
 Config00290990* config=at08->at04;
 if(config->at10.accepts((BfmeRvaA760Object*)target,0)) return false;
 const Coord3D* position=(const Coord3D*)((char*)target+0x38);
 if(g_path00290990->at0c->bfmeGroundCellThreshold(position,false)) return false;
 Rva0037C310Owner** it=at08->at80;
 for(;it!=at08->at84;++it) {
  int kind=*(int*)(*(char**)((char*)*it+4)+4);
  if((kind==0 || kind==3) && (*it)->Rva0037C310(at14,at18,target)) break;
 }
 if(it==at08->at84) return false;
 if(!g_path00290990->getPathfinder()->bfmeGroundCellThreshold((const Coord3D*)((char*)at0c+0x38),false) && ((BfmeHolderNS*)target)->bfmeQueryNS()==1 && !g_path00290990->getPathfinder()->worldLineNoHit((const Coord3D*)((char*)at0c+0x38),position)) return false;
 at1c=target;
 return true;
}


