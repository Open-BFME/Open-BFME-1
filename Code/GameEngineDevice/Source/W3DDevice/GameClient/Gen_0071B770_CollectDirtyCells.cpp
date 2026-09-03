// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0071B770. Walk the two fog byte planes and collect changed cells.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TexHandle
{
public:
	TexHandle() : m_p(0) {}
	~TexHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}
	TextureBaseClass *m_p;
};

class BfmeListHeader
{
public:
	void *m_unused;
	BfmeListHeader *m_parent;
	BfmeListHeader *m_right;
	BfmeListHeader *m_left;
};

class BfmeShroudList
{
public:
	void bfmeErase(BfmeListHeader *node);
	BfmeListHeader *m_header;
	unsigned int m_size;
};

class W3DShroud
{
public:
	void collectDirtyCells();

	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	float m_cellWidth;
	float m_cellHeight;
	void *m_shroudData;
	TexHandle m_dstTexture;
	void *m_20;
	void *m_24;
	int m_shroudFilter;
	int m_2c;
	int m_30;
	unsigned char m_34;
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;
	unsigned char m_pad37;
	unsigned char *m_38;
	unsigned char *m_3c;
	unsigned char m_40;
	unsigned char m_pad41[3];
	_STL::set<int> m_dirty;
};

void W3DShroud::collectDirtyCells()
{
	{
		BfmeShroudList *tree = (BfmeShroudList *)&m_dirty;
		if (tree->m_size != 0)
		{
			tree->bfmeErase(tree->m_header->m_parent);
			tree->m_header->m_right = tree->m_header;
			tree->m_header->m_parent = 0;
			tree->m_header->m_left = tree->m_header;
			tree->m_size = 0;
		}
	}

	unsigned char *a = m_3c;
	unsigned char *b = m_38;
	int cell;
	int y = 0;
	cell = 0;
	for (; y < m_numCellsY; ++y)
	{
		for (int x = 0; x < m_numCellsX; ++x, ++a, ++b, ++cell)
		{
			if (*a != *b)
				m_dirty.insert(cell);
		}
	}
	m_40 = 1;
}
