// Retail 0x00467270 formats an APT level path into the supplied AsciiString.

template <typename T>
class StringBase
{
	StringBase(const char *text);
	friend class AsciiString;
};

class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &that)
	{
		m_text = that.m_text;
	}
	~AsciiString() {}
	void __cdecl format(AsciiString format, ...);

private:
	void *m_text;
};

void rva00467270(AsciiString *text, int level)
{
	text->format("/_level%d", level);
}
