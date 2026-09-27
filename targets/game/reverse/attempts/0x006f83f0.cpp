// ?rva006F83F0@Rva006F8700Owner@@QAEHPAXH00@Z
// partial score=0.82 date=2026-09-27
// ?rva006F83F0@Rva006F8700Owner@@QAEHPAXH00@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define Matrix4x4 Matrix4
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "common/GlobalData.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "WW3D2/matinfo.h"
#include "WW3D2/vertmaterial.h"
#include "WW3D2/dx8fvf.h"

extern Real g_bfmeDefaultBU;
extern const Real BfmeZeroRange;
extern double g_bfmeMulB3;
extern "C" long __cdecl __ftol2(double value);

class Rva006F83F0Shape
{
public:
	char m_prefix[0xb0];
	Real m_b0;
	Real m_b4;
};

struct Rva006F83F0GlobalDataView
{
	char m_prefix[0x218];
	Int m_timeOfDay;
};

class Rva006F7DA0TreeBuffer
{
public:
	static UnsignedInt __stdcall doLighting(const GlobalData::TerrainLighting *objectLighting,
		const Vector3 *emissive, UnsignedInt vertDiffuse, Real scale, UnsignedInt alpha);
};

class Rva006F8700Owner
{
private:
	char m_prefix[0x28];
	Rva006F83F0Shape *m_shape;
	Vector3 m_offset;
	char m_gap38[0x48];
	Real m_alpha;

public:
	int rva006F83F0(void *destination_vb, int curVertex, void *mtx, void *rawMesh);
};

int Rva006F8700Owner::rva006F83F0(void *destination_vb, int curVertex,
	void *rawMtx, void *rawMesh)
{
	if (rawMesh == NULL)
		return(0);
	const Matrix3D &mtx = *(const Matrix3D *)rawMtx;

	Real value;
	volatile Rva006F83F0Shape *shape = m_shape;
	if (shape == NULL)
		value = m_alpha;
	else
	{
		Real product = shape->m_b0 * shape->m_b4;
		if (product == g_bfmeDefaultBU)
			value = shape->m_b0 * shape->m_b4;
		else
			value = m_alpha;
	}
	if (value > BfmeZeroRange)
		value = BfmeZeroRange;
	else if (value > g_bfmeDefaultBU)
		value = g_bfmeDefaultBU;
	Int alpha = (Int)(value * g_bfmeMulB3);
	Rva006F83F0GlobalDataView *global = (Rva006F83F0GlobalDataView *)TheWritableGlobalData;
	const GlobalData::TerrainLighting *objectLighting =
		(const GlobalData::TerrainLighting *)((const char *)global + 0x224 + global->m_timeOfDay * 0x6c);
	MeshClass *pMesh = (MeshClass *)rawMesh;

	Vector3 emissive(0.0f, 0.0f, 0.0f);
	MaterialInfoClass *matInfo = pMesh->Get_Material_Info();
	if (matInfo != NULL)
	{
		VertexMaterialClass *vertMat = matInfo->Peek_Vertex_Material(0);
		if (vertMat != NULL)
			vertMat->Get_Emissive(&emissive);
	}
	REF_PTR_RELEASE(matInfo);

	Int numVertex = pMesh->Peek_Model()->Get_Vertex_Count();
	Vector3 *pVert = pMesh->Peek_Model()->Get_Vertex_Array();
	if (curVertex + numVertex + 2 >= 15000)
		return(0);

	const Vector2 *uvs = pMesh->Peek_Model()->Get_UV_Array_By_Index(0);
	unsigned *colors = pMesh->Peek_Model()->Get_Color_Array(0, false);
	VertexFormatXYZNDUV1 *curVb = ((VertexFormatXYZNDUV1 *)destination_vb) + curVertex;

	for (Int i = 0; i < numVertex; ++i)
	{
		curVb->u1 = uvs[i].U;
		curVb->v1 = uvs[i].V;
		Vector3 vertex;
		Vector3 vLoc;
		Matrix3D::Transform_Vector(mtx, pVert[i], &vertex);
		vLoc = vertex;
		vLoc.X += m_offset.X;
		vLoc.Y += m_offset.Y;
		vLoc.Z += m_offset.Z;
		curVb->x = vLoc.X;
		curVb->y = vLoc.Y;
		curVb->z = vLoc.Z;
		UnsignedInt vertexDiffuse = colors ? colors[i] : 0xffffffff;
		curVb->diffuse = Rva006F7DA0TreeBuffer::doLighting(
			objectLighting,
			&emissive, vertexDiffuse, 1.0f, alpha);
		++curVb;
	}
	return(numVertex);
}
