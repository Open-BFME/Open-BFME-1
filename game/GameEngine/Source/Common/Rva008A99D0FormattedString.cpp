// Open-BFME5 conversion.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" int __cdecl vsprintf(char *buffer, const char *format, char *args);

struct Rva008A99D0Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

// The pool pointer at VA 0x01337A30 has one canonical global; this TU keeps
// its own view type of the {void *unused; void (*free)(void *);} table and
// casts at each use.
struct BfmeStringPool3AF0;

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

static __forceinline Rva008A99D0Pool *localPool()
{
	return (Rva008A99D0Pool *)g_rva01337A30AllocPair;
}

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
			localPool()->free(block);
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
		localPool()->free(old);
	object->m_text.m_block = text.m_block;
}
