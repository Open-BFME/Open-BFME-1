// cl: /DNDEBUG /MD /EHsc
// RVA 0x0081EB50: true only when both pointer arguments are non-null.
bool __cdecl Rva0081EB50BothPresent(const void *first, const void *second)
{
    if (first != 0 && second != 0)
        return true;
    return false;
}
