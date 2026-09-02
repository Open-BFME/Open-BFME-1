// ?collectDirtyCells@W3DShroud@@QAEXXZ
// partial score=0.7 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x0071B770. Walk the two fog byte planes; on a mismatch insert the
// cell into the dirty set at +0x44, then set the dirty flag at +0x40.

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
	int z = 0;
	_STL::set<int> *tree = &m_dirty;
	if (tree->size() != (unsigned)z)
		tree->clear();

	unsigned char *a = m_38;
	unsigned char *b = m_3c;
	for (int y = 0; y < m_numCellsY; ++y)
	{
		for (int x = 0; x < m_numCellsX; ++x, ++a, ++b)
		{
			if (*a != *b)
				tree->insert(x + y * m_numCellsX);
		}
	}
	m_40 = 1;
}
