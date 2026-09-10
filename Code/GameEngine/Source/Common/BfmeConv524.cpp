extern "C" __declspec(dllimport) char *__cdecl strncpy(char *destination, const char *source,
	unsigned int count);

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

struct BfmeSubBSD
{
	unsigned char m_bfmeHead[4];
};

BFMERetailAsciiString bfmeDoBSD(void *what)
{
	char buffer[0x8000];
	const char *source = (const char *)what;

	if (source == 0)
		source = (const char *)0x0107301c;
	else if (*source == '.')
		++source;

	strncpy(buffer, source, 0x7fff);
	char *cursor = buffer;
	if (buffer[0] != 0)
	{
		do
		{
			if (*cursor == '.')
				*cursor = '/';
			++cursor;
		}
		while (*cursor != 0);
	}

	BFMERetailAsciiString text(buffer);
	return text;
}

void bfmeDoBSD(BfmeSubBSD *sub, void *what);

class BfmeThingBSD
{
public:
	BfmeThingBSD *bfmeGoBSD(char kind, void *what);
	char m_bfmeKind;
	unsigned char m_bfmePad[3];
	BfmeSubBSD m_bfmeSub;
};

BfmeThingBSD *BfmeThingBSD::bfmeGoBSD(char kind, void *what)
{
	m_bfmeKind = kind;
	bfmeDoBSD(&m_bfmeSub, what);
	return this;
}
