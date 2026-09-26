void __cdecl f_00881eb0(void *block);
void __cdecl rva423670SmallDeallocate(void *block, unsigned int size);

extern "C" void __stdcall Rva14B500SizedBufferDeallocate(void *block, unsigned int count)
{
    if (block != 0) {
        unsigned int size = count * 16;
        if (size > 128) {
            f_00881eb0(block);
        } else {
            rva423670SmallDeallocate(block, size);
        }
    }
}
