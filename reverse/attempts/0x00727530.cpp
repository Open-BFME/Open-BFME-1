// ??0Rva00727530TaintBuf@@QAE@XZ
// partial score=0.7 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00727530: constructor for the taint overlay buffer.  Stores 10.0f
// at +0x10/+0x14, copies GlobalData TaintAlpha to +0x36, and allocates a
// 0x14-byte circular sentinel at +0x44.  Texture pointer at +0x1C has a
// destructor so the ctor registers SEH around the throwing allocate.

class GlobalData
{
public:
	unsigned char m_pad[0xCA0];
	unsigned char m_taintAlpha;
};

extern GlobalData *TheWritableGlobalData;

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

struct TerrainTexPtr
{
	TextureBaseClass *p;
	~TerrainTexPtr()
	{
		if (p)
			p->Release_Ref();
	}
};

class Rva00727530TaintBuf
{
public:
	Rva00727530TaintBuf();

private:
	int m_00, m_04, m_08, m_0C;
	float m_10, m_14;
	int m_18;
	TerrainTexPtr m_1C;
	int m_20, m_24, m_28, m_2C, m_30;
	unsigned char m_34, m_35, m_36;
	int m_38, m_3C;
	unsigned char m_40;
	void *m_44;
	int m_48;
};

Rva00727530TaintBuf::Rva00727530TaintBuf()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 10.0f;
	m_14 = 10.0f;
	m_18 = 0;
	m_1C.p = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 4;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_35 = 1;
	m_36 = TheWritableGlobalData->m_taintAlpha;
	m_38 = 0;
	m_3C = 0;
	m_40 = 1;
	m_44 = 0;
	void *node = operator new(0x14);
	m_44 = node;
	m_48 = 0;
	*(unsigned char *)m_44 = 0;
	*((int *)m_44 + 1) = 0;
	*((void **)m_44 + 2) = m_44;
	*((void **)m_44 + 3) = m_44;
}
