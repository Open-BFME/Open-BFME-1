// cl: /DNDEBUG /MD
// Retail 0x009D79F0 is a 46-byte hash/modulo body, ending at RET 8.
// The former 76-byte dump also covered a separate iterator body at 0x009D7A20.
// No receiver or source-level template identity is established for this copy.
// Keep its owner and partial key view address-derived. The byte loads are signed.

struct Rva009D79F0Key
{
    const signed char *begin;
    const signed char *end;
};
class Rva009D79F0Owner
{
public:
    unsigned int bucket(const Rva009D79F0Key *key, unsigned int count) const;
};
unsigned int Rva009D79F0Owner::bucket(const Rva009D79F0Key *key, unsigned int count) const
{
    unsigned int value = 0;
    unsigned int length = static_cast<unsigned int>(key->end - key->begin);
    unsigned int base = reinterpret_cast<unsigned int>(key->begin);
    for (unsigned int i = 0; i < length; ++i)
        value = value * 5 + *reinterpret_cast<const signed char *>(i + base);
    return value % count;
}

