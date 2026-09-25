// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
// AptMapPreview map-name update, retail 0x005217A0 (391 bytes).
//
// Owner: the named callback AptMapPreview::mapGadgetInit (0x00521990, string
// "AptMapPreview::MapGadgetInit") passes its unchanged receiver and the string
// at +0x00 through ILT 0x0003EC57; this body forwards the same receiver to the
// AptMapPreview helpers at 0x005216B0, 0x00520920, 0x00521390, 0x00521000 and
// 0x00520E70. The method keeps its address token.
//
// An empty name refreshes the preview with no metadata. Otherwise the lowered
// name is looked up in TheMapCache (ILT 0x000263D7); a cached entry refreshes
// the preview from its MapMetaData (node +0x14), and an unknown map fills the
// preview's own metadata (+0x3C) with the file-name title and refreshes.
//
// Same-TU companions (docs/shape_levers.md, "Compiler-private ABI: compile the
// static helper with its caller"): retail inlines the empty-name call to
// 0x005216B0 together with 0x005208D0, and the inlined description setter's
// dead by-value UnicodeString path is what makes VC7.1 save EBP in the
// prologue. Both companion bodies are the landed ones (AptMapPreview.cpp and
// AptMapPreviewSetMapDescription.cpp) and independently match retail here;
// they are already claimed and get no coverage credit from this file.

#include "ascii_string.h"
#include "unicode_string.h"

extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *, int);

// Retail's inline str() falls back to the empty text at 0x0107388B.
extern char g_bfmeEmptyAscii[];

template <typename T> inline int StringBase<T>::getLength() const
{
	return m_data ? m_data->length : 0;
}
template <> inline const char *StringBase<char>::str() const
{
	return m_data ? &m_data->data[0] : g_bfmeEmptyAscii;
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other)
{
	((StringBase<unsigned short> *)this)->set(
		*(const StringBase<unsigned short> *)&other);
	return *this;
}

class GameWindow;
class Image;
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite);

// Offsets used here: +0x00 display name, +0x20 player count and +0x50 file
// name follow MapMetaData_ctor.cpp; +0xF4 is written with the same title.
class MapMetaData
{
public:
	UnicodeString bfme_getDescriptionFirstLine();

	UnicodeString m_displayName;
	char m_bfmePad04[0x1c];
	int m_numPlayers;
	char m_bfmePad24[0x2c];
	AsciiString m_fileName;
	char m_bfmePad54[0xa0];
	UnicodeString m_unmodelledF4;
};

// MapCache::find returns the tree node; the cache's end node is at +0x00 and
// a node's MapMetaData value starts at +0x14 (as in MapUtil_isValidMap_Thunk.cpp).
struct MapCacheNode
{
	char m_links[0x14];
	MapMetaData second;
};

class MapCache
{
public:
	MapCacheNode *find(const AsciiString &name);
	MapCacheNode *m_end;
};

extern MapCache *TheMapCache;

// Layout as witnessed by AptMapPreviewConstructor.cpp and AptMapPreview.cpp.
class AptMapPreview
{
public:
	void rva005216B0(MapMetaData *metadata);
	void rva00521390(MapMetaData *metadata);
	void rva00521000(MapMetaData *metadata);
	void bfmeSetMapTitle(MapMetaData *metadata);
	void bfmeSetMapDescription(MapMetaData *metadata);
	void bfmeSetMapPicture(MapMetaData *metadata);
	void rva005217A0(const AsciiString &mapName);

private:
	AsciiString m_baseString;
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	GameWindow *m_children[8];
	const Image *m_picture;
	bool m_pictureOwned;
	bool m_flag39;
	char m_padding3a[2];
	MapMetaData *m_mapData;
};

// Companion, retail 0x005208D0 (landed in AptMapPreviewSetMapDescription.cpp).
void AptMapPreview::bfmeSetMapDescription(MapMetaData *map)
{
	if (m_mapDescription)
	{
		GadgetListBoxReset(m_mapDescription);
		if (map)
			GadgetListBoxAddEntryText(m_mapDescription,
				map->bfme_getDescriptionFirstLine(), -1, -1, -1, true);
	}
}

// Companion, retail 0x005216B0 (landed in AptMapPreview.cpp).
void AptMapPreview::rva005216B0(MapMetaData *metadata)
{
	if (metadata != 0)
		m_baseString = metadata->m_fileName;
	else
		((StringBase<char> *)&m_baseString)->set("", 0);
	bfmeSetMapTitle(metadata);
	rva00521390(metadata);
	rva00521000(metadata);
	bfmeSetMapDescription(metadata);
	bfmeSetMapPicture(metadata);
}

// ?rva005217A0@AptMapPreview@@QAEXABVAsciiString@@@Z
void AptMapPreview::rva005217A0(const AsciiString &mapName)
{
	if (mapName.getLength() == 0)
	{
		rva005216B0(0);
		return;
	}

	AsciiString lowerMap(mapName);
	lowerMap.toLower();
	MapCache *cache = TheMapCache;
	MapCacheNode *it = cache->find(lowerMap);
	if (it != cache->m_end)
	{
		rva005216B0(&it->second);
	}
	else
	{
		UnicodeString title;
		AsciiString fileTitle(strrchr(mapName.str(), '\\') + 1);
		title.translate(fileTitle);
		m_mapData->m_numPlayers = 1;
		m_mapData->m_displayName = title;
		m_mapData->m_unmodelledF4 = title;
		m_mapData->m_fileName = mapName;
		rva005216B0(m_mapData);
	}
}
