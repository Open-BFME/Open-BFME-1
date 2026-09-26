// ?resize@Gen003C2EE0Vector@@QAEXIG@Z
// Address-derived STLport vector<unsigned short>::resize body at 0x003C2EE0.
// stlport

typedef unsigned int size_t_;

namespace Gen003C2EE0Stl
{
struct __true_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
inline Type *__copy(Type *first, Type *last, Type *result)
{
	int count = (int)(last - first);
	while (count > 0)
	{
		*result = *first;
		++first;
		++result;
		--count;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
public:
	Type *begin() { return _M_start; }
	Type *end() { return _M_finish; }
	unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }

	Type *erase(Type *first, Type *last)
	{
		Type *i = __copy(_M_finish, _M_finish, first);
		_M_finish = i;
		return first;
	}

	void resize(unsigned int newSize, Type value);
	void _M_fill_insert(Type *position, unsigned int count, const Type &value);

private:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(unsigned int newSize, Type value)
{
	Type *oldFinish = _M_finish;
	if (newSize < (unsigned int)(oldFinish - _M_start))
		erase(_M_start + newSize, oldFinish);
	else
		_M_fill_insert(oldFinish,
			newSize - (unsigned int)(oldFinish - _M_start), value);
}
}

typedef Gen003C2EE0Stl::vector<unsigned short,
	Gen003C2EE0Stl::allocator<unsigned short> > Gen003C2EE0Vector;

template void Gen003C2EE0Vector::resize(unsigned int, unsigned short);
