// cl: /O2 /Ob0
// stlport

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include <map>

enum NameKeyType;
extern template class _STL::_Rb_tree<NameKeyType,
	_STL::pair<const NameKeyType, float>,
	_STL::_Select1st<_STL::pair<const NameKeyType, float> >,
	_STL::less<NameKeyType>,
	_STL::allocator<_STL::pair<const NameKeyType, float> > >;

class Rva005672C0Map
{
public:
	Rva005672C0Map &operator=(const Rva005672C0Map &other);

private:
	int m_pad[3];
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva00567460
{
	int m_00;
	Rva005672C0Map m_04;
	Rva00630D00UStr m_10;

public:
	Rva00567460 &operator=(const Rva00567460 *other);
};

Rva00567460 &Rva00567460::operator=(const Rva00567460 *other)
{
	*reinterpret_cast<_STL::_Rb_tree<NameKeyType,
		_STL::pair<const NameKeyType, float>,
		_STL::_Select1st<_STL::pair<const NameKeyType, float> >,
		_STL::less<NameKeyType>,
		_STL::allocator<_STL::pair<const NameKeyType, float> > > *>(&m_04) =
		*reinterpret_cast<const _STL::_Rb_tree<NameKeyType,
			_STL::pair<const NameKeyType, float>,
			_STL::_Select1st<_STL::pair<const NameKeyType, float> >,
			_STL::less<NameKeyType>,
			_STL::allocator<_STL::pair<const NameKeyType, float> > > *>(
				other ? &other->m_04 : 0);
	reinterpret_cast<StringBase<unsigned short> *>(&m_10)->set(
		*reinterpret_cast<const StringBase<unsigned short> *>((char *)other + 0x10));
	return *this;
}
