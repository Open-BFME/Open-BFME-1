// cl: /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
#include <stl/_tree.h>

struct PrefMapNodeShim
{
	char m_unreconstructed00[ 0x10 ];
	int m_key;
};

struct PrefMapShim
{
	char m_unreconstructed00[ 8 ];
	PrefMapNodeShim *m_begin;
};
class Rva0036E3E0KeySet
{
public:
	bool containsDifferentKey(int key, int unused) const;

private:
	char m_unreconstructed00[ 0x108 ];
	PrefMapShim *m_map;
};

bool Rva0036E3E0KeySet::containsDifferentKey(int key, int) const
{
	PrefMapShim *map = m_map;
	PrefMapNodeShim *node = map->m_begin;
	while( node != (PrefMapNodeShim *)map )
	{
		if( node->m_key != key )
			return true;
		node = (PrefMapNodeShim *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)node);
	}
	return false;
}

// @?containsDifferentKey@Rva0036E3E0KeySet@@QBE_NHH@Z 0x0036E3E0
