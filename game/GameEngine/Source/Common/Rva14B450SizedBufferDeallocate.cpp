void __cdecl operator delete(void *block);
void __cdecl rva423670SmallDeallocate(void *block, unsigned int size);

extern "C" void __stdcall Rva14B450SizedBufferDeallocate(void *block, unsigned int count)
{
    if (block != 0) {
        unsigned int size = count * 12;
        if (size > 128) {
            operator delete(block);
        } else {
            rva423670SmallDeallocate(block, size);
        }
    }
}
