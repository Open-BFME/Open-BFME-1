// ?get@Rva001E1200@@QAEPAXXZ
// The carved boundary proves a three-byte thiscall accessor that returns this.
// No caller or table proves a semantic owner, so the address stays in the type.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva001E1200
{
public:
    void *get();
};

void *Rva001E1200::get()
{
    return this;
}
