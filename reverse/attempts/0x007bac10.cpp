// ?addFreeEdge@Rva007BAC10Owner@@QAEXHPAUPolyNeighbor@@PBF@Z
// partial score=0.09 date=2026-09-21
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include

// Neighbour 0x007BD430 (Rva007BD430BuildPolygonNeighbors.cpp) establishes this
// TU-local PolygonHolder/TriIndex/NeighborEdge/PolyNeighbor layout for the W3D
// shadow-geometry mesh family; this body walks the same record array (stride
// 0x34, embedded mesh sub-object at +0x14) and appends one triangle's "free"
// (non-shared) edge into per-polygon growable buffers at this+0x4180, with
// per-polygon counts at this+0x4400.

typedef int Int;
typedef short Short;
typedef unsigned char Byte;
typedef unsigned short UnsignedShort;

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

struct Rva007BAC10Mesh
{
	PolygonHolder *m_holder;
	Byte m_pad04[4];
	const void *m_verts;
	Byte m_pad0c[4];
	void *m_polygonNormals;
	Byte m_pad14[8];
	Int m_numPolygons;
	UnsignedShort *m_parentVerts;
};

class Rva007BAC10Owner
{
public:
	void addFreeEdge(Int polyIndex, PolyNeighbor *neighbor, const Short *otherIndex);
};

void Rva007BAC10Owner::addFreeEdge(Int polyIndex, PolyNeighbor *neighbor, const Short *otherIndex)
{
	Byte *self = (Byte *)this;
	Byte *meshArray = *(Byte **)(self + 0x6c);
	Rva007BAC10Mesh *mesh = (Rva007BAC10Mesh *)(meshArray + polyIndex * 0x34 + 0x14);

	Short target = *otherIndex;
	Int slot = 0;
	{
		Int i;
		for (i = 0; i < 3; ++i)
		{
			if (neighbor->neighbor[i].neighborIndex == target)
			{
				slot = i;
				break;
			}
		}
	}

	Short idx = neighbor->myIndex;
	PolygonHolder *holder = mesh->m_holder;
	const TriIndex *polys = holder->polygons;
	UnsignedShort *parentVerts = mesh->m_parentVerts;
	const TriIndex *tri = &polys[idx];

	UnsignedShort gJ = parentVerts[tri->J];
	UnsignedShort gI = parentVerts[tri->I];
	UnsignedShort gK = parentVerts[tri->K];

	NeighborEdge *edge = &neighbor->neighbor[slot];
	Short idx0 = edge->neighborEdgeIndex[0];
	Short idx1 = edge->neighborEdgeIndex[1];

	UnsignedShort outA, outB;
	if ((Short)gI != idx0 && (Short)gI != idx1)
	{
		outA = gJ;
		outB = gK;
	}
	else if ((Short)gJ == idx0 || (Short)gJ == idx1)
	{
		outA = gI;
		outB = gJ;
	}
	else
	{
		outA = gK;
		outB = gI;
	}

	UnsignedShort **buffers = (UnsignedShort **)(self + 0x4180);
	Short *counts = (Short *)(self + 0x4400);

	UnsignedShort *buf = buffers[polyIndex];
	buf[counts[polyIndex]] = outA;
	counts[polyIndex]++;

	buf = buffers[polyIndex];
	buf[counts[polyIndex]] = outB;
	counts[polyIndex]++;
}
