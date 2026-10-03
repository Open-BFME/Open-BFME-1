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
// The Apt operator-new/delete pair cell at 0x01337A30 is defined once, as
// ?g_rva01337A30AllocPair, in game/Libraries/Source/Apt/Apt.cpp; this TU
// declares that spelling and casts at each use to its own pool view.
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

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
			((BfmeStringPoolVKI *)g_rva01337A30AllocPair)->free(data);
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

// Native VA 0x01337864 is one zero-filled .data callback cell (the installer at
// bfmeInstallHandlersVB stores slot 12 here); address-derived name, no EA name proven.
void (__cdecl *g_rva01337864)(const char *a, const char *b) = 0;

char __stdcall bfmeReportEAW(void *unused, BfmeStrEAW *other, BfmeHostEAW *host)
{
	BfmeStrEAW text;

	((Rva8CD130Value *)host)->getName((Rva8CD130String *)&text);

	g_rva01337864(other->strEAW(), text.strEAW());

	return 1;
}
