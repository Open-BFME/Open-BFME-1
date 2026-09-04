// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x004063C0 (82B): thiscall on a host that owns map<unsigned, Val20>
// at +0x235FC. Packs two ushort args into an undirected dword key
// (min<<16)|max, then returns &it->second or null. Early-out when the two
// ushorts are equal.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

struct BfmePackedMapVal20
{
	char m_bytes[0x20];
};

typedef _STL::map<unsigned, BfmePackedMapVal20> BfmePackedUshortMap;

class BfmePackedUshortMapHost
{
public:
	BfmePackedMapVal20 *findPacked(unsigned short a, unsigned short b);

private:
	char m_pad[0x235FC];
	BfmePackedUshortMap m_map;
};

// ?findPacked@BfmePackedUshortMapHost@@QAEPAUBfmePackedMapVal20@@GG@Z
BfmePackedMapVal20 *BfmePackedUshortMapHost::findPacked(unsigned short a, unsigned short b)
{
	if (a == b)
		return 0;
	if (a > b)
	{
		unsigned short t = a;
		a = b;
		b = t;
	}
	unsigned key = ((unsigned)a << 16) | (unsigned)b;
	BfmePackedUshortMap::iterator it = m_map.find(key);
	if (it != m_map.end())
		return &it->second;
	return 0;
}
