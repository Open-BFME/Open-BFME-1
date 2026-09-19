// ?bfmeBuildString1284@BfmeStringWriter1284@@QAEXPAVBfmeString1284@@H@Z
// partial score=0.9 date=2026-09-18
struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

extern "C" char *__cdecl strcpy(char *destination, const char *source);
#pragma intrinsic(strcpy)

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI;

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
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeString1284 &operator=(const BfmeStrVKI &text);
	void append(const BfmeString1284 &text);
	void append(int value);

	BfmeStringData3AF0 *m_data;
};

class BfmeStringWriter1284
{
public:
	void bfmeBuildString1284(BfmeString1284 *result, int value);
	void bfmeWriteString1284(char *destination, int value);

	private:
	char m_pad0[0x20];
	struct ElementVector
	{
		BfmeString1284 **m_begin;
		char m_pad04[4];
		int m_size;

		__forceinline BfmeString1284 **begin() const
		{
			return m_begin;
		}

		__forceinline int size() const
		{
			return m_size;
		}
	} m_elements;
};

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	void bfmeSetVKI(const char *text);

	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class BfmeStrVKJ
{
public:
	BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &text);
	BfmeStringData3AF0 *m_data;
};

class Rva8CD130String
{
public:
	BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *name);
};

#pragma comment(linker, "/alternatename:?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z=?d_008985c0@@YAXXZ")
#pragma comment(linker, "/alternatename:?append@BfmeString1284@@QAEXH@Z=?d_0089ea60@@YAXXZ")

BfmeString1284 &BfmeString1284::operator=(const BfmeStrVKI &text)
{
	++text.m_data->m_refCount;
	BfmeStringData3AF0 *old = m_data;
	if (--old->m_refCount == 0)
		g_bfmeStringPool1284->free(old);
	m_data = text.m_data;
	return *this;
}

void BfmeString1284::append(const BfmeString1284 &text)
{
	reinterpret_cast<BfmeStrVKJ *>(this)->bfmeAssignVKJ(
		reinterpret_cast<const BfmeStrVKJ &>(text));
}

void BfmeStringWriter1284::bfmeBuildString1284(BfmeString1284 *result, int value)
{
	BfmeStringWriter1284 *writer = this;
	BfmeString1284 *output = result;
	*output = BfmeStrVKI((const char *)0x0107301c);
	int index = 0;

	for (; index < writer->m_elements.size(); ++index)
	{
		BfmeString1284 element;
		BfmeString1284 *entry = reinterpret_cast<BfmeString1284 *>(
			reinterpret_cast<unsigned>(writer->m_elements.begin()[index]) & ~1U);
		if (entry != 0)
		{
			reinterpret_cast<Rva8CD130Value *>(entry)->getName(
				reinterpret_cast<Rva8CD130String *>(&element));
			output->append(element);
			if (index < writer->m_elements.size() - 1)
				output->append(value);
		}
	}
}

void BfmeStringWriter1284::bfmeWriteString1284(char *destination, int value)
{
	BfmeString1284 result;
	bfmeBuildString1284(&result, value);
	strcpy(destination, result.m_data->m_text);
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
