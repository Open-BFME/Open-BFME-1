// Retail RVA 0x0004ABF6 tail-jumps to the verified STLport vector body at 0x00638FF0.

struct tConnInfoStruct
{
	unsigned int state;
	unsigned long localIP;
	unsigned short localPort;
	unsigned long remoteIP;
	unsigned short remotePort;
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);

public:
};
}

class Rva0004ABF6ConnInfoThunk
	: public _STL::vector<tConnInfoStruct, _STL::allocator<tConnInfoStruct> >
{
public:
	void forward(tConnInfoStruct *, const tConnInfoStruct &, const _STL::__false_type &, unsigned int, bool);
};

void Rva0004ABF6ConnInfoThunk::forward(
	tConnInfoStruct *position, const tConnInfoStruct &value,
	const _STL::__false_type &tag, unsigned int fillLength, bool atEnd)
{
	this->_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
