// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*,unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void*);
extern void j_00041006();
extern void j_00029695();
extern void j_00023f79();
extern void j_00024e97();
struct Info006AD790 { char pad[0x84]; int dword_84; };
class AudioEventRTS { public:
    unsigned int getSoundClass() const;
    void *vptr; int dword_4; Info006AD790 *info_8; unsigned handle_c;
};
class Rva006A1790EventRef { public:
    // 0x00691200: the counted-handle release Rva006A3200EntryList.cpp emits.
    ~Rva006A1790EventRef();
    AudioEventRTS *ptr;
};
class Rva006A3200Owner { public: Rva006A1790EventRef newEventCopy(const AudioEventRTS*); };
class Open2696480Handle { public: Open2696480Handle &assign(const Open2696480Handle&); AudioEventRTS *ptr; };
class Rva006AD590Owner { public: void bfmeAdjustPriorityAndVolume(AudioEventRTS*); };
class Guard006AD790 { void *handle; char owned; public:
    Guard006AD790(void *h) { owned=0; handle=h; if(WaitForSingleObject(h,~0u)!=0x102) owned=1; }
    ~Guard006AD790() { if(owned) { ReleaseMutex(handle); owned=0; } }
};
struct Request006AD790 { int kind; Open2696480Handle ref; int dword_8,dword_c; bool byte_10; };
class SubmitAudioEvent006AD790 {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(AudioEventRTS*);
    virtual void slot44(); virtual void slot45(); virtual bool slot46(unsigned);
    unsigned submit(AudioEventRTS*,int);
    char pad4[0x4c-4]; _STL::list<Request006AD790*> requests; char pad50[0x95c-0x50]; void *mutex_95c;
};
unsigned SubmitAudioEvent006AD790::submit(AudioEventRTS *event,int flag) {
    void *handle=mutex_95c;
    Guard006AD790 guard(handle);
    if(!event->info_8) { slot43(event); if(!event->info_8) return 0; }
    if(event->info_8->dword_84!=0) return 0;
    if(!slot46(event->getSoundClass())) return 1;
    Rva006A1790EventRef copy=((Rva006A3200Owner*)this)->newEventCopy(event);
    ((Rva006AD590Owner*)this)->bfmeAdjustPriorityAndVolume(copy.ptr);
    typedef bool (SubmitAudioEvent006AD790::*CanPlay)(AudioEventRTS*);
    union { void (__cdecl *raw)(); CanPlay member; } check;
    check.raw=j_00029695;
    if(!(this->*check.member)(copy.ptr)) return 3;
    typedef Request006AD790 *(SubmitAudioEvent006AD790::*NewRequest)();
    union { void (__cdecl *raw)(); NewRequest member; } allocate;
    allocate.raw=j_00023f79;
    Request006AD790 *request=(this->*allocate.member)();
    request->ref.assign(*(Open2696480Handle*)&copy);
    request->kind=3;
    request->byte_10=(flag==0);
    requests.push_back(request);
    return copy.ptr->handle_c;
}


