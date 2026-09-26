// cl: /O2 /MD
// Retail emitted two independent startup bodies at 0x00C6D830 and 0x00C6D850.
class Gen_0081c9c0
{
public:
    void *m(int unusedAllocator);
};

extern Gen_0081c9c0 g_bfmeRva0130B19CStatic;
void bfmeForward_00C70C70();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6D830Initialize()
{
    unsigned char allocator;
    g_bfmeRva0130B19CStatic.m((int)&allocator);
    atexit(bfmeForward_00C70C70);
}

void bfmeAssignSlotsVA();
void *bfmeTwoTB();
extern int g_bfmeCountWE;
extern void *_Bfme_classic_locale;
void rva00C70CA0Release();

void bfmeRva00C6D850InitializeLocale()
{
    bfmeAssignSlotsVA();
    _Bfme_classic_locale = bfmeTwoTB();
    ++g_bfmeCountWE;
    atexit(rva00C70CA0Release);
}
