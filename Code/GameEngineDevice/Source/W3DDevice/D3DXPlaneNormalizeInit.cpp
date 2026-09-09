// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's PlaneNormalize initializer enables the selected CPU path,
// then tail-dispatches through fast-table slot 0x54.

struct D3DXPLANE
{
	float a;
	float b;
	float c;
	float d;
};

typedef D3DXPLANE *(__stdcall *D3DXPlaneNormalizeFunction)(D3DXPLANE *,
	const D3DXPLANE *);

struct D3DXFASTTABLE
{
	unsigned int reserved[21];
	D3DXPlaneNormalizeFunction planeNormalize;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXPLANE *__stdcall init_D3DXPlaneNormalize(D3DXPLANE *output,
	const D3DXPLANE *input)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.planeNormalize(output, input);
}
