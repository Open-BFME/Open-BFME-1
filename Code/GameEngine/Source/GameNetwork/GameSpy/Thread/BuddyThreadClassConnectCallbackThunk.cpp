// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?connectCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPConnectResponseArg@@@Z: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp

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
