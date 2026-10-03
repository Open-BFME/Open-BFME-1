struct BfmeStringData1284
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

extern "C" char *__cdecl strcpy(char *destination, const char *source);
#pragma intrinsic(strcpy)

// The Apt allocation table at 0x01337A30 is a POINTER to a {allocate, free}
// pair, not the pair itself; only the free slot (+4) is ever called here.
struct BfmeStringPool3AF0
{
	void *(__cdecl *allocate)(unsigned int bytes);
	void (__cdecl *free)(void *storage);
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
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class BfmeString1284
{
public:
	BfmeString1284()
	{
		m_data = (BfmeStringData1284 *)&g_rva012D5298Empty;
		++((BfmeStringData1284 *)&g_rva012D5298Empty)->m_refCount;
	}

	~BfmeString1284()
	{
		BfmeStringData1284 *data = m_data;
		if (--data->m_refCount == 0)
			g_rva01337A30AllocPair->free(data);
	}

	BfmeStringData1284 *m_data;
};

class BfmeStringWriter1284
{
public:
	// LINK: the call target 0x008B8E70 is owned by the gen-asm dump as the
	// zero-argument `?d_008b8e70@@YAXXZ`, but the caller pushes two stack
	// words, so no spelling of a __cdecl reference to that name can both
	// resolve and keep the 139 bytes (a varargs `(...)` declaration mangles
	// the same but changes the call's stack setup -- measured byte mismatch).
	// Needs a ledger repoint of 0x008B8E70 to a two-argument __cdecl name.
	void bfmeBuildString1284(BfmeString1284 *result, int value);
	void bfmeWriteString1284(char *destination, int value);
};

void BfmeStringWriter1284::bfmeWriteString1284(char *destination, int value)
{
	BfmeString1284 result;
	bfmeBuildString1284(&result, value);
	strcpy(destination, result.m_data->m_text);
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
