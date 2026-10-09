// ?get@Rva00417430Owner@@QAE?AVRva000B5FD0Ref@@H@Z
// partial score=0.547 date=2026-10-09
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Complete selector with the matched singleton's native private return ABI.
#include "ascii_string.h"
#include <new>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

class RefCountedThing {
public:
 virtual ~RefCountedThing();
 void Add_Ref() { InterlockedIncrement(&m_refCount); }
 void Release_Ref() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
 long m_refCount;
};
struct Rva000B97D0Target { char m_unreconstructed_00[4]; long m_refCount; };
class Rva000B97D0Ptr {
public:
 Rva000B97D0Ptr(const Rva000B97D0Ptr &);
 Rva000B97D0Target *m_ptr;
};
extern void j_00036075();
class Rva000B5FD0Ref {
public:
 Rva000B5FD0Ref() : m_ptr(0) {}
 Rva000B5FD0Ref(RefCountedThing *p) : m_ptr(p) { if (p) p->Add_Ref(); }
 Rva000B5FD0Ref(const Rva000B5FD0Ref &other) : m_ptr(other.m_ptr) {
  if (m_ptr) m_ptr->Add_Ref();
 }
 __forceinline Rva000B5FD0Ref(const Rva000B97D0Ptr &other) {
  union { void (*raw)(); void *(Rva000B5FD0Ref::*copy)(const Rva000B97D0Ptr &); } target;
  target.raw = j_00036075;
  (this->*target.copy)(other);
 }
 ~Rva000B5FD0Ref() { if (m_ptr) m_ptr->Release_Ref(); }
 void assign(RefCountedThing *p);
 bool operator!=(const Rva000B5FD0Ref &other) const { return m_ptr != other.m_ptr; }
 RefCountedThing *m_ptr;
};
class Rva000B5450Thing : public RefCountedThing {
public:
 explicit Rva000B5450Thing(void *value);
 char m_rest[0xA4 - 8];
};
static __declspec(noinline) Rva000B5FD0Ref Rva00415C20()
{
 static Rva000B5FD0Ref singleton;
 if (!singleton.m_ptr) singleton.assign(new Rva000B5450Thing(0));
 return singleton;
}
template<> inline bool StringBase<char>::isEmpty() const
{
 return !m_data || m_data->length == 0;
}
class AudioEventRTS {
public:
 void *m_vtable;
 void *m_filenameToLoad;
 Rva000B97D0Ptr m_eventInfo;
 char m_beforeName[8];
 AsciiString m_eventName;
};
extern AudioEventRTS BfmeTheEmptyAudioEvent;
extern void j_0000286a();
struct Rva005A00B0AudioClient {
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual void slot3C(); virtual void slot40(); virtual void slot44();
 virtual void slot48(); virtual void slot4C(); virtual void slot50();
 virtual void slot54(); virtual void slot58(); virtual void slot5C();
 virtual void slot60(); virtual void slot64(); virtual void slot68();
 virtual void slot6C(); virtual void slot70(); virtual void slot74();
 virtual void slot78(); virtual void slot7C(); virtual void slot80();
 virtual void slot84(); virtual void slot88(); virtual void slot8C();
 virtual void slot90(); virtual void slot94(); virtual void slot98();
 virtual void slot9C(); virtual void slotA0(); virtual void slotA4();
 virtual void slotA8(); virtual void slotAC(const AudioEventRTS *) const;
};
extern Rva005A00B0AudioClient *TheAudioClientUpdate;
class Rva00417430Owner {
public:
 Rva000B5FD0Ref get(int dt);
 void *lookup(int index) const {
  union { void (*raw)(); void *(Rva00417430Owner::*member)(int) const; } target;
  target.raw = j_0000286a;
  return (this->*target.member)(index);
 }
 const AudioEventRTS *sound(int index) const {
  const AudioEventRTS *s = (const AudioEventRTS *)lookup(index);
  if (!s) s = &BfmeTheEmptyAudioEvent;
  return s;
 }
 const AudioEventRTS *pick(int dt) const {
  switch(dt) {
   case 1: return sound(0x58);
   case 2: return sound(0x59);
   case 3: return sound(0x5A);
   default: return sound(0x57);
  }
 }
 char m_beforeRef[0x10C];
 Rva000B5FD0Ref m_ref;
};
// ?get@Rva00417430Owner@@QAE?AVRva000B5FD0Ref@@H@Z
Rva000B5FD0Ref Rva00417430Owner::get(int dt)
{
 if (dt != 3 && m_ref.m_ptr) {
  if (m_ref != Rva00415C20()) return Rva000B5FD0Ref(m_ref.m_ptr);
 } else {
  const AudioEventRTS *sound = pick(dt);
  if (!sound->m_eventName.isEmpty()) {
   if (!sound->m_eventInfo.m_ptr) TheAudioClientUpdate->slotAC(sound);
   return Rva000B5FD0Ref((RefCountedThing *)sound->m_eventInfo.m_ptr);
  } else if (dt != 0 && dt != 3) {
   const AudioEventRTS *pristine = pick(0);
   if (pristine->m_eventName.isNotEmpty()) {
    if (!pristine->m_eventInfo.m_ptr) TheAudioClientUpdate->slotAC(pristine);
    return Rva000B5FD0Ref(pristine->m_eventInfo);
   }
  }
 }
 return Rva000B5FD0Ref();
}
