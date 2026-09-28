// Retail 0x002434D0..0x002435B2: complete ret-4 body.
// Address-qualified identity: member lookup and per-player vision-mask dispatch.
// ILT 0x1F91F is the thiscall map subscript at 0x226FA0;
// ILTs 0x348EC and 0x122AB route to the witnessed vision handlers.
// cl: /DNDEBUG /MD /EHsc
#include "../../object.h"
extern void j_0001f91f();
extern void j_000348ec();
extern void j_000122ab();
class Route002434D0 {};
struct Entry002434D0 { void *at000; char at004[16]; unsigned at014,at018; bool at01c; };
struct Data002434D0 { char at000[0x224]; Entry002434D0 **at224,**at228; char at22c[0x2f1-0x22c]; bool at2f1; };
struct Slot002434D0 { void *at000; char at004[12]; };
class MemberVision002434D0 {
public:
 char at000[4]; Data002434D0 *at004; Object *at008; char at00c[0x120-12]; char at120[12]; Slot002434D0 *at12c;
 void run(Object *member);
};
__forceinline int id002434D0(Object *member) {return member->m_id;}
void MemberVision002434D0::run(Object *member) {
 unsigned add, remove;
 Data002434D0 *data=at004;
 typedef int *(Route002434D0::*Lookup)(const int&);
 union { void (*fn)(); Lookup call; } lookup={j_0001f91f};
 int index=*(((Route002434D0*)at120)->*lookup.call)(id002434D0(member));
 void *key=at12c[index].at000;
 for(Entry002434D0 **it=at004->at224;it!=at004->at228;++it) {
  Entry002434D0 *entry=*it;
  if(key==entry->at000) {
   if(entry->at01c) {
    add=entry->at014;
    remove=entry->at018;
    for(int i=0;i<29;++i) {
     unsigned bit=1<<(i&31);
     typedef void (Route002434D0::*Notify)(int);
     if(add&bit) {
      union { void (*fn)(); Notify call; } notify={j_000348ec};
      (((Route002434D0*)member)->*notify.call)(i);
      if(data->at2f1) (((Route002434D0*)at008)->*notify.call)(i);
     } else if(remove&bit) {
      union { void (*fn)(); Notify call; } notify={j_000122ab};
      (((Route002434D0*)member)->*notify.call)(i);
      if(data->at2f1) (((Route002434D0*)at008)->*notify.call)(i);
     }
    }
   }
   break;
  }
 }
}
