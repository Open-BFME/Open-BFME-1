// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DataChunkOutput::writeUnicodeString, retail 0x00102D00.

typedef unsigned short WideChar;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) unsigned int fwrite(const void *, unsigned int, unsigned int, void *);

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
