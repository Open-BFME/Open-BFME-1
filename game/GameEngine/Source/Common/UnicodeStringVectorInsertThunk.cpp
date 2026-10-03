// Retail 0x00016A63 is an incremental-link thunk to the matched UnicodeString
// vector insert-overflow body at 0x00532A00.
class UnicodeString;

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
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &tag, unsigned int count, bool unused );
	friend class Rva00016A63UnicodeStringVectorInsertThunk;
};

class Rva00016A63UnicodeStringVectorInsertThunk
{
public:
	void forward( UnicodeString *position, const UnicodeString &value,
		const __false_type &tag, unsigned int count, bool unused );
};

void Rva00016A63UnicodeStringVectorInsertThunk::forward(
	UnicodeString *position, const UnicodeString &value,
	const __false_type &tag, unsigned int count, bool unused )
{
	( ( vector<UnicodeString, allocator<UnicodeString> > * )this )->_M_insert_overflow(
		position, value, tag, count, unused );
}
}
