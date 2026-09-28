// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x004B1C80, 1021 bytes. The owning BFME class is not proved.
// This address-derived view describes the observed button animation update.
// name_oracle has no witnessed layout for AnimateButtons004B1C80 or Map004B1C80.
//
// The vector at +0x0C contains windows: each is passed to winIsHidden and
// GadgetButtonGetData. +0x44 is the map also witnessed by the already-landed
// Rva004B1880MapSubscript.cpp, whose sole caller is this function.
// A new 20-byte Gen_ctor_004b02a0 creates a Flash%d action name (see its TU).
// Map values retain it through the +4 reference count and slot-0 destructor.
//
// Existing callee bindings are reused wherever their exact declarations exist.
// The two opaque map adapters below preserve independently decoded contracts:
// find: ILT 0x00046A10 -> 0x004B0530. Unsigned lower-bound/equality walk,
//       node key +0x10, hidden iterator-result pointer plus key reference, ret 8.
// erase: ILT 0x000406F6 -> 0x004B12F0. One key reference, ret 4, returns the
//        number of nodes counted between equal_range iterators before erasure.
// These views do not assert the unrelated hashtable/State mapped types used by
// older pins and generic duplicate rows at those addresses.
// Rva004B00D0Element::act is the for_each member pointer at VA 0x004261C0:
// ILT RVA 0x000261C0 -> 0x00478F30, which dispatches through virtual slot +0x14.
//
// Absolute references: timeGetTime IAT 0x01359544; Display singleton 0x012F1270
// (unsigned width/height slots +0x2C/+0x30); Shell singleton 0x012F4B58, byte +0x58.
// All numeric literals below were read as float32 values from the retail image.
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include "ascii_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Rva004B00D0Element { public: void act(); };
class BfmeB1044 { public: void bfmeTailA1044(); void bfmeTailB1044(); };
class BfmeGlobLF { public: bool bfmeTwoLF(); };
class BfmeNodeW;
class BfmeListW { public: void bfmeEraseFrom(BfmeNodeW *); };
class GameWindow;
extern void *GadgetButtonGetData(GameWindow *);
namespace _STL {
template<> __declspec(noinline) mem_fun_t<void,Rva004B00D0Element> for_each(Rva004B00D0Element **first,Rva004B00D0Element **last,mem_fun_t<void,Rva004B00D0Element> op);
}
class Gen_ctor_004b02a0Base {
public: virtual ~Gen_ctor_004b02a0Base() {}
 int field04;
 __forceinline void release() { if(--field04<=0) delete this; }
};
class Gen_ctor_004b02a0 : public Gen_ctor_004b02a0Base {
public: Gen_ctor_004b02a0(); virtual ~Gen_ctor_004b02a0();
 AsciiString field08; int field0c,field10;
};
struct Counted004B1C80 {
 Gen_ctor_004b02a0 *p;
 Counted004B1C80(Gen_ctor_004b02a0 *v):p(v) { if(p) ++p->field04; }
 ~Counted004B1C80() { if(p) p->release(); }
 __forceinline Counted004B1C80 &operator=(const Counted004B1C80 &v) {
  if(this!=&v) { if(v.p) ++v.p->field04; if(p) p->release(); p=v.p; } return *this;
 }
};
struct Node004B1C80 { int field00; Node004B1C80 *field04,*field08,*field0c; };
struct Iterator004B1C80 { Node004B1C80 *p; Iterator004B1C80(Node004B1C80 *v):p(v) {} };
// The existing 004B1B90 map specialization is already identified by its caller.
class Rva004B1880Counted
{
public:
	virtual ~Rva004B1880Counted();
	int m_refCount;
};

struct Rva004B1880Key
{
	unsigned int m_value;

	bool operator<(const Rva004B1880Key &other) const
	{
		return m_value < other.m_value;
	}
};

struct Rva004B1880Value
{
	Rva004B1880Value() { m_counted = 0; }
	Rva004B1880Value(const Rva004B1880Value &other)
		: m_counted(other.m_counted)
	{
	}
	~Rva004B1880Value()
	{
		if (m_counted != 0 && --m_counted->m_refCount <= 0)
			delete m_counted;
	}
	Rva004B1880Counted *m_counted;
};

typedef _STL::map<Rva004B1880Key, Rva004B1880Value> Rva004B1880Map;

