// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00194810: split name on the first '/'. Hit returns (prefix, suffix);
// miss returns (AsciiString::TheEmptyString, name). Pair construction is the
// landed bfmeMakePairEL factory (ILT 0x0001E7EF -> 0x00193520).
// Address-derived name: used as the map key for 0x0019B780.

template <typename T>
class StringBase
{
	friend class BfmeWordEL;

	StringBase(const StringBase<T> &other);
	StringBase(const StringBase<T> &other, int start, int len);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

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

class BfmeWordEL : private StringBase<char>
{
public:
	BfmeWordEL(const BfmeWordEL &other) : StringBase<char>(other) {}
	BfmeWordEL(const BfmeWordEL &other, int start, int len)
		: StringBase<char>(other, start, len) {}
	~BfmeWordEL() {}

	int getLength() const { return StringBase<char>::getLength(); }
	char getCharAt(int index) const { return StringBase<char>::getCharAt(index); }
};

struct BfmePairEL
{
	BfmeWordEL first;
	BfmeWordEL second;
};

BfmePairEL __cdecl bfmeMakePairEL(const BfmeWordEL &first, const BfmeWordEL &second);

// Same four-byte StringBase<char> representation as BfmeWordEL above.
class AsciiString
{
	void *m_data;
public:
	static const AsciiString TheEmptyString;
};

// ?Rva00194810@@YA?AUBfmePairEL@@ABVBfmeWordEL@@@Z
BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name)
{
	int i = 0;
	while (i < name.getLength())
	{
		if (name.getCharAt(i) == '/')
		{
			BfmeWordEL suffix(name, i + 1, name.getLength() - i - 1);
			BfmeWordEL prefix(name, 0, i);
			return bfmeMakePairEL(prefix, suffix);
		}
		++i;
	}
	return bfmeMakePairEL(
		*reinterpret_cast<const BfmeWordEL *>(&AsciiString::TheEmptyString),
		name);
}
