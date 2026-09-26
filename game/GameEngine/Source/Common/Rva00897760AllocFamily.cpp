// cl: /DNDEBUG /MD /O2

class BfmeItemDX;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
void __cdecl bfmePush(BfmeItemDX *item);

#define BFME_ALLOC_WRAPPER(NAME)                         \
    void *NAME(unsigned int bytes)                       \
    {                                                     \
        char *item = (char *)Rva008C5D70Alloc(bytes + 8) + 8; \
        bfmePush((BfmeItemDX *)item);                    \
        return item;                                      \
    }

BFME_ALLOC_WRAPPER(Rva00897760Allocate)
BFME_ALLOC_WRAPPER(Rva008977C0Allocate)
BFME_ALLOC_WRAPPER(Rva00897820Allocate)
BFME_ALLOC_WRAPPER(Rva00897880Allocate)
BFME_ALLOC_WRAPPER(Rva008978E0Allocate)
BFME_ALLOC_WRAPPER(Rva00897940Allocate)
