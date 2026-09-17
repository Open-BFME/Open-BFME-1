// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ivendor/stlport
// stlport
// STLport 4.5.3 deque<ThingRef>::clear, RVA 0x006A4540 (185 bytes).
// Instantiate the vendored header with the recovered 4-byte ThingRef layout.
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

class RefCountedThing {
public:
    virtual ~RefCountedThing();
    void Release_Ref() {
        if (InterlockedDecrement(&m_refCount) <= 0)
            delete this;
    }
    long m_refCount;
};

class ThingRef {
public:
    ~ThingRef() {
        if (m_ptr)
            m_ptr->Release_Ref();
    }
private:
    RefCountedThing *m_ptr;
};

#include <deque>

template void _STL::deque<ThingRef, _STL::allocator<ThingRef> >::clear();
