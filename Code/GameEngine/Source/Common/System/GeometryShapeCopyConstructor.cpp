// Open-BFME: GeometryShape copy constructor, retail 0x000FCED0.
//
// The 0x24-byte element layout is proven by GeometryInfo's shape vector:
// scalar fields occupy 0x00..0x18, followed by AsciiString at 0x1c and the
// enabled byte at 0x20.  The retail body is the corresponding memberwise
// copy, including the existing AsciiString copy-constructor call.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
private:
	void *m_data;

public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	int m_unmodelled00c;
	int m_unmodelled10;
	int m_unmodelled14;
	float m_offsetZ;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape(const GeometryShape &other);
};

// ??0GeometryShape@@QAE@ABU0@@Z
GeometryShape::GeometryShape(const GeometryShape &other)
	: m_type(other.m_type),
	  m_height(other.m_height),
	  m_majorRadius(other.m_majorRadius),
	  m_unmodelled00c(other.m_unmodelled00c),
	  m_unmodelled10(other.m_unmodelled10),
	  m_unmodelled14(other.m_unmodelled14),
	  m_offsetZ(other.m_offsetZ),
	  m_name(other.m_name),
	  m_enabled(other.m_enabled),
	  m_unmodelled21()
{
}
