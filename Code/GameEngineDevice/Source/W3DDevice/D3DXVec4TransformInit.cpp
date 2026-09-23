// Retail 0x009FAA3B, 13 bytes. d3dxmath.obj names this initializer;
// the adjacent public Vec4Transform stub and fast-table slot +8 fix its route.
struct D3DXVECTOR4 { float values[4]; };
struct D3DXMATRIX { float values[16]; };

typedef D3DXVECTOR4 *(__stdcall *D3DXVec4TransformFunction)(
    D3DXVECTOR4 *, const D3DXVECTOR4 *, const D3DXMATRIX *);
struct D3DXFASTTABLE
{
    unsigned int reserved[2];
    D3DXVec4TransformFunction vec4Transform;
};
extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXVECTOR4 *__stdcall init_D3DXVec4Transform(D3DXVECTOR4 *output,
    const D3DXVECTOR4 *vector, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return g_D3DXFastTable.vec4Transform(output, vector, matrix);
}
