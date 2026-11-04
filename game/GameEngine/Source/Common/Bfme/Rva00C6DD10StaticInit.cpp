// cl: /O2 /MD
// Two static manager instances share the matched Rva00906340::init body.
class Rva00906340
{
public:
    Rva00906340 *init();
};

// Retire ?g_bfmeRva01340C50Static@@3VRva00906340@@A: 0x01340C50 is recorded (DIR32) as
// ?TheBfmeObject_00C70FD0@@3VGen_00C70FD0Target@@A.
extern "C" Rva00906340 __identifier("?TheBfmeObject_00C70FD0@@3VGen_00C70FD0Target@@A");
extern Rva00906340 g_bfmeRva01340EC0Static;
void bfmeForward_00C70FD0();
void bfmeForward_00C71000();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DD10Initialize()
{
    __identifier("?TheBfmeObject_00C70FD0@@3VGen_00C70FD0Target@@A").init();
    atexit(bfmeForward_00C70FD0);
}

void bfmeRva00C6DD60Initialize()
{
    g_bfmeRva01340EC0Static.init();
    atexit(bfmeForward_00C71000);
}
