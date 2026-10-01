// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad

#include "matrix4.h"
#include "rendobj.h"
#include <d3dx8math.h>

struct BfmeShadowShareBuffer
{
	unsigned char m_pad[0xc];
	Vector3 *m_data;
};

struct BfmeShadowMeshModel
{
	unsigned char m_beforeFlags[0x18];
	unsigned int m_flags;
	unsigned char m_betweenFlagsAndVertexCount[0xc];
	int m_vertexCount;
	unsigned char m_betweenVertexCountAndVertex[4];
	BfmeShadowShareBuffer *m_vertex;

	Vector3 *Get_Vertex_Array()
	{
		return m_vertex->m_data;
	}

	int Get_Vertex_Count() const
	{
		return m_vertexCount;
	}
};

// Direct helper called by BfmeShadowMesh::Get_Deformed_Vertices.
// Address-keyed shim: the helper body at 0x00925860 is still a dump, so the
// name and the two-pointer thiscall ABI come from the symbols.csv pin
// ?method@Rva00925860@@QAEXPAX0@Z (stack cleanup of 8 bytes).
struct Rva00925860
{
	void method(void *dst, void *tree);
};

class BfmeShadowMesh
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void Validate_Transform() const;

	unsigned char m_beforeTransform[0x14];
	Matrix3D m_transform;
	unsigned char m_betweenTransformAndField84[0x3c];
	unsigned int m_field84;
	unsigned char m_betweenField84AndModel[0x40];
	BfmeShadowMeshModel *m_model;

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return m_transform;
	}

	BfmeShadowMeshModel *Peek_Model() const
	{
		return m_model;
	}

	// noinline: retail keeps the call from BfmeShadowBufferEntry::update
	// instead of expanding this 67-byte body there.
	__declspec(noinline) void Get_Deformed_Vertices(Vector3 *dst);
};

// D3DX9 array API absent from DX81 headers. Microsoft documents these native
// types; the Summer2003 archive's @24 public symbol proves stdcall cleanup.
extern "C" D3DXVECTOR3 * __stdcall D3DXVec3TransformCoordArray(
 D3DXVECTOR3 *dst, UINT dstStride,
 const D3DXVECTOR3 *src, UINT srcStride,
 const D3DXMATRIX *matrix, UINT count);

struct BfmeShadowBufferEntry
{
	BfmeShadowMesh *m_mesh;
	void *m_allocation0;
	void *m_allocation1;
	void *m_allocation2;
	unsigned int m_reserved10;
	unsigned char m_reserved14;

	void update();
};

void BfmeShadowBufferEntry::update()
{
	if ((m_mesh->m_model->m_flags & 0x400) != 0)
	{
		m_mesh->Get_Deformed_Vertices((Vector3 *)m_allocation0);
		return;
	}

	Matrix4 matrix(m_mesh->Get_Transform());
	D3DXVec3TransformCoordArray(
		(D3DXVECTOR3 *)m_allocation0, 0xc,
		(const D3DXVECTOR3 *)m_mesh->Peek_Model()->Get_Vertex_Array(), 0xc,
		(D3DXMATRIX *)&matrix.Transpose(),
		m_mesh->Peek_Model()->Get_Vertex_Count());
}

// Defined after its caller so the compiler does not inline it: retail keeps
// the call at 0x007C1DC0. Skin the mesh's vertices into dst; when m_field84
// names a container the deformed pass is driven by that container's HTree,
// otherwise the model is asked for its vertices with no tree. Retail spells
// this as one conditional argument, which is what keeps the two helper call
// sites in the order observed in the binary.
void BfmeShadowMesh::Get_Deformed_Vertices(Vector3 *dst)
{
	((Rva00925860 *)m_model)->method(
		dst,
		m_field84 ? (void *)((RenderObjClass *)m_field84)->Get_HTree() : (void *)0);
}
