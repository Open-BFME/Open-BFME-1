// Open-BFME5 conversion.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" int __cdecl vsprintf(char *buffer, const char *format, char *args);

struct Rva008A99D0Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva008A99D0Pool *g_rva008A99D0Pool;

struct Rva008A99D0Block
{
	unsigned short m_ref;
};

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text);
	__forceinline ~BfmeStrVKI()
	{
		Rva008A99D0Block *block = m_block;
		if (--block->m_ref == 0)
			g_rva008A99D0Pool->free(block);
	}

	Rva008A99D0Block *m_block;
};

struct Rva008A99D0Object
{
	char m_padding00[8];
	BfmeStrVKI m_text;
};

extern char g_rva008A99D0Buffer[];

void rva008A99D0FormattedString(Rva008A99D0Object *object,
	const char *format, ...)
{
	vsprintf(g_rva008A99D0Buffer, format,
		(char *)(&format + 1));
	BfmeStrVKI text(g_rva008A99D0Buffer);

	++text.m_block->m_ref;
	Rva008A99D0Block *old = object->m_text.m_block;
	if (--old->m_ref == 0)
		g_rva008A99D0Pool->free(old);
	object->m_text.m_block = text.m_block;
}
