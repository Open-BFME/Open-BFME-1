// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <map>
// Matched MapMetaData ctor and dtor witness a 252-byte object with 4-byte alignment.
class MapMetaData
{
public:
	MapMetaData();
	MapMetaData(const MapMetaData &);
	~MapMetaData();
private:
	unsigned storage[63];
};

typedef _STL::pair<const AsciiString, MapMetaData> MapMetaDataPair;

typedef _STL::_Rb_tree<AsciiString, MapMetaDataPair, _STL::_Select1st<MapMetaDataPair>,
	_STL::less<AsciiString>, _STL::allocator<MapMetaDataPair> > MapMetaDataTree;

// The landed hinted insertion names its 252-byte value view by its allocator RVA.
struct Rva000C1740Value {	unsigned storage[63]; };
typedef _STL::pair<const AsciiString, Rva000C1740Value> StoragePair;
typedef _STL::_Rb_tree<AsciiString, StoragePair, _STL::_Select1st<StoragePair>,
	_STL::less<AsciiString>, _STL::allocator<StoragePair> > StorageTree;

class Rva000C1D10MapCache
{
public:
	MapMetaData &operator[](const AsciiString &key);

private:
	MapMetaDataTree::iterator insert(MapMetaDataTree::iterator pos, const MapMetaDataPair &value)
	{
		StorageTree::iterator result = ((StorageTree *)&m_tree)->insert_unique(
			*(StorageTree::iterator *)&pos, *(const StoragePair *)&value);
		return MapMetaDataTree::iterator((MapMetaDataTree::_Link_type)result._M_node);
	}
	MapMetaDataTree m_tree;
};

// Existing MapCache callers use this name via ILT 00031E99.
// Keep the native map::insert inline layer: direct tree insertion adds an
// extra saved-ESP slot. Pair/default-value temporaries end at the expression.
// RvaTreeInsertUniqueHint.cpp and RvaTreeMInsertStringKey.cpp establish the
// insertion ABI's 252-byte mapped storage. Adapt only this existing view;
// do not add another pin to the conflicting MapMetaData template name.
MapMetaData &Rva000C1D10MapCache::operator[](const AsciiString &key)
{
	MapMetaDataTree::iterator it = m_tree.lower_bound(key);

	if (it == m_tree.end() || key.compare(it->first) < 0)
		it = insert(it, MapMetaDataPair(key, MapMetaData()));
	return it->second;
}
