// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's Vec3Normalize initializer enables the selected CPU path,
// then tail-dispatches through the fast-table slot for three-vectors.

struct D3DXVECTOR3
{
	float x;
	float y;
	float z;
};

typedef D3DXVECTOR3 *(__stdcall *D3DXVec3NormalizeFunction)(D3DXVECTOR3 *,
	const D3DXVECTOR3 *);

struct D3DXFASTTABLE
{
	unsigned int reserved[7];
	D3DXVec3NormalizeFunction vec3Normalize;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXVECTOR3 *__stdcall init_D3DXVec3Normalize(D3DXVECTOR3 *output,
	const D3DXVECTOR3 *input)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.vec3Normalize(output, input);
}
