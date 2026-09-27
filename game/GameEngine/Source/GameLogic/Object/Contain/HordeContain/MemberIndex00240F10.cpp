// cl: /DNDEBUG /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include "../../object.h"
#include "ascii_string.h"
extern void j_00028560(); extern void j_000022bb(); extern void j_0003e80b();
extern void j_0001f91f(); extern void j_000499f9();
class Route00240F10 {};

struct TemplateView00240F10 {
 void *at000; TemplateView00240F10 *at004;
 __forceinline TemplateView00240F10 *finalOverride() {
  if(at004) {
   typedef TemplateView00240F10 *(Route00240F10::*Call)();
   union { void (*fn)(); Call call; } route={j_000022bb};
   return (((Route00240F10*)at004)->*route.call)();
  }
  return this;
 }
};
__forceinline int objectID00240F10(Object *obj) { return obj->m_id; }
__forceinline TemplateView00240F10 *objectTemplate00240F10(Object *obj) {
 if(!obj->m_template) return 0;
 return ((TemplateView00240F10*)obj->m_template)->finalOverride();
}
struct Factory00240F10 {};
extern Factory00240F10 *g00240F10Va012EF1D8;
template<int N> class Slots00240F10 : public Slots00240F10<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots00240F10<0> {};
class Primary00240F10 : public Slots00240F10<30> { public: virtual void slot078(int)=0; };
struct Entry00240F10 { void *at000; AsciiString at004; };
struct Data00240F10 { char pad[0x224]; Entry00240F10 **at224, **at228; };
struct Slot00240F10 { void *at000; char pad[12]; };
struct InsertResult00240F10 { void *iterator; bool inserted; };
class MemberIndex00240F10 {
public:
 void run(Object *member);
 char at000[0x30]; char at030[12]; char at03c[12];
 Slot00240F10 *at048, *at04c, *at050;
 _STL::list<int> at054;
 char at058;
};
// Reconstructed from the banked 0x00240F10 attempt; retail loops over all free indices.
void MemberIndex00240F10::run(Object *member) {
 if(!at058) ((Primary00240F10*)((char*)this-0xe4))->slot078(1);
 _STL::list<int>::iterator node=at054.begin();
 for(;node!=at054.end();++node) {
  int index=*node;
  void *key=at048[index].at000;
  Data00240F10 *data=*(Data00240F10**)((char*)this-0xe0);
  Entry00240F10 **entry=data->at224;
  for(;entry!=data->at228;++entry) {
   Entry00240F10 *current=*entry;
   if(key==current->at000) {
    typedef TemplateView00240F10 *(Route00240F10::*Find)(const AsciiString&);
    union { void (*fn)(); Find call; } find={j_00028560};
    TemplateView00240F10 *wanted=(((Route00240F10*)g00240F10Va012EF1D8)->*find.call)(current->at004);
    TemplateView00240F10 *actual=objectTemplate00240F10(member);
    typedef bool (Route00240F10::*Equal)(TemplateView00240F10*);
    union { void (*fn)(); Equal call; } equal={j_0003e80b};
    if(!(((Route00240F10*)actual)->*equal.call)(wanted)) break;
    
    typedef int *(Route00240F10::*Lookup)(const int&);
    union { void (*fn)(); Lookup call; } lookup={j_0001f91f};
    *(((Route00240F10*)at03c)->*lookup.call)(objectID00240F10(member))=index;
    at054.erase(node);
    typedef InsertResult00240F10 (Route00240F10::*Insert)(const int&);
    union { void (*fn)(); Insert call; } insert={j_000499f9};
    
    (((Route00240F10*)at030)->*insert.call)(objectID00240F10(member));
    return;
   }
  }
 }
}
