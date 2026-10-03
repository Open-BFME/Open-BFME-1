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

template <class Type, class Allocator>
class vector;

template <class Allocator>
class vector<bool, Allocator>
{
protected:
	void _M_insert_aux( _Bit_iter< _Bit_reference, _Bit_reference * > position,
		bool value );
	friend class Rva0002CB5BBitVectorThunk;
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
	( ( vector<bool, allocator<bool> > * )this )->_M_insert_aux( position, value );
}
}
