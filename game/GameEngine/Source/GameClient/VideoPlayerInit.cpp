// ?init@VideoPlayer@@UAEXXZ -- retail RVA 0x0081CB30, 574 bytes.
// cl: /DNDEBUG /MD /EHsc
//
// Recovered shape (each claim is checked against the retail bytes):
//  - a single-shot guard: the byte global at 0x0130B194 is read before the
//    callee-saved pushes and set to 1 after the table walk, so the whole body
//    is one `if` block.
//  - the loop bound is the POINTER DIFFERENCE of the two table globals, not a
//    byte count divided by sizeof(Video): retail's `imul 0x92492493 / add /
//    sar 4 / mov / shr 31 / add` is exactly what MSVC 7.1 emits for
//    `(unsigned)(g_end - g_begin)` on 28-byte elements, and adding a
//    `/ sizeof(Video)` appends a SECOND division by 28 that retail does not
//    have.  Both globals are re-read every iteration.
//  - the EH word at [esp+0x10b8] is a count of live cleanup scopes
//    (1 path, 2 +operator new, 1 after the placement new, 3 +subtitle INI
//    and the by-value temp, 1, 0, -1), not a nesting depth.
//  - the two INI parse callbacks are one ILT thunk (0x0041BB4E) that routes to
//    INI::parseVideoDefinition; retail pushes the THUNK address, not the
//    function's.
//  - bfmeMakeNameAB is called on `this`: BfmeHookAB is a 0x0c-byte base of
//    VideoPlayer (vptr, four pad bytes, the movie-name callback at +0x08), so
//    VideoPlayer's own members start at +0x0c.
//  - the SubtitleManager block is a plain `new` expression, not an explicit
//    `::operator new` plus a placement new: retail's `push 0x64 / call
//    ??2@YAPAXI@Z / add esp,4 / mov [esp+0x1c],eax / cmp / state 2 / je /
//    ctor / jmp / xor eax,eax` is what MSVC 7.1 emits for the new-expression
//    when its class operator new is this project's non-throwing one -- the
//    single store, the free-on-unwind cleanup (tools/eh_info.py state 2 calls
//    operator delete on the saved pointer) and the null arm all come from it.
//    Writing the allocation and the construction as separate statements costs
//    a fifth frame dword, because the pointer then needs a local of its own.
//  - the `Video *` local is load-bearing too: with the record addressed as
//    `g_bfmeVideoTableBegin[index]` the index stays an index and retail's
//    byte-offset induction slot (read back as `mov ecx,[esp+0x14]` at the loop
//    head, `add edi,0x1c` in the tail) disappears with it.
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
extern Video *g_bfmeVideoTableBegin; // retail 0x0130B19C
extern Video *g_bfmeVideoTableEnd;   // retail 0x0130B1A0

// sizeof(INI) is 0x848: the two locals sit at [esp+0x20] and [esp+0x868].
// The third load argument is the parse callback; the second is a flag the
// pinned spelling carries as an int and retail pushes as zero.
extern void j_0001bb4e();

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, int loadType, int reload, void *parseVideo);

private:
	char m_storage[0x848];
};

// parseSubtitle (0x0081D7C0) is the callback for the per-movie subtitle INI.
extern void parseSubtitle(INI *, void *, void *, const void *);

// The path local is a StringBase<char>: retail calls the 0x00887D60 concat on
// it directly and releases it with 0x0087940 at the end of the body.
class AsciiStringAB : public AsciiString
{
public:
	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}
};

// 0x0081C7E0 is pinned as BfmeHookAB::bfmeMakeNameAB, and retail calls it on
// the VideoPlayer itself, so BfmeHookAB is this class's 0x0c-byte base: the
// shared vptr, four pad bytes, and the movie-name callback at +0x08 that the
// body at 0x0081C7E0 formats Data/%s/Movies/ through.
class BfmeHookAB
{
public:
	virtual void slot00();
	void bfmeMakeNameAB(AsciiStringAB &out);

private:
	char m_pad04[4];
	void *m_makeNameCallback; // +0x08
};

class SubtitleEntry;

// 0x0081DA30 reads exactly three stack arguments and returns `ret 0xc`, and
// stores argument two at +0x04 beside the entry factory at +0x00, so this is
// the same three-argument spelling the matched body in
// game/GameEngine/Source/GameClient/SubtitleManagerAccessors.cpp declares.
typedef SubtitleEntry *(__cdecl *CreateSubtitleEntry)(AsciiString *, int,
	const AsciiString &, unsigned int, int, int, int, int, int);

// sizeof(SubtitleManager) is 0x64: the fields the retail ctor clears run to
// +0x60 and `operator new` is called with 0x64.
class SubtitleManager
{
public:
	SubtitleManager(CreateSubtitleEntry createEntry, int second,
		const AsciiString &name);

private:
	char m_storage[0x64];
};

// Witnessed layout: the BfmeHookAB base ends at +0x0c, the subtitle INI loads
// for a record that has subtitles only when both of these are set.
class VideoPlayer : public BfmeHookAB
{
public:
	virtual void init();

	int m_second;                            // +0x0c, the ctor's second argument
	CreateSubtitleEntry m_createSubtitleEntry; // +0x10, the entry factory
};

static unsigned char s_videoPlayerInitialised;

// ?init@VideoPlayer@@UAEXXZ
void VideoPlayer::init(void)
{
	if (s_videoPlayerInitialised == 0)
	{
		INI ini;
		ini.load(AsciiString("Data\\INI\\Default\\Video.ini"),
			INI_LOAD_OVERWRITE, 0, (void *)j_0001bb4e);
		ini.load(AsciiString("Data\\INI\\Video.ini"),
			INI_LOAD_OVERWRITE, 0, (void *)j_0001bb4e);

		for (unsigned int index = 0;
			index < (unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin);
			index++)
		{
			Video *video = g_bfmeVideoTableBegin + index;
			if (video->m_hasSubtitles)
			{
				if (m_createSubtitleEntry != 0 && m_second != 0)
				{
					AsciiStringAB path;
					bfmeMakeNameAB(path);

					const BfmeStringObject *name =
						(const BfmeStringObject *)&video->m_internalName;
					int length = name->m_data ? name->m_data->m_length : 0;
					const char *text = name->m_data
						? name->m_data->m_text : "";
					path.concat(text, length);
					path.concat(".ini", 4);

					video->m_subtitleManager =
						new SubtitleManager(m_createSubtitleEntry, m_second, path);

					{
						INI subtitleIni;
						subtitleIni.load(path, INI_LOAD_OVERWRITE, 0,
							(void *)parseSubtitle);
					}
				}
			}
		}

		s_videoPlayerInitialised = 1;
	}
}
