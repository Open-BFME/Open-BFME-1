// cl: /DNDEBUG /MD /EHsc
// The D3DX9 d3dxmath.obj initializer calls CPU detection, then tail-dispatches
// through the shared fast table before the public MatrixMultiply stub.

struct D3DXMATRIX
{
	float values[16];
};

typedef D3DXMATRIX *(__stdcall *D3DXMatrixMultiplyFunction)(D3DXMATRIX *,
	const D3DXMATRIX *, const D3DXMATRIX *);

struct D3DXFASTTABLE
{
	unsigned int reserved[3];
	D3DXMatrixMultiplyFunction matrixMultiply;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXMATRIX *__stdcall init_D3DXMatrixMultiply(D3DXMATRIX *output,
	const D3DXMATRIX *left, const D3DXMATRIX *right)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.matrixMultiply(output, left, right);
}
