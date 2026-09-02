// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: compiler-generated copy ctor of a 0x20-byte record whose first
// two members are AsciiString then UnicodeString, retail 0x004F97B0, 117 bytes.
// The frame exists so the char string is destroyed if the wide copy throws;
// the six dwords after that are POD and copied after both strings exist.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	int *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

struct AsciiUnicodePair
{
	AsciiString m_ascii;
	UnicodeString m_unicode;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;

	AsciiUnicodePair(const AsciiUnicodePair &other);
};

AsciiUnicodePair::AsciiUnicodePair(const AsciiUnicodePair &other)
	: m_ascii(other.m_ascii)
	, m_unicode(other.m_unicode)
	, m_a(other.m_a)
	, m_b(other.m_b)
	, m_c(other.m_c)
	, m_d(other.m_d)
	, m_e(other.m_e)
	, m_f(other.m_f)
{
}
