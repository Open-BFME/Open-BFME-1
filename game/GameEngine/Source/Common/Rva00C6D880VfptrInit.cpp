// cl: /O2 /MD
#include <new>

class Rva00848AB0
{
public:
    Rva00848AB0() throw();
    virtual void slot();
};

extern Rva00848AB0 g_bfmeRva0130BCACStatic;
void bfmeForward_00C70C80();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6D880InitializeVfptr()
{
    new (&g_bfmeRva0130BCACStatic) Rva00848AB0;
    atexit(bfmeForward_00C70C80);
}
