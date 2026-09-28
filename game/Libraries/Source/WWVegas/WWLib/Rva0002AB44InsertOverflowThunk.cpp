// Five-byte incremental-link thunk at 0x0002AB44 into the solve-side 8-byte
// element _M_insert_overflow at 0x000960A0; see
// targets/game/reverse/identity_evidence/000960a0-002fed10-objectid-pair-overflow.md.

struct Rva000960A0Element
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
	void _M_insert_overflow(Type *, const Type &, const __false_type &,
		unsigned int, bool);
};

class Rva0002AB44InsertOverflowThunk
	: public vector<Rva000960A0Element,
		allocator<Rva000960A0Element > >
{
public:
	void insert_overflow(
		Rva000960A0Element *position,
		const Rva000960A0Element &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);
};

void Rva0002AB44InsertOverflowThunk::insert_overflow(
	Rva000960A0Element *position,
	const Rva000960A0Element &value,
	const __false_type &tag, unsigned int fillLength, bool atEnd)
{
	this->_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
}
