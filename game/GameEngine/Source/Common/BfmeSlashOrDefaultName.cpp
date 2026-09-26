// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x001945D0: if name contains '/', return the prefix and strip name
// to the suffix; otherwise copy fallback into the hidden return.
// ILT 0x00044E3B is pinned as slash-or-default with two const refs; the body
// calls StringBase::set on the first argument so that ref is not const.

template <typename T>
class StringBase
{
	friend class AsciiString;

	StringBase(const StringBase<T> &other);
	StringBase(const StringBase<T> &other, int start, int len);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

public:
	void set(const StringBase<T> &src, int start, int len);

private:
	int getLength() const { return m_data ? m_data->length : 0; }
	T getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const AsciiString &other, int start, int len)
		: StringBase<char>(other, start, len) {}
	~AsciiString() {}

	int getLength() const { return StringBase<char>::getLength(); }
	char getCharAt(int index) const { return StringBase<char>::getCharAt(index); }
	void set(const AsciiString &src, int start, int len)
	{
		StringBase<char>::set(src, start, len);
	}
};

// ?bfmeSlashOrDefaultName@@YA?AVAsciiString@@AAV1@ABV1@@Z
AsciiString __cdecl bfmeSlashOrDefaultName(AsciiString &name, const AsciiString &fallback)
{
	int len = name.getLength();
	for (int i = 0; i < len; ++i)
	{
		if (name.getCharAt(i) == '/')
		{
			AsciiString prefix(name, 0, i);
			name.set(name, i + 1, name.getLength() - i - 1);
			return prefix;
		}
	}
	return fallback;
}
