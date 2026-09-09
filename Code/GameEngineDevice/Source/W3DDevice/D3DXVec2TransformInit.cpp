// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's Vec2Transform initializer enables the selected CPU path,
// then tail-dispatches through fast-table slot zero.

struct D3DXVECTOR2
{
	float x;
	float y;
};

struct D3DXVECTOR4
{
	float x;
	float y;
	float z;
	float w;
};

struct D3DXMATRIX
{
	float values[16];
};

typedef D3DXVECTOR4 *(__stdcall *D3DXVec2TransformFunction)(D3DXVECTOR4 *,
	const D3DXVECTOR2 *, const D3DXMATRIX *);

struct D3DXFASTTABLE
{
	D3DXVec2TransformFunction vec2Transform;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXVECTOR4 *__stdcall init_D3DXVec2Transform(D3DXVECTOR4 *output,
	const D3DXVECTOR2 *input, const D3DXMATRIX *matrix)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.vec2Transform(output, input, matrix);
}
