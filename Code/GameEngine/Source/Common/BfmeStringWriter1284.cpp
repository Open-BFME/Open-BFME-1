struct BfmeStringData1284
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

extern "C" char *__cdecl strcpy(char *destination, const char *source);
#pragma intrinsic(strcpy)

struct BfmeStringPool1284
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringData1284 g_bfmeDefaultString1284;
extern BfmeStringPool1284 *g_bfmeStringPool1284;

class BfmeString1284
{
public:
	BfmeString1284()
	{
		m_data = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
	}

	~BfmeString1284()
	{
		BfmeStringData1284 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData1284 *m_data;
};

class BfmeStringWriter1284
{
public:
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
