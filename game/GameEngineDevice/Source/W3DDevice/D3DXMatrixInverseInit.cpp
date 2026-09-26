// Retail 0x009FB314, 13 bytes. d3dxmath.obj names this initializer;
// the adjacent public MatrixInverse stub and fast-table slot +0x48 fix its route.
struct D3DXMATRIX { float values[16]; };

typedef D3DXMATRIX *(__stdcall *D3DXMatrixInverseFunction)(
    D3DXMATRIX *, float *, const D3DXMATRIX *);
struct D3DXFASTTABLE
{
    unsigned int reserved[18];
    D3DXMatrixInverseFunction matrixInverse;
};
extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXMATRIX *__stdcall init_D3DXMatrixInverse(D3DXMATRIX *output,
    float *determinant, const D3DXMATRIX *input)
{
    D3DXCpuOptimizations(1);
    return g_D3DXFastTable.matrixInverse(output, determinant, input);
}
