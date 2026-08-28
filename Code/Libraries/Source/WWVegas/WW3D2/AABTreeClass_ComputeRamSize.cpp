// Open-BFME5: AABTreeClass::Compute_Ram_Size reconstructed from retail
// RVA 0x0096A630.  The real AAB tree node is eight dwords and the object
// layout is 0x1c bytes, so the source-level formula matches the retail LEAs.

struct AABTreeCullNode
{
	unsigned int m_words[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
class AABTreeClass
{
public:
	int Compute_Ram_Size();

	char m_base[8];
	int NodeCount;
	void *Nodes;
	int PolyCount;
	void *PolyIndices;
	void *Mesh;
};

int AABTreeClass::Compute_Ram_Size()
{
	return NodeCount * sizeof( AABTreeCullNode ) +
		PolyCount * sizeof( int ) +
		sizeof( AABTreeClass );
}
