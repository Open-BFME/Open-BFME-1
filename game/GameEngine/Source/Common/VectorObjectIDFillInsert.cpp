// cl: /DNDEBUG /MD /EHsc
// stlport

// De-lift: STLport vector<ObjectID>::_M_fill_insert, retail 0x002CCBD0,
// 251 bytes.  ObjectID is an enum, so this instantiates separately from the
// shared four-byte-POD siblings (vector<int>, vector<Object *>, vector<void *>).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ObjectID { INVALID_ID = 0 };

template class _STL::vector<ObjectID>;
