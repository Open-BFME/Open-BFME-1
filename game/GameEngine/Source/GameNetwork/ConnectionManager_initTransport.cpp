// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

#pragma pack(push, 1)
struct TransportAddress
{
    UnsignedInt ip;
    UnsignedShort port;
};
#pragma pack(pop)

class Transport
{
public:
    Transport();
    ~Transport();
    void reset();
    bool init(const TransportAddress *address);

    char m_data[0x410E4];
};

class ConnectionManager
{
public:
    void initTransport();

    char m_unknown00[0x12024];
    Transport *m_transport;
    char m_unknown12028[0x28];
    TransportAddress m_localAddress;
};

void ConnectionManager::initTransport()
{
    if (m_transport != 0)
    {
        delete m_transport;
        m_transport = 0;
    }

    m_transport = new Transport;
    m_transport->reset();
    m_transport->init(&m_localAddress);
}
