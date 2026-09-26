// Retail 0x00016A63 is an incremental-link thunk to the matched UnicodeString
// vector insert-overflow body at 0x00532A00.
class UnicodeString;

namespace _STL
{
struct __false_type
{
};

class UnicodeStringInsertOverflowShim
{
public:
	void insert_overflow( UnicodeString *position, const UnicodeString &value,
		const __false_type &tag, unsigned int count, bool unused );
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
	( ( UnicodeStringInsertOverflowShim * )this )->insert_overflow(
		position, value, tag, count, unused );
}
}
