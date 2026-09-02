// ??1Rva00727380TaintBuf@@QAE@XZ
// partial score=0.75 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00727380: destructor of the taint overlay buffer.  Releases the
// texture at +0x1C, delete[]s the three buffers at +0x18/+0x38/+0x3C, then
// runs the embedded list dtor at +0x44.  Texture member dtor re-runs on +0x1C.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

extern "C" void Gen00881EF0(void *);

struct TerrainTexPtr
{
	TextureBaseClass *p;
	~TerrainTexPtr()
	{
		if (p)
			p->Release_Ref();
	}
};

struct TaintList
{
	void *node;
	int size;
	~TaintList();
};

class Rva00727380TaintBuf
{
public:
	~Rva00727380TaintBuf();

private:
	unsigned char m_pad00[0x18];
	void *m_18;
	TerrainTexPtr m_1C;
	unsigned char m_pad20[0x38 - 0x20];
	void *m_38;
	void *m_3C;
	unsigned char m_pad40[0x44 - 0x40];
	TaintList m_list;
};

Rva00727380TaintBuf::~Rva00727380TaintBuf()
{
	if (m_1C.p)
	{
		m_1C.p->Release_Ref();
		m_1C.p = 0;
	}
	if (m_18)
	{
		Gen00881EF0(m_18);
		m_18 = 0;
	}
	if (m_38)
	{
		Gen00881EF0(m_38);
		m_38 = 0;
	}
	if (m_3C)
	{
		Gen00881EF0(m_3C);
		m_3C = 0;
	}
}
