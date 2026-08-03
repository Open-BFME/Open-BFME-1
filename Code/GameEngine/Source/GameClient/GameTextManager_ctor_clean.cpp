// cl: /DNDEBUG /MD /EHsc

class GameTextManager;

template <class Character>
class StringBase
{
public:
    StringBase();

private:
    friend class GameTextManager;
    StringBase(const Character *text);

    void *m_data;
};

typedef StringBase<char> AsciiString;
typedef StringBase<unsigned short> UnicodeString;

class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
    virtual void init() = 0;
    virtual void postProcessLoad();
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual void draw();

protected:
    AsciiString m_name;
};

class GameTextInterface : public SubsystemInterface
{
};

struct AsciiStringVector
{
    void *begin;
    void *end;
    void *capacity;
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
    virtual UnicodeString fetch(const char *label, char *exists = 0);
    virtual UnicodeString fetch(AsciiString label, char *exists = 0);
    virtual AsciiStringVector &getStringsWithLabelPrefix(AsciiString label);
    virtual void initMapStringFile(const AsciiString &filename);

protected:
    int m_textCount;
    char m_buffer[0x2800];
    char m_buffer2[0x2800];
    char m_buffer3[0x2800];
    void *m_stringInfo;
    void *m_stringLUT;
    char m_initialized;
    void *m_noStringList;
    int m_useStringFile;
    int m_language;
    UnicodeString m_failed;
    void *m_mapStringInfo;
    void *m_mapStringLUT;
    int m_mapTextCount;
    AsciiStringVector m_asciiStringVec;
};

GameTextManager::GameTextManager()
    : m_textCount(0),
      m_stringInfo(0),
      m_stringLUT(0),
      m_initialized(0),
      m_noStringList(0),
      m_useStringFile(1),
      m_language(0),
      m_failed(L"***FATAL*** String Manager failed to initilaize properly"),
      m_mapStringInfo(0),
      m_mapStringLUT(0),
      m_mapTextCount(0)
{
    m_asciiStringVec.begin = 0;
    m_asciiStringVec.end = 0;
    m_asciiStringVec.capacity = 0;
}
