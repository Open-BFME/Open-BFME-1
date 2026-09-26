// cl: /DNDEBUG /MD /EHsc
// RVA 0x008C4650: allocate an eight-byte linked-list header and link its item.
class BfmeItemDX;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
void __cdecl bfmePush(BfmeItemDX *item);

void *aptHeaderedAlloc008C4650(unsigned int bytes)
{
    char *item = (char *)Rva008C5D70Alloc(bytes + 8) + 8;
    bfmePush((BfmeItemDX *)item);
    return item;
}
