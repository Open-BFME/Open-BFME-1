// Open-BFME5: retail RVA 0x00615B10, 210 bytes.
//
// The neighboring exact bodies at 0x006157C0, 0x00615850, 0x006159C0 and
// 0x00615C20 prove the LivingWorldManager receiver and its native STLport
// AsciiString hash map at this+0x194. This method visits every mapped
// BfmeThingNA object, then arms the manager and selects the mouse cursor 0x28
// when the global state at 0x012F7048 is ready.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

typedef bool Bool;

class BfmeThingNA
{
public:
	void bfmeGoNA();
};

typedef _STL::hash_map<AsciiString, BfmeThingNA *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615B10Map;

class Rva00615B10State
{
public:
	unsigned char m_pad00[4];
	void *m_field04;
};

class Rva00615B10Mouse
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setCursor(int cursor) = 0;
};

extern "C" __declspec(dllimport) int __stdcall ShowCursor(int show);

class BfmeLivingWorldManager
{
public:
	void rva00615b10();

	private:
	unsigned char m_prefix[0x194];
	Rva00615B10Map m_objects;
};

#define TheState (*(Rva00615B10State **)0x012F7048)
#define TheMouse (*(Rva00615B10Mouse **)0x012F4C5C)

// ?rva00615b10@BfmeLivingWorldManager@@QAEXXZ
void BfmeLivingWorldManager::rva00615b10()
{
	register BfmeLivingWorldManager *manager = this;
	for (Rva00615B10Map::iterator it = manager->m_objects.begin();
		it != manager->m_objects.end(); ++it)
	{
		it->second->bfmeGoNA();
	}

	if (TheState->m_field04)
	{
		*(Bool *)((char *)manager + 0x288) = true;
		*(Bool *)((char *)manager + 0x294) = false;
		return;
	}

	*(int *)((char *)manager + 0x290) = 0x3c;
	*(Bool *)((char *)manager + 0x294) = true;
	Rva00615B10Mouse *mouse = TheMouse;
	volatile unsigned char *cursorShown = (unsigned char *)mouse + 0x4e0c;
	if (!*cursorShown)
	{
		ShowCursor(1);
	}
	*cursorShown = 1;
	TheMouse->setCursor(0x28);
}
