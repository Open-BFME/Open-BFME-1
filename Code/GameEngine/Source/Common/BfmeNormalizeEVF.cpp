// Open-BFME7: normalize an Apt hierarchy path, using the root separator when
// the recursive mode-zero path builder produces an empty string.

extern const char g_Rva0107301CEmptyString[];
extern const char g_Rva0107531CBackslash[];

struct BfmeHdrVKI
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

extern BfmeStringPoolVKI *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		other.m_data->m_refCount++;

		BfmeHdrVKI *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);

		m_data = other.m_data;
		return *this;
	}

	BfmeHdrVKI *m_data;
};

void bfmeApplyEVF(void *node, BfmeStrVKI *text, int mode);

void bfmeNormalizeEVF(void *node, BfmeStrVKI *text)
{
	*text = g_Rva0107301CEmptyString;
	bfmeApplyEVF(node, text, 0);
	if (text->m_data->m_length == 0)
		*text = g_Rva0107531CBackslash;
}
