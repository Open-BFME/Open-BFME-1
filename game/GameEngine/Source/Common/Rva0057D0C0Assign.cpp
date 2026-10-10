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

struct Rva0057D0C0Pod
{
	int a[10];
};

class Rva0057D0C0
{
	int m_00;
	Rva005672C0Map m_04;
	Rva00630D00UStr m_10;
	Rva0057D0C0Pod m_14;

public:
	Rva0057D0C0 &operator=(const Rva0057D0C0 *other);
};

Rva0057D0C0 &Rva0057D0C0::operator=(const Rva0057D0C0 *other)
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
	m_14 = *(Rva0057D0C0Pod *)((char *)other + 0x14);
	return *this;
}
