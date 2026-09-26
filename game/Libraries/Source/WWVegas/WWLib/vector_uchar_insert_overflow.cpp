// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: _STL::vector<unsigned char>::_M_insert_overflow, retail
// 0x0074D6F0, 263 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// The element is a byte and the trailing __true_type in the signature is
// STLport's has-trivial-copy tag, so the grow path is all block moves rather
// than element loops.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

void BfmeUnsignedCharVectorInsertAnchor(_STL::vector<unsigned char> &v, const unsigned char &value)
{
	v.insert(v.begin(), value);
}
