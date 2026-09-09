// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's Vec3TransformNormal initializer enables the selected CPU
// path, then tail-dispatches through the fast-table normal slot.

struct D3DXVECTOR3
{
	float x;
	float y;
	float z;
};

struct D3DXMATRIX
{
	float values[16];
};

typedef D3DXVECTOR3 *(__stdcall *D3DXVec3TransformNormalFunction)(
	D3DXVECTOR3 *, const D3DXVECTOR3 *, const D3DXMATRIX *);

struct D3DXFASTTABLE
{
	unsigned int reserved[6];
	D3DXVec3TransformNormalFunction vec3TransformNormal;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXVECTOR3 *__stdcall init_D3DXVec3TransformNormal(D3DXVECTOR3 *output,
	const D3DXVECTOR3 *input, const D3DXMATRIX *matrix)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.vec3TransformNormal(output, input, matrix);
}
