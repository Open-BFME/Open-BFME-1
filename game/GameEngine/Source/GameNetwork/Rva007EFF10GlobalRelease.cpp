// cl: /O2
// The global owns an object whose callback at +8 receives (object, 0).
extern void *g_bfme929Ptr;

typedef void (__cdecl *Rva007EFF10Release)(void *, int);

void Rva007EFF10GlobalRelease()
{
    void *object = g_bfme929Ptr;
    if (object)
    {
        ((Rva007EFF10Release *)object)[2](object, 0);
        g_bfme929Ptr = 0;
    }
}
