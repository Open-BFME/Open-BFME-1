// Retail 0x007E5080: VP6 player open path.
// Evidence: targets/game/reverse/identity_evidence/007e5080-vp6-open.md
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I.
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "game/GameEngine/Include/GameClient/Video.h"

class Debug
{
public:
	class Format
	{
        friend class BfmeAwakenLogFormat;
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
	virtual BfmeAwakenLogFormat *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
    BfmeAwakenLogFormat *slot38(const Debug::Format &message)
    {
        slot38(message.m_buffer);
        return this;
    }

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

typedef Video Rva007E5080Vp6Video;

class Rva007E5080Vp6Stream
{
public:
	char m_storage[0x64];
};

class Rva007E3C20Vp6Stream
{
public:
    Rva007E3C20Vp6Stream(int first, int second);
    virtual ~Rva007E3C20Vp6Stream();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual char invoke(const AsciiString &name, int value, bool flag);
private:
    char m_storage[0x60];
};
typedef Rva007E3C20Vp6Stream Rva007E3B40Vp6TailStream;

struct Rva01309848MoviePath
{
    unsigned char m_enabled;
    char m_path[260];
    char m_label[64];
};
extern Rva01309848MoviePath g_Va01309848[3];

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
	virtual const Rva007E5080Vp6Video *getVideo(AsciiString title);

	Rva007E5080Vp6Stream *open(AsciiString movieTitle, int flags);
};

// ?open@Rva007E5080Vp6Player@@QAEPAVRva007E5080Vp6Stream@@VAsciiString@@H@Z
Rva007E5080Vp6Stream *Rva007E5080Vp6Player::open(AsciiString movieTitle, int flags)
{
    if (TheWritableGlobalData->m_videoDisabled)
        return 0;

    Rva007E3B40Vp6TailStream *stream;
    const Rva007E5080Vp6Video *video = getVideo(movieTitle);
    if (video != 0)
    {
        AsciiString lookup;
        int pathCount;
        for (pathCount = 0; pathCount < 3; ++pathCount)
        {
            const char *path = g_Va01309848[pathCount].m_path;
            if (path[-1] != 0)
            {
                lookup.format(AsciiString("%s%s.%s"), path, video->m_filename.str(), "vp6");
                if (TheFileSystem->doesFileExist(lookup.str()))
                    break;
            }
        }
        if (pathCount >= 3)
        {
            if (_bfme_debugReportingEnabled())
            {
                _bfme_debugRecordCallsite(1);
                TheBfmeAwakenDebug->slot60();
                const char *videoFilename = video->m_filename.str();
                const char *movieName = movieTitle.str();
                BfmeAwakenLogFormat *report = (BfmeAwakenLogFormat *)TheBfmeAwakenDebug->slot6C(0, 0);
                report->slot38(Debug::Format("Could not open VP6 video file for %s - %s.", movieName, videoFilename));
                report->slot4C(2);
            }
            if (pathCount >= 3)
                return 0;
        }
        stream = new Rva007E3B40Vp6TailStream((int)video, (int)this);
        bool initializationFlag = (flags | 0x40) != 0;
        if (stream->invoke(lookup, (int)video, initializationFlag))
        {
            // Retail supplies the player in ECX; the pinned helper consumes only the stack argument.
            typedef BfmeNodeEQB *(Rva007E5080Vp6Player::*LinkMethod)(BfmeNodeEQB *);
            union {
                LinkMethod method;
                BfmeNodeEQB *(__stdcall *function)(BfmeNodeEQB *);
            } link;
            link.function = bfmeLinkEQB;
            (this->*link.method)((BfmeNodeEQB *)stream);
        }
        else
        {
            delete stream;
            stream = 0;
        }
    }
    else
    {
        stream = 0;
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
    }
    return (Rva007E5080Vp6Stream *)stream;
}
