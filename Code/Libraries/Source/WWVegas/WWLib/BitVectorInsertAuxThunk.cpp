// Retail 0x0002CB5B is an incremental-link thunk to the matched bit-vector body.
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

class BitVectorInsertAuxShim
{
public:
	void insert_aux( _Bit_iter< _Bit_reference, _Bit_reference * > position,
		bool value );
};

class Rva0002CB5BBitVectorThunk
{
public:
	void forward( _Bit_iter< _Bit_reference, _Bit_reference * > position,
		bool value );
};

void Rva0002CB5BBitVectorThunk::forward(
	_Bit_iter< _Bit_reference, _Bit_reference * > position, bool value )
{
	( ( BitVectorInsertAuxShim * )this )->insert_aux( position, value );
}
}
