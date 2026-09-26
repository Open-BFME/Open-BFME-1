class Object;

namespace _STL
{
struct __true_type {};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, Type const &, __true_type const &, unsigned int, bool);
};

class ObjectPointerInsertOverflowShim
{
public:
	void insert_overflow(Object **pos, Object *const &x, __true_type const &tag, unsigned int fill_len, bool at_end);
};

void vector<Object *, allocator<Object *> >::_M_insert_overflow(
	Object **pos, Object *const &x, __true_type const &tag, unsigned int fill_len, bool at_end)
{
	((ObjectPointerInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
