// Retail 0x00290990 target eligibility callback. Owning filter identity unproved.
// Object/Thing ABI offsets witnessed in retail; unknown members remain address-derived.
struct Coord3D { float x,y,z; };
class Overridable { public: const Overridable* getFinalOverride() const; };
enum KindOfType { K2=2,K47=47,K53=53,K108=108 };
enum Relationship { ENEMY=0 };
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS Relationship getRelationship(const Object*) const; bool query(Object*,int);
#include "../object.h"
class BfmeHolderNS {};
class BfmeRvaA760Object;
class BfmeRvaA760ProbeInterface {};
class Rva0037C310Owner {};
class Pathfinder { public: bool bfmeGroundCellThreshold(const Coord3D*,bool); };
// Exact ILT identities; member views preserve ECX and3/2/0/2 stack slots.
extern "C" void __cdecl __identifier("?j_000466b4@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0001da34@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0003a391@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00030ecc@@YAXXZ")();
struct PathSystem00290990 { char pad00[12]; Pathfinder* at0c; Pathfinder* getPathfinder() { return at0c; } };
// retail's TheAI singleton; PathSystem00290990 is the view its pathfinder sits in
class AI;
extern AI *TheAI;
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
 union { void (*raw)(); bool (BfmeRvaA760ProbeInterface::*member)(BfmeRvaA760Object*,int); } filter = { __identifier("?j_0001da34@@YAXXZ") };
 if((config->at10.*filter.member)((BfmeRvaA760Object*)target,0)) return false;
 const Coord3D* position=(const Coord3D*)((char*)target+0x38);
 if(reinterpret_cast<PathSystem00290990 *>(TheAI)->at0c->bfmeGroundCellThreshold(position,false)) return false;
 Rva0037C310Owner** it=at08->at80;
 for(;it!=at08->at84;++it) {
  int kind=*(int*)(*(char**)((char*)*it+4)+4);
  union { void (*raw)(); bool (Rva0037C310Owner::*member)(int,int,Object*); } test = { __identifier("?j_000466b4@@YAXXZ") };
  if((kind==0 || kind==3) && ((*it)->*test.member)(at14,at18,target)) break;
 }
 if(it==at08->at84) return false;
 union { void (*raw)(); int (BfmeHolderNS::*member)(); } query = { __identifier("?j_0003a391@@YAXXZ") };
 union { void (*raw)(); bool (Pathfinder::*member)(const Coord3D*,const Coord3D*); } line = { __identifier("?j_00030ecc@@YAXXZ") };
 if(!reinterpret_cast<PathSystem00290990 *>(TheAI)->getPathfinder()->bfmeGroundCellThreshold((const Coord3D*)((char*)at0c+0x38),false) && (((BfmeHolderNS*)target)->*query.member)()==1 && !(reinterpret_cast<PathSystem00290990 *>(TheAI)->getPathfinder()->*line.member)((const Coord3D*)((char*)at0c+0x38),position)) return false;
 at1c=target;
 return true;
}

