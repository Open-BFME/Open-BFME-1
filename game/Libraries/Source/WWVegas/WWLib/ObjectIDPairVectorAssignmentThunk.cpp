// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

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

template <class Type, class Allocator>
class vector
{
public:
	vector &operator=(const vector &);
protected:
	void _M_insert_overflow(Type *, const Type &, const struct __false_type &, unsigned int, bool);
};

struct __false_type
{
};

class ObjectIDPairVectorAssignShim
{
public:
	vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &assign(
		const vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &rhs);
};

class ObjectIDOverflowShim
{
public:
	void insert_overflow(ObjectID *pos, ObjectID const &x, const __false_type &tag, unsigned int n, bool at_end);
};

vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > >::operator=(const vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &rhs)
{
	return ((ObjectIDPairVectorAssignShim *)this)->assign(rhs);
}

void vector<ObjectID, allocator<ObjectID> >::_M_insert_overflow(ObjectID *pos, ObjectID const &x, const __false_type &tag, unsigned int n, bool at_end)
{
	((ObjectIDOverflowShim *)this)->insert_overflow(pos, x, tag, n, at_end);
}
}
