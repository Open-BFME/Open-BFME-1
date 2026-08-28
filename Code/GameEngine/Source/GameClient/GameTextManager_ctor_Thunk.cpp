// cl: /DNDEBUG /MD /EHsc

typedef unsigned short WideChar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const WideChar *);
	~UnicodeString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	unsigned int m_unknown;
};

class GameTextInterface : public SubsystemInterface
{
public:
	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void update() = 0;
	virtual void reset() = 0;
};

class GameTextManager : public GameTextInterface
{
public:
	GameTextManager();
	virtual ~GameTextManager();
	virtual void init();
	virtual void deinit();
	virtual void update();
	virtual void reset();

private:
	int m_textCount;
	unsigned char m_unreconstructed_000c[0x7800];
	void *m_stringInfo;
	void *m_stringLUT;
	bool m_initialized;
	unsigned char m_pad_7815[3];
	void *m_noStringList;
	int m_useStringFile;
	int m_language;
	UnicodeString m_failed;
	void *m_mapStringInfo;
	void *m_mapStringLUT;
	int m_mapTextCount;
	void *m_vectorBegin;
	void *m_vectorEnd;
	void *m_vectorCapacity;
};

// ??0GameTextManager@@QAE@XZ
GameTextManager::GameTextManager() :
	m_textCount(0),
	m_stringInfo(0),
	m_stringLUT(0),
	m_initialized(false),
	m_noStringList(0),
	m_useStringFile(1),
	m_language(0),
	m_failed(L"***FATAL*** String Manager failed to initilaize properly"),
	m_mapStringInfo(0),
	m_mapStringLUT(0),
	m_mapTextCount(0),
	m_vectorBegin(0),
	m_vectorEnd(0),
	m_vectorCapacity(0)
{
}
