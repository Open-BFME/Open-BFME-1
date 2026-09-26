// ?d_005efb10@@YAXXZ
// Color-module constructor recovered from the update layout and matched helper.
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

extern "C" char g_bfmeV1189[];
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva005E5E60Sys;

struct Rva005EFB10Color
{
	float red;
	float green;
	float blue;
};

struct Rva005EFB10ColorKey
{
	Rva005EFB10Color color;
	unsigned int frame;
	Rva005EFB10ColorKey(void)
	{
		color.blue = 0.0f;
		color.green = 0.0f;
		color.red = 0.0f;
		frame = 0;
	}
};

struct Rva005EFB10Quad
{
	Rva005EFB10Quad(void)
	{
		m08 = 0;
		m04 = 0;
		m00 = 0;
		m0c = 0;
	}
	unsigned int m00;
	unsigned int m04;
	unsigned int m08;
	unsigned int m0c;
};

class BfmeBase1189
{
public:
	BfmeBase1189(void) { m_bfme00 = g_bfmeV1189; }
	char *volatile m_bfme00;
};

class BfmeA1189 : public BfmeBase1189
{
public:
	BfmeA1189(void);
	Rva005EFB10ColorKey m_colorKey[8];
	float m_colorScale;
};

// ??0BfmeA1189@@QAE@XZ present-unmatched
BfmeA1189::BfmeA1189(void)
{
	m_colorScale = 0.0f;
}

class BfmeHostEN
{
public:
	void bfmeStepEN();
};

class __declspec(novtable) Rva005EFB10Part0
{
public:
	Rva005EFB10Part0(void *owner)
		: m_system(owner)
	{
	}
	virtual void unusedVirtual();
	void *m_system;
};

class PolymorphicVptrBase01073760
{
public:
	virtual void unusedVirtual();
	virtual ~PolymorphicVptrBase01073760() {}
};

struct Rva005EFB10SourceImage
{
	unsigned char m_prefix[0x0c];
	Rva005EFB10ColorKey m_colorKey[8];
	float m_colorScale;
};

class Rva005EFB10
	: public Rva005EFB10Part0,
	  public PolymorphicVptrBase01073760,
	  public BfmeA1189
{
public:
	Rva005EFB10(Rva005E5E60Sys &sys, const void *source);
	Rva005EFB10Color m_color;
	Rva005EFB10Color m_colorRate;
	int m_colorTargetKey;
};

Rva005EFB10::Rva005EFB10(Rva005E5E60Sys &sys, const void *source)
	: Rva005EFB10Part0(&sys), PolymorphicVptrBase01073760(), BfmeA1189()
{
	*(volatile unsigned int *)((unsigned char *)this + 0x0c) = 0x01112b3c;
	*(volatile unsigned int *)this = 0x01112b54;
	*(volatile unsigned int *)((unsigned char *)this + 0x08) = 0x01112b50;
	_ReadWriteBarrier();
	const Rva005EFB10SourceImage *sourceImage =
		(const Rva005EFB10SourceImage *)source;
	m_colorKey[0] = sourceImage->m_colorKey[0];
	m_colorKey[1] = sourceImage->m_colorKey[1];
	m_colorKey[2] = sourceImage->m_colorKey[2];
	m_colorKey[3] = sourceImage->m_colorKey[3];
	m_colorKey[4] = sourceImage->m_colorKey[4];
	m_colorKey[5] = sourceImage->m_colorKey[5];
	m_colorKey[6] = sourceImage->m_colorKey[6];
	m_colorKey[7] = sourceImage->m_colorKey[7];
	m_colorScale = sourceImage->m_colorScale;
	m_color = m_colorKey[0].color;
	m_colorTargetKey = 1;
	((BfmeHostEN *)this)->bfmeStepEN();
}
