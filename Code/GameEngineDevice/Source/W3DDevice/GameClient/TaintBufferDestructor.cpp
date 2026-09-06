// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
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

class TaintBuffer
{
public:
	~TaintBuffer();

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

// ??1TaintBuffer@@QAE@XZ
TaintBuffer::~TaintBuffer()
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
