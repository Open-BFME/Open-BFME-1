// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's MatrixRotationQuaternion initializer enables the selected CPU
// path, then tail-dispatches through fast-table slot 0x98.

struct D3DXMATRIX
{
	float values[16];
};

struct D3DXQUATERNION
{
	float x;
	float y;
	float z;
	float w;
};

typedef D3DXMATRIX *(__stdcall *D3DXMatrixRotationQuaternionFunction)(
	D3DXMATRIX *, const D3DXQUATERNION *);

struct D3DXFASTTABLE
{
	unsigned int reserved[38];
	D3DXMatrixRotationQuaternionFunction matrixRotationQuaternion;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXMATRIX *__stdcall init_D3DXMatrixRotationQuaternion(
	D3DXMATRIX *output, const D3DXQUATERNION *quaternion)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.matrixRotationQuaternion(output, quaternion);
}
