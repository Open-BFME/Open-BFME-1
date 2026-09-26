// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's MatrixTranspose initializer enables the selected CPU path,
// then tail-dispatches through fast-table slot 0x94.

struct D3DXMATRIX
{
	float values[16];
};

typedef D3DXMATRIX *(__stdcall *D3DXMatrixTransposeFunction)(D3DXMATRIX *,
	const D3DXMATRIX *);

struct D3DXFASTTABLE
{
	unsigned int reserved[37];
	D3DXMatrixTransposeFunction matrixTranspose;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXMATRIX *__stdcall init_D3DXMatrixTranspose(D3DXMATRIX *output,
	const D3DXMATRIX *input)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.matrixTranspose(output, input);
}
