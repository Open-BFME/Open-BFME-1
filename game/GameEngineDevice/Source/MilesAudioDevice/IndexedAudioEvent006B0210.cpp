// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*,unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void*);
extern void j_0001815b();
extern void j_00002815();
extern void j_000337d0();
// The constructor/destructor bodies and caller stack allocation prove 0x70 bytes.
class AudioEventRTS {
public:
    AudioEventRTS(const AsciiString&,int);
    ~AudioEventRTS();
    void *vptr_00;
    char storage_04[8]; int handle_0c; char storage_10[4]; AsciiString eventName_14; char storage_18[0x58];
    int handle() const { return handle_0c; }
    const AsciiString &name() const { return eventName_14; }
};
class Guard006B0210 {
    void *handle; char owned;
public:
    Guard006B0210(void *&h) { owned=0; handle=h; if(WaitForSingleObject(h,~0u)!=0x102) owned=1; }
    ~Guard006B0210() { if(owned) { ReleaseMutex(handle); owned=0; } }
};
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
class Counted006B0210 { public: virtual ~Counted006B0210(); long count; };
// Retail EH state 2 destroys this zero-initialized holder through 0x46F6 -> 0x696870.
class NullHolder006B0210 {
    Counted006B0210 *ptr;
public:
    NullHolder006B0210():ptr(0) {}
    ~NullHolder006B0210() { if(ptr && InterlockedDecrement(&ptr->count)<=0) { if(ptr) delete ptr; } }
};
struct Payload006B0210 { char pad0[0x14]; AudioEventRTS *event; AudioEventRTS *get() { return event; } };
struct Node006B0210 { char pad0[8]; Payload006B0210 *payload; Payload006B0210 *get() { return payload; } };
struct Ref006B0210 { Node006B0210 *node; };
class IndexedAudioEvent006B0210 {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(AudioEventRTS*); virtual void slot18(); virtual void slot19(int);
    void select(int direction);
    char pad04[0x604-4]; int dword_604;
    char pad608[0x95c-0x608]; void *mutex_95c;
    char pad960[0x9d0-0x960]; Node006B0210 *node_9d0;
    char pad9d4[0xac4-0x9d4]; int indices_ac4[3];
};
void IndexedAudioEvent006B0210::select(int direction) {
    void *handle=mutex_95c;
    Guard006B0210 guard(handle);
    AsciiString name;
    NullHolder006B0210 emptyRef;
    typedef Ref006B0210 (IndexedAudioEvent006B0210::*GetSlot)(int,int);
    union { void (__cdecl *raw)(); GetSlot member; } call;
    call.raw=j_0001815b;
    int value=1;
    Ref006B0210 ref=(this->*call.member)(dword_604,indices_ac4[dword_604]);

    if(ref.node!=node_9d0) {
        name=ref.node->get()->get()->name();
        value=ref.node->get()->get()->handle();
    }
    slot19(value);
    typedef AsciiString (IndexedAudioEvent006B0210::*GetName)(void*);
    union { void (__cdecl *raw)(); GetName member; } next,prev;
    next.raw=j_00002815; prev.raw=j_000337d0;
    if(direction==0) name=(this->*next.member)(&name); else name=(this->*prev.member)(&name);
    AudioEventRTS event(name,dword_604);
    slot17(&event);
}





