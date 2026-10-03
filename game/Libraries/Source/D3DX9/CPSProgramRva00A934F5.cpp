// cl: /O1 /MD
// CPSProgram constructor A92B30 installs table VA01158598 at A92B49;
// destructor A92B55 reinstalls it then tail-jumps to base teardown AB8350.
// The original cpsprogram.obj table proves this owner. Slot19 independently
// points at the complete32B body A934F5 ending RET at A93514. Ghidra agrees.
namespace D3DXShader
{
    class CPSProgram
    {
    public:
        long rva00A934F5();
    };
    long CPSProgram::rva00A934F5()
    {
        const char *base = reinterpret_cast<const char *>(this);
        unsigned int index = *reinterpret_cast<const unsigned int *>(base + 0xf8);
        unsigned int *data = *reinterpret_cast<unsigned int *const *>(base + 0xec);
        unsigned int count = *reinterpret_cast<const unsigned int *>(base + 0xf0);
        data[index] |= (count - index - 1) << 24;
        return 0;
    }
}
