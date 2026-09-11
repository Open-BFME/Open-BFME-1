// Open-BFME5: retail RVA 0x00616240, 178 bytes.
//
// BfmeLivingWorldManager find-or-insert factory. If the item argument is
// non-null, builds an AsciiString key from the item's name (BfmeItemAM's
// getName, matched caller at retail 0x00617A10), looks it up in the same
// +0x224 AsciiString table the matched rva00615cb0/rva00615d50/rva00616410
// siblings walk, and on miss constructs a Rva00618600Poly(which, (int)item,
// second) and inserts it under that key. Its public method spelling is not
// recovered and therefore remains address-derived, matching its siblings.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

	bool operator==(const BFMERetailAsciiString &other) const
	{
		return strcmp((const char *)m_bfmeBufXB, (const char *)other.m_bfmeBufXB) == 0;
	}

	void *m_bfmeBufXB;

private:
	void releaseBuffer();
};

namespace rts
{
	template<> struct hash<BFMERetailAsciiString>
	{
		size_t operator()(BFMERetailAsciiString ast) const
		{
			std::hash<const char *> tmp;
			return tmp((const char *)ast.m_bfmeBufXB);
		}
	};
}

class BfmeItemAM
{
public:
	BFMERetailAsciiString getName();
};

class Rva00618600Poly
{
public:
	Rva00618600Poly(int which, int first, int second);

	unsigned char m_pad[0x24];
};

typedef _STL::hash_map<BFMERetailAsciiString, Rva00618600Poly *,
	rts::hash<BFMERetailAsciiString>, _STL::equal_to<BFMERetailAsciiString> > Rva00616240Map;

class BfmeLivingWorldManager
{
public:
	void rva00616240(BfmeItemAM *item, int which, int second);

private:
	unsigned char m_prefix[0x224];
	Rva00616240Map m_objects;
};

void BfmeLivingWorldManager::rva00616240(BfmeItemAM *item, int which, int second)
{
	if (item == 0)
		return;

	BFMERetailAsciiString key = item->getName();

	if (m_objects.find(key) == m_objects.end())
	{
		Rva00618600Poly *poly = new Rva00618600Poly(which, (int)item, second);
		m_objects[key] = poly;
	}
}
