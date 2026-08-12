// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

enum NameKeyType
{
};

struct AsciiStringData
{
    int m_refCount;
    int m_numChars;
};

extern "C" char g_NAMEKEY_empty_string;

class AsciiString
{
public:
    ~AsciiString();

    const char *str() const
    {
        return m_data != 0 ? reinterpret_cast<const char *>(m_data) + 8 : &g_NAMEKEY_empty_string;
    }

    AsciiStringData *m_data;
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
    NameKeyType nameToKey(const AsciiString &name) { return nameToKey(name.str()); }
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameEngine
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void serviceWindowsOS() = 0;
};

extern GameEngine *TheGameEngine;

class ChunkInputStream
{
public:
    virtual int read(char *data, int size) = 0;
};

class InputChunk
{
public:
    virtual ~InputChunk() {}

    InputChunk *next;
    unsigned int id;
    unsigned short version;
    unsigned short padding;
    int chunkStart;
    int dataSize;
    int dataLeft;
};

class DataChunkTableOfContents
{
public:
    AsciiString getName(unsigned int id);

private:
    void *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};

class DataChunkInput
{
public:
    NameKeyType readNameKey();

private:
    __forceinline int readIntInline()
    {
        Sleep(0);
        if (TheGameEngine != 0) {
            TheGameEngine->serviceWindowsOS();
        }

        int value;
        m_file->read(reinterpret_cast<char *>(&value), sizeof(value));
        for (InputChunk *chunk = m_chunkStack; chunk != 0; chunk = chunk->next) {
            chunk->dataLeft -= sizeof(value);
        }
        return value;
    }

    ChunkInputStream *m_file;
    DataChunkTableOfContents m_contents;
    int m_fileposOfFirstChunk;
    void *m_parserList;
    InputChunk *m_chunkStack;
};

// ?readNameKey@DataChunkInput@@QAE?AW4NameKeyType@@XZ
NameKeyType DataChunkInput::readNameKey()
{
    int keyAndType = readIntInline();
    keyAndType >>= 8;
    AsciiString name = m_contents.getName(keyAndType);
    return TheNameKeyGenerator->nameToKey(name);
}
