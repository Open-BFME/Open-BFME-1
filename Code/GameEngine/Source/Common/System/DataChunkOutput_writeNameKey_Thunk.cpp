// cl: /DNDEBUG /MD /EHsc

#include <stdio.h>

enum NameKeyType
{
};

class AsciiString
{
public:
    ~AsciiString();

private:
    char *m_data;
};

class NameKeyGenerator
{
public:
    AsciiString keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class DataChunkTableOfContents
{
public:
    unsigned int allocateID(const AsciiString &name);

private:
    void *m_list;
    unsigned int m_nextID;
    int m_listLength;
    bool m_headerOpened;
};

class DataChunkOutput
{
public:
    void writeNameKey(NameKeyType key);

private:
    void *m_pOut;
    FILE *m_tmp_file;
    DataChunkTableOfContents m_contents;
};

// ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
void DataChunkOutput::writeNameKey(NameKeyType key)
{
    AsciiString name = TheNameKeyGenerator->keyToName(key);
    unsigned int id = m_contents.allocateID(name);
    id = (id << 8) | 3;
    fwrite(&id, sizeof(id), 1, m_tmp_file);
}
