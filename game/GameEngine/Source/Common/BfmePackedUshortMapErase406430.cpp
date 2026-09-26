// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x00406430 (113B): sibling of findPacked @ 0x4063C0. Same undirected
// ushort-pair pack into map<unsigned,Val20> at +0x235FC, find (out-of-line),
// then inlined erase(iterator): rebalance + delete 0x34 + size--.

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
	void erasePacked(unsigned short a, unsigned short b);

private:
	char m_pad[0x235FC];
	BfmePackedUshortMap m_map;
};

// ?erasePacked@BfmePackedUshortMapHost@@QAEXGG@Z
void BfmePackedUshortMapHost::erasePacked(unsigned short a, unsigned short b)
{
	if (a == b)
		return;
	if (a > b)
	{
		unsigned short t = a;
		a = b;
		b = t;
	}
	unsigned key = ((unsigned)a << 16) | (unsigned)b;
	BfmePackedUshortMap::iterator it = m_map.find(key);
	if (it != m_map.end())
		m_map.erase(it);
}
