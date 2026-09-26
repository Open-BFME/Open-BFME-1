// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: STLport hashtable<V, K>::resize, near-twin of the 20-body family
// in RvaHashResize.cpp (twin 0x00067270). Every one of those computes the
// bucket index from a single dword key field at value+0 (node+4): "mov eax,
// [ecx+4]; xor edx,edx; div [esp+0x10]". This body (0x00927DE0) instead reads
// TWO dword fields, node+4 and node+8, and combines them before the div:
// "mov eax,[ecx+8]; mov edx,[ecx+4]; shl eax,0x10; add eax,edx; xor edx,edx;
// div [esp+0x10]" -- i.e. key = (value.a[1] << 16) + value.a[0]. The caller
// at 0x00928590 and the landed neighbour ??_$_Rb_tree<Gen_p16pod,...>::_M_insert
// (0x00927C30, RvaTreeMInsert00927C30.cpp) show a 16-byte Gen_p16pod{int a[4]}
// POD already in use one function below this one in the same source file, so
// this table is spelled with the same POD and a hash functor that folds two
// of its four ints into the bucket key.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned int UnsignedInt;

struct Gen_p16pod { int a[4]; };

struct Gen_p16podExtractKey
{
	UnsignedInt operator()( const Gen_p16pod &x ) const
	{
		return ( static_cast<UnsignedInt>( x.a[1] ) << 16 ) + static_cast<UnsignedInt>( x.a[0] );
	}
};

typedef _STL::hashtable<Gen_p16pod, UnsignedInt, _STL::hash<UnsignedInt>,
	Gen_p16podExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Gen_p16pod> > Rva00927DE0Table;

// retail 0x00927DE0
void BfmeHashResizeAnchor00927DE0( Rva00927DE0Table &table, UnsignedInt count )
{
	table.resize( count );
}
