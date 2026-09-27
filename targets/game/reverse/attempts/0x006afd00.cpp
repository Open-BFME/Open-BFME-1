// ?d_006afd00@@YAXXZ
// partial score=0.953 date=2026-09-27
// stlport
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>
#include <deque>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern void j_0001ffc8();
struct Info006AFD00 { char pad0[0x3c]; unsigned flags_3c; };
struct Event006AFD00 { char pad0[8]; Info006AFD00 *info_8; unsigned handle_c; char pad10[0x45-0x10]; bool byte_45; };
class Playing006AFD00 { public:
 virtual ~Playing006AFD00(); long count_4; char pad8[12]; Event006AFD00 *event_14;
 void release() { if(InterlockedDecrement(&count_4)<=0) delete this; }
};
class Ref006AFD00 {
 Playing006AFD00 *ptr;
 public:
 Playing006AFD00 *get() const { return ptr; }
 Ref006AFD00():ptr(0) {}
 Ref006AFD00 &operator=(const Ref006AFD00 &r) { if(this!=&r) { if(r.ptr) InterlockedIncrement(&r.ptr->count_4); if(ptr) ptr->release(); ptr=r.ptr; } return *this; }
 Ref006AFD00(const Ref006AFD00 &r) { Playing006AFD00 *p=r.ptr; ptr=p; if(p) InterlockedIncrement(&p->count_4); }
 ~Ref006AFD00() { Playing006AFD00 *p=ptr; if(p) p->release(); }
 void clear() { Playing006AFD00 *p=ptr; if(p) { if(InterlockedDecrement(&p->count_4)<=0) delete p; ptr=0; } }
};
class BfmeHostESG { public: ~BfmeHostESG(); };
struct Request006AFD00 { int kind; Event006AFD00 *event; unsigned handle; char padc[12];
 bool matches(unsigned h) const { if(event) return event->handle_c==h; return handle==h; }
 ~Request006AFD00() { ((BfmeHostESG*)this)->~BfmeHostESG(); }
};
struct InlineEvent006AFD00 { char pad0[12]; unsigned handle_c; char pad10[0x74-0x10]; bool byte_74; char pad75[3]; };
struct Node006AFD00 { Node006AFD00 *next; Request006AFD00 *value; };
struct SelfPair006A1650 { Node006AFD00 *m_value; void *m_owner; };
class Rva006A1650Maker { public: SelfPair006A1650* make(SelfPair006A1650*,void*); };
struct Rva006A0810Node;
class Rva006A0810Table { public: void erase(Rva006A0810Node**); };
class StopAudioHandle006AFD00 { public:
 void stop(unsigned);
 char pad0[0x4c]; _STL::list<Request006AFD00*> requests_4c; char table_50[0x44];
 _STL::vector<InlineEvent006AFD00> vectors_94[3]; char padb8[0x9c8-0xb8];
 _STL::list<Ref006AFD00> sounds_9c8,sounds_9cc,streams_9d0;
 _STL::deque<Ref006AFD00> queues_9d4[3][2]; char padac4[12]; Ref006AFD00 refs_ad0[3];
};
void StopAudioHandle006AFD00::stop(unsigned handle) {
 if(handle<5) return;
 for(_STL::list<Ref006AFD00>::iterator it=streams_9d0.begin();it!=streams_9d0.end();++it) {
  const Ref006AFD00 audio=*it;
  if(!audio.get()) continue;
  if(audio.get()->event_14->handle_c==handle) {
   audio.get()->event_14->byte_45=true;
   if(!(audio.get()->event_14->info_8->flags_3c&0x10)) {
    typedef void (StopAudioHandle006AFD00::*Fn)(const Ref006AFD00&);
    union { void (__cdecl *raw)(); Fn member; } call; call.raw=j_0001ffc8; (this->*call.member)(audio);
   }
   break;
  }
 }
 for(_STL::list<Ref006AFD00>::iterator it=sounds_9c8.begin();it!=sounds_9c8.end();++it) {
  const Ref006AFD00 audio=*it; if(!audio.get()) continue;
  if(audio.get()->event_14->handle_c==handle) { audio.get()->event_14->byte_45=true; break; }
 }
 for(_STL::list<Ref006AFD00>::iterator it=sounds_9cc.begin();it!=sounds_9cc.end();++it) {
  const Ref006AFD00 audio=*it; if(!audio.get()) continue;
  if(audio.get()->event_14->handle_c==handle) { audio.get()->event_14->byte_45=true; break; }
 }
 for(int i=0;i<3;++i) {
  for(_STL::vector<InlineEvent006AFD00>::iterator it=vectors_94[i].begin();it!=vectors_94[i].end();++it)
   if(it->handle_c==handle) { it->byte_74=true; break; }
  if(refs_ad0[i].get() && refs_ad0[i].get()->event_14->handle_c==handle) refs_ad0[i].clear();
  for(int j=0;j<2;++j)
   for(_STL::deque<Ref006AFD00>::iterator it=queues_9d4[i][j].begin();it!=queues_9d4[i][j].end();++it)
    if(it->get() && it->get()->event_14->handle_c==handle) { queues_9d4[i][j].erase(it); break; }
 }
 { SelfPair006A1650 found;
 ((Rva006A1650Maker*)table_50)->make(&found,(void*)handle);
 if(found.m_value) {
  Request006AFD00 *request=found.m_value->value;
  SelfPair006A1650 copy=found;
  ((Rva006A0810Table*)table_50)->erase((Rva006A0810Node**)&copy);
  delete request;
 }
 }
 for(_STL::list<Request006AFD00*>::iterator it=requests_4c.begin();it!=requests_4c.end();) {
  Request006AFD00 *request=*it;
  if(request && request->kind==0 && request->matches(handle)) {
   delete request; it=requests_4c.erase(it);
  } else ++it;
 }
}


