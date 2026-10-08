// cl: /O2 /MD
// Retail 00C6DFB0 constructs the owning texture handle at VA01346E70
// through ILT110D6 -> BfmeHandleCX ctor0044F3C0 and registers cleanup
// 00C712F0, which dispatches its destructor through ILT30652.
#include <new>
class TextureClass;
class BfmeHandleCX {
public:
    BfmeHandleCX() throw();
    ~BfmeHandleCX();
    TextureClass *rva00000000;
};
class Gen_00C712F0Target {
public:
    void *m_handle;
};
// Retail VA 0x01346E70 (zero-initialized): the 4-byte handle constructed here;
// the next recorded datum starts at 0x01346E74.
Gen_00C712F0Target TheBfmeObject_00C712F0;
void bfmeForward_00C712F0();
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void Rva00C6DFB0Initialize()
{
    new (&TheBfmeObject_00C712F0) BfmeHandleCX;
    atexit(bfmeForward_00C712F0);
}
