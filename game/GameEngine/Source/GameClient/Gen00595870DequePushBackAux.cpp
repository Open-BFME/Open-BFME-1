// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

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

// The generated payload name records the observed 12-byte copy-and-destroy
// shape. Its first dword is a string-family subobject; the remaining two
// dwords are copied inline by MSVC 7.1.
struct Gen_t_00595870_p12cd
{
	AsciiString m_name;
	int m_first;
	int m_second;
};

void BfmeGen00595870DequeAnchor(
	_STL::deque<Gen_t_00595870_p12cd> &values,
	const Gen_t_00595870_p12cd &value )
{
	values.push_back( value );
}
