// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's QuaternionExp initializer enables the selected CPU path,
// then tail-dispatches through fast-table slot 0xe0.

struct D3DXQUATERNION
{
	float x;
	float y;
	float z;
	float w;
};

typedef D3DXQUATERNION *(__stdcall *D3DXQuaternionExpFunction)(
	D3DXQUATERNION *, const D3DXQUATERNION *);

struct D3DXFASTTABLE
{
	unsigned int reserved[56];
	D3DXQuaternionExpFunction quaternionExp;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXQUATERNION *__stdcall init_D3DXQuaternionExp(
	D3DXQUATERNION *output, const D3DXQUATERNION *input)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.quaternionExp(output, input);
}
