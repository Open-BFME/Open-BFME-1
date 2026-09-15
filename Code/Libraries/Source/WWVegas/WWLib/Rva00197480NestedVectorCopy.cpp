// Clean C++ reconstruction of retail RVA 0x00197480 (290 bytes).
// The semantic owner is not identified; the address-labelled element type is
// intentional.  Retail is a copy constructor for a vector of three-pointer
// inner vectors whose point payload is three 32-bit words.
//
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

struct Rva00197480Point
{
	int words[ 3 ];
};

typedef _STL::vector<Rva00197480Point,
	_STL::allocator<Rva00197480Point> > Rva00197480InnerVector;

typedef _STL::vector<Rva00197480InnerVector,
	_STL::allocator<Rva00197480InnerVector> > Rva00197480OuterVector;

// The explicit member instantiations retain the real STLport copy-constructor
// surface.  The nested vector is itself copied with placement construction;
// its point loop is the vendor POD path (three dword copies).
// The get_allocator bodies at 0x001924D0 (outer) and 0x001924A0 (inner)
// return their empty allocator through the caller-provided result slot
// (7 bytes each). Legacy generated ledger keys are retained with explicit
// object-symbols naming the actual canonical specializations.
// The _Vector_base constructors allocate point storage (0x00193930) and
// inner-vector storage (0x001939B0) through STLport's normal small-node/
// large-allocation split (100 bytes each).
// The allocator proxy constructors at 0x001932F0 (points) and 0x00193410
// (inner vectors) copy the initial pointer after constructing their empty
// allocator base (11 bytes each).
template _STL::vector<Rva00197480Point,
	_STL::allocator<Rva00197480Point> >::vector(
	const _STL::vector<Rva00197480Point,
	_STL::allocator<Rva00197480Point> > &);

template _STL::vector<Rva00197480InnerVector,
	_STL::allocator<Rva00197480InnerVector> >::vector(
	const _STL::vector<Rva00197480InnerVector,
	_STL::allocator<Rva00197480InnerVector> > &);

typedef char PointSizeCheck[(sizeof(Rva00197480Point) == 12) ? 1 : -1];
typedef char InnerVectorSizeCheck[(sizeof(Rva00197480InnerVector) == 12) ? 1 : -1];
