// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <stdio.h>

class OutputChunk
{
public:
    virtual ~OutputChunk() {}
    void deleteInstance() { delete this; }

    OutputChunk *next;
    unsigned int id;
    int filepos;
};

class DataChunkOutput
{
public:
    void closeDataChunk();

private:
    void *m_pOut;
    FILE *m_tmp_file;
    char m_contents[16];
    OutputChunk *m_chunkStack;
};

// ?closeDataChunk@DataChunkOutput@@QAEXXZ
void DataChunkOutput::closeDataChunk()
{
    if (m_chunkStack != NULL) {
        int currentPos = ftell(m_tmp_file);
        fseek(m_tmp_file, m_chunkStack->filepos, SEEK_SET);
        int dataSize = currentPos - m_chunkStack->filepos - sizeof(int);
        fwrite(&dataSize, sizeof(dataSize), 1, m_tmp_file);
        fseek(m_tmp_file, currentPos, SEEK_SET);

        OutputChunk *chunk = m_chunkStack;
        m_chunkStack = m_chunkStack->next;
        chunk->deleteInstance();
    }
}
