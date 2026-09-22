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
// position is reached only when the FIRST leading word is written during
// member construction -- here the inlined AsciiString default constructor at
// +0x24 -- and the other four are written from the body. Initialising all
// five before the body hoists the xor above `push esi` (five bytes off);
// writing all five from the body sinks it below
// the EH `this` spill (seven bytes off), which is where twelve earlier
// sessions stalled.

typedef unsigned short UnsignedShort;

extern "C" void *memset(void *, int, unsigned int);
#pragma intrinsic(memset)

void * __cdecl operator new(unsigned int);

class GameWindow;
class Image;

#include "ascii_string.h"

// 0x00887D20 carries the ledger's own name for the narrow set(), which is a
// C++ alias of ?set@?$StringBase@D@@QAEXPBDH@Z. The class is AsciiString's
// layout under the ledger's spelling: one heap pointer, and the ledger's
// ??1RetailLayoutString@@QAE@XZ is the same ILT 0x0000D828 as ~AsciiString.
class RetailLayoutString
{
public:
	void set(const char *text, int length);

private:
	char *m_text;
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

// Empty literals the constructor seeds the metadata strings with. The narrow
// one carries the ledger's address-derived name. The wide one is the pinned
// empty wide literal at 0x01088AF4: retail .rdata holds four zero bytes there,
// immediately ahead of L"UserDataLeafName" at 0x01088AF8. MSVC 7.1 wchar_t is
// unsigned short, so the literal's element type is G in the mangled callee.
extern const unsigned short g_Rva01088AF4EmptyWideString[];
extern const char g_Rva0107301CEmptyString[];
extern __declspec(dllimport) unsigned __cdecl bfmeLenVGI(const UnsignedShort *text);

// Layout witnessed by AptMapPreview.cpp: windows at +04..+10, the image at
// +34 and its owned flag at +38. +39 stays unmodelled; +3C is the metadata
// this constructor allocates. +0x00 is an AsciiString, named by retail's own
// unwind map rather than guessed: tools/eh_info.py 0x00520670 shows state 0's
// cleanup at 0x00C2FEE0 loading the `this` spill ([ebp-0x14]) into ecx and
// jumping to ILT 0x0000D828 -> 0x0005EE90 = ??1AsciiString@@QAE@XZ. Its
// inlined default constructor is the `mov [esi],ebx` at +0x24, and that
// destructor state is what keeps the second frame slot live. The span at
// +0x14..+0x33 is read as eight window pointers by the gadget-callback
// witness quoted in AptMapPreview.cpp.
class AptMapPreview
{
public:
	AptMapPreview();

private:
	AsciiString m_string00;
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	GameWindow *m_children[8];
	const Image *m_picture;
	bool m_pictureOwned;
	bool m_unmodelled39;
	char m_padding3a[2];
	MapMetaData *m_mapData;
};

// ??0AptMapPreview@@QAE@XZ
AptMapPreview::AptMapPreview()
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
