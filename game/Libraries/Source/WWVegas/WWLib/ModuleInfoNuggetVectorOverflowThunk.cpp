// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

struct ModuleInfo
{
	struct Nugget;
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
	void _M_insert_overflow( Type *, const Type &, const __false_type &,
		unsigned int, bool );
};

class NuggetInsertOverflowShim
{
public:
	void insert_overflow( ModuleInfo::Nugget *, const ModuleInfo::Nugget &,
		const __false_type &, unsigned int, bool );
};

void vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_insert_overflow(
	ModuleInfo::Nugget *position, const ModuleInfo::Nugget &value,
	const __false_type &tag, unsigned int fillLength, bool atEnd )
{
	((NuggetInsertOverflowShim *)this)->insert_overflow(
		position, value, tag, fillLength, atEnd );
}
}
