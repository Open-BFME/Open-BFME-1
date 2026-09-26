// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail target uses StringBase<char> symbols for the by-value token objects.
// This TU-local layout view preserves the proven header pointer at +0 and the
// retail payload at +8 while declaring the canonical StringBase member names.
struct StringBaseCharHeader {
	int references;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T> class StringBase;
class Rva002E7E00Owner;
template <> class StringBase<char>
{
public:
	StringBase() : m_data(0) {}
	bool nextToken(StringBase *token, const char *delimiters);
private:
	friend class Rva002E7E00Owner;
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	StringBaseCharHeader *m_data;
};

typedef StringBase<char> AsciiString;
extern const char g_bfmeEmptyAscii[];

class GenItem;
class Gen000140D8
{
public:
	bool handle(GenItem *item, bool *foundNormal, bool *foundAddOrSub);
private:
	unsigned char m_bits[40];
};
class Rva002E7E00Owner
{
public:
	void parse(AsciiString text);
};
void Rva002E7E00Owner::parse(AsciiString text)
{
	bool first = false;
	bool second = false;
	AsciiString token;
	while (text.nextToken(&token, 0))
	{
		const char *value = token.m_data != 0
			? reinterpret_cast<const char *>(token.m_data) + 8
			: g_bfmeEmptyAscii;
		if (!reinterpret_cast<Gen000140D8 *>(this)->handle(
			reinterpret_cast<GenItem *>(const_cast<char *>(value)),
			&first, &second))
			return;
	}
}
