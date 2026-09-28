// cl: /O2 /MD
class Vector3 { public: float x, y, z; };
struct ShadowPool
{
    char m_prefix[4];
    Vector3 *m_buffer;
    int m_available;
};
extern ShadowPool g_rva01306F54Object;
extern void j_0002a40a();
void bfmeForward_00C70B10();
struct Rva00C6C600Caller
{
    Rva00C6C600Caller()
    {
        typedef void (ShadowPool::*Member)(int, const Vector3 *);
        union { void (*function)(); Member method; } call;
        call.function = j_0002a40a;
        (g_rva01306F54Object.*call.method)(0, 0);
        atexit(bfmeForward_00C70B10);
    }
};
struct Rva00C6C600Global
{
    Rva00C6C600Caller m_caller;
    unsigned char m_pad[0xB];
};
Rva00C6C600Global g_rva01306F54Global;
