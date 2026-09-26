// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The retail tree insertion uses the original BFME branch layout retained by
// our STLport shim.  Keep the switch local to this explicit instantiation so
// unrelated container bodies retain their native source layout.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef _STL::pair<const unsigned int, unsigned char> UnsignedIntBytePair;
typedef _STL::_Rb_tree<unsigned int,
    UnsignedIntBytePair,
    _STL::_Select1st<UnsignedIntBytePair>,
    _STL::less<unsigned int>,
    _STL::allocator<UnsignedIntBytePair> > UnsignedIntByteTree;

template _STL::pair<UnsignedIntByteTree::iterator, bool>
UnsignedIntByteTree::insert_unique(const UnsignedIntBytePair &);
