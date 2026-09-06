class BfmeStrDataAQ
{
public:
	unsigned char m_bfmeHeadAQ[8];
	char m_bfmeTextAQ[1];
};

extern const char g_bfmeEmptyAscii[];
extern void *(__cdecl *g_lookup)(void *, void *);

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
	return (int)g_lookup((void *)left->m_bfmeStrAQ->bfmeStrAQ(), right) < 0;
}
