// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
//
// The carved body at 0x003B0030 clears an eight-byte vector by forwarding its
// begin and end pointers to the existing vector erase thunk at 0x0003D3AC.
// The element identity is not recovered, so the vector keeps the address in
// its name while the thunk uses the pinned call-site type.

struct Rva003B0030Element
{
	char m_body[ 8 ];
};

struct Gen003AA010
{
	char m_body[ 8 ];
};

namespace _STL
{
template <class Type> class allocator
{
};

template <class Type, class Allocator = allocator<Type> > class vector
{
public:
	Type *erase(Type *first, Type *last);
	void clear();

protected:
	Type *_M_start;
	Type *_M_finish;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::clear()
{
	typedef vector<Gen003AA010,
		allocator<Gen003AA010> > EraseVector;
	((EraseVector *)this)->erase((Gen003AA010 *)_M_start,
		(Gen003AA010 *)_M_finish);
}

template void vector<Rva003B0030Element>::clear();
}
