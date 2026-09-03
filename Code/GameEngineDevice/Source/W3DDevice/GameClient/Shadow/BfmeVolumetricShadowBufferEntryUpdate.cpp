// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWDebug

#include "matrix4.h"

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
	unsigned char m_betweenTransformAndModel[0x80];
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

	void Get_Deformed_Vertices(Vector3 *dst);
};

struct _D3DXMATRIX
{
	float m[4][4];
};
typedef struct _D3DXMATRIX D3DXMATRIX;

extern "C" Vector3 * __stdcall D3DXVec3TransformCoordArray(
	Vector3 *dst, unsigned int dstStride,
	const Vector3 *src, unsigned int srcStride,
	const D3DXMATRIX *matrix, unsigned int count);

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
		(Vector3 *)m_allocation0, 0xc,
		m_mesh->Peek_Model()->Get_Vertex_Array(), 0xc,
		(D3DXMATRIX *)&matrix.Transpose(),
		m_mesh->Peek_Model()->Get_Vertex_Count());
}
