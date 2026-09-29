// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
// Retail RVA 0x007764E0, 1104 bytes. Shared FXEvent parser, preserving
// bfmeTailCHG: both matched parseFXEvent (00776A90) and bfmeGoCHG (00776A50)
// already call this name via ILT 0001F596. The record base constructor is the
// independently landed Rva00761E10; derived records add a raw FXList pointer
// or an owning clone handle, both at +10. The handle uses the witnessed
// secondary ref-counted subobject at +24 with its count at +28.
// The clone and nugget extractor keep their address tokens; their ABI and
// pin evidence is in targets/game/reverse/identity_evidence/007764e0.md.
// The nextToken local separator is significant to MSVC's scratch allocation.
// Separate zero stores preserve the record constructor's field order.
#include "string_base.h"
#include "ascii_string.h"
#include "Common/INI/INI.h"
#include <string.h>
#pragma intrinsic(strcmp,strcpy,strlen)
class FXList;
class FXListStore { public: const FXList* findFXList(const char*) const; };
extern FXListStore* TheFXListStore;
class Rva00761E10 {
public:
 Rva00761E10();
 int m_first,m_state,m_third;
 AsciiString m_name;
};
struct FxRefCount0042CDF0 {
 virtual ~FxRefCount0042CDF0();
 int count;
 void add() { ++count; }
 void release() { if(--count<=0) delete this; }
};
struct FxShared0042CDF0 { char at00[0x24]; FxRefCount0042CDF0 at24; };
class FxHandle0042CDF0 {
public:
 FxShared0042CDF0* pointer;
 FxHandle0042CDF0():pointer(0) {}
 FxHandle0042CDF0(const FxHandle0042CDF0& v):pointer(v.pointer) { if(pointer)pointer->at24.add(); }
 ~FxHandle0042CDF0() { if(pointer)pointer->at24.release(); }
 FxHandle0042CDF0& operator=(const FxHandle0042CDF0& v) {
  if(this!=&v) { if(v.pointer)v.pointer->at24.add(); if(pointer)pointer->at24.release(); pointer=v.pointer; } return *this;
 }
};
class FxClone0042CDF0 { public: FxHandle0042CDF0 clone(const char*); };
namespace _STL {
struct Rva007742A0Element: public Rva00761E10 { const FXList* fx; };
struct Rva00774410Element: public Rva00761E10 { FxHandle0042CDF0 fx; };
template<class T> void __cdecl _Construct(T*,const T&);
}
struct Rva0076CEE0Element {
 AsciiString at00;
 bool at04;
 int at08,at0c,at10,at14,at18,at1c;
 bool at20;
 Rva0076CEE0Element() { at04=false; at08=0; at0c=0; at10=0; at14=0; at18=0; at1c=0; at20=false; }
};
namespace _STL {
template<class T,class U> void __cdecl _Construct(T*,const U&);
inline void _Construct(Rva0076CEE0Element* destination,const Rva0076CEE0Element& value) {
 _Construct<Rva0076CEE0Element,Rva0076CEE0Element>(destination,value);
}
}
#include <vector>
#include <list>
struct FxNugget007764E0 { int at00; int at04; };
void __cdecl extractNugget007656B0(const FxNugget007764E0*,Rva0076CEE0Element*);
struct FxNode007764E0 { FxNode007764E0* next; FxNode007764E0* prev; FxNugget007764E0* value; };
struct Rva0042D170Member04 {
 FxNode007764E0* head;
 Rva0042D170Member04(const Rva0042D170Member04&);
 ~Rva0042D170Member04() {
  FxNode007764E0* node=head->next;
  while(node!=head) { FxNode007764E0* old=node; node=node->next; _STL::allocator<FxNode007764E0>().deallocate(old,1); }
  head->next=head;head->prev=head;
  _STL::allocator<FxNode007764E0>().deallocate(head,1);
 }
};
static const char* nextToken(INI* ini) { const char* seps=*(const char**)((char*)ini+0x41c); return ini->getNextTokenOrNull(seps); }
void bfmeTailCHG(void* one,void* two,void* three,void* four) {
 INI* ini=(INI*)one;
 _STL::Rva007742A0Element event;
 char fxName[64];
 fxName[0]=0;
 const char* token=nextToken(ini);
 while(token) {
  if(strcmp(token,"Frame")==0) { token=nextToken(ini); if(token)event.m_state=INI::scanInt(token); }
  else if(strcmp(token,"FrameStep")==0) { token=nextToken(ini); if(token)event.m_first=INI::scanInt(token); }
  else if(strcmp(token,"FrameStop")==0) { token=nextToken(ini); if(token)event.m_third=INI::scanInt(token); }
  else if(strcmp(token,"Name")==0) { token=nextToken(ini); strcpy(fxName,token); if(token)event.fx=TheFXListStore->findFXList(token); }
  else if(strcmp(token,"Bone")==0) { token=nextToken(ini); event.m_name.StringBase<char>::set(token,token?strlen(token):0); }
  token=nextToken(ini);
 }
 if(*((const char*)event.fx+8)) {
  _STL::Rva00774410Element shared;
  shared.m_state=event.m_state; shared.m_name=event.m_name; shared.m_first=event.m_first; shared.m_third=event.m_third;
  shared.fx=((FxClone0042CDF0*)TheFXListStore)->clone(fxName);
  Rva0042D170Member04 list(*(Rva0042D170Member04*)((char*)shared.fx.pointer+4));
  for(FxNode007764E0* it=list.head->next;it!=list.head;it=it->next) {
   if(it->value->at04==9) {
    Rva0076CEE0Element record;
    extractNugget007656B0(it->value,&record);
    ((_STL::list<Rva0076CEE0Element>*)four)->push_back(record);
   }
  }
  ((_STL::vector<_STL::Rva00774410Element>*)three)->push_back(shared);
 } else {
  ((_STL::vector<_STL::Rva007742A0Element>*)two)->push_back(event);
 }
}
