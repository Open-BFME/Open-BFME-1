// cl: /O1 /MD
// Original cshaderprogram.obj's named table proves CShaderProgram ownership
// and these argument/return types. Retail table VA0115B678 independently
// selects every listed address. Ctor AB82AA stores it at AB82B8 and dtor
// AB8350 reinstalls it at AB835A. Ghidra and baseline agree. Each complete extent ends at its own RET.
// Method names retain addresses; identical bytes are not identity evidence.
namespace D3DXShader
{
    class CArgument;
    class CInstruction;
    class CShaderProgram
    {
    public:
        long rva00AB1048(CArgument *);
        long rva00AB104D();
        long rva00AB107F(CArgument *, unsigned long *);
        long rva00AB1084(CArgument *, int);
        long rva00AB108C();
        int rva00AB1092(CInstruction *, unsigned int *);
        long rva00AB1097();
        long rva00AB109D();
        long rva00AB10A0();
        int rva00AB10A6(CInstruction *, unsigned int);
        long rva00AB7138();
        unsigned long rva00AB7140(unsigned long value);
    };

    // Table slot 16; RVA 00AB1048, 5 bytes.
    long CShaderProgram::rva00AB1048(CArgument *)
    {
        return 0;
    }

    // Table slot 17; RVA 00AB104D, 3 bytes.
    long CShaderProgram::rva00AB104D()
    {
        return 0;
    }

    // Table slot 15; RVA 00AB107F, 5 bytes.
    long CShaderProgram::rva00AB107F(CArgument *, unsigned long *)
    {
        return 0;
    }

    // Table slot 1; RVA 00AB1084, 8 bytes.
    long CShaderProgram::rva00AB1084(CArgument *, int)
    {
        return static_cast<long>(0x80004005);
    }

    // Table slot 10; RVA 00AB108C, 6 bytes.
    long CShaderProgram::rva00AB108C()
    {
        return static_cast<long>(0x80004005);
    }

    // Table slot 7; RVA 00AB1092, 5 bytes.
    int CShaderProgram::rva00AB1092(CInstruction *, unsigned int *)
    {
        return 0;
    }

    // Table slot 8; RVA 00AB1097, 6 bytes.
    long CShaderProgram::rva00AB1097()
    {
        return static_cast<long>(0x80004005);
    }

    // Table slot 12; RVA 00AB109D, 3 bytes.
    long CShaderProgram::rva00AB109D()
    {
        return 0;
    }

    // Table slot 9; RVA 00AB10A0, 6 bytes.
    long CShaderProgram::rva00AB10A0()
    {
        return static_cast<long>(0x80004005);
    }

    // Table slot 11; RVA 00AB10A6, 5 bytes.
    int CShaderProgram::rva00AB10A6(CInstruction *, unsigned int)
    {
        return 0;
    }

    // Table slot 19; RVA 00AB7138, 3 bytes.
    long CShaderProgram::rva00AB7138()
    {
        return 0;
    }

    // Table slot 18; RVA 00AB7140, 7 bytes.
    unsigned long CShaderProgram::rva00AB7140(unsigned long value)
    {
        return value;
    }
}
