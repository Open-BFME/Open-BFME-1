// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's PlaneFromPointNormal initializer enables the selected CPU
// path, then tail-dispatches through fast-table slot 0x30.

struct D3DXVECTOR3
{
	float x;
	float y;
	float z;
};

struct D3DXPLANE
{
	float a;
	float b;
	float c;
	float d;
};

typedef D3DXPLANE *(__stdcall *D3DXPlaneFromPointNormalFunction)(D3DXPLANE *,
	const D3DXVECTOR3 *, const D3DXVECTOR3 *);

struct D3DXFASTTABLE
{
	unsigned int reserved[12];
	D3DXPlaneFromPointNormalFunction planeFromPointNormal;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXPLANE *__stdcall init_D3DXPlaneFromPointNormal(D3DXPLANE *output,
	const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.planeFromPointNormal(output, point, normal);
}
