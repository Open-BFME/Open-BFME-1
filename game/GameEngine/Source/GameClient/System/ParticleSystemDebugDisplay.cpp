// cl: /O2 /Ob2 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ParticleSystemDebugDisplay, RVA 0x005CA370. Retail ends at +0x544, not +0x541.
// Identity: ZH ParticleSys.cpp's callback and the retail statistics strings agree.
// BFME adds the timing flag at GlobalData +0xA91, total cost at manager +0x94,
// and a third map accumulating ParticleSystem +0xB0. The manager list is +0x80.
// All offsets and virtual slots below are witnessed by this caller; unproved
// members retain their offsets rather than taking Zero Hour's layout names.
// The old 1345-byte dump stopped in `mov esp,ebp`; ret is at +0x543.
//
// Callee contracts: list copy 5C8490 takes one reference and allocates 20-byte
// nodes; clear 5C5CE0 unlinks the intrusive handles at node +8/+12/+16.
// The three make_pair bodies are 5C4350 (int), 5C4390 (unsigned), 5C43D0 (float).
// Integer/float trees use find 3405C0/5C7770, insert 33FA50/5C8B10 and
// destructors 3418C0/5C85F0. Their emitted STLport bodies match retail shape.
// _BFME_RETAIL_TREE_INSERT_LAYOUT preserves the witnessed insert variant.
#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_STATIC_LIB
#include <map>
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a,const AsciiString &b) const { return a.compare(b)<0; } }; }

class DebugDisplayInterface;
struct _iobuf;
class ParticleSystemManager;
class GlobalData;
extern ParticleSystemManager *TheParticleSystemManager;
extern GlobalData *TheWritableGlobalData;

// Address-derived views: only slots/offsets used by this retail body are asserted.
struct Rva005CA370Display {
 virtual void slot00();
 virtual void print(const char *, ...);
 virtual void slot08();
 virtual void cursor(int, int);
 virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual void slot1c(); virtual void slot20();
 virtual void margin(int);
};
struct Rva005CA370Manager {
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual int onScreen();
};
namespace FXParticleSystem { class ParticleSystemTemplate { public: AsciiString getName() const; }; }
struct Rva005CA370Particle {
 char bytes00[0xa8];
 unsigned m_particleCount; // name_oracle ParticleSystem +0xa8
 int bytesac;
 float valueb0;
 char bytesb4[0x19c-0xb4];
 FXParticleSystem::ParticleSystemTemplate *value19c;
 FXParticleSystem::ParticleSystemTemplate *getTemplate() const { return value19c; }
 unsigned getParticleCount() const { return m_particleCount; }
 float getCost() const { return valueb0; }
};
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();
inline Rva005CA370Particle *nullParticle005CFF50() { return (Rva005CA370Particle *)bfmeNullSystemZA(); }
struct Rva005CA370ListNode {
 Rva005CA370ListNode *next, *previous;
 Rva005CA370Particle *particle;
 void *handlePrevious, *handleNext;
 Rva005CA370Particle *get() const { return particle ? particle : nullParticle005CFF50(); }
};
struct Rva005CA370List {
 Rva005CA370ListNode *head;
 Rva005CA370List(const Rva005CA370List &);
 void clear005C5CE0();
 ~Rva005CA370List() { clear005C5CE0(); if(head) _STL::__node_alloc<true,0>::deallocate(head,20); }
};
static bool timing() { return *((char *)TheWritableGlobalData+0xa91)!=0; }
static float managerFloat(unsigned off) { return *(float *)((char *)TheParticleSystemManager+off); }
static int managerInt(unsigned off) { return *(int *)((char *)TheParticleSystemManager+off); }

void ParticleSystemDebugDisplay(DebugDisplayInterface *display, void *, _iobuf *) {
 Rva005CA370Display *dd=(Rva005CA370Display *)display;
 if(!dd) return;
 dd->cursor(0,0);
 dd->margin(2);
 dd->print("Total Particles: %d\n",managerInt(0x84));
 dd->print("Total Particles (On Screen): %d\n",((Rva005CA370Manager *)TheParticleSystemManager)->onScreen());
 dd->print("Total Particle\tSystems: %d\n",managerInt(0x8c));
 if(timing()) dd->print("Total Particle\tSystems Cost: %.2f msec\n",managerFloat(0x94));
 Rva005CA370List list=*(Rva005CA370List *)((char *)TheParticleSystemManager+0x80);
 _STL::map<AsciiString,int> templateMap;
 _STL::map<AsciiString,int> templateMapParticleCount;
 _STL::map<AsciiString,float> templateMapCost;
 _STL::map<AsciiString,float>::iterator costIt;
 _STL::map<AsciiString,int>::iterator mapIt;
 _STL::map<AsciiString,int>::iterator countIt;

 for(Rva005CA370ListNode *it=list.head->next;it!=list.head;it=it->next) {
  AsciiString templateName=it->get()->getTemplate()->getName();
  mapIt=templateMap.find(templateName);
  if(mapIt==templateMap.end()) {
   templateMap.insert(_STL::make_pair(templateName,1));
   templateMapParticleCount.insert(_STL::make_pair(templateName,it->get()->getParticleCount()));
   if(timing()) templateMapCost.insert(_STL::make_pair(templateName,it->get()->getCost()));
  } else {
   ++mapIt->second;
   countIt=templateMapParticleCount.find(templateName);
   if(countIt!=templateMapParticleCount.end()) countIt->second+=it->get()->getParticleCount();
   if(timing()) {
    costIt=templateMapCost.find(templateName);
    if(costIt!=templateMapCost.end()) costIt->second+=it->get()->getCost();
   }
  }
 }
 for(mapIt=templateMap.begin();mapIt!=templateMap.end();++mapIt) {
  countIt=templateMapParticleCount.find(mapIt->first);
  if(timing()) costIt=templateMapCost.find(mapIt->first);
  dd->print("  %s: %d instances",mapIt->first.str(),mapIt->second);
  if(countIt!=templateMapParticleCount.end() && mapIt->second>0) {
   // A separate compound divide preserves retail's x87/argument-stack order.
   float average=(float)countIt->second;
   average/=mapIt->second;
   dd->print("    (Avg per system %.2f) ",average);
  }
  if(timing() && costIt!=templateMapCost.end() && mapIt->second>0)
   dd->print("   (Avg cost per system %.2f msec)",costIt->second/(float)mapIt->second);
  dd->print("\n");
 }
}

