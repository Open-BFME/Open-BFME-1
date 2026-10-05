// cl: /O2 /MD
class MutexClass
{
public:
    MutexClass(const char *name = 0);
    ~MutexClass() {}
    void *m_handle;
    unsigned m_locked;
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());
MutexClass g_w3dMouseThreadRunLock(0);
