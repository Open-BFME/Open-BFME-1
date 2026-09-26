// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini_bfme /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

struct FieldParse;
extern "C" int strlen(const char *text);

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseVideoDefinition(INI *ini);
};

#include "../../../Include/GameClient/Video.h"

Video::~Video()
{
}

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface() { }
	virtual void init() = 0;
	virtual void postProcessLoad() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void deinit() = 0;
	virtual void loseFocus() = 0;
	virtual void regainFocus() = 0;
	virtual void open(AsciiString) = 0;
	virtual void load(AsciiString) = 0;
	virtual void firstStream() = 0;
	virtual void closeAllStreams() = 0;
	virtual void beforeAddVideo() = 0;
	virtual void beforeAddVideo2() = 0;
	virtual void addVideo(Video*) = 0;
	virtual void removeVideo(Video*) = 0;
	virtual int getNumVideos() = 0;
	virtual const Video *getVideo(const AsciiString) = 0;
	virtual const Video *getVideo(int) = 0;
	virtual const FieldParse *getFieldParse() const = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;

void INI::parseVideoDefinition(INI *ini)
{
	const Video *defaultVideo;
	const char *c = ini->getNextToken();
	Video video;
	defaultVideo = TheVideoPlayer->getVideo(AsciiString("DefaultVideoData"));
	if (defaultVideo != 0)
	{
		video = *defaultVideo;
		video.m_isDefault = 0;
	}
	((StringBase<char> *)&video.m_internalName)->set(c, c ? strlen(c) : 0);
	ini->initFromINI(&video, TheVideoPlayer->getFieldParse());
	TheVideoPlayer->addVideo(&video);
}
