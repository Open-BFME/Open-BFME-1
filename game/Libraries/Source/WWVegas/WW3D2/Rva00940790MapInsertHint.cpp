// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /MD /EHsc
// stlport
// Retail 0x00940790 (31 B): a second, directly linked copy of
// map<unsigned short, unsigned char>::insert(iterator, const value_type &).
// Its bytes equal the canonical copy at 0x00668A30 (ConnectionManager.cpp),
// but it calls the duplicate _Rb_tree::insert_unique hint body at 0x009401F0
// (the ConnectionManager.cpp COMDAT's byte twin) with a direct rel32 instead
// of the ILT 0x0000DE77, so it belongs to a different statically linked unit
// beside the WW3D2 font/sentence code. Retail has no identical-COMDAT folding,
// so the owner stays address-scoped over STLport's own tree.
#include <map>

typedef _STL::map<unsigned short, unsigned char> Rva00940790StlMap;
typedef _STL::_Rb_tree<unsigned short, Rva00940790StlMap::value_type,
	_STL::_Select1st<Rva00940790StlMap::value_type>, _STL::less<unsigned short>,
	Rva00940790StlMap::allocator_type> Rva00940790Tree;

class Rva00940790Map
{
public:
	Rva00940790StlMap::iterator insert(Rva00940790StlMap::iterator position, const Rva00940790StlMap::value_type &value);

private:
	Rva00940790Tree m_tree;
};

Rva00940790StlMap::iterator Rva00940790Map::insert(Rva00940790StlMap::iterator position, const Rva00940790StlMap::value_type &value)
{
	return m_tree.insert_unique(position, value);
}
