// cl: /O1 /MD
// Original cfxlprogram.obj identifies CFXLProgram and the long thiscall ABI.
// Retail constructor A98C86 installs table VA01158A78 at A98C95. Slot5
// selects this distinct4B XOR EAX,EAX; INC EAX; RET. Ghidra agrees.
namespace D3DXShader
{
    class CFXLProgram
    {
    public:
        long rva00A98CF7();
    };
    long CFXLProgram::rva00A98CF7()
    {
        return 1;
    }
}
