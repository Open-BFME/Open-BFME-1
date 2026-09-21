// ?getModelVertices@W3DBridgeGetModelVerticesShim@@QAEHPAUVertexFormatXYZNDUV1@@HMAAVVector3@@111ABVMatrix3D@@PAVMeshClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// partial score=0.9 date=2026-09-14
// Identity review: retail identity is ?getModelVertices@W3DBridge@@IAEHPAUVertexFormatXYZNDUV1@@HMAAVVector3@@111ABVMatrix3D@@PAVMeshClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z at 0x006D7EA0. The shim name is probe-only because the matched 5-byte ILT at 0x0001B14E already owns the real symbol.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "W3DDevice/GameClient/W3DBridgeBuffer.h"

#include "common/GlobalData.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "sharebuf.h"

class BfmeC998
{
public:
	void bfmeGo998C(Int);
};

struct BfmeStaticDiffuseGlobalData
{
	char m_padding0[0xA04];
	Coord3D m_terrainLightPos[4];
	char m_paddingA34[0xA58 - 0xA34];
	Int m_numGlobalLights;
};

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array_By_Index(int index, bool allow_default);
};

class MeshGeometryClass
{
	char m_prefix[0x28];
	Int m_vertexCount;
	ShareBufferClass<Vector3> *m_poly;
	ShareBufferClass<Vector3> *m_vertex;
	char m_materialPadding[0x68];

public:
	Int Get_Vertex_Count() const
	{
		return m_vertexCount;
	}

	Vector3 *Get_Vertex_Array()
	{
		return m_vertex->Get_Array();
	}

	const Vector3 *Get_Vertex_Normal_Array()
	{
		union
		{
			void (BfmeC998::*void_function)(Int);
			const Vector3 *(BfmeC998::*normal_function)(Int);
		} function;
		function.void_function = &BfmeC998::bfmeGo998C;
		return (((BfmeC998 *)this)->*function.normal_function)(0);
	}
};

class MeshModelClass : public MeshGeometryClass
{
	MeshMatDescClass *m_curMatDesc;

public:
	const Vector2 *Get_UV_Array_By_Index(int index)
	{
		return m_curMatDesc->Get_UV_Array_By_Index(index, false);
	}
};

class MeshClass
{
	char m_padding[0xc8];
	MeshModelClass *m_model;

public:
	MeshModelClass *Peek_Model()
	{
		return m_model;
	}
};

// The reloc-derived caller in W3DBridgeBuffer.cpp names this body at retail
// 0x006D7EA0. The first member keeps m_start at the retail offset.
class W3DBridgeGetModelVerticesShim
{
	Vector3 m_start;

public:
	Int getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
		Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset,
		const Matrix3D &mtx, register MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator);
};

Int W3DBridgeGetModelVerticesShim::getModelVertices(
	VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
	Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset,
	const Matrix3D &mtx, register MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == NULL)
		return(0);

	Int i;
	Vector3 *pVert = pMesh->Peek_Model()->Get_Vertex_Array();
	Int numVertex = pMesh->Peek_Model()->Get_Vertex_Count();
	const Vector3 *pNormal = pMesh->Peek_Model()->Get_Vertex_Normal_Array();

	if (curVertex+numVertex+2 >= 8000)
		return(0);

	Vector3 lightRay[MAX_GLOBAL_LIGHTS];
	const Coord3D *lightPos;

	for (Int lightIndex=0; lightIndex <
		((const BfmeStaticDiffuseGlobalData *)TheWritableGlobalData)->m_numGlobalLights; lightIndex++)
	{
		lightPos = &((const BfmeStaticDiffuseGlobalData *)TheWritableGlobalData)->m_terrainLightPos[lightIndex];
		lightRay[lightIndex].Set(-lightPos->x, -lightPos->y, -lightPos->z);
		lightRay[lightIndex].Normalize();
	}

	const Vector2 *uvs = pMesh->Peek_Model()->Get_UV_Array_By_Index(0);
	VertexFormatXYZNDUV1 *curVb = destination_vb+curVertex;

	for (i=0; i<numVertex; i++)
	{
		curVb->u1 = uvs[i].U;
		curVb->v1 = uvs[i].V;
		Vector3 vLoc;
		Vector3 vertex;
		Matrix3D::Transform_Vector(mtx, pVert[i], &vertex);
		vLoc = (vertex.X+xOffset) * vec + vertex.Y*vecNormal + vertex.Z*vecZ;

		vLoc.X += m_start.X;
		vLoc.Y += m_start.Y;
		vLoc.Z += m_start.Z;

		curVb->x = vLoc.X;
		curVb->y = vLoc.Y;
		curVb->z = vLoc.Z;

		VERTEX_FORMAT vb;
		vb.x = vLoc.X;
		vb.y = vLoc.Y;
		vb.z = vLoc.Z;

		Vector3 normal;
		Matrix3D::Rotate_Vector(mtx, pNormal[i], &normal);
		curVb->diffuse = 0xFF000000;
#ifdef USE_BRIDGE_NORMALS
		curVb->nx = normal.X;
		curVb->ny = normal.Y;
		curVb->nz = normal.Z;
		curVb->diffuse = 0xFF000000;
#else
		normal = normal.X * vec + normal.Y*vecNormal + normal.Z*vecZ;
		normal.Normalize();
		TheTerrainRenderObject->doTheLight(&vb, lightRay, &normal, NULL, 1.0f);
		curVb->nx = 0;
		curVb->ny = 0;
		curVb->nz = 1;
		curVb->diffuse = vb.diffuse | 0xFF000000;
#endif
		curVb++;
	}
	return(numVertex);
}
