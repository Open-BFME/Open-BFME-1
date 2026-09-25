// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// 0x0041ABE0 and private singleton helper 0x00415C20.
// The helper returns its four-byte owning reference through EDI. Keeping it
// visible with its caller lets VC7.1 select this private ABI without assembly.
// Retail allocates 0xA4 bytes and calls ILT 0x000430CC -> 0x000B5450:
// base construction, vtable 0x010827DC, two zero fields, argument at +0xA0.
// Owner slots +0x144/+0x148 supply handles at +0x10 to audio slot +0x4C.
// Semantic owner/resource identities remain unclaimed.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

// Identical refcount and deletion contract to Rva000B5FD0ThingRefAssign.cpp.
class RefCountedThing {
public:
 virtual ~RefCountedThing();
 void Add_Ref() { InterlockedIncrement(&m_refCount); }
 void Release_Ref() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
 long m_refCount;
};
class Rva000B5FD0Ref {
public:
 Rva000B5FD0Ref() : m_ptr(0) {}
 Rva000B5FD0Ref(const Rva000B5FD0Ref &other) : m_ptr(other.m_ptr) {
  if (m_ptr) m_ptr->Add_Ref();
 }
 ~Rva000B5FD0Ref() { if (m_ptr) m_ptr->Release_Ref(); }
 void assign(RefCountedThing *p);
 Rva000B5FD0Ref &operator=(const Rva000B5FD0Ref &other) {
  if (this != &other) {
   if (other.m_ptr) other.m_ptr->Add_Ref();
   if (m_ptr) m_ptr->Release_Ref();
   m_ptr = other.m_ptr;
  }
  return *this;
 }
 void clear() { if (m_ptr) { m_ptr->Release_Ref(); m_ptr = 0; } }
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
struct Rva005A00B0AudioClient {
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual void slot3C(); virtual void slot40(); virtual void slot44();
 virtual void slot48(); virtual void slot4C(void *);
};
extern Rva005A00B0AudioClient *TheAudioClientUpdate;
struct Rva0041ABE0Slot { char m_beforeHandle[0x10]; void *m_handle; };
class Rva0041ABE0Owner {
public:
 void rva0041abe0();
 char m_beforeRef[0x10C];
 Rva000B5FD0Ref m_ref;
 char m_beforeSlots[0x144 - 0x110];
 Rva0041ABE0Slot *m_slot144;
 Rva0041ABE0Slot *m_slot148;
};
void Rva0041ABE0Owner::rva0041abe0()
{
 if (m_slot144) { void *handle = m_slot144->m_handle; TheAudioClientUpdate->slot4C(handle); }
 if (m_slot148) { void *handle = m_slot148->m_handle; TheAudioClientUpdate->slot4C(handle); }
 m_ref.clear();
 m_ref = Rva00415C20();
}
