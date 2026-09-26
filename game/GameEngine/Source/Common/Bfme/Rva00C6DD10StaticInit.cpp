// cl: /O2 /MD
// Two static manager instances share the matched Rva00906340::init body.
class Rva00906340
{
public:
    Rva00906340 *init();
};

extern Rva00906340 g_bfmeRva01340C50Static;
extern Rva00906340 g_bfmeRva01340EC0Static;
void bfmeForward_00C70FD0();
void bfmeForward_00C71000();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DD10Initialize()
{
    g_bfmeRva01340C50Static.init();
    atexit(bfmeForward_00C70FD0);
}

void bfmeRva00C6DD60Initialize()
{
    g_bfmeRva01340EC0Static.init();
    atexit(bfmeForward_00C71000);
}
