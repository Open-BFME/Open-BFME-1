// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

struct Rva00899770Block
{
	unsigned short m_ref;
	unsigned short m_length;
	char m_padding[4];
	char m_text[1];
};

// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU keeps its own local view of the block and casts at each use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;

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
		m_block = (Rva00899770Block *)&g_rva012D5298Empty;
		++((Rva00899770Block *)&g_rva012D5298Empty)->m_ref;
	}

	~Rva00899770String()
	{
		Rva00899770Block *block = m_block;
		if (--block->m_ref == 0)
			g_pool01337A30->free(block);
	}
};

class Rva8CD130String;

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *a);
};

class Rva00899770
{
public:
	void exportString(char *out);
};

void Rva00899770::exportString(char *out)
{
	Rva00899770String value;
	((Rva8CD130Value *)this)->getName((Rva8CD130String *)&value);
	strcpy(out, (const char *)value.m_block->m_text);
}
