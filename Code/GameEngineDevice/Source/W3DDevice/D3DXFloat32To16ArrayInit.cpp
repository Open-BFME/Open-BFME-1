// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's Float32 initializer enables the selected CPU path, then
// tail-dispatches through fast-table slot 0xe4.

struct D3DXFLOAT16
{
	unsigned short value;
};

typedef D3DXFLOAT16 *(__stdcall *D3DXFloat32To16ArrayFunction)(D3DXFLOAT16 *,
	const float *, unsigned int);

struct D3DXFASTTABLE
{
	unsigned int reserved[57];
	D3DXFloat32To16ArrayFunction float32To16Array;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXFLOAT16 *__stdcall init_D3DXFloat32To16Array(D3DXFLOAT16 *output,
	const float *input, unsigned int count)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.float32To16Array(output, input, count);
}
