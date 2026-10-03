// cl: /O1 /MD
// Original cprogram.obj identifies CProgram and the long thiscall return ABI.
// Retail table VA01151884 slots4/5/6 select these distinct four-byte leaves;
// ctor A6C23A and dtor A6C2CC store it at A6C2C2/A6C2D5 respectively.
// All three bodies are XOR EAX,EAX; INC EAX; RET, independently in Ghidra.
namespace D3DXShader
{
    class CArgument;
    class CProgram
    {
    public:
        long rva00A6C2E9(CArgument *, int);
        long rva00A6C370();
        long rva00A6C374();
        long rva00A6C378();
    };

    long CProgram::rva00A6C370()
    {
        return 1;
    }

    long CProgram::rva00A6C374()
    {
        return 1;
    }

    long CProgram::rva00A6C378()
    {
        return 1;
    }
}

// Table slot1 selects the separate eight-byte HRESULT/RET8 before SetName.
long D3DXShader::CProgram::rva00A6C2E9(CArgument *, int)
{
    return static_cast<long>(0x80004005);
}
