// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// ZH twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp:311
// BFME layout is witnessed by GetPolygonIndex/GetVertex/allocateNeighbors:
// holder +0x00, vertices +0x08, polygon normals +0x10, parent vertices +0x20.

#include "vector3.h"

struct TriIndex
{
	unsigned short I;
	unsigned short J;
	unsigned short K;
};

struct PolygonHolder
{
	unsigned char pad[0x0c];
	const TriIndex *polygons;
};

class Rva007BBB60W3DShadowGeometryMesh
{

protected:
	Vector3 *buildPolygonNormal(long polygonIndex, Vector3 *normal) const;

private:
	PolygonHolder *holder;
	unsigned char pad04[4];
	const Vector3 *vertices;
	unsigned char pad0c[4];
	Vector3 *polygonNormals;
	unsigned char pad14[0x0c];
	unsigned short *parentVertices;

	__forceinline void GetPolygonIndex(long polygonId, short *indexList) const
	{
		const TriIndex *polygon = &holder->polygons[polygonId];
		*indexList++ = parentVertices[polygon->I];
		*indexList++ = parentVertices[polygon->J];
		*indexList++ = parentVertices[polygon->K];
	}

	__forceinline const Vector3 &GetVertex(int vertexId) const
	{
		return vertices[vertexId];
	}
};

// ?buildPolygonNormal@W3DShadowGeometryMesh@@IBEPAVVector3@@JPAV2@@Z
Vector3 *Rva007BBB60W3DShadowGeometryMesh::buildPolygonNormal(long polygonIndex, Vector3 *normal) const
{
	if (polygonNormals)
		return &(*normal = polygonNormals[polygonIndex]);

	short indexList[3];
	GetPolygonIndex(polygonIndex, indexList);

	const Vector3 &v0 = GetVertex(indexList[0]);
	const Vector3 &v1 = GetVertex(indexList[1]);
	const Vector3 &v2 = GetVertex(indexList[2]);

	Vector3 edge1 = v1 - v0;
	Vector3 edge2 = v1 - v2;
	Vector3::Normalized_Cross_Product(edge2, edge1, normal);
	return normal;
}
