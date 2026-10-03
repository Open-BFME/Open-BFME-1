// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// The carved 5-byte ILT at 0x000112C0 forwards to the matched
// vector<AsciiString>::_M_insert_overflow body at 0x00757C70.

class AsciiString;

namespace _STL
{
struct __false_type
{
};

template <class T>
class allocator
{
};

template <class T, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(T *position, const T &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);

public:
	void d_000112c0(T *position, const T &value, const __false_type &tag,
		unsigned int fillLength, bool atEnd)
	{
		this->_M_insert_overflow(position, value, tag, fillLength, atEnd);
	}
};

template class vector<AsciiString, allocator<AsciiString> >;
}
