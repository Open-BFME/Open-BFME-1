// cl: /DNDEBUG /MD
//
// Retail 0x00741830: thiscall constructor that zeroes the lead dword, copy-
// constructs a StringBase<char> at +4, copies a 12-byte record from the second
// argument, then stores six more dword arguments and a trailing zero byte.

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	unsigned x;
	unsigned y;
	unsigned z;
};

class Rva00741830
{
public:
	Rva00741830(
		const AsciiString &name,
		const Coord3D &pos,
		unsigned a,
		unsigned b,
		unsigned c,
		unsigned e,
		unsigned f,
		unsigned d);

private:
	unsigned m_zero;
	AsciiString m_name;
	Coord3D m_pos;
	unsigned m_a;
	unsigned m_b;
	unsigned m_c;
	unsigned m_d;
	unsigned m_e;
	unsigned m_f;
	unsigned char m_flag;
};

Rva00741830::Rva00741830(
	const AsciiString &name,
	const Coord3D &pos,
	unsigned a,
	unsigned b,
	unsigned c,
	unsigned e,
	unsigned f,
	unsigned d)
	: m_zero(0), m_name(name)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z = pos.z;
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
	m_e = e;
	m_f = f;
	m_flag = 0;
}
