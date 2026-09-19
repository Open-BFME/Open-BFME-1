// Open-BFME5: retail RVA 0x00615900, 144 bytes.
//
// Exact adjacent methods at 0x006157C0, 0x00615850, 0x006159C0 and
// 0x00615C20 independently establish the LivingWorldManager receiver and its
// native STLport AsciiString/BfmeThingNA pointer map at +0x194.  This body
// sets the manager flags at +0x288/+0x294, passes its Coord2D argument to the
// matched BfmeThingNA update at 0x0061C220, then dispatches InGameUI slot
// +0x5C.  The public method spelling is not retained, so it stays
// address-derived while preserving the proven owner and argument type.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class BfmeThingNA
{
public:
	void bfmeUpdateBFromPointNA(const Coord2D &point);
};

typedef _STL::hash_map<AsciiString, BfmeThingNA *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615900Map;

class Rva00615900InGameUI
{
public:
	virtual void v00() = 0; virtual void v04() = 0;
	virtual void v08() = 0; virtual void v0c() = 0;
	virtual void v10() = 0; virtual void v14() = 0;
	virtual void v18() = 0; virtual void v1c() = 0;
	virtual void v20() = 0; virtual void v24() = 0;
	virtual void v28() = 0; virtual void v2c() = 0;
	virtual void v30() = 0; virtual void v34() = 0;
	virtual void v38() = 0; virtual void v3c() = 0;
	virtual void v40() = 0; virtual void v44() = 0;
	virtual void v48() = 0; virtual void v4c() = 0;
	virtual void v50() = 0; virtual void v54() = 0;
	virtual void v58() = 0;
	virtual void rvaSlot5c() = 0;
};

extern Rva00615900InGameUI *TheInGameUI;

class BfmeLivingWorldManager
{
public:
	void rva00615900(const Coord2D &point);

private:
	unsigned char m_prefix[0x194];
	Rva00615900Map m_objects;
	unsigned char m_middle[0x288 - 0x194 - sizeof(Rva00615900Map)];
	bool m_flag288;
	unsigned char m_tail[0x294 - 0x289];
	bool m_flag294;
};

void BfmeLivingWorldManager::rva00615900(const Coord2D &point)
{
	m_flag288 = true;
	m_flag294 = false;

	for (Rva00615900Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		it->second->bfmeUpdateBFromPointNA(point);
	}

	TheInGameUI->rvaSlot5c();
}
