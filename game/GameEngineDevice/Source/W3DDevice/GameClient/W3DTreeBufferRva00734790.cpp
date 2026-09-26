// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DTreeBuffer method at retail 0x00734790: counts a tree's +0xD4 countdown down, forwards the remaining
// share to its two render objects, and removes the tree once the count ends or the tree is flagged.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

void Rva00739900Forward(void *object, Real value);

struct Rva00734790TypeData
{
	unsigned char m_pad00[0x4c];
	UnsignedInt m_duration;
};

struct Rva00734790Type
{
	unsigned char m_pad00[0x20];
	const Rva00734790TypeData *m_data;
	unsigned char m_pad24[0x5c - 0x24];
};

struct Rva00734790Tree
{
	unsigned char m_pad00[0x40];
	Int m_treeType;
	unsigned char m_pad44[0x80 - 0x44];
	Int m_field80;
	unsigned char m_pad84[0xc4 - 0x84];
	bool m_flagc4;
	unsigned char m_padc5[0xd4 - 0xc5];
	UnsignedInt m_fieldd4;
	void *m_fieldd8;
	void *m_fielddc;
	unsigned char m_pade0[0xe8 - 0xe0];
};

class W3DTreeBuffer
{
public:
	void removeTreeAtIndex(Int index);
	void rva00734790(Int index);

private:
	unsigned char m_pad0000[0x1b0];
	Rva00734790Tree m_trees[12000];
	Int m_numTrees;
	unsigned char m_pad2a7cb4[0x2a7cbc - 0x2a7cb4];
	Rva00734790Type m_treeTypes[64];
};

// ?rva00734790@W3DTreeBuffer@@QAEXH@Z
void W3DTreeBuffer::rva00734790(Int index)
{
	if (index >= m_numTrees)
		return;
	Int type = m_trees[index].m_treeType;
	if (type < 0)
		return;
	if (m_trees[index].m_flagc4 || m_trees[index].m_field80 != 0) {
		removeTreeAtIndex(index);
		return;
	}
	--m_trees[index].m_fieldd4;
	Real fraction = (Real)m_trees[index].m_fieldd4 / (Real)m_treeTypes[type].m_data->m_duration;
	if (m_trees[index].m_fieldd8 != 0)
		Rva00739900Forward(m_trees[index].m_fieldd8, fraction);
	if (m_trees[index].m_fielddc != 0)
		Rva00739900Forward(m_trees[index].m_fielddc, 1.0f - fraction);
	if (m_trees[index].m_fieldd4 == 0)
		removeTreeAtIndex(index);
}
