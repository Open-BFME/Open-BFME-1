// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's Vec2TransformCoord initializer enables the selected CPU
// path, then tail-dispatches through the fast-table coordinate-transform slot.

struct D3DXVECTOR2
{
	float x;
	float y;
};

struct D3DXMATRIX
{
	float values[16];
};

typedef D3DXVECTOR2 *(__stdcall *D3DXVec2TransformCoordFunction)(
	D3DXVECTOR2 *, const D3DXVECTOR2 *, const D3DXMATRIX *);

struct D3DXFASTTABLE
{
	unsigned int reserved[9];
	D3DXVec2TransformCoordFunction vec2TransformCoord;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXVECTOR2 *__stdcall init_D3DXVec2TransformCoord(D3DXVECTOR2 *output,
	const D3DXVECTOR2 *input, const D3DXMATRIX *matrix)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.vec2TransformCoord(output, input, matrix);
}
