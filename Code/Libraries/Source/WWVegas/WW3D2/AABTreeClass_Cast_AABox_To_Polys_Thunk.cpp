// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the AAB-tree AA-box polygon cast to clean C++.

typedef unsigned short uint16;
typedef unsigned int uint32;

struct Vector3
{
	float x;
	float y;
	float z;
};

struct TriIndex
{
	uint16 index[3];
	const uint16 &operator[](int position) const { return index[position]; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/tri.h
class TriClass
{
public:
	void Compute_Normal();
	Vector3 *N;
	const Vector3 *V[3];
};

class AABoxCollisionTestData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/coltest.h
class AABoxCollisionTestClass
{
public:
	unsigned char m_unreconstructed_00[4];
	AABoxCollisionTestData *getCollisionData()
	{
		return reinterpret_cast<AABoxCollisionTestData *>(m_unreconstructed_00 + 4);
	}
};

namespace CollisionMath
{
	bool Collide(AABoxCollisionTestData &, TriClass &);
}

template <class T> class VectorStorage
{
private:
	unsigned char m_unreconstructed_00[0x0C];
public:
	T *data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
private:
	unsigned char m_unreconstructed_00[0x2C];
public:
	VectorStorage<TriIndex> *polygons;
	VectorStorage<Vector3> *vertices;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
class AABTreeClass
{
private:
	struct CullNodeStruct
	{
		Vector3 minimum;
		Vector3 maximum;
		uint32 frontOrPolygon0;
		uint32 backOrPolygonCount;
		int Get_Poly0() { return frontOrPolygon0 & 0x7FFFFFFF; }
		int Get_Poly_Count() { return backOrPolygonCount; }
	};

	unsigned char m_unreconstructed_00[0x14];
	uint32 *PolyIndices;
	MeshGeometryClass *Mesh;

	bool Cast_AABox_To_Polys(CullNodeStruct *, AABoxCollisionTestClass &);
};

// ?Cast_AABox_To_Polys@AABTreeClass@@AAE_NPAUCullNodeStruct@1@AAVAABoxCollisionTestClass@@@Z
bool AABTreeClass::Cast_AABox_To_Polys(CullNodeStruct *node, AABoxCollisionTestClass &boxTest)
{
	int polygon0 = node->Get_Poly0();
	int polygonCount = node->Get_Poly_Count();
	if (polygonCount > 0)
	{
		const Vector3 *locations = Mesh->vertices->data;
		const TriIndex *polygonVertices = Mesh->polygons->data;
		for (int polygonCounter = 0; polygonCounter < polygonCount; ++polygonCounter)
		{
			int polygonIndex = PolyIndices[polygon0 + polygonCounter];
			TriClass triangle;
			triangle.V[0] = &locations[polygonVertices[polygonIndex][0]];
			triangle.V[1] = &locations[polygonVertices[polygonIndex][1]];
			triangle.V[2] = &locations[polygonVertices[polygonIndex][2]];
			Vector3 normal;
			triangle.N = &normal;
			triangle.Compute_Normal();
			if (CollisionMath::Collide(*boxTest.getCollisionData(), triangle))
				return true;
		}
	}
	return false;
}
