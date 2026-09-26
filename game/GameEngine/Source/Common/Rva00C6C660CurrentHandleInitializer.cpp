// Retail 0x00C6C660 initializes the global handle at 0x01307214 and
// registers its existing destruction forwarder for process shutdown.
// The callee at 0x0044F3C0 writes the handle's null pointer; its ILT
// thunk is 0x000110D6.
class Gen_0044f3c0
{
public:
    void *m();
};

extern Gen_0044f3c0 g_bfmeCurrentCZ;
extern void j_000110d6();
extern void bfmeForward_00C70B40();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void Rva00C6C660InitializeCurrentHandle()
{
    typedef void *(Gen_0044f3c0::*Member)(void);
    union { void (*function)(void); Member method; } call;
    call.function = j_000110d6;
    (g_bfmeCurrentCZ.*call.method)();
    atexit(bfmeForward_00C70B40);
}
