// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib

struct NetPacketAddress;

class Transport
{
public:
    bool queueSend(unsigned int ip, unsigned short port, const unsigned char *data, int length);
    bool queueSend(NetPacketAddress *address, const unsigned char *data, int length);
};

typedef bool (Transport::*TransportQueueSendMethod)(NetPacketAddress *,
	const unsigned char *, int);
typedef bool (Transport::*TransportQueueSendWrapperMethod)(unsigned int,
	unsigned short, const unsigned char *, int);

// The x86 nonvirtual member pointer is the code pointer. The alternate member
// type keeps the thunk's signature so MSVC can emit a direct tail jump.
union TransportQueueSendTarget
{
    TransportQueueSendMethod member;
    TransportQueueSendWrapperMethod wrapper;
};

bool Transport::queueSend(unsigned int ip, unsigned short port, const unsigned char *data, int length)
{
    TransportQueueSendTarget target;
    target.member = static_cast<TransportQueueSendMethod>(&Transport::queueSend);
    return (this->*target.wrapper)(ip, port, data, length);
}
