// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MeshGeometryClass::Intersect_OBBox, retail 0x00927920, 34 bytes.
//
// The Zero Hour body. AABTreeClass::Intersect_OBBox is one line, so MSVC
// inlines it and the cull-tree arm becomes a direct call to
// Intersect_OBBox_Recursive with the root node read from tree+0x0C; the
// brute-force arm is a tail jump because its result is returned unchanged.

class OBBoxIntersectionTestClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
class AABTreeClass
{
public:
	struct CullNodeStruct;

	bool Intersect_OBBox(OBBoxIntersectionTestClass &test)
	{
		return Intersect_OBBox_Recursive(RootNode, test);
	}

private:
	bool Intersect_OBBox_Recursive(CullNodeStruct *node, OBBoxIntersectionTestClass &test);

	unsigned char m_unmodelled_000[0xc];
	CullNodeStruct *RootNode;			// tree+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
public:
	bool Intersect_OBBox(OBBoxIntersectionTestClass &boxtest);

private:
	bool intersect_obbox_brute_force(OBBoxIntersectionTestClass &boxtest);

	unsigned char m_unmodelled_000[0x90];
	AABTreeClass *CullTree;				// this+0x90
};

// ?Intersect_OBBox@MeshGeometryClass@@QAE_NAAVOBBoxIntersectionTestClass@@@Z
bool MeshGeometryClass::Intersect_OBBox(OBBoxIntersectionTestClass &boxtest)
{
	bool hit = false;

	if (CullTree)
	{
		hit = CullTree->Intersect_OBBox(boxtest);
	}
	else
	{
		hit = intersect_obbox_brute_force(boxtest);
	}

	return hit;
}
