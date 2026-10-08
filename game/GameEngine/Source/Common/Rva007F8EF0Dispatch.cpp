// Retail .data VA 0x012C3B30 (4 B) points at the "decodedSize" key at VA 0x0112B928.
void *g_012C3B30 = (void *)"decodedSize";

class BfmeThingRF
{
public:
    void *bfmeGoRF(void *first, void *second);
};

void * __stdcall rva007F8EF0Dispatch(BfmeThingRF *owner)
{
    return owner->bfmeGoRF(g_012C3B30, 0);
}
