// cl: /Igame/Libraries/Source/WWVegas/WWLib /O2 /MD
#include "../../../../Libraries/Source/WWVegas/WWMath/vector3.h"
struct ShadowPool
{
    char m_prefix[4];
    Vector3 *m_buffer;
    int m_available;
};
extern ShadowPool ShadowPoolA;
extern void j_0002a40a();
void bfmeForward_00C70B00();
struct Rva00C6C5E0Caller
{
    Rva00C6C5E0Caller()
    {
        typedef void (ShadowPool::*Member)(int, const Vector3 *);
        union { void (*function)(); Member method; } call;
        call.function = j_0002a40a;
        (ShadowPoolA.*call.method)(0, 0);
        atexit(bfmeForward_00C70B00);
    }
};
struct Rva00C6C5E0Global
{
    Rva00C6C5E0Caller m_caller;
    unsigned char m_pad[0xB];
};
Rva00C6C5E0Global g_rva01306F3CGlobal;