namespace _STL {
template<> Rva004B1880Value &Rva004B1880Map::operator[](const Rva004B1880Key &key);
}
struct Map004B1C80 {
 Node004B1C80 *field00; unsigned field04;
 Iterator004B1C80 find(const Rva004B00D0Element *const &key);
 __forceinline Counted004B1C80 &at(const Rva004B00D0Element *const &key) { return (Counted004B1C80 &)((Rva004B1880Map*)this)->operator[]((const Rva004B1880Key &)key); }
 unsigned erase(const Rva004B00D0Element *const &key);
 void clear() { if(field04) { ((BfmeListW*)this)->bfmeEraseFrom((BfmeNodeW*)field00->field04); field00->field08=field00; field00->field04=0; field00->field0c=field00; field04=0; } }
};
class Display004B1C80 { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c(); virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual unsigned width(); virtual unsigned height();
};
extern Display004B1C80 *display004B1C80;
struct Shell004B1C80 { char field00[0x58]; bool field58; };
extern Shell004B1C80 *shell004B1C80;
struct ButtonData004B1C80 { char field00[0x144]; int field144; };
class AnimateButtons004B1C80 {
public:
 void update();
 int field00[2]; bool field08; char field09[3];
 _STL::vector<Rva004B00D0Element*> field0c;
 int field18,field1c,field20,field24,field28,field2c;
 unsigned field30,field34,field38;
 float field3c,field40;
 Map004B1C80 field44;
};
// Keep this float helper inline: spelling the calculation in update instead
// schedules FSIN before the numerator multiplication. Named half/angle locals
// reproduce the retail FXCH/FMUL/FXCH/FSIN order without assembly.
__forceinline float radius004B1C80(float width, unsigned count)
{
    float half = width * 0.5f;
    float angle = 3.1415927410125732f / count;
    return half * 1.175f / sin(angle);
}
void AnimateButtons004B1C80::update() {
 if(field1c!=field18) {
  field18=field1c; field20=field24=0; field28=field2c=0;
  field30=0; field34=0; field38=0; field3c=0; field40=0;
  if(field18) ((BfmeB1044*)this)->bfmeTailA1044(); else ((BfmeB1044*)this)->bfmeTailB1044();
 }
 unsigned count=field0c.size();
 if(count==0) { field44.clear(); return; }
 _STL::for_each(field0c.begin(),field0c.end(),_STL::mem_fun(&Rva004B00D0Element::act));
 unsigned now=timeGetTime();
 if(field30==0) {
  double w=field28;
  if(count>2) {
   field30=(unsigned)radius004B1C80(w,count);
   field30=(unsigned)((float)field30>(float)w*0.6666666865348816f ? (float)field30 : (float)w*0.6666666865348816f);
  } else field30=(unsigned)((float)w*0.6666666865348816f);
  field40=6.2831854820251465f/count;
  field34=now; field38=0;
  field28=(int)(display004B1C80->width()*0.046875f);
  field2c=(int)(display004B1C80->height()*0.0625f);
 }
 if(!shell004B1C80->field58) field38+=now-field34;
 field34=now;
 if(count>1) {
  if((float)field38<600.0f) field3c=field38*0.0018333334010094404f;
  else if((float)field38<650.0f) { float f=(field38-600.0f)*0.019999999552965164f; field3c=1.0f+(1.0f-f)*0.10000002384185791f; }
  else field3c=1.0f;
 } else { float f=field38*0.0018333334010094404f; field3c=1.0f<f?1.0f:f; }
 if(field3c>=1.0f) {
  for(Rva004B00D0Element **it=field0c.begin();it!=field0c.end();++it) {
   Rva004B00D0Element *window=*it;
   Rva004B00D0Element *key=window;
   if(!((BfmeGlobLF*)window)->bfmeTwoLF()) {
    ButtonData004B1C80 *data=(ButtonData004B1C80*)GadgetButtonGetData((GameWindow*)window);
    if(data && data->field144>0) {
     Node004B1C80 *end=field44.field00;
     Iterator004B1C80 found=field44.find(key);
     if(found.p==end) {
      field44.at(key)=Counted004B1C80(new Gen_ctor_004b02a0);
      field08=true;
     }
     continue;
    }
   }
   field44.erase(key);
  }
 } else field44.clear();
}
