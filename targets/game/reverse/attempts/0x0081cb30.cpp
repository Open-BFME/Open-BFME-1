// ?init@VideoPlayer@@UAEXXZ
// partial score=0.68 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// ?init@VideoPlayer@@UAEXXZ -- retail RVA 0x0081CB30, 574 bytes.
// Banked body. The include below is relative to
// game/GameEngine/Source/GameClient/, so copy the file there to probe it:
// cp targets/game/reverse/attempts/0x0081cb30.cpp \
//    game/GameEngine/Source/GameClient/VideoPlayerInit.cpp
// Findings vs the previous 0.62 banked attempt:
//  - the loop condition re-reads BOTH table globals every iteration, so retail
//    recomputes (end-begin)/0x1c and keeps the byte offset in a stack slot
//    while the element counter lives in EBP.  Caching begin/end in locals (as
//    the banked attempt does) is what kept `this` in EDI and cost the frame
//    four bytes.
//  - retail's EH word at [esp+0x10b8] is a COUNT of active cleanup scopes, not
//    a depth: 1 = path live, 2 = + operator new, 1 = after the placement new,
//    3 = + subtitle INI + by-value temp, 1, 0, -1.
//  - the two INI parse callbacks are the same ILT thunk that routes to
//    INI::parseVideoDefinition (0x000C3480) and retail pushes the THUNK
//    address 0x0041BB4E, not the function's.
#include <new.h>

#include "../../Include/GameClient/Video.h"

class Xfer;

// Read-only view of the canonical StringBase allocation header: refcount +0,
// length +4, capacity +6, text +8. init() inlines these two reads.
struct BfmeStringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

struct BfmeStringObject
{
	BfmeStringHeader *m_data;
};

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1
};

extern const char Rva006A16B0Empty[]; // retail 0x0107388B
extern Video *g_bfmeVideoTableBegin; // retail 0x0130B19C
extern Video *g_bfmeVideoTableEnd;   // retail 0x0130B1A0

// retail 0x00853CB0 takes the parse callback as its FOURTH argument; the third
// is the xfer. The mangling below is the pinned spelling of that overload.
class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, int loadType, Xfer *xfer,
		void (__cdecl *parse)(INI *));

private:
	char m_storage[0x848];
};

// parseSubtitle (0x0081D7C0) is the callback for the per-movie subtitle INI.
extern void parseSubtitle(INI *, void *, void *, const void *);

// The path local is a StringBase<char>: retail calls the 0x00887D60 concat on
// it directly and releases it with 0x00887940 at the end of the body.
class AsciiStringAB : public AsciiString
{
public:
	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}
};

// The movie-path object; bfmeMakeNameAB is pinned at 0x0081C7E0 and its mangling
// carries AsciiStringAB&, so the local path string must be that type.
class BfmeHookAB
{
public:
	void bfmeMakeNameAB(AsciiStringAB &out);
};

// 0x0081DA30 reads exactly three stack arguments and returns with `ret 0xc`.
class SubtitleManager
{
public:
	SubtitleManager(void *createEntry, void *second, const AsciiString &name);
};

// Witnessed layout: +0x0c movie-path hook, +0x10 subtitle-entry factory.
class VideoPlayer
{
public:
	virtual void init();

	char m_pad0c[0x0c];
	BfmeHookAB *m_moviePath;
	void *m_createSubtitleEntry;
};

static unsigned char s_videoPlayerInitialised;

// ?init@VideoPlayer@@UAEXXZ
void VideoPlayer::init(void)
{
	if (s_videoPlayerInitialised == 0)
	{
		INI ini;
		ini.load(AsciiString("Data\\INI\\Default\\Video.ini"),
			INI_LOAD_OVERWRITE, 0, (void (__cdecl *)(INI *))0x0041BB4E);
		ini.load(AsciiString("Data\\INI\\Video.ini"),
			INI_LOAD_OVERWRITE, 0, (void (__cdecl *)(INI *))0x0041BB4E);

		for (unsigned int index = 0;
			index < (unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin) / sizeof(Video);
			index++)
		{
			Video *video = g_bfmeVideoTableBegin + index;
			if (video->m_hasSubtitles)
			{
				if (m_createSubtitleEntry != 0 && m_moviePath != 0)
				{
					AsciiStringAB path;
					m_moviePath->bfmeMakeNameAB(path);

					const BfmeStringObject *name =
						(const BfmeStringObject *)&video->m_internalName;
					int length = name->m_data ? name->m_data->m_length : 0;
					const char *text = name->m_data
						? name->m_data->m_text : Rva006A16B0Empty;
					path.concat(text, length);
					path.concat(".ini", 4);

					void *storage = ::operator new(sizeof(SubtitleManager));
					if (storage != 0)
					{
						video->m_subtitleManager = new (storage) SubtitleManager(
							m_createSubtitleEntry, m_moviePath, path);
					}
					else
					{
						video->m_subtitleManager = 0;
					}

					{
						INI subtitleIni;
						subtitleIni.load(path, INI_LOAD_OVERWRITE, 0,
							(void (__cdecl *)(INI *))parseSubtitle);
					}
				}
			}
		}

		s_videoPlayerInitialised = 1;
	}
}
