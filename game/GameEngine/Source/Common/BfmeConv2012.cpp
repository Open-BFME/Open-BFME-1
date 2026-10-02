struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
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
extern BfmeStringPoolVKI *g_bfmeStringPool1284;

class BfmeStrEAW
{
public:
	BfmeStrEAW()
	{
		((BfmeStringData3AF0 *)&g_rva012D5298Empty)->m_refCount++;

		m_data = (BfmeStringData3AF0 *)&g_rva012D5298Empty;
	}
	~BfmeStrEAW()
	{
		BfmeStringData3AF0 *data = m_data;

		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	const char *strEAW() const
	{
		return (const char *)m_data + 8;
	}

	BfmeStringData3AF0 *m_data;
};

class BfmeHostEAW;

class Rva8CD130String;

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *out);
};

extern void (__cdecl *g_bfmeCompareEAW)(const char *a, const char *b);

char __stdcall bfmeReportEAW(void *unused, BfmeStrEAW *other, BfmeHostEAW *host)
{
	BfmeStrEAW text;

	((Rva8CD130Value *)host)->getName((Rva8CD130String *)&text);

	g_bfmeCompareEAW(other->strEAW(), text.strEAW());

	return 1;
}
