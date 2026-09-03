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

class Rva00727380TaintBuf
{
public:
	~Rva00727380TaintBuf();

private:
	unsigned char m_pad00[0x18];
	void *m_18;
	TexHandle m_1C;
	unsigned char m_pad20[0x38 - 0x20];
	void *m_38;
	void *m_3C;
	unsigned char m_pad40[0x44 - 0x40];
	_STL::set<int> m_dirty;
};

// ??1Rva00727380TaintBuf@@QAE@XZ
Rva00727380TaintBuf::~Rva00727380TaintBuf()
{
	if (m_1C.m_p)
		m_1C.Clear();
	if (m_18)
		operator delete[](m_18);
	m_18 = 0;
	if (m_38)
		operator delete[](m_38);
	m_38 = 0;
	if (m_3C)
		operator delete[](m_3C);
	m_3C = 0;
}
