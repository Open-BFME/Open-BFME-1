// cl: /O2

class Rva007E8810Message
{
public:
    __int64 getInt64(const char *name, __int64 missing);
};

class BfmeThingRF
{
public:
    void *bfmeGoRF(void *name, void *missing);
};

class Rva007F0460BlobHeader
{
public:
    Rva007F0460BlobHeader(Rva007E8810Message *message);

private:
    Rva007E8810Message *m_message;
    int m_field04;
    __int64 m_blobId;
    int m_decodedLength;
};

Rva007F0460BlobHeader::Rva007F0460BlobHeader(Rva007E8810Message *message)
{
    m_message = message;
    m_blobId = m_message->getInt64("blobId", -1);
    int size = (int)((BfmeThingRF *)m_message)->bfmeGoRF((void *)"size", (void *)-1);
    m_decodedLength = (size / 4) * 3 - 1;
}
