enum ObjectID
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
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

class Rva0002AB44ObjectIDPairOverflowThunk
	: public vector<pair<ObjectID, unsigned int>,
		allocator<pair<ObjectID, unsigned int> > >
{
public:
	void insert_overflow(
		pair<ObjectID, unsigned int> *position,
		const pair<ObjectID, unsigned int> &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);
};

void Rva0002AB44ObjectIDPairOverflowThunk::insert_overflow(
	pair<ObjectID, unsigned int> *position,
	const pair<ObjectID, unsigned int> &value,
	const __false_type &tag, unsigned int fillLength, bool atEnd)
{
	this->_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
}
