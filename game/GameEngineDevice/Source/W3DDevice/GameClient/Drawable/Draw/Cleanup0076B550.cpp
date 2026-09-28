// cl: /O2 /Ob2 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
namespace _STL { template<bool Threads,int Instance> class __node_alloc { public: static void _M_deallocate(void*,unsigned int); }; }
class BfmeHandleERU;
class BfmeThingERU { public:
 char pad00[0x98]; BfmeHandleERU* m_head; BfmeHandleERU* m_tail;
 void bfmeStopERU();
};
class BfmeHandleERU { public:
 BfmeThingERU* m_bfmePtrERU; BfmeHandleERU* m_previous; BfmeHandleERU* m_next;
 ~BfmeHandleERU() {
  if(m_bfmePtrERU) {
   if(m_previous) m_previous->m_next=m_next; else m_bfmePtrERU->m_head=m_next;
   if(m_next) m_next->m_previous=m_previous; else m_bfmePtrERU->m_tail=m_previous;
   m_previous=0; m_next=0;
  }
 }
};
class BfmeMgrERU { public: BfmeHandleERU bfmeGetERU(int); };
extern BfmeMgrERU* g_bfmeMgrERU;
struct Record0076B550 { int id; int at04; AsciiString name; int at0c; bool at10; };
struct Node0076B550 { Node0076B550* next; Node0076B550* previous; Record0076B550 value; };
class Cleanup0076B550 { public:
 char pad00[0x48]; Node0076B550* node;
 void stopParticles(bool);
};
void Cleanup0076B550::stopParticles(bool preserve) {
 Node0076B550* it=node->next;
 while(it!=node) {
  bool skip=false;
  if(preserve) { Record0076B550 copy=it->value; if(copy.at0c) skip=true; }
  BfmeHandleERU handle=g_bfmeMgrERU->bfmeGetERU(it->value.id);
  if(!skip && handle.m_bfmePtrERU) {
   handle.m_bfmePtrERU->bfmeStopERU();
   Node0076B550* next=it->next;
   Node0076B550* previous=it->previous;
   previous->next=next;
   next->previous=previous;
   it->value.~Record0076B550();
   _STL::__node_alloc<false,0>::_M_deallocate(it,0x1c);
   it=next;
  } else it=it->next;
 }
}


