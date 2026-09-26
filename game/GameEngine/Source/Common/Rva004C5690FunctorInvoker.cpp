// cl: /O2 /DNDEBUG /MD

// The carved body at 0x004C5690 tail-jumps through a callback at this plus 0x8.
// The nearby wrapper records do not prove a semantic owner, so the type keeps the address.
class Rva004C5690Functor
{
public:
    typedef void (__cdecl *Callback)();
    void invoke();

private:
    char m_prefix[8];
    Callback m_callback;
};

// ?invoke@Rva004C5690Functor@@QAEXXZ
void Rva004C5690Functor::invoke()
{
    m_callback();
}
