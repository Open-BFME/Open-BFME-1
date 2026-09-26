// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

struct Rva00899770Block
{
	unsigned short m_ref;
	unsigned short m_length;
	char m_padding[4];
	char m_text[1];
};

extern Rva00899770Block g_default012D5298;

struct Rva00899770Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva00899770Pool *g_pool01337A30;

struct Rva00899770String
{
	Rva00899770Block *m_block;

	Rva00899770String()
	{
		m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	~Rva00899770String()
	{
		Rva00899770Block *block = m_block;
		if (--block->m_ref == 0)
			g_pool01337A30->free(block);
	}
};

struct BfmeStr1233
{
	Rva00899770Block *m_block;
};

class BfmeE1233
{
public:
	void bfmeName1233(BfmeStr1233 *a);
};

class Rva00899770
{
public:
	void exportString(char *out);
};

void Rva00899770::exportString(char *out)
{
	Rva00899770String value;
	((BfmeE1233 *)this)->bfmeName1233((BfmeStr1233 *)&value);
	strcpy(out, (const char *)value.m_block->m_text);
}
