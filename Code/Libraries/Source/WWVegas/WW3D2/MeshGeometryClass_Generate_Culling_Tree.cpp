// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME5: BFME MeshGeometryClass::Generate_Culling_Tree ABI slice.
// Retail places PolyCount/VertexCount/Poly/Vertex at +0x24/+0x28/+0x2c/+0x30
// and CullTree at +0x90.  The shared MeshGeometry declaration has a shifted
// geometry slice, so retain the original source shape against this local ABI.

#include "always.h"
#include "refcount.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass;

class AABTreeBuilderClass
{
public:
	AABTreeBuilderClass(void);
	~AABTreeBuilderClass(void);
	void Build_AABTree(int polycount, TriIndex *polys, int vertcount, Vector3 *verts);

private:
	char _storage[0x18];
};

class AABTreeClass
{
public:
	AABTreeClass(AABTreeBuilderClass *builder);
	void Set_Mesh(MeshGeometryClass *mesh);

private:
	char _storage[0x1c];
};

class MeshGeometryClass
{
protected:
	void Generate_Culling_Tree(void);

	private:
	char _prefix[0x24];
	int PolyCount;
	int VertexCount;
	ShareBufferClass<TriIndex> *Poly;
	ShareBufferClass<Vector3> *Vertex;
	char _between_vertex_and_tree[0x5c];
	AABTreeClass *CullTree;
};

// ?Generate_Culling_Tree@MeshGeometryClass@@IAEXXZ
void MeshGeometryClass::Generate_Culling_Tree(void)
{
	{
		AABTreeBuilderClass builder;
		builder.Build_AABTree(PolyCount, Poly->Get_Array(), VertexCount, Vertex->Get_Array());

		CullTree = NEW_REF(AABTreeClass, (&builder));
		CullTree->Set_Mesh(this);
	}
}
