// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME stores this call site's AsciiString data through StringBase.

#include <list>
#include <string>

typedef int Int;
typedef bool Bool;

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);

    struct Data
    {
        int m_refCount;
        unsigned short m_length;
        unsigned short m_capacity;
        T m_text[1];
    };

    Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() { releaseBuffer(); }

    const char *str() const
    {
        const StringBase<char>::Data *data = m_data;
        return data ? data->m_text : "";
    }

private:
    void releaseBuffer();
};

class GameSpyConfigInterface
{
public:
    virtual ~GameSpyConfigInterface() {}
    virtual std::list<AsciiString> getPingServers() = 0;
    virtual Int getNumPingRepetitions() = 0;
    virtual Int getPingTimeoutInMs() = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

class PingRequest
{
public:
    _STL::string hostname;
    Int repetitions;
    Int timeout;
};

class PingerInterface
{
public:
    virtual ~PingerInterface() {}
    virtual void startThreads() = 0;
    virtual void endThreads() = 0;
    virtual Bool areThreadsRunning() = 0;
    virtual void addRequest(const PingRequest &request) = 0;
};

extern PingerInterface *ThePinger;

// ?startPings@@YAXXZ
void startPings()
{
    std::list<AsciiString> pingServers = TheGameSpyConfig->getPingServers();
    Int timeout = TheGameSpyConfig->getPingTimeoutInMs();
    Int reps = TheGameSpyConfig->getNumPingRepetitions();

    for (std::list<AsciiString>::const_iterator it = pingServers.begin(); it != pingServers.end(); ++it)
    {
        AsciiString pingServer = *it;
        PingRequest req;
        req.hostname = pingServer.str();
        req.repetitions = reps;
        req.timeout = timeout;
        ThePinger->addRequest(req);
    }
}
