// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class GlobalData
{
	unsigned char m_pad[0xCA0];

public:
	unsigned char m_taintAlpha;
};

extern GlobalData *TheWritableGlobalData;

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

class Rva00727530TaintBuf
{
public:
	Rva00727530TaintBuf();

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	void *m_18;
	TexHandle m_1C;
	void *m_20;
	void *m_24;
	int m_28;
	int m_2C;
	int m_30;
	unsigned char m_34;
	unsigned char m_35;
	unsigned char m_36;
	unsigned char m_pad37;
	void *m_38;
	void *m_3C;
	unsigned char m_40;
	unsigned char m_pad41[3];
	_STL::set<int> m_dirty;
};

// ??0Rva00727530TaintBuf@@QAE@XZ
Rva00727530TaintBuf::Rva00727530TaintBuf()
	: m_00(0)
	, m_04(0)
	, m_08(0)
	, m_0C(0)
	, m_10(10.0f)
	, m_14(10.0f)
	, m_18(0)
	, m_20(0)
	, m_24(0)
	, m_28(4)
	, m_2C(0)
	, m_30(0)
	, m_34(0)
	, m_35(1)
	, m_36(TheWritableGlobalData->m_taintAlpha)
	, m_38(0)
	, m_3C(0)
	, m_40(1)
{
}
