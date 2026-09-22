// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
// AptMapPreview constructor, retail 0x00520670, 257 bytes.
//
// Identity: the landed reset at 0x005207C0 (?bfmeReset@AptMapPreview@@QAEXXZ
// in AptMapPreview.cpp) clears exactly the members this body initialises, in
// the same idiom -- the four window pointers at +04..+10 and the image pair at
// +34/+38 through a zero register, then `add esi,0x14` and eight dword stores
// over +14..+30. The caller
// ??0SkirmishScreenState@@QAE@PAVGen00529110Owner@@H@Z builds this object at
// SkirmishScreenState+0x28 through ILT 0x0004081D, and AptMapPreview.cpp
// already records 0x00520670 as the constructor that writes through +3C.
//
// Shape note (docs/shape_levers.md, constant materialisation): retail puts
// `xor ebx,ebx` between the `this` copy and the deferred `push edi`. That
// position is reached only when the FIRST leading word is written from the
// constructor's member-initialiser list and the other four are written from
// the body. Initialising all five from the list hoists the xor above
// `push esi` (five bytes off); writing all five from the body sinks it below
// the EH `this` spill (seven bytes off), which is where twelve earlier
// sessions stalled.

typedef unsigned short UnsignedShort;

extern "C" void *memset(void *, int, unsigned int);
#pragma intrinsic(memset)

void * __cdecl operator new(unsigned int);

class GameWindow;
class Image;

#include "string_base.h"

// 0x00887D20 carries the ledger's own name for the narrow set(), which is a
// C++ alias of ?set@?$StringBase@D@@QAEXPBDH@Z.
class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

// Field names follow the landed model in MapMetaData_ctor.cpp; the extent
// block between +08 and +1F is untouched here and stays raw storage.
class MapMetaData
{
public:
	MapMetaData();
	~MapMetaData();

	StringBase<UnsignedShort> m_displayName;
	StringBase<UnsignedShort> m_description;
	char m_extents[0x18];
	int m_numPlayers;
	unsigned char m_isMultiplayer;
	unsigned char m_isScenarioMP;
	unsigned char m_isOfficial;
	char m_unmodelled27[0x29];
	RetailLayoutString m_fileName;
	char m_unmodelled54[0xa8];
};

// preview+0x14..+0x33. The gadget-callback witness quoted in AptMapPreview.cpp
// reads this span as eight window pointers. Retail's unwind map additionally
// keeps a destructor state live over it from before the metadata allocation,
// so the span is modelled as a destructible record parked under its address:
// dropping the destructor costs the second frame slot and seven bytes of the
// prologue. What that destructor releases is not proven here.
class Rva00520670Children
{
public:
	~Rva00520670Children();

	GameWindow *m_children[8];
};

// Empty literals the constructor seeds the metadata strings with. The narrow
// one carries the ledger's address-derived name; the wide one at 0x01088AF4
// (two zero bytes ahead of L"UserDataLeafName") has no pin yet.
extern const UnsignedShort g_Rva01088AF4EmptyWideString[];
extern const char g_Rva0107301CEmptyString[];
extern __declspec(dllimport) unsigned __cdecl bfmeLenVGI(const UnsignedShort *text);

// Layout witnessed by AptMapPreview.cpp: windows at +04..+10, the image at
// +34 and its owned flag at +38. +00 and +39 stay unmodelled; +3C is the
// metadata this constructor allocates.
class AptMapPreview
{
public:
	AptMapPreview();

private:
	int m_unmodelled00;
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	Rva00520670Children m_children;
	const Image *m_picture;
	bool m_pictureOwned;
	bool m_unmodelled39;
	char m_padding3a[2];
	MapMetaData *m_mapData;
};

// ??0AptMapPreview@@QAE@XZ
AptMapPreview::AptMapPreview()
	: m_unmodelled00(0)
{
	m_currentMap = 0;
	m_mapPicture = 0;
	m_mapInfo = 0;
	m_mapDescription = 0;
	m_picture = 0;
	m_pictureOwned = false;
	m_unmodelled39 = false;
	m_mapData = 0;
	memset(&m_children, 0, sizeof(m_children));
	m_mapData = new MapMetaData;
	StringBase<UnsignedShort> *description = &m_mapData->m_description;
	description->set(g_Rva01088AF4EmptyWideString,
		bfmeLenVGI(g_Rva01088AF4EmptyWideString));
	MapMetaData *map = m_mapData;
	map->m_displayName.set(g_Rva01088AF4EmptyWideString,
		bfmeLenVGI(g_Rva01088AF4EmptyWideString));
	m_mapData->m_isOfficial = 0;
	m_mapData->m_fileName.set(g_Rva0107301CEmptyString, 0);
	m_mapData->m_numPlayers = 8;
	m_mapData->m_isMultiplayer = 1;
}
