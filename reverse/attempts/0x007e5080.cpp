// ?open@Rva007E5080Vp6Player@@QAEPAVRva007E5080Vp6Stream@@VAsciiString@@H@Z
// partial score=0.35 date=2026-09-10
// Retail 0x007E5080: VP6 video-player open path (737 bytes).
// The owner and stream names are address-derived until a named retail caller
// establishes the original BFME class name.  The neighbouring VP6 constructor
// establishes the 0x64-byte stream layout and vtable family.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &source);

	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	struct Data
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	AsciiString(const char *text);
	AsciiString(const AsciiString &source)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&source);
	}
	~AsciiString();
	void __cdecl format(AsciiString format, ...);

	const char *str(void) const
	{
		return m_data ? m_data->data : (const char *)0x0107388B;
	}

	Data *m_data;
};

class Debug
{
public:
	class Format
	{
	public:
		explicit Format(const char *format, ...);

	private:
		char m_buffer[512];
	};
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
	virtual void slot4C(int report);
};

class BfmeAwakenLogFormat
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
	virtual BfmeAwakenLogFormat *slot38(const Debug::Format *message);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
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
extern bool _bfme_debugReportingEnabled(void);

class GlobalData
{
private:
	char m_pad[0xA7D];

public:
	unsigned char m_videoDisabled;
};

extern GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

struct BfmeNodeEQB
{
	void *m_bfmeSlotEQB;
	BfmeNodeEQB *m_bfmeNextEQB;
};

BfmeNodeEQB *__stdcall bfmeLinkEQB(BfmeNodeEQB *node);

struct Rva007E5080Vp6Video
{
	AsciiString m_filename;
};

class Rva007E5080Vp6Stream
{
public:
	char m_storage[0x64];
};

class Rva007E3B40Vp6TailStream
{
public:
	Rva007E3B40Vp6TailStream(int first, int second);

private:
	char m_storage[0x64];
};

// Retail calls the existing ILT at 0x0001A2FD, which enters the adjacent
// 0x007E3B40 constructor.  Keep that constructor body in its own family TU.
#pragma comment(linker, "/alternatename:??0Rva007E3B40Vp6TailStream@@QAE@HH@Z=?j_0001a2fd@@YAXXZ")

class Rva007E5080Vp6Player
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual Rva007E5080Vp6Video *getVideo(AsciiString title);

	Rva007E5080Vp6Stream *open(AsciiString movieTitle, int flags);
};

Rva007E5080Vp6Stream *Rva007E5080Vp6Player::open(
	AsciiString movieTitle, int flags)
{
	if (TheWritableGlobalData->m_videoDisabled)
		return 0;

	AsciiString lookup(movieTitle);
	Rva007E5080Vp6Video *video = getVideo(lookup);
	if (video == 0)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
			report = report->slot38("A movie named '");
			report = report->slot38(movieTitle.str());
			report = report->slot38("' was requested but can't be found.\n");
			report->slot4C(2);
		}
		return 0;
	}

	int pathCount = 0;
	const char *path = (const char *)0x01309849;
	for (; path < (const char *)0x01309C18 && path[-1] != 0;
		path += 0x145, ++pathCount)
	{
		lookup.format(AsciiString("%s%s.%s"), path,
			video->m_filename.str(), "vp6");
		if (TheFileSystem->doesFileExist(lookup.str()))
			break;
	}

	if (pathCount >= 3)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			BfmeAwakenLogFormat *report =
				(BfmeAwakenLogFormat *)TheBfmeAwakenDebug->slot6C(0, 0);
			Debug::Format message("Could not open VP6 video file for %s - %s.",
				video->m_filename.str(), movieTitle.str());
			report = report->slot38(&message);
			report->slot4C(2);
		}
		return 0;
	}

	Rva007E3B40Vp6TailStream *stream =
		new Rva007E3B40Vp6TailStream((int)video, (int)this);
	if (stream != 0)
	{
		typedef bool (*InitializeFn)(void *, AsciiString *,
			void *, bool);
		typedef void (*DestroyFn)(void *, unsigned int);
		void **vtable = *(void ***)stream;
		bool accepted = ((InitializeFn)vtable[19])(
			stream, &lookup, video, (flags | 0x40) != 0);
		if (accepted)
		{
			bfmeLinkEQB((BfmeNodeEQB *)stream);
			return (Rva007E5080Vp6Stream *)stream;
		}
		((DestroyFn)vtable[0])(stream, 1);
	}
	return 0;
}
