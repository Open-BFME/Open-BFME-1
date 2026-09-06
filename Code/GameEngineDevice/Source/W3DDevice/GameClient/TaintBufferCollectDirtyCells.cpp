// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x007279B0: clear the dirty-cell tree and collect changed taint cells.
//
// TaintBuffer is a descriptive name, not a recovered EA one.  What the exe
// proves is the subject: the GlobalData FieldParse table at 0x00C77018 maps the
// INI keys TaintOn to +0xCF5, TaintAlpha to +0xCA0 and TaintColor to +0xC88
// (reverse/field_names.csv), every body in this family gates on TheWritableGlobalData
// ->m_taintOn, TaintBuffer::init drives TheTaintManager -- the literal at 0x79060 --
// and the shaders it feeds are shaders\terraintaint.pso and terraintaint2.pso.
// The object itself is the render-side cell buffer for that overlay: a cell grid
// sized from WorldHeightMap, a destination texture it reacquires, and a dirty-cell
// set, which is the same shape W3DShroud has for the shroud.  No __FILE__ literal
// reaches this code run, so the retail class name is still unknown.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
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

class TaintBuffer
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

// ?collectDirtyCells@TaintBuffer@@QAEXXZ
void TaintBuffer::collectDirtyCells()
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
