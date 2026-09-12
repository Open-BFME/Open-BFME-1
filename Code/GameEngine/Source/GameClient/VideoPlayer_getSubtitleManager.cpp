// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);
extern const char Rva006A16B0Empty[];

template <typename T>
class StringBase
{
public:
	struct Data
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	Data *m_data;
};

class AsciiString : private StringBase<char>
{
};

inline int compare(const AsciiString &left, const AsciiString &right)
{
	const StringBase<char> *self = (const StringBase<char> *)&left;
	const StringBase<char> *that = (const StringBase<char> *)&right;
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

class SubtitleManager
{
};

struct VideoRecord
{
	unsigned char m_padding[0x18];
	SubtitleManager *m_subtitleManager;
};

extern VideoRecord *g_videoTableBegin; // retail 0x0130B19C
extern VideoRecord *g_videoTableEnd;   // retail 0x0130B1A0

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

class VideoPlayer
{
public:
	virtual SubtitleManager *getVideo(const AsciiString &title);
};

// ?getVideo@VideoPlayer@@UAEPAVSubtitleManager@@ABVAsciiString@@@Z
SubtitleManager *VideoPlayer::getVideo(const AsciiString &title)
{
	unsigned int index = 0;
	if ((unsigned int)(g_videoTableEnd - g_videoTableBegin) != 0)
	{
		unsigned int offset = 0;
		do
		{
			VideoRecord *record = (VideoRecord *)((char *)g_videoTableBegin + offset);
			SubtitleManager *manager = *(SubtitleManager **)((char *)record + 0x18);
			if (manager != 0 && compare(title, *(AsciiString *)((char *)manager + 8)) == 0)
				return *(SubtitleManager **)((char *)record + 0x18);
			++index;
			offset += sizeof(VideoRecord);
		} while (index < (unsigned int)(g_videoTableEnd - g_videoTableBegin));
	}

	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->slot60();
	BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
	report->slot38((const char *)0x0112CD30)->slot4C(1);
	return 0;
}
