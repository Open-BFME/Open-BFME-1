// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// BFME1's ObjectID/Object* lookup table uses the STLport hashtable key-erase
// member.  This explicit instantiation supplies the clean template body that
// processDestroyList reaches through GameLogic::removeObjectFromLookupTable.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Object;

typedef _STL::pair<const int, Object *> ObjectIDPair;
typedef _STL::hashtable<ObjectIDPair, int, _STL::hash<int>,
	_STL::_Select1st<ObjectIDPair>, _STL::equal_to<int>,
	_STL::allocator<ObjectIDPair> > ObjectIDHashtable;

template unsigned int ObjectIDHashtable::erase(const int &key);
