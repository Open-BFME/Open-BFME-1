// cl: /O2 /MD
// Retail 0x00C6DB60 initializes the singleton at 0x0130C0D4 and registers its cleanup.
class BfmeThingTB
{
public:
    BfmeThingTB *bfmeGoTB();
};

extern BfmeThingTB g_bfmeRva0130C0D4Static;
void bfmeForward_00C70E50();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DB60Initialize()
{
    g_bfmeRva0130C0D4Static.bfmeGoTB();
    atexit(bfmeForward_00C70E50);
}
