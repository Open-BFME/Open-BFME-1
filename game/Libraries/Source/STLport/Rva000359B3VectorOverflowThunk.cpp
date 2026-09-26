// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA 0x000359B3 is a five-byte tail jump to the matched
// vector<Rva00755100Element>::_M_insert_overflow body at 0x006FA7C0.

struct Rva00755100Element;

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
	void _M_insert_overflow(Type *, const Type &, const __false_type &,
		unsigned int, bool);
};
}

class Rva000359B3VectorOverflowThunk
	: public _STL::vector<Rva00755100Element,
		_STL::allocator<Rva00755100Element> >
{
public:
	void forward(Rva00755100Element *, const Rva00755100Element &,
		const _STL::__false_type &, unsigned int, bool);
};

void Rva000359B3VectorOverflowThunk::forward(
	Rva00755100Element *position, const Rva00755100Element &value,
	const _STL::__false_type &tag, unsigned int fillLength, bool atEnd)
{
	this->_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
