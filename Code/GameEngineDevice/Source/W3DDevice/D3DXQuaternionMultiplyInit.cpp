// cl: /DNDEBUG /MD /EHsc
// d3dxmath.obj's QuaternionMultiply initializer enables the selected CPU
// path, then tail-dispatches through fast-table slot 0x4c.

struct D3DXQUATERNION
{
	float x;
	float y;
	float z;
	float w;
};

typedef D3DXQUATERNION *(__stdcall *D3DXQuaternionMultiplyFunction)(
	D3DXQUATERNION *, const D3DXQUATERNION *, const D3DXQUATERNION *);

struct D3DXFASTTABLE
{
	unsigned int reserved[19];
	D3DXQuaternionMultiplyFunction quaternionMultiply;
};

extern D3DXFASTTABLE g_D3DXFastTable;
extern "C" void __stdcall D3DXCpuOptimizations(int optimization);

D3DXQUATERNION *__stdcall init_D3DXQuaternionMultiply(
	D3DXQUATERNION *output, const D3DXQUATERNION *left,
	const D3DXQUATERNION *right)
{
	D3DXCpuOptimizations(1);
	return g_D3DXFastTable.quaternionMultiply(output, left, right);
}
