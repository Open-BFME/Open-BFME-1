class BfmeStrDataAR
{
public:
	unsigned char m_bfmeHeadAR[8];
	char m_bfmeTextAR[1];
};

extern const char g_bfmeEmptyAscii[];
extern void *(__cdecl *g_lookup)(void *, void *);

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
	return (int)g_lookup(left, (void *)right->m_bfmeStrAR->bfmeStrAR()) < 0;
}
