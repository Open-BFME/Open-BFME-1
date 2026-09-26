// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

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

class IntInsertOverflowShim
{
public:
	void insert_overflow(int *pos, const int &x, const __true_type &tag, unsigned int fill_len, bool at_end);
};

void vector<int, allocator<int> >::_M_insert_overflow(
	int *pos, const int &x, const __true_type &tag, unsigned int fill_len, bool at_end)
{
	((IntInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
