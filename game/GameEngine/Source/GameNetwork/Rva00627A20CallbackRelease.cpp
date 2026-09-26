// cl: /O2
// Disable the callback before invoking it; clear the pointer only after invocation.
extern void (__cdecl *Rva00627A20Callback)();
extern unsigned char Rva00627A20Enabled;

void Rva00627A20Release()
{
    void (__cdecl *callback)() = Rva00627A20Callback;
    Rva00627A20Enabled = 0;
    if (callback)
    {
        callback();
        Rva00627A20Callback = 0;
    }
}
