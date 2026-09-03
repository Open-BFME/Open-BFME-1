// cl: /DNDEBUG /MD /EHsc
// readable body of ?writeUnicodeString@DataChunkOutput@@QAEXVUnicodeString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// Open-BFME: DataChunkOutput::writeUnicodeString, retail 0x00102D00.

typedef unsigned short WideChar;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) unsigned int fwrite(const void *, unsigned int, unsigned int, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
    ~UnicodeString();

    int getLength(void) const
    {
        return m_data ? *(const UnsignedShort *)((const char *)m_data + 4) : 0;
    }

    const WideChar *str(void) const
    {
        static const WideChar nullChar = 0;
        return m_data ? (const WideChar *)((const char *)m_data + 8) : &nullChar;
    }

private:
    void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
    void *m_pOut;
    void *m_tmp_file;

public:
    void writeUnicodeString(UnicodeString theString);
};

// ?writeUnicodeString@DataChunkOutput@@QAEXVUnicodeString@@@Z
void DataChunkOutput::writeUnicodeString(UnicodeString theString)
{
    UnsignedShort len = theString.getLength();
    ::fwrite((const char *)&len, sizeof(UnsignedShort), 1, m_tmp_file);
    ::fwrite((const char *)theString.str(), len * sizeof(WideChar), 1, m_tmp_file);
}
