// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??1DataChunkOutput@@QAE@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp

#include <stdio.h>

typedef int Int;
#include "string_base.h"

// The retail call sites inline str() and call the StringBase<char> destructor
// directly; the header's AsciiString declares both out of line.
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    void concat(const char *text, int length) { StringBase<char>::concat(text, length); }
    const char *str() const { return m_data ? m_data->data : ""; }
};

class GlobalData
{
public:
    AsciiString getPath_UserData() const;
};
extern GlobalData *TheGlobalData;

class OutputStream
{
public:
    virtual Int write(const void *pData, Int numBytes) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
struct Mapping
{
    virtual ~Mapping();
    Mapping *next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
    ~DataChunkTableOfContents()
    {
        Mapping *m, *next;
        for (m = m_list; m; m = next)
        {
            next = m->next;
            delete m;
        }
    }
    void write(OutputStream &s);
private:
    Mapping *m_list;
    Int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};

class OutputChunk;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
    ~DataChunkOutput();
private:
    OutputStream *m_pOut;
    FILE *m_tmp_file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};

// ??1DataChunkOutput@@QAE@XZ
// Zero Hour's DataChunk.cpp body unchanged: write the table of contents, reopen
// the temporary file and append it to the output 256 bytes at a time.
DataChunkOutput::~DataChunkOutput()
{
    m_contents.write(*m_pOut);

    ::fclose(m_tmp_file);

    AsciiString tmpFileName = TheGlobalData->getPath_UserData();
    tmpFileName.concat("_tmpChunk.dat", 13);

    m_tmp_file = ::fopen(tmpFileName.str(), "rb");
    ::fseek(m_tmp_file, 0, SEEK_SET);

    char buffer[256];
    int len = 256;
    while (len == 256)
    {
        len = ::fread(buffer, 1, 256, m_tmp_file);
        m_pOut->write(buffer, len);
    }

    ::fclose(m_tmp_file);
}
