// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/GameClient /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x007882F0: owner and value retain address identities. The key is
// represented as an opaque 32-bit word; its original semantic type is unknown.
// Both inline find and callee 0x00787E00 hash that word by bucket count,
// compare node+4 and return the mapped pointer at node+8.
#include <hash_map>

struct Rva007882F0Value
{
	unsigned int value;
};

class Rva007882F0PointerMap
{
public:
	Rva007882F0Value *lookup(unsigned int key);

private:
	typedef _STL::hash_map<unsigned int, Rva007882F0Value *> PointerMap;

	char m_unknown[0x1c];
	PointerMap m_pointerMap;
};

Rva007882F0Value *Rva007882F0PointerMap::lookup(unsigned int key)
{
	PointerMap::iterator found = m_pointerMap.find(key);
	if (found == m_pointerMap.end())
	{
		Rva007882F0Value *value = new Rva007882F0Value();
		m_pointerMap[key] = value;
		return value;
	}
	return m_pointerMap[key];
}
