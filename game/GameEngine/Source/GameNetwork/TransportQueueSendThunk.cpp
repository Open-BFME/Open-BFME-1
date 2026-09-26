// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib

class Transport
{
public:
    bool queueSend(unsigned int ip, unsigned short port, const unsigned char *data, int length);
};

class TransportQueueSendShim
{
public:
    bool queue(unsigned int ip, unsigned short port, const unsigned char *data, int length);
};

bool Transport::queueSend(unsigned int ip, unsigned short port, const unsigned char *data, int length)
{
    return ((TransportQueueSendShim *)this)->queue(ip, port, data, length);
}
