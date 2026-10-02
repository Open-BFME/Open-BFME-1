// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Unclaimed STLport allocator<T>::allocate / deallocate instantiations.
//
// Each body is the vendor _alloc.h member compiled for one element type: the
// byte count is n * sizeof(T) (shl 2 / shl 3 / shl 5, or lea*3 + shl 2 for
// twelve bytes), requests above 0x80 bytes go to operator new / delete and
// the rest to __node_alloc, and both members pop two stack arguments (ret 8).
// Every body sat in a .text gap no ledger row covered: 16-byte-aligned start
// after an int3 pad run, ret 8 followed by int3 padding or the next row, and
// no call, ILT stub, table slot or code immediate reaches it.
//
// IDENTITY IS NOT RECOVERED beyond the element SIZE.  Retail has no
// identical-COMDAT folding, so each address is a different T of that size;
// which T is not witnessed, so each element type is named for its address.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>
#include <vector>

struct Rva0081D580Element { char m_bytes[ 4 ]; };
struct Rva0081D5B0Element { char m_bytes[ 4 ]; };
struct Rva008F9D10Element { char m_bytes[ 4 ]; };
struct Rva008F9D70Element { char m_bytes[ 8 ]; };
struct Rva008F9DD0Element { char m_bytes[ 4 ]; };
struct Rva008F9E00Element { char m_bytes[ 4 ]; };
struct Rva008FEE40Element { char m_bytes[ 32 ]; };
struct Rva008FEE80Element { char m_bytes[ 32 ]; };
struct Rva0090E360Element { char m_bytes[ 4 ]; };
struct Rva00926470Element { char m_bytes[ 32 ]; };
struct Rva009264E0Element { char m_bytes[ 32 ]; };
struct Rva00943980Element { char m_bytes[ 8 ]; };
struct Rva009A1930Element { char m_bytes[ 8 ]; };
struct Rva009A1960Element { char m_bytes[ 8 ]; };
struct Rva009CBBD0Element { char m_bytes[ 8 ]; };
struct Rva009ECF30Element { char m_bytes[ 4 ]; };
struct Rva009ECF90Element { char m_bytes[ 4 ]; };
struct Rva009ECFC0Element { char m_bytes[ 4 ]; };
struct Rva009ED060Element { char m_bytes[ 12 ]; };
struct Rva009F2FE0Element { char m_bytes[ 8 ]; };

template Rva0081D580Element *_STL::allocator<Rva0081D580Element>::allocate( size_t, const void * ) const;
template void _STL::allocator<Rva0081D5B0Element>::deallocate( Rva0081D5B0Element *, size_t ) const;
template Rva008F9D10Element *_STL::allocator<Rva008F9D10Element>::allocate( size_t, const void * ) const;
template Rva008F9D70Element *_STL::allocator<Rva008F9D70Element>::allocate( size_t, const void * ) const;
template Rva008F9DD0Element *_STL::allocator<Rva008F9DD0Element>::allocate( size_t, const void * ) const;
template void _STL::allocator<Rva008F9E00Element>::deallocate( Rva008F9E00Element *, size_t ) const;
template void _STL::allocator<Rva008FEE40Element>::deallocate( Rva008FEE40Element *, size_t ) const;
template Rva008FEE80Element *_STL::allocator<Rva008FEE80Element>::allocate( size_t, const void * ) const;
template void _STL::allocator<Rva0090E360Element>::deallocate( Rva0090E360Element *, size_t ) const;
template void _STL::allocator<Rva00926470Element>::deallocate( Rva00926470Element *, size_t ) const;
template Rva009264E0Element *_STL::allocator<Rva009264E0Element>::allocate( size_t, const void * ) const;
template Rva00943980Element *_STL::allocator<Rva00943980Element>::allocate( size_t, const void * ) const;
template Rva009A1930Element *_STL::allocator<Rva009A1930Element>::allocate( size_t, const void * ) const;
template void _STL::allocator<Rva009A1960Element>::deallocate( Rva009A1960Element *, size_t ) const;
template Rva009CBBD0Element *_STL::allocator<Rva009CBBD0Element>::allocate( size_t, const void * ) const;
template Rva009ECF30Element *_STL::allocator<Rva009ECF30Element>::allocate( size_t, const void * ) const;
template Rva009ECF90Element *_STL::allocator<Rva009ECF90Element>::allocate( size_t, const void * ) const;
template void _STL::allocator<Rva009ECFC0Element>::deallocate( Rva009ECFC0Element *, size_t ) const;
template Rva009ED060Element *_STL::allocator<Rva009ED060Element>::allocate( size_t, const void * ) const;
template Rva009F2FE0Element *_STL::allocator<Rva009F2FE0Element>::allocate( size_t, const void * ) const;

// 0x009F35B0 (45 bytes): _Vector_base<T>::~_Vector_base for an eight-byte T
// (sar 3 / shl 3 of end_of_storage - start), freeing through the same
// operator delete / __node_alloc split.  Same boundary evidence as above.
struct Rva009F35B0Element { char m_bytes[ 8 ]; };
template _STL::_Vector_base<Rva009F35B0Element, _STL::allocator<Rva009F35B0Element> >::~_Vector_base();
