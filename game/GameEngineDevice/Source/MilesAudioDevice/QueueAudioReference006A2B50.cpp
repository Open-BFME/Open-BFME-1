// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A2B50 and 0x006A2E50, 296 bytes each. Both acquire the
// Miles global mutex, look up a key, retain its reference and queue it at
// +0xB04. The two bucket arrays start at +0xB0C and +0xB34 respectively.
// No source identity is established for the owner, so retain the address.
// The visible, non-inlined assign body is the existing 0x0069B800 contract;
// its visibility allows the compiler to track the local reference lifetime.
// The shared failure label preserves unlock-before-reference-destruction.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex();
extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex();
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
class RefCountedThing {
public:
    virtual ~RefCountedThing();
    void Add_Ref() { InterlockedIncrement(&m_refCount); }
    void Release_Ref()
    {
        if (InterlockedDecrement(&m_refCount) <= 0)
            delete this;
    }
    long m_refCount;
};
class Open269B800Ref {
public:
    RefCountedThing *m_ptr;
    Open269B800Ref() : m_ptr(0) {}
    Open269B800Ref(const Open269B800Ref &v) : m_ptr(v.m_ptr) { if(m_ptr) m_ptr->Add_Ref(); }
    ~Open269B800Ref() { if(m_ptr) m_ptr->Release_Ref(); }
    __declspec(noinline) void assign(RefCountedThing *p) {
        if(p!=m_ptr) {
            if (m_ptr) {
                m_ptr->Release_Ref();
                m_ptr = 0;
            }
            m_ptr=p;
            if(p) p->Add_Ref();
        }
    }
    operator RefCountedThing *() const { return m_ptr; }
};
class MilesMutex006A2B50 {
    bool m_locked;
public:
    MilesMutex006A2B50() { AIL_lock_mutex(); m_locked=true; }
    ~MilesMutex006A2B50() { if(m_locked) AIL_unlock_mutex(); }
    void unlock() { AIL_unlock_mutex(); m_locked=false; }
};
typedef _STL::hash_map<unsigned int,Open269B800Ref> AudioReferenceMap006A2B50;
class AudioReferenceQueue006A2B50 {
    char pad000[0xb04];
    _STL::list<Open269B800Ref> listB04;
    AudioReferenceMap006A2B50 mapB08;
    AudioReferenceMap006A2B50 mapB1C;
    AudioReferenceMap006A2B50 mapB30;
public:
    void queue(unsigned int key);
    void queue006A2E50(unsigned int key);
    void queue006A2CD0(unsigned int key);
};
void AudioReferenceQueue006A2B50::queue(unsigned int key) {
    MilesMutex006A2B50 guard;
    AudioReferenceMap006A2B50::iterator found=mapB08.find(key);
    Open269B800Ref value;
    if(found==mapB08.end()) goto failed;
    value.assign(found->second.m_ptr);
    if(!value) {
failed:
        guard.unlock();
        return;
    }
    listB04.push_back(value);
}

void AudioReferenceQueue006A2B50::queue006A2E50(unsigned int key) {
    MilesMutex006A2B50 guard;
    AudioReferenceMap006A2B50::iterator found=mapB30.find(key);
    Open269B800Ref value;
    if(found==mapB30.end()) goto failed;
    value.assign(found->second.m_ptr);
    if(!value) {
failed:
        guard.unlock();
        return;
    }
    listB04.push_back(value);
}

// RVA 006A2CD0: the middle map has its bucket array at +0xB20.
void AudioReferenceQueue006A2B50::queue006A2CD0(unsigned int key) {
    MilesMutex006A2B50 guard;
    AudioReferenceMap006A2B50::iterator found=mapB1C.find(key);
    Open269B800Ref value;
    if(found==mapB1C.end()) goto failed;
    value.assign(found->second.m_ptr);
    if(!value) {
failed:
        guard.unlock();
        return;
    }
    listB04.push_back(value);
}
