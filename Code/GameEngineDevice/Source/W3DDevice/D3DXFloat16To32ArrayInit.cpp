// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's Float16 initializer enables the selected CPU path, then
// tail-dispatches through the shared D3DX fast table.

struct D3DXFLOAT16
{
	unsigned short value;
};

typedef float *(__stdcall *D3DXFloat16To32ArrayFunction)(float *,
	const D3DXFLOAT16 *, unsigned int);

struct D3DXFASTTABLE
{
	unsigned int reserved[58];
	D3DXFloat16To32ArrayFunction float16To32Array;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

float *__stdcall init_D3DXFloat16To32Array(float *output,
	const D3DXFLOAT16 *input, unsigned int count)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.float16To32Array(output, input, count);
}
