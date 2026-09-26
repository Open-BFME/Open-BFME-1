// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Address-derived model for the retail static cdecl INI field callback at 0x005C80F0.
// The anonymous retail boundary proves getNextToken, temporary string comparison,
// the factory-list walk, virtual replacement, and the destination offset below.
// The original owner name remains unclaimed until a caller or field table proves it.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

extern const char g_bfmeEmptyAscii[];

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class BFMERetailAsciiString
{
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	int compare(const char *right) const
	{
		int rightLength = right ? (int)strlen(right) : 0;
		int leftLength = m_data ? m_data->length : 0;
		const char *leftData = m_data ? &m_data->data[0] : g_bfmeEmptyAscii;
		int count = leftLength < rightLength ? leftLength : rightLength;
		const int result = memcmp(leftData, right, count);
		if (result != 0)
			return result;
		return leftLength - rightLength;
	}

private:
	void releaseBuffer();
	Header *m_data;
};

class Rva005C80F0Factory
{
public:
	virtual void *createTemplate(INI *ini);

	const char *m_name;
	const char *m_key;
	Rva005C80F0Factory *m_next;
};

class Rva005C80F0ModuleTemplate
{
public:
	virtual void destroy(unsigned int flags);
};

class Rva005C80F0Parse
{
public:
	static void parse(INI *ini, void *data, void *store, const void *userData);
};

// ?parse@Rva005C80F0Parse@@SAXPAVINI@@PAX1PBX@Z
void Rva005C80F0Parse::parse(INI *ini, void *data, void *, const void *)
{
	const char *token = ini->getNextToken(0);
	BFMERetailAsciiString name(token);
	Rva005C80F0Factory *factory = *reinterpret_cast<Rva005C80F0Factory **>(0x012F6504);

	for (;;)
	{
		if (name.compare(factory->m_name) == 0)
			break;
		factory = factory->m_next;
	}

	void *created = factory->createTemplate(ini);
	void *old = *reinterpret_cast<void **>((char *)data + 0xBC);
	if (old)
		((Rva005C80F0ModuleTemplate *)old)->destroy(1);
	*reinterpret_cast<void **>((char *)data + 0xBC) = created;
}

