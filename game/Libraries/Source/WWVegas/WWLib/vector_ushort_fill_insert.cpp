// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0093FC10/294 and 0x006288F0/263 are reproduced with the
// stock STLport two-byte scalar vector carrier. This proves the bodies
// and layout, not unsigned-versus-signed element identity; no corresponding
// reloc_names.csv identity entry exists. The latter body is a distinct
// code-generation variant from the typed helper at 0x003C16A0.
#define _STLP_NO_EXCEPTIONS 1
// Scope this address-qualified helper identity to this one instantiation.
#define _M_insert_overflow Rva006288F0InsertOverflow
#include <vector>
#undef _M_insert_overflow

void BfmeUnsignedShortVectorFillInsertAnchor(_STL::vector<unsigned short> &v,
	unsigned int n, const unsigned short &value)
{
	v.insert(v.begin(), n, value);
}
