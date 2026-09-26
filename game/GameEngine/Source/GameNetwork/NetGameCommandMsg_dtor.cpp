// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class GameMessageArgument
{
public:
    virtual ~GameMessageArgument() {}

    GameMessageArgument *m_next;
};

class NetCommandMsg
{
public:
    virtual ~NetCommandMsg() {}

    UnsignedInt m_timestamp;
    UnsignedInt m_executionFrame;
    UnsignedInt m_playerID;
    UnsignedShort m_id;
    Int m_commandType;
    Int m_referenceCount;
};

class NetGameCommandMsg : public NetCommandMsg
{
public:
    virtual ~NetGameCommandMsg();

    Int m_numArgs;
    Int m_argSize;
    Int m_type;
    GameMessageArgument *m_argList;
    GameMessageArgument *m_argTail;
};

NetGameCommandMsg::~NetGameCommandMsg()
{
    GameMessageArgument *arg = m_argList;
    while (arg != 0)
    {
        m_argList = m_argList->m_next;
        delete arg;
        arg = m_argList;
    }
}
