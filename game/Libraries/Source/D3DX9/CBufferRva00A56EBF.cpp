// cl: /O2 /MD
// D3DXCore::CBuffer constructor A57151 installs VA0114D830 at A5715B;
// destructor A56E88 reinstalls it at A56E8B. Original cbuffer.obj's named
// CBuffer vtable has the matching seven-slot layout (QueryInterface/Release
// and Init independently anchor it). Slots 1/3/4 select these exact leaves.
// Keep method addresses; do not infer semantic names from the body bytes.
namespace D3DXCore
{
    class CBuffer
    {
    public:
        unsigned long __stdcall rva00A56EBF();
        unsigned long __stdcall rva00A56EEC();
        unsigned long __stdcall rva00A56EF6();
    };

    unsigned long __stdcall CBuffer::rva00A56EBF()
    {
        unsigned long *value = reinterpret_cast<unsigned long *>(
            reinterpret_cast<char *>(this) + 4);
        ++*value;
        // Preserve retail's separate readback without claiming a member type.
        return *static_cast<volatile unsigned long *>(value);
    }

    unsigned long __stdcall CBuffer::rva00A56EEC()
    {
        return *reinterpret_cast<const unsigned long *>(
            reinterpret_cast<const char *>(this) + 0x0c);
    }

    unsigned long __stdcall CBuffer::rva00A56EF6()
    {
        return *reinterpret_cast<const unsigned long *>(
            reinterpret_cast<const char *>(this) + 8);
    }
}
