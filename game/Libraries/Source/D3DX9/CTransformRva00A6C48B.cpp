// cl: /O1 /MD
// Original cprogram.obj: CTransform table slot 1 has long thiscall/no args.
// Retail VA011518A0 +4 and derived VA011518A8 +4 both select RVA00A6C48B.
// Ctor A6C472 and dtor A6C484 install the first table; the archive's complete
// table and ctor relocation establish the owner independently of the older
// masked ctor ledger label. Method identity remains address-qualified.
namespace D3DXShader
{
    class CTransform
    {
    public:
        long rva00A6C48B();
    };

    long CTransform::rva00A6C48B()
    {
        return static_cast<long>(0x80004001);
    }
}
