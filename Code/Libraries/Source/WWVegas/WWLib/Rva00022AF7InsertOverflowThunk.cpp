// cl: /DNDEBUG /MD /EHsc
// The retail body is a five-byte incremental-link tail thunk. Its decoded
// target is the matched vector<pair<ObjectID,ObjectID> > insertion body at
// 0x00771870. This derived view preserves the exact thiscall ABI while keeping
// the thunk's own identity address-qualified.
enum ObjectID
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
	First first;
	Second second;
};

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

typedef _STL::pair<ObjectID, ObjectID> Rva00022AF7ObjectIDPair;
typedef _STL::allocator<Rva00022AF7ObjectIDPair> Rva00022AF7Allocator;

class Rva00022AF7InsertOverflowThunk :
	public _STL::vector<Rva00022AF7ObjectIDPair, Rva00022AF7Allocator>
{
public:
	void forward(Rva00022AF7ObjectIDPair *position,
		const Rva00022AF7ObjectIDPair &value,
		const _STL::__false_type &tag, unsigned int fillLength, bool atEnd);
};

void Rva00022AF7InsertOverflowThunk::forward(
	Rva00022AF7ObjectIDPair *position,
	const Rva00022AF7ObjectIDPair &value,
	const _STL::__false_type &tag, unsigned int fillLength, bool atEnd)
{
	_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
