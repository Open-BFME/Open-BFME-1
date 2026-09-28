// Five-byte incremental-link thunk at 0x0002AB44 into the solve-side 8-byte
// SolutionVec (pair<ObjectID, ObjectID>) _M_insert_overflow at 0x000960A0; see
// targets/game/reverse/identity_evidence/000960a0-00771870-objectid-pair-vector.md.

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
	void _M_insert_overflow(Type *, const Type &, const __false_type &,
		unsigned int, bool);
};

class Rva0002AB44InsertOverflowThunk
	: public vector<pair<ObjectID, ObjectID>,
		allocator<pair<ObjectID, ObjectID> > >
{
public:
	void insert_overflow(
		pair<ObjectID, ObjectID> *position,
		const pair<ObjectID, ObjectID> &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);
};

void Rva0002AB44InsertOverflowThunk::insert_overflow(
	pair<ObjectID, ObjectID> *position,
	const pair<ObjectID, ObjectID> &value,
	const __false_type &tag, unsigned int fillLength, bool atEnd)
{
	this->_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
}
