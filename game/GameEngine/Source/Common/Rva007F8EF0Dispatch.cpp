extern void *g_012C3B30;

class BfmeThingRF
{
public:
    void *bfmeGoRF(void *first, void *second);
};

void * __stdcall rva007F8EF0Dispatch(BfmeThingRF *owner)
{
    return owner->bfmeGoRF(g_012C3B30, 0);
}
