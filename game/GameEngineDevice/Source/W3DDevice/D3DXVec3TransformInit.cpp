// cl: /DNDEBUG /MD /EHsc
// The D3DX9 d3dxmath.obj initializer calls CPU detection, then tail-dispatches
// through the shared fast table before the public Vec3Transform implementation.

struct D3DXVECTOR3
{
	float values[3];
};

struct D3DXVECTOR4
{
	float values[4];
};

struct D3DXMATRIX
{
	float values[16];
};

typedef D3DXVECTOR4 *(__stdcall *D3DXVec3TransformFunction)(D3DXVECTOR4 *,
	const D3DXVECTOR3 *, const D3DXMATRIX *);

struct D3DXFASTTABLE
{
	// Vec2Transform, Vec3Transform, Vec4Transform sit in slots 0, 1, 2 (see D3DXVec4TransformInit.cpp).
	unsigned int vec2Transform;
	D3DXVec3TransformFunction vec3Transform;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXVECTOR4 *__stdcall init_D3DXVec3Transform(D3DXVECTOR4 *output,
	const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.vec3Transform(output, vector, matrix);
}
