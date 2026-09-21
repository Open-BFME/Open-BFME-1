// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// The retail boundary at 0x0001636F is a five-byte ILT jump.
// The symbol pin at that thunk proves the WeaponTemplateSet vector target.

class WeaponTemplateSet
{
	unsigned char m_data[84];
};

namespace _STL
{
struct __false_type
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
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

public:
	void Rva0001636FThunk(Type *position, const Type &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd)
	{
		_M_insert_overflow(position, value, tag, fillLength, atEnd);
	}
};

template class vector<WeaponTemplateSet, allocator<WeaponTemplateSet> >;
}
