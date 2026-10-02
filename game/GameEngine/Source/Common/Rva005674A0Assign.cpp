// cl: /O2 /Ob0 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>
#include <list>
#include "unicode_string.h"

enum NameKeyType {};

typedef _STL::pair<const NameKeyType, float> NameKeyFloatPair;
typedef _STL::_Rb_tree<NameKeyType, NameKeyFloatPair,
	_STL::_Select1st<NameKeyFloatPair>, _STL::less<NameKeyType>,
	_STL::allocator<NameKeyFloatPair> > Rva005672C0Map;
typedef _STL::list<UnicodeString> Rva005673A0Vec;

// ILTs 0x00013403 and 0x0002099B reach the existing container assignments
// at 0x005672C0 and 0x005673A0. Reference their owners without instantiating
// another set of container methods in this TU.
extern template class _STL::_Rb_tree<NameKeyType, NameKeyFloatPair,
	_STL::_Select1st<NameKeyFloatPair>, _STL::less<NameKeyType>,
	_STL::allocator<NameKeyFloatPair> >;
extern template class _STL::list<UnicodeString>;

class Rva005674A0
{
	int m_00;
	Rva005672C0Map m_04;
	UnicodeString m_10;
	Rva005673A0Vec m_14;

public:
	Rva005674A0 &operator=(const Rva005674A0 *other);
};

Rva005674A0 &Rva005674A0::operator=(const Rva005674A0 *other)
{
	m_04 = *(other ? &other->m_04 : 0);
	((StringBase<unsigned short> *)&m_10)->set(
		*(const StringBase<unsigned short> *)((const char *)other + 0x10));
	m_14 = *(Rva005673A0Vec *)((char *)other + 0x14);
	return *this;
}
