// cl: /O2 /Ob0

// Retail returns the address at this plus eight for the carved body.
// No evidence proves the owning type, so the source keeps the address-derived name.
class Rva003CB940 {
public:
    void *field();
};

void *Rva003CB940::field()
{
    return reinterpret_cast<char *>(this) + 8;
}
