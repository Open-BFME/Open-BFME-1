class BfmeStrDataAR
{
public:
	unsigned char m_bfmeHeadAR[8];
	char m_bfmeTextAR[1];
};

extern const char g_bfmeEmptyAscii[];

// The comparator reaches MSVCR71's case-insensitive compare through the import
// slot at 0x0135933C; targets/game/reverse/symbols.csv pins that slot as
// __imp___stricmp, so the reference must be spelled _stricmp (dllimport) to
// land on it -- the placeholder g_lookup named nothing that existed.
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char *, const char *);

class BfmeStrAR
{
public:
	const char *bfmeStrAR(void) const
	{
		return m_bfmeDataAR ? m_bfmeDataAR->m_bfmeTextAR : g_bfmeEmptyAscii;
	}

	BfmeStrDataAR *m_bfmeDataAR;
};

class BfmeHolderAR
{
public:
	BfmeStrAR *m_bfmeStrAR;
};

bool __stdcall bfmeLessAR(void *left, BfmeHolderAR *right)
{
	return _stricmp((const char *)left, right->m_bfmeStrAR->bfmeStrAR()) < 0;
}
