// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	void *m_data;
};

class Rva0036CCC0Pair
{
public:
	Rva0036CCC0Pair(const Rva0036CCC0Pair &other);

private:
	AsciiString m_first;
	AsciiString m_second;
	int m_value;
};

Rva0036CCC0Pair::Rva0036CCC0Pair(const Rva0036CCC0Pair &other)
	: m_first(other.m_first),
	  m_second(other.m_second),
	  m_value(other.m_value)
{
}

// @??0Rva0036CCC0Pair@@QAE@ABV0@@Z 0x0036CCC0
