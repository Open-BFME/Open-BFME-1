// Open-BFME5: retail RVA 0x00615850, 131 bytes.
//
// The body uses the same native STLport
// hash_map<AsciiString, Rva0061C1D0Object *> at manager+0x194 as the matched
// LivingWorldManager methods at 0x006157C0, 0x006159C0 and 0x00615C20.
// In particular, it calls their same begin body 0x006115A0 through ILT
// 0x00009561 and their same bucket helper 0x00611CA0 through ILT 0x0000687A.
// Those independently owned siblings are reached by matched callers that load
// TheLivingWorldManager, establishing this body's manager receiver and map
// layout even though this body's ILT 0x0002EE33 has no named direct caller.
//
// Before traversing the map, retail guards TheAudioClientUpdate at 0x012ED668
// and dispatches its vtable slot +0x24 with the dword value 2.  The inherited
// AudioManager layout in GameAudio.h places pauseAmbient(Bool) at that slot;
// Bool is a 32-bit parameter.  The retail Miles audio vtable 0x0111C0C0 also
// routes slot +0x24 through ILT 0x0003D52D to body 0x006B86D0.
//
// Each node's +8 mapped pointer is the established Rva0061C1D0Object receiver.
// Its direct call goes through ILT 0x0001447F to body 0x0061BBB0, so the
// address-derived member below preserves that receiver rather than introducing
// a second map value type.
//
// First exact probe: 131/131 bytes with four relocations and no non-relocation
// differences, t=11min.
// campaign=luna36h-20260907 lane=expand08 model=gpt-5.6-sol-ultra.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

struct Rva005A00B0AudioClient
{
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1c() = 0;
	virtual void v20() = 0;
	virtual void pauseAmbient(int shouldPause) = 0;
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class Rva0061C1D0Object
{
public:
	void rva0061bbb0();
};

typedef _STL::hash_map<AsciiString, Rva0061C1D0Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615850Map;

class BfmeLivingWorldManager
{
public:
	void rva00615850();

private:
	unsigned char m_prefix[0x194];
	Rva00615850Map m_objects;
};

void BfmeLivingWorldManager::rva00615850()
{
	if (TheAudioClientUpdate)
		TheAudioClientUpdate->pauseAmbient(2);

	for (Rva00615850Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		it->second->rva0061bbb0();
	}
}
