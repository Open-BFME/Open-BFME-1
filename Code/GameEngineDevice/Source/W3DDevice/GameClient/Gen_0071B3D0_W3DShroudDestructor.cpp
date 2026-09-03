// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

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
	void Clear()
	{
		if (m_p)
		{
			m_p->Release_Ref();
			m_p = 0;
		}
	}
	TextureBaseClass *m_p;
};

void operator delete[](void *);

class W3DShroud
{
public:
	~W3DShroud();

private:
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
	void *m_38;
	void *m_3c;
	unsigned char m_40;
	unsigned char m_pad41[3];
	_STL::set<int> m_dirty;
};

W3DShroud::~W3DShroud()
{
	if (m_dstTexture.m_p)
		m_dstTexture.Clear();
	if (m_shroudData)
		operator delete[](m_shroudData);
	m_shroudData = 0;
	if (m_38)
		operator delete[](m_38);
	m_38 = 0;
	if (m_3c)
		operator delete[](m_3c);
	m_3c = 0;
	m_34 = 0;
}
