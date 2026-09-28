// cl: /DNDEBUG /MD /EHsc
// The retail body is a five-byte incremental-link tail thunk. Its decoded
// target is the matched 8-byte-element insertion body at 0x00771870
// (W3D side; targets/game/reverse/identity_evidence/000960a0-00771870-objectid-pair-vector.md). This derived view preserves the exact thiscall ABI while keeping
// the thunk's own identity address-qualified.
struct Rva00771870Element
{
	unsigned char m_data[8];
};

namespace _STL
{
template <class Type>
class allocator
{
};

struct __false_type
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_end;
};
}

typedef Rva00771870Element Rva00022AF7Element;
typedef _STL::allocator<Rva00022AF7Element> Rva00022AF7Allocator;

class Rva00022AF7InsertOverflowThunk :
	public _STL::vector<Rva00022AF7Element, Rva00022AF7Allocator>
{
public:
	void forward(Rva00022AF7Element *position,
		const Rva00022AF7Element &value,
		const _STL::__false_type &tag, unsigned int fillLength, bool atEnd);
};

void Rva00022AF7InsertOverflowThunk::forward(
	Rva00022AF7Element *position,
	const Rva00022AF7Element &value,
	const _STL::__false_type &tag, unsigned int fillLength, bool atEnd)
{
	_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
