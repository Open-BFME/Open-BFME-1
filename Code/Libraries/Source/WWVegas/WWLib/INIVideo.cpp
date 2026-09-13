// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini_bfme /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) { }
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
	friend class StringBase<char>;

public:
	AsciiString() : StringBase<char>() { }
	AsciiString(const char *text) : StringBase<char>(text) { }
	AsciiString(const AsciiString &other) : StringBase<char>(other) { }
	~AsciiString() { }
	void set(const AsciiString &other);
	void set(const char *text, int length);
	void set(const char *text)
	{
		int length = text ? strlen(text) : 0;
		set(text, length);
	}
};

struct Gen000C3410
{
	AsciiString m_filename;
	AsciiString m_internalName;
	AsciiString m_commentForWB;
	unsigned char m_isLooping;
	float m_volume;
	unsigned char m_isDefault;
	int m_unknown;

	Gen000C3410()
		: m_isLooping(0),
		  m_volume(1.0f),
		  m_isDefault(0),
		  m_unknown(0)
	{
	}

	__forceinline Gen000C3410 &operator=(const Gen000C3410 &other)
	{
		m_filename.set(other.m_filename);
		m_internalName.set(other.m_internalName);
		m_commentForWB.set(other.m_commentForWB);
		m_isLooping = other.m_isLooping;
		m_volume = other.m_volume;
		m_isDefault = other.m_isDefault;
		m_unknown = other.m_unknown;
		return *this;
	}

};

typedef Gen000C3410 Video;

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
	video.m_internalName.set(c);
	ini->initFromINI(&video, TheVideoPlayer->getFieldParse());
	TheVideoPlayer->addVideo(&video);
}
