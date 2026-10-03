// cl: /O1 /MD
// Original cnode.obj gives distinct owner tables and void thiscall()
// slot2 signatures. Retail constructors install each table independently:
// CNode A68582 -> VA011515D0; CNodeList A68630 -> VA011515DC;
// CNodeTree A686CB -> VA011515E8. Their slot2 values select the distinct
// one-byte RET bodies below; the following entries are never included.
namespace D3DXShader
{
    class CNode
    {
    public:
        void rva00A6861B();
    };
    class CNodeList
    {
    public:
        void rva00A686B9();
    };
    class CNodeTree
    {
    public:
        void rva00A68751();
    };

    void CNode::rva00A6861B() {}
    void CNodeList::rva00A686B9() {}
    void CNodeTree::rva00A68751() {}
}

// CNodeToken ctor A68820 installs VA011515F4; CNodeProgram ctor A68885
// installs VA01151600. Their own slot2 entries prove these separate leaves.
namespace D3DXShader
{
    class CNodeToken
    {
    public:
        void rva00A68884();
    };
    class CNodeProgram
    {
    public:
        void rva00A6891D();
    };
    void CNodeToken::rva00A68884() {}
    void CNodeProgram::rva00A6891D() {}
}

// Further distinct cnode.obj slot2 leaves, each void thiscall/no arguments.
namespace D3DXShader
{
    // Ctor A6891E installs VA0115160C; its slot2 selects 00A689DC.
    class CNodeScope
    {
    public:
        void rva00A689DC();
    };
    void CNodeScope::rva00A689DC() {}
    // Ctor A689DD installs VA01151618; its slot2 selects 00A68AC4.
    class CNodeDecl
    {
    public:
        void rva00A68AC4();
    };
    void CNodeDecl::rva00A68AC4() {}
    // Ctor A68AC5 installs VA01151624; its slot2 selects 00A68B59.
    class CNodeUsage
    {
    public:
        void rva00A68B59();
    };
    void CNodeUsage::rva00A68B59() {}
    // Ctor A68B5D installs VA01151630; its slot2 selects 00A68BD1.
    class CNodeArray
    {
    public:
        void rva00A68BD1();
    };
    void CNodeArray::rva00A68BD1() {}
}

// Distinct cnode.obj slot2 leaves; original signatures are void thiscall().
namespace D3DXShader
{
    // Constructor store A68BE2 installs VA0115163C; slot2 selects 00A68C74.
    class CNodeType
    {
    public:
        void rva00A68C74();
    };
    void CNodeType::rva00A68C74() {}
    // Constructor store A68C86 installs VA01151648; slot2 selects 00A68DCC.
    class CNodeFunction
    {
    public:
        void rva00A68DCC();
    };
    void CNodeFunction::rva00A68DCC() {}
    // Constructor store A68DDE installs VA01151654; slot2 selects 00A68F1B.
    class CNodeVariable
    {
    public:
        void rva00A68F1B();
    };
    void CNodeVariable::rva00A68F1B() {}
    // Constructor store A68F2D installs VA01151660; slot2 selects 00A68FE1.
    class CNodeStatement
    {
    public:
        void rva00A68FE1();
    };
    void CNodeStatement::rva00A68FE1() {}
}

// Each cnode.obj slot2 has its own void thiscall() signature and retail entry.
namespace D3DXShader
{
    // Constructor store A6900C installs VA0115166C.
    class CNodeExpression
    {
    public:
        void rva00A690EA();
    };
    void CNodeExpression::rva00A690EA() {}
    // Constructor store A69103 installs VA01151678.
    class CNodeValue
    {
    public:
        void rva00A692E5();
    };
    void CNodeValue::rva00A692E5() {}
    // Constructor store A692F7 installs VA01151684.
    class CNodeState
    {
    public:
        void rva00A69381();
    };
    void CNodeState::rva00A69381() {}
    // Constructor store A69393 installs VA01151690.
    class CNodeBuffer
    {
    public:
        void rva00A69415();
    };
    void CNodeBuffer::rva00A69415() {}
    // Constructor store A69427 installs VA0115169C.
    class CNodeRegister
    {
    public:
        void rva00A69498();
    };
    void CNodeRegister::rva00A69498() {}
}
