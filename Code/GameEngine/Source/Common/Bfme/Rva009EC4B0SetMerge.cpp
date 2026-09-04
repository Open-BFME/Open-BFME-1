// Retail 0x009EC4B0: merge one pointer set into another, removing the
// destination node when insert_unique reports a duplicate.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class Rva009EC4B0SetHolder
{
public:
	Rva009EC4B0SetHolder &merge(Rva009EC4B0SetHolder &other);

	Rva001408C0Set m_values;
	unsigned int m_treeLayoutPad;
	volatile bool m_changed;
};

Rva009EC4B0SetHolder &Rva009EC4B0SetHolder::merge(Rva009EC4B0SetHolder &other)
{
	if (other.m_values.size() == 0)
		return *this;

	Rva001408C0Set::iterator it = other.m_values.begin();
	while (it != other.m_values.end())
	{
		_STL::pair<Rva001408C0Set::iterator, bool> result =
			m_values.insert(*it);
		if (!result.second)
			m_values.erase(result.first);
		++it;
	}
	m_changed = true;
	return *this;
}
