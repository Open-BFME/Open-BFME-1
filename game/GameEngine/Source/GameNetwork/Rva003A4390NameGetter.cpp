// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Opaque retail twins that used to sit on the pristine Zero Hour
// ConnectionManager.cpp, which kept that whole reference object (and its many
// non-retail strong bodies) in the link.
//
// - Nine 32-byte bodies (?dup_003a4390 and siblings): return by value the
//   string member at +4 of a polymorphic object, copied through the narrow
//   StringBase<char> copy constructor 0x00887B60. Zero Hour's
//   User::GetName has this shape; the BFME owner class is unproven, so the
//   carrier keeps an address-derived name.
// - Two 31-byte bodies (?dup_0037c2e0, ?dup_00668a60):
//   map<unsigned short,int>::insert(const value_type &), forwarding to
//   _Rb_tree::insert_unique.

#include <map>

#include "ascii_string.h"

class Rva003A4390Owner
{
public:
	virtual ~Rva003A4390Owner();
	AsciiString getName();

	AsciiString m_name;
};

AsciiString Rva003A4390Owner::getName()
{
	return m_name;
}

typedef _STL::map<unsigned short, int> Rva0037C2E0Map;

template Rva0037C2E0Map::iterator Rva0037C2E0Map::insert(Rva0037C2E0Map::iterator, const Rva0037C2E0Map::value_type &);
