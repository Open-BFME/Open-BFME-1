// cl: /O2 /MD
// Table VA01149DD0 slots 1 and 2 independently select the adjacent RET12
// bodies A303FF and A30402. CCodec ctor A31321 stores it at A3132D;
// dtor A303D9 reinstalls it at A303DF. Ghidra and baseline agree.
// Original ccodec.obj table relocations establish CCodec and the signature
// void thiscall(unsigned int, unsigned int, D3DXCOLOR *). Method names stay
// address-qualified; no name is inferred from either empty body.
struct D3DXCOLOR;

namespace D3DXTex
{
    class CCodec
    {
    public:
        void rva00A303FF(unsigned int, unsigned int, D3DXCOLOR *);
        void rva00A30402(unsigned int, unsigned int, D3DXCOLOR *);
    };

    void CCodec::rva00A303FF(unsigned int, unsigned int, D3DXCOLOR *)
    {
    }

    void CCodec::rva00A30402(unsigned int, unsigned int, D3DXCOLOR *)
    {
    }
}
