class ObjectCreationNugget;

namespace _STL
{
struct __true_type
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
	void _M_insert_overflow(Type *, const Type &, const __true_type &, unsigned int, bool);
};

class ObjectCreationNuggetPointerInsertOverflowShim
{
public:
	void insert_overflow(ObjectCreationNugget **pos, ObjectCreationNugget *const &x, const __true_type &tag, unsigned int fill_len, bool at_end);
};

void vector<ObjectCreationNugget *, allocator<ObjectCreationNugget *> >::_M_insert_overflow(
	ObjectCreationNugget **pos, ObjectCreationNugget *const &x, const __true_type &tag, unsigned int fill_len, bool at_end)
{
	((ObjectCreationNuggetPointerInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
