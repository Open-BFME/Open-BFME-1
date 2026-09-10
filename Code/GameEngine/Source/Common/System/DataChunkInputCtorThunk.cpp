// cl: /DNDEBUG /MD /EHsc

class ChunkInputStream
{
public:
    virtual int read(char *data, int size) = 0;
    virtual int tell() = 0;
};

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_listLength(0), m_nextID(1), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    void read(ChunkInputStream &stream);

private:
    void *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};

class DataChunkInput
{
public:
    DataChunkInput(ChunkInputStream *stream);

private:
    ChunkInputStream *m_file;
    DataChunkTableOfContents m_contents;
    int m_fileposOfFirstChunk;
    void *m_parserList;
    void *m_chunkStack;

public:
    void *m_currentObject;
    void *m_userData;
};

// ??0DataChunkInput@@QAE@PAVChunkInputStream@@@Z
DataChunkInput::DataChunkInput(ChunkInputStream *stream) :
    m_file(stream)
{
    m_chunkStack = 0;
    m_currentObject = 0;
    m_userData = 0;
    m_parserList = 0;
    m_contents.read(*m_file);
    m_fileposOfFirstChunk = m_file->tell();
}
