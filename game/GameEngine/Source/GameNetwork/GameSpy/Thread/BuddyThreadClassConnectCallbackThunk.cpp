// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?connectCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPConnectResponseArg@@@Z: game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp

class GPConnection;
struct GPConnectResponseArg;

class BuddyThreadClass
{
public:
    void connectCallback(GPConnection *, GPConnectResponseArg *);
};

class BuddyThreadClassConnectCallbackShim
{
public:
    void run(GPConnection *conn, GPConnectResponseArg *arg);
};

void BuddyThreadClass::connectCallback(GPConnection *conn, GPConnectResponseArg *arg)
{
    ((BuddyThreadClassConnectCallbackShim *)this)->run(conn, arg);
}
