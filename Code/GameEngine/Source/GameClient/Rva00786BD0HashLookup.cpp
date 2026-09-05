// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
//
// 70B twin of ?findDrawableByID@GameClient@@QAEPAVDrawable@@I@Z
// (GameClientFindDrawableByID.cpp, retail 0x00430AF0): identical
// bucket-divide/chain-walk shape over a hash_map<unsigned int, void *>, but
// the map sits 8 bytes into the object here instead of 0x18, so the
// class prefix ahead of it is 8 bytes, not 0x14. Address-derived name
// pending the real owning class/caller.

class Rva00786BD0Owner
{
public:
	void *find(unsigned int key);

private:
	unsigned char m_prefix[8];
	_STL::hash_map<unsigned int, void *> m_lookup;
};

// ?find@Rva00786BD0Owner@@QAEPAXI@Z
void *Rva00786BD0Owner::find(unsigned int key)
{
	_STL::hash_map<unsigned int, void *>::iterator it = m_lookup.find(key);
	if (it == m_lookup.end())
		return 0;
	return (*it).second;
}
