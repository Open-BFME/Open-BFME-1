// ?bfmeDispatchDescriptor1288@BfmeSubmitter1283@@QAEXPAUBfmeDescriptor1288@@PAUBfmeContext1288@@@Z
// partial score=0.82 date=2026-08-30
struct BfmeStringData1288
{
	unsigned short m_refCount;
};

struct BfmeStringPool1288
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool1288 *g_bfmeStringPool1284;
extern BfmeStringData1288 g_bfmeDefaultString1284;

class BfmeString1288
{
public:
	BfmeString1288(int value);

	BfmeString1288()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~BfmeString1288()
	{
		BfmeStringData1288 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeString1288 &operator=(const BfmeString1288 &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData1288 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
		m_data = other.m_data;
		return *this;
	}

private:
	BfmeStringData1288 *m_data;
};

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *key, int name, void **previousResult, void **nodeResult);
};

struct BfmeLookupLevel1288
{
	char m_padding00[0x18];
	void **m_entries;
};

struct BfmeLookupMiddle1288
{
	char m_padding00[0x04];
	BfmeLookupLevel1288 *m_level;
};

struct BfmeLookupOuter1288
{
	char m_padding00[0x0c];
	BfmeLookupMiddle1288 *m_middle;
};

struct BfmeContext1288
{
	char m_padding00[0x50];
	BfmeLookupOuter1288 *m_lookup;
};

struct BfmeDescriptor1288
{
	unsigned int m_flags;
	int m_value04;
	int m_index08;
	char m_values0c[0x18];
	unsigned int m_colors24[2];
	int m_value2c;
	int m_string30;
	int m_value34;
	void *m_value38;
};

class BfmeSubmitter1283
{
public:
	void bfmeSubmitColors1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		const unsigned int *colors, int a9, int a10, int a11);
	void bfmeDispatchDescriptor1288(BfmeDescriptor1288 *descriptor, BfmeContext1288 *context);

private:
	BfmeQuery1279 *m_query;
};

void BfmeSubmitter1283::bfmeDispatchDescriptor1288(BfmeDescriptor1288 *descriptor,
	BfmeContext1288 *context)
{
	unsigned int flags = descriptor->m_flags;
	if ((flags & 2) != 0) {
		void *selected = context->m_lookup->m_middle->m_level->m_entries[descriptor->m_index08];
		BfmeString1288 name;
		BfmeString1288 *nameArgument = 0;
		if ((descriptor->m_flags & 0x20) != 0) {
			BfmeString1288 requestedName(descriptor->m_string30);
			name = requestedName;
			nameArgument = &name;
		}

		bfmeSubmitColors1283(0, descriptor->m_value04, (int)selected, (int)nameArgument,
			(int)context, 0, descriptor->m_value34,
			(descriptor->m_flags & 8) != 0 ? descriptor->m_colors24 : 0,
			(descriptor->m_flags & 4) != 0 ? (int)descriptor->m_values0c : 0,
			(int)(descriptor->m_flags & 0x80 ? descriptor->m_value38 : 0), descriptor->m_value2c);
		return;
	}

	if ((flags & 1) != 0) {
		void *previousResult;
		void *nodeResult;
		m_query->bfmeQuery1279((void *)descriptor->m_value04, 0, &previousResult, &nodeResult);
		bfmeSubmitColors1283((int)previousResult, 0, 0, 0, (int)nodeResult, 0, -1,
			(flags & 8) != 0 ? descriptor->m_colors24 : 0,
			(flags & 4) != 0 ? (int)descriptor->m_values0c : 0,
			(int)(flags & 0x80 ? descriptor->m_value38 : 0), descriptor->m_value2c);
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
