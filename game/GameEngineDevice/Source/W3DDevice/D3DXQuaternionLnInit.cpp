// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's QuaternionLn initializer enables the selected CPU path,
// then tail-dispatches through fast-table slot 0xdc.

struct D3DXQUATERNION
{
	float x;
	float y;
	float z;
	float w;
};

typedef D3DXQUATERNION *(__stdcall *D3DXQuaternionLnFunction)(
	D3DXQUATERNION *, const D3DXQUATERNION *);

struct D3DXFASTTABLE
{
	unsigned int reserved[55];
	D3DXQuaternionLnFunction quaternionLn;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXQUATERNION *__stdcall init_D3DXQuaternionLn(
	D3DXQUATERNION *output, const D3DXQUATERNION *input)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.quaternionLn(output, input);
}
