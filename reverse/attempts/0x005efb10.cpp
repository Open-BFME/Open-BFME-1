// ?d_005efb10@@YAXXZ
// partial score=0.2 date=2026-09-22
// Probe for the three-subobject color-module constructor at retail 0x005EFB10.
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct Rva005E5E60Sys;

struct Rva005EFB10Quad
{
	unsigned int m00;
	unsigned int m04;
	unsigned int m08;
	unsigned int m0c;
};

class BfmeA1189
{
public:
	BfmeA1189();
	unsigned int m_base;
	Rva005EFB10Quad m_quad[8];
	unsigned int m_field84;
};

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

class Rva005EFB10Part1
{
public:
	Rva005EFB10Part1()
	{
		*(volatile unsigned int *)this = 0x01073760;
	}
	virtual void unusedVirtual();
};

struct Rva005EFB10SourceImage
{
	unsigned char m_prefix[0x0c];
	Rva005EFB10Quad m_quad[8];
	unsigned int m_field8c;
};

class Rva005EFB10
	: public Rva005EFB10Part0,
	  public Rva005EFB10Part1,
	  public BfmeA1189
{
public:
	Rva005EFB10(Rva005E5E60Sys &sys, const void *source);

	unsigned int m_position[3];
	unsigned int m_velocity[3];
	int m_index;
};

Rva005EFB10::Rva005EFB10(Rva005E5E60Sys &sys, const void *source)
	: Rva005EFB10Part0(&sys), Rva005EFB10Part1(), BfmeA1189()
{
	*(volatile unsigned int *)((unsigned char *)this + 0x0c) = 0x01112b3c;
	*(volatile unsigned int *)this = 0x01112b54;
	*(volatile unsigned int *)((unsigned char *)this + 0x08) = 0x01112b50;
	const Rva005EFB10SourceImage *sourceImage =
		(const Rva005EFB10SourceImage *)source;
	m_quad[0] = sourceImage->m_quad[0];
	m_quad[1] = sourceImage->m_quad[1];
	m_quad[2] = sourceImage->m_quad[2];
	m_quad[3] = sourceImage->m_quad[3];
	m_quad[4] = sourceImage->m_quad[4];
	m_quad[5] = sourceImage->m_quad[5];
	m_quad[6] = sourceImage->m_quad[6];
	m_quad[7] = sourceImage->m_quad[7];
	m_field84 = sourceImage->m_field8c;
	const unsigned int *base = (const unsigned int *)((const unsigned char *)this + 0x0c);
	m_position[0] = base[0];
	m_position[1] = base[1];
	m_position[2] = base[2];
	m_index = 1;
	((BfmeHostEN *)this)->bfmeStepEN();
}
