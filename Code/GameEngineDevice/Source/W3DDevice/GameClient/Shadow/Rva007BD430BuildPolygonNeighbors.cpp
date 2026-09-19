// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include

#include <assert.h>
#include <math.h>

#include "vector3.h"

typedef int Int;
typedef short Short;
typedef unsigned char Byte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct TriIndex
{
	UnsignedShort I;
	UnsignedShort J;
	UnsignedShort K;
};

struct PolygonHolder
{
	Byte pad[0x0c];
	const TriIndex *polygons;
};

typedef struct _NeighborEdge
{
	Short neighborIndex;
	Short neighborEdgeIndex[2];
} NeighborEdge;

struct PolyNeighbor
{
	Short myIndex;
	Byte status;
	NeighborEdge neighbor[3];
};

class W3DShadowGeometryMesh
{
public:
	void buildPolygonNormals();
	void buildPolygonNeighbors();

private:
	PolygonHolder *m_holder;
	Byte m_pad04[4];
	const Vector3 *m_verts;
	Byte m_pad0c[4];
	Vector3 *m_polygonNormals;
	Byte m_pad14[8];
	Int m_numPolygons;
	UnsignedShort *m_parentVerts;
	PolyNeighbor *m_polyNeighbors;
	Int m_numPolyNeighbors;

	__forceinline const Vector3 &GetPolygonNormal(long polygon) const
	{
		return m_polygonNormals[polygon];
	}

	__forceinline Int GetNumPolygon() const
	{
		return m_numPolygons;
	}

	__forceinline void GetPolygonIndex(long polygon, Short *indexList) const
	{
		const TriIndex *poly = &m_holder->polygons[polygon];
		*indexList++ = m_parentVerts[poly->I];
		*indexList++ = m_parentVerts[poly->J];
		*indexList++ = m_parentVerts[poly->K];
	}

	__forceinline Bool allocateNeighbors(Int numPolys)
	{
		assert(m_numPolyNeighbors == 0);
		assert(m_polyNeighbors == NULL);
		m_polyNeighbors = new PolyNeighbor[numPolys];
		if (m_polyNeighbors == NULL)
		{
			assert(0);
			return false;
		}
		m_numPolyNeighbors = numPolys;
		return true;
	}

	__forceinline void deleteNeighbors()
	{
		if (m_polyNeighbors)
		{
			delete [] m_polyNeighbors;
			m_polyNeighbors = NULL;
			m_numPolyNeighbors = 0;
		}
		assert(m_numPolyNeighbors == 0);
		assert(m_polyNeighbors == NULL);
	}
};

void W3DShadowGeometryMesh::buildPolygonNeighbors()
{
	Int numPolys;
	Int i, j;
	buildPolygonNormals();
	numPolys = GetNumPolygon();

	if (numPolys == 0)
	{
		if (m_numPolyNeighbors != 0)
			deleteNeighbors();
		return;
	}

	if (numPolys != m_numPolyNeighbors)
	{
		deleteNeighbors();
		if (allocateNeighbors(numPolys) == false)
			return;
	}

	for (i = 0; i < m_numPolyNeighbors; i++)
	{
		m_polyNeighbors[i].myIndex = i;
		for (j = 0; j < 3; j++)
			m_polyNeighbors[i].neighbor[j].neighborIndex = -1;
	}

	for (i = 0; i < m_numPolyNeighbors; i++)
	{
		Short poly[3];
		Short otherPoly[3];
		GetPolygonIndex(i, poly);
		const Vector3 &vNorm = GetPolygonNormal(i);

		for (j = 0; j < m_numPolyNeighbors; j++)
		{
			Int a, b;
			Int index1, index2;
			Int index1Pos[2];
			Int diff1, diff2;

			if (i == j)
				continue;

			GetPolygonIndex(j, otherPoly);
			index1 = -1;
			index2 = -1;
			for (a = 0; a < 3; a++)
				for (b = 0; b < 3; b++)
					if (poly[a] == otherPoly[b])
					{
						if (index1 == -1)
						{
							index1 = poly[a];
							index1Pos[0] = a;
							index1Pos[1] = b;
						}
						else if (index2 == -1)
						{
							diff1 = a - index1Pos[0];
							diff2 = b - index1Pos[1];
							if (((diff1 & 0x80000000) ^ ((abs(diff1) & 2) << 30)) !=
								((diff2 & 0x80000000) ^ ((abs(diff2) & 2) << 30)))
							{
								const Vector3 &vOtherNorm = GetPolygonNormal(j);
								if (fabs(Vector3::Dot_Product(vOtherNorm, vNorm) + 1.0f) <= 0.01f)
									continue;
								index2 = poly[a];
							}
							else
								continue;
						}
						else
						{
							index1 = index2 = -1;
							continue;
						}
					}

			if (index1 != -1 && index2 != -1)
			{
				for (a = 0; a < 3; a++)
					if (m_polyNeighbors[i].neighbor[a].neighborIndex == -1)
					{
						m_polyNeighbors[i].neighbor[a].neighborIndex = j;
						m_polyNeighbors[i].neighbor[a].neighborEdgeIndex[0] = index1;
						m_polyNeighbors[i].neighbor[a].neighborEdgeIndex[1] = index2;
						break;
					}
			}
		}
	}
}
