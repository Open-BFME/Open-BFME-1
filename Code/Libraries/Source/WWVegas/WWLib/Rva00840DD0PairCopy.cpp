// cl: /DNDEBUG /MD /EHsc
// RVA 0x00840DD0: copy two adjacent words and return the destination.
struct Rva00840DD0Pair
{
    unsigned int m_first;
    unsigned int m_second;
};

Rva00840DD0Pair *__cdecl Rva00840DD0Copy(Rva00840DD0Pair *destination,
                             const Rva00840DD0Pair *source)
{
    *destination = *source;
    return destination;
}
