class BfmeThingRF
{
public:
    void *bfmeGoRF(void *first, void *second);
};

void * __stdcall rva007F8EF0Dispatch(BfmeThingRF *owner)
{
    return owner->bfmeGoRF(*reinterpret_cast<void **>(0x012C3B30), 0);
}
