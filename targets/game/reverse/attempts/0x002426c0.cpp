// ?d_002426c0@@YAXXZ
// partial score=0.9950819672131147 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <set>
#include <hash_map>
#include <vector>
#include <bitset>
#include "object.h"
#include "ascii_string.h"
class UpgradeTemplate;
extern void j_00027174(); extern void j_00019579(); extern void j_000077b6(); extern void j_0001a97e();
class Route002426C0 {};
extern Route002426C0 *g002426C0Va012EF188;
typedef _STL::hash_map<unsigned,Object*,_STL::hash<unsigned>,_STL::equal_to<unsigned> > Hash002426C0;
struct Logic002426C0 {
 char pad[0xb0]; Hash002426C0 at0b0;
 __forceinline Object *find(unsigned id) {
  if(!id) return 0;
  Hash002426C0::iterator it=at0b0.find(id);
  if(it==at0b0.end()) return 0;
  return it->second;
 }
};
extern Logic002426C0 *g002426C0Va012F0898;
struct Bits002426C0 { _STL::bitset<192> bits; bool test(int i) const { return bits._Unchecked_test(i); } };
class MemberUpgrades002426C0 {
public:
 char pad[0x30]; _STL::set<unsigned> at030;
 void run(const Bits002426C0 &bits,const AsciiString *name);
 _STL::list<Object*>& members() { return *(_STL::list<Object*>*)((char*)this-0xac); }
 __forceinline bool matches(Object *obj,const AsciiString &name) {
  typedef bool (Route002426C0::*Match)(Object*,const AsciiString&);
  union {void(*fn)();Match call;} match={j_00019579};
  return (((Route002426C0*)((char*)this-0xe4))->*match.call)(obj,name);
 }
};
__forceinline void apply002426C0(Object *obj,const _STL::vector<const UpgradeTemplate*> &upgrades) {
 unsigned count=upgrades.size();
 for(unsigned i=0;i<count;++i) {
  const UpgradeTemplate *upgrade=upgrades[i];
  typedef bool (Route002426C0::*Affected)(const UpgradeTemplate*);
  union {void(*fn)();Affected call;} affected={j_000077b6};
  if((((Route002426C0*)obj)->*affected.call)(upgrade)) {
   typedef void (Route002426C0::*Give)(const UpgradeTemplate*);
   union {void(*fn)();Give call;} give={j_0001a97e};
   (((Route002426C0*)obj)->*give.call)(upgrade);
  }
 }
}
void MemberUpgrades002426C0::run(const Bits002426C0 &bits,const AsciiString *name) {
 _STL::list<Object*>::iterator it=members().begin();
 _STL::vector<const UpgradeTemplate*> upgrades;
 for(int i=0;i<192;++i) {
  if(bits.test(i)) {
   typedef const UpgradeTemplate *(Route002426C0::*Lookup)(int);
   union {void(*fn)();Lookup call;} lookup={j_00027174};
   const UpgradeTemplate *upgrade=(g002426C0Va012EF188->*lookup.call)(i);
   upgrades.push_back(upgrade);
  }
 }
 while(it!=members().end()) {
  Object *obj=*it;
  if(name && !matches(obj,*name)) {++it; continue;}
  apply002426C0(obj,upgrades);
  ++it;
 }
 for(_STL::set<unsigned>::iterator id=at030.begin();id!=at030.end();++id) {
  Object *obj=g002426C0Va012F0898->find(*id);
  if(name && !matches(obj,*name)) continue;
  apply002426C0(obj,upgrades);
 }
}
