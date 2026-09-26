// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?find@Rva006123C0Table@@QAEHI@Z
// Retail 0x006123C0, 78 bytes. The banked body established an unsigned-key
// bucket lookup with 12-byte chained nodes and an int result. The STLport
// hash_map formulation below reproduces that body exactly, including the
// witnessed bucket-vector offsets at +0x214 and +0x218.
//
// No named caller, vtable slot, literal, or independent layout witness proves
// a semantic owner for this address. Rva006123C0Table is therefore deliberately
// address-derived rather than a guessed game class; `find` states only the
// operation proved by the retail bytes.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Rva006123C0Table
{
public:
	int find(unsigned int key);

private:
	unsigned char m_prefix[0x210];
	_STL::hash_map<unsigned int, int> m_lookup;
};

int Rva006123C0Table::find(unsigned int key)
{
	_STL::hash_map<unsigned int, int>::iterator it = m_lookup.find(key);
	if (it != m_lookup.end())
		return (*it).second;
	return 0;
}
