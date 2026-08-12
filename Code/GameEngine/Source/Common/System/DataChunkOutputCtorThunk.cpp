// cl: /DNDEBUG /MD /EHsc

#include <stdio.h>

class OutputStream;

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
    void concat(const char *text, int length);

    const char *str() const
    {
        return m_data != 0 ? reinterpret_cast<const char *>(m_data) + 8 : &g_NAMEKEY_empty_string;
    }

private:
    AsciiStringData *m_data;
};

class GlobalData
{
public:
    AsciiString getPath_UserData() const;
};

extern GlobalData *TheGlobalData;

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_listLength(0), m_nextID(1), m_headerOpened(false) {}
    ~DataChunkTableOfContents();

private:
    void *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};

class DataChunkOutput
{
public:
    DataChunkOutput(OutputStream *output);

private:
    OutputStream *m_pOut;
    FILE *m_tmp_file;
    DataChunkTableOfContents m_contents;
    void *m_chunkStack;
};

// ??0DataChunkOutput@@QAE@PAVOutputStream@@@Z
DataChunkOutput::DataChunkOutput(OutputStream *output) : m_pOut(output)
{
    AsciiString tmpFileName = TheGlobalData->getPath_UserData();
    tmpFileName.concat("_tmpChunk.dat", 13);
    m_tmp_file = fopen(tmpFileName.str(), "wb");
    m_chunkStack = 0;
}
