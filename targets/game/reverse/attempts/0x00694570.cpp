// ?run@Rva00694570@@QAEKXZ
// partial score=0.9873 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc
// stlport
#include <list>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

class Gen0002857E {
public:
    char m_beforeCount[0x34];
    int m_count;
};
class Gen0002857EOwner {
public:
    void Rva00693B00(Gen0002857E *value);
};
class Rva00691140Handle {
public:
    Rva00691140Handle &operator=(const Rva00691140Handle &other);
    Gen0002857E *m_target;
};
class Rva006910F0Handle {
public:
    Rva006910F0Handle();
    Rva006910F0Handle(Gen0002857E *target);
    ~Rva006910F0Handle();
    Gen0002857E *m_target;
};
class Rva006915E0 {
public:
    Rva006915E0() : m_live(false) {}
    unsigned long acquire(void *mutex) {
        m_object = mutex;
        unsigned long status = WaitForSingleObject(mutex, 500);
        if (status != 0x102)
            m_live = true;
        return status;
    }
    ~Rva006915E0() { release(); }
    void release() {
        if (m_live) {
            ReleaseMutex(m_object);
            m_live = false;
        }
    }
    bool isHeld() const { return m_live; }
    void *m_object;
    bool m_live;
};
class Rva00694570 {
public:
    unsigned long run();
    void rva00694230(Gen0002857E *value);
    char m_beforeRequests[0x14];
    _STL::list<Gen0002857E *> m_requests[3];
    char m_beforeStop[0x24];
    bool m_stop;
    void *m_context;
};

// ?run@Rva00694570@@QAEKXZ
unsigned long Rva00694570::run()
{
    while (!m_stop) {
        Gen0002857E *selected = 0;
        Rva006910F0Handle handle;
        {
            Rva006915E0 lock;
            if (lock.acquire(m_context) != 0x102) {
                for (int priority = 2; !selected && priority >= 0; --priority) {
                    if (!m_requests[priority].empty()) {
                        selected = m_requests[priority].front();
                        if (!selected->m_count)
                            reinterpret_cast<Gen0002857EOwner *>(this)->Rva00693B00(selected);
                        *reinterpret_cast<Rva00691140Handle *>(&handle) = reinterpret_cast<const Rva00691140Handle &>(Rva006910F0Handle(selected));
                        m_requests[priority].pop_front();
                    }
                }
            }
        }
        if (selected)
            rva00694230(selected);
        Sleep(1);
    }
    return 0;
}
