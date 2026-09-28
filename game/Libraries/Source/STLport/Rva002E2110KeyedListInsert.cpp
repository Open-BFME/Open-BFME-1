// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>
#include <algorithm>
// Retail 0x002E2110 / 384B: scan a vector of two-key records; append
// the item only once to the matching record's list, or construct a new record.
// Owner identity is unproven, so the class retains the address. The existing
// vector overflow body proves Gen_t_002e20c0_p12cd; list range insertion at
// 0x002E06C0 proves its address-derived pointer payload type.
// Native copy-constructor visibility is required: an external declaration
// forces an extra sentinel spill and changes the EH state. The emitted list
// copy constructor independently matches 0x002E0F20 / 111B and calls the
// already matched Rva002E06C0Target list range-insertion specialization.
// The !found guard must precede the end comparison. Keep a pointer to the
// last record (not a cached list reference), preserving the sentinel reload.
class Rva002E06C0Target;

struct Gen_002e0dd0 { void m(void*); };
struct Gen_t_002e20c0_p12cd {
 int a,b;
 _STL::list<Rva002E06C0Target*> items;
 Gen_t_002e20c0_p12cd(int x,int y): a(x),b(y) {}
};
class Rva002E2110 { public: void add(void*,int,int); unsigned m_00; _STL::vector<Gen_t_002e20c0_p12cd> m_04; };
void Rva002E2110::add(void* item,int a,int b) {
 bool found=false;
 for(_STL::vector<Gen_t_002e20c0_p12cd>::iterator i=m_04.begin();!found&&i!=m_04.end();++i) {
  if(i->a==a && i->b==b) { ((Gen_002e0dd0*)&*i)->m(item); found=true; }
 }
 if(!found) {
  Gen_t_002e20c0_p12cd value(a,b);
  m_04.push_back(value);
  Gen_t_002e20c0_p12cd* last=&m_04.back();
  _STL::list<Rva002E06C0Target*>::iterator it=_STL::find(last->items.begin(),last->items.end(),(Rva002E06C0Target*)item);
  if(it==last->items.end()) last->items.push_back((Rva002E06C0Target*)item);
 }
}


