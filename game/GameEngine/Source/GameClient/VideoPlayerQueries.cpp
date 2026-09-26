// cl: /DNDEBUG /MD /EHsc
#include "../../Include/GameClient/Video.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);
extern const char Rva006A16B0Empty[];

// Read-only view of the canonical StringBase allocation header: refcount+0,
// length+4, capacity+6, text+8. The Video name comparison inlines these reads.
struct VideoNameBufferView
{
    int m_refCount;
    unsigned short m_length;
    unsigned short m_capacity;
    char m_text[1];
};

struct VideoStringStorageView
{
    VideoNameBufferView *m_data;
};

inline int compareVideoNames(const AsciiString &left, const AsciiString &right)
{
    const VideoStringStorageView *self = (const VideoStringStorageView *)&left;
    const VideoStringStorageView *that = (const VideoStringStorageView *)&right;
    int thatLength = that->m_data ? that->m_data->m_length : 0;
    const char *thatText = that->m_data ? that->m_data->m_text : Rva006A16B0Empty;
    int selfLength = self->m_data ? self->m_data->m_length : 0;
    const char *selfText = self->m_data ? self->m_data->m_text : Rva006A16B0Empty;
    int count = selfLength < thatLength ? selfLength : thatLength;
    int result = _memicmp(selfText, thatText, count);
    if (result != 0)
        return result;
    return selfLength - thatLength;
}

// Both retail queries read the same 28-byte table at VA0130B19C/0130B1A0.
extern Video *g_bfmeVideoTableBegin;
extern Video *g_bfmeVideoTableEnd;

class VideoPlayer
{
public:
    virtual const Video *getVideo(AsciiString movieTitle);
    virtual SubtitleManager *getSubTitleMgrForVideo(const AsciiString &title);
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);


// ?getVideo@VideoPlayer@@UAEPBUVideo@@VAsciiString@@@Z
const Video *VideoPlayer::getVideo(AsciiString movieTitle)
{
	AsciiString title(movieTitle);
	title.trim();

	Video *it = g_bfmeVideoTableBegin;
	for (; it != g_bfmeVideoTableEnd; ++it)
	{
		AsciiString name(it->m_internalName);
		name.trim();
		if (compareVideoNames(name, title) == 0)
			return it;
	}
	return 0;
}

// Exact diagnostic at VA 0112CD30 names this method; parseSubtitle calls slot +58.
// ?getSubTitleMgrForVideo@VideoPlayer@@UAEPAVSubtitleManager@@ABVAsciiString@@@Z
SubtitleManager *VideoPlayer::getSubTitleMgrForVideo(const AsciiString &title)
{
	unsigned int index = 0;
	if ((unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin) != 0)
	{
		unsigned int offset = 0;
		do
		{
			Video *record = (Video *)((char *)g_bfmeVideoTableBegin + offset);
			SubtitleManager *manager = record->m_subtitleManager;
			if (manager != 0 && compareVideoNames(title, *(AsciiString *)((char *)manager + 8)) == 0)
				return record->m_subtitleManager;
			++index;
			offset += sizeof(Video);
		} while (index < (unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin));
	}

	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->slot60();
	BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
	report->slot38((const char *)0x0112CD30)->slot4C(1);
	return 0;
}
