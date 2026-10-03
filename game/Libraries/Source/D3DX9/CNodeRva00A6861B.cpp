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
