// cl: /O2 /DNDEBUG /MD

// The carved body at 0x001D3EF0 returns this minus 0x70.
// The adjacent wrappers do not prove a semantic owner, so the type keeps the address.
class Rva001D3EF0Minus70Owner
{
public:
    void *get() const;
};

// ?get@Rva001D3EF0Minus70Owner@@QBEPAXXZ
void *Rva001D3EF0Minus70Owner::get() const
{
    return reinterpret_cast<char *>(const_cast<Rva001D3EF0Minus70Owner *>(this)) - 0x70;
}
