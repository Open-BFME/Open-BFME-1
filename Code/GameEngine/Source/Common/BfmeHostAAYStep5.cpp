// Open-BFME5: retail RVA 0x006156A0, 226 bytes.
//
// BfmeHostAAY::bfmeShutdownAAY at 0x00617DB0 calls the pinned ILT 0x00010299
// for this fifth step.  The ILT reaches this body, so the shutdown caller
// establishes the owner and method name.
//
// The body walks the native AsciiString hash map at this+0x194 twice.  It
// calls BfmeThingKB::bfmeGoKB on the first walk, pauses ambient audio with
// value 2, and calls BfmeThingNA::bfmeResetStateNA on the second walk.

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

class BfmeThingKB;
class BfmeThingNA;
class Rva0061C1D0Object;

typedef _STL::hash_map<AsciiString, Rva0061C1D0Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeHostAAYMap;

class BfmeHostAAY
{
public:
	void bfmeStep5AAY();

private:
	unsigned char m_prefix[0x194];
	BfmeHostAAYMap m_objects;
};

class BfmeThingKB
{
public:
	void bfmeGoKB();
};

class BfmeThingNA
{
public:
	void bfmeResetStateNA();
};

class Rva0061C1D0Object
{
};

void BfmeHostAAY::bfmeStep5AAY()
{
	BfmeHostAAYMap::iterator it = m_objects.begin();
	while (it != m_objects.end())
	{
		((BfmeThingKB *)it->second)->bfmeGoKB();
		++it;
	}

	if (TheAudioClientUpdate)
		TheAudioClientUpdate->pauseAmbient(2);

	it = m_objects.begin();
	while (it != m_objects.end())
	{
		((BfmeThingNA *)it->second)->bfmeResetStateNA();
		++it;
	}
}
