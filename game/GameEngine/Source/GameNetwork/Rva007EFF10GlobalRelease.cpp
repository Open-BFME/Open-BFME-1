// cl: /O2
// The global owns an object whose callback at +8 receives (object, 0).
struct Rva007F00B0Allocator;
extern Rva007F00B0Allocator *g_Rva0130A5B0;

typedef void (__cdecl *Rva007EFF10Release)(void *, int);

void Rva007EFF10GlobalRelease()
{
    void *object = g_Rva0130A5B0;
    if (object)
    {
        ((Rva007EFF10Release *)object)[2](object, 0);
        g_Rva0130A5B0 = 0;
    }
}
