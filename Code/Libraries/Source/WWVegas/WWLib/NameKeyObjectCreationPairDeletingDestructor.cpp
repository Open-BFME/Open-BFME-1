// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// Retail 0x00654CF0 is the scalar-deleting wrapper for the value_type in the
// ObjectCreationList map.  Its complete destructor is already matched through
// the incremental-link thunk at 0x00009525.

enum NameKeyType
{
};

class ObjectCreationList;

namespace _STL {

template <class First, class Second>
struct pair
{
	~pair();
};

} // namespace _STL

void DeleteNameKeyObjectCreationPair(
	_STL::pair<const NameKeyType, ObjectCreationList> *value)
{
	delete value;
}
