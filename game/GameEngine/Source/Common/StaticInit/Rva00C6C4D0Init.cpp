// cl: /O2 /MD
class MutexClass
{
public:
    MutexClass(const char *name = 0);
    ~MutexClass();	// WWLib mutex.cpp; retail's atexit thunk calls it (0x009DB350)
    void *m_handle;
    unsigned m_locked;
};

MutexClass g_w3dMouseThreadRunLock(0);
