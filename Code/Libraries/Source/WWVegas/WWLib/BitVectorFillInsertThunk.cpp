// Retail 0x0000886E is an incremental-link thunk to the matched vector<bool>
// fill-insert body at 0x002CC290.
namespace _STL
{
struct _Bit_reference
{
};

template <class Reference, class Pointer>
struct _Bit_iter
{
};

template <class Type>
class allocator
{
};

class BitVectorFillInsertShim
{
public:
	void fill_insert( _Bit_iter< _Bit_reference, _Bit_reference * > position,
		unsigned int count, bool value );
};

class Rva0000886EBitVectorFillInsertThunk
{
public:
	void forward( _Bit_iter< _Bit_reference, _Bit_reference * > position,
		unsigned int count, bool value );
};

void Rva0000886EBitVectorFillInsertThunk::forward(
	_Bit_iter< _Bit_reference, _Bit_reference * > position,
		unsigned int count, bool value )
{
	( ( BitVectorFillInsertShim * )this )->fill_insert(
		position, count, value );
}
}
