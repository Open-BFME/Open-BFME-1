class BfmeStrDataAQ
{
public:
	unsigned char m_bfmeHeadAQ[8];
	char m_bfmeTextAQ[1];
};

extern const char g_bfmeEmptyAscii[];

// The comparator reaches MSVCR71's case-insensitive compare through the import
// slot at 0x0135933C; targets/game/reverse/symbols.csv pins that slot as
// __imp___stricmp, but retail imports msvcr71!_strcmpi (import_binding.py), so the reference must be spelled _strcmpi (dllimport) to
// land on it -- the placeholder g_lookup named nothing that existed.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class BfmeStrAQ
{
public:
	const char *bfmeStrAQ(void) const
	{
		return m_bfmeDataAQ ? m_bfmeDataAQ->m_bfmeTextAQ : g_bfmeEmptyAscii;
	}

	BfmeStrDataAQ *m_bfmeDataAQ;
};

class BfmeHolderAQ
{
public:
	BfmeStrAQ *m_bfmeStrAQ;
};

bool __stdcall bfmeLessAQ(BfmeHolderAQ *left, void *right)
{
	return _strcmpi(left->m_bfmeStrAQ->bfmeStrAQ(), (const char *)right) < 0;
}
