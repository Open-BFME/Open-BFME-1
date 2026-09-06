// BaseHeightMapRenderObjClass::writeEnvironmentData, retail 0x006C8F60.
// The body sits between BaseHeightMapRenderObjClass::updateCenter and xfer.
// Its field offsets match the BFME BaseHeightMap layout, and the chunk name
// is the retail EnvironmentData string.

class AsciiString
{
    void *m_data;
};

class DataChunkOutput
{
public:
    void openDataChunk(char *name, unsigned short version);
    void closeDataChunk();
    void writeReal(float value);
    void writeByte(char value);
    void writeAsciiString(const AsciiString &value);
};

class BaseHeightMapRenderObjClass
{
public:
    void writeEnvironmentData(DataChunkOutput *output);

private:
    char m_padding00[0x3018];
    float m_environmentFirst;
    float m_environmentSecond;
    char m_padding3020[0x306c - 0x3020];
    char m_environmentFlag;
    char m_padding306d[3];
    AsciiString m_environmentName;
    AsciiString m_environmentDefaultName;
};

void BaseHeightMapRenderObjClass::writeEnvironmentData(DataChunkOutput *output)
{
    output->openDataChunk("EnvironmentData", 3);
    output->writeReal(m_environmentFirst);
    output->writeReal(m_environmentSecond);
    output->writeByte(m_environmentFlag != 0);
    output->writeAsciiString(m_environmentName);
    output->writeAsciiString(m_environmentDefaultName);
    output->closeDataChunk();
}
