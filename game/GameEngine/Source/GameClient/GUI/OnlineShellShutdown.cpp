// BfmeAptScreenOnlineShell::shutdown, retail 0x0055D680 (287 bytes).
// The owner is identified by the paired OnlineShell constructor/destructor,
// the openScreen body, and the 0x01108F48 vtable slot reached by 0x00009219.

#include <vector>

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase( const T *text );
    StringBase( const StringBase<T> &other );
    ~StringBase();
    void clear();

    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    ~AsciiString() { clear(); }

    bool isEmpty() const
    {
        return !m_data || *(const unsigned short *)( (const char *)m_data + 4 ) == 0;
    }

    const char *str() const
    {
        return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
    }

    void clear();
};

#pragma comment(linker, "/alternatename:?clear@AsciiString@@QAEXXZ=??1AsciiString@@QAE@XZ")

class _bfme_AptGameWindow
{
public:
    virtual ~_bfme_AptGameWindow();
};

class BfmeAptScreenRef
{
public:
    virtual ~BfmeAptScreenRef();
    virtual void close();
    virtual void release();
    virtual void slot0C();
    virtual void slot10();
    virtual int shutdown();
};

class GenActionSink
{
public:
    void add( void *owner, const char *name, int count, const char *first,
        int second, int third, int fourth, int fifth );
};

extern GenActionSink *g_mgr12F19E8;

class PSRequest
{
public:
    PSRequest();
    ~PSRequest();

    int requestType;
    struct
    {
        int id;
    } player;

private:
    unsigned char m_unmodelled[ 0x208 ];
};

#pragma comment(linker, "/alternatename:??0PSRequest@@QAE@XZ=?j_0002e38e@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PSRequest@@QAE@XZ=?j_0001658b@@YAXXZ")

class GameSpyPSMessageQueueInterface
{
public:
    virtual ~GameSpyPSMessageQueueInterface();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void addRequest( const PSRequest &request );
};

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

class GameSpyInfoInterface
{
public:
    virtual ~GameSpyInfoInterface();
    virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18();
    virtual void slot1C(); virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual void slot2C(); virtual void slot30();
    virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48();
    virtual void slot4C(); virtual void slot50(); virtual void slot54();
    virtual void slot58(); virtual void slot5C(); virtual void slot60();
    virtual void slot64(); virtual void slot68(); virtual void slot6C();
    virtual int getLocalProfileID();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class BfmeAptScreenOnlineShell : public _bfme_AptGameWindow
{
public:
    virtual void shellSlot04() = 0;
    virtual void shellSlot08() = 0;
    virtual void shellSlot0C() = 0;
    virtual void shellSlot10() = 0;
    virtual int shutdown();

private:
    unsigned char m_unmodelled[ 0x250 ];
    int m_258;
    std::vector<BfmeAptScreenRef *> m_refs;
    AsciiString m_name;
    BfmeAptScreenRef *m_current;
    AsciiString m_fileName;
    void *m_274;
    void *m_278;
    void *m_27c;
};

int BfmeAptScreenOnlineShell::shutdown()
{
    if( m_current )
        m_current->shutdown();

    for( std::vector<BfmeAptScreenRef *>::iterator it = m_refs.begin();
        it != m_refs.end(); ++it )
    {
        (*it)->release();
    }

    if( !m_name.isEmpty() )
    {
        const char *name = m_name.str();
        int owner = *(volatile int *)( (char *)this + 0x250 );
        g_mgr12F19E8->add(
            (void *)owner,
            (const char *)0x01109084, 1,
            name, 0, 0, 0, 0 );
        m_name.clear();

        if( TheGameSpyInfo )
        {
            int profileID = TheGameSpyInfo->getLocalProfileID();
            if( profileID )
            {
                PSRequest request;
                request.requestType = 0;
                request.player.id = profileID;
                TheGameSpyPSMessageQueue->addRequest( request );
            }
        }
    }

    return 1;
}
