namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int size);
void *__cdecl vectorSmallAllocate(unsigned int size);
}

extern "C" void *__stdcall Rva14B550SizedBufferAllocate(unsigned int count, int)
{
    if (count != 0) {
        unsigned int size = count * 12;
        if (size > 128) {
            return _STL::vectorLargeAllocate(size);
        }

        return _STL::vectorSmallAllocate(size);
    }

    return 0;
}
