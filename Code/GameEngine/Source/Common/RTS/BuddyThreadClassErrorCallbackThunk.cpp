// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?errorCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPErrorArg@@@Z: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp

class GPConnection;
struct GPErrorArg;

class BuddyThreadClass
{
public:
    void errorCallback(GPConnection *, GPErrorArg *);
};

class BuddyThreadClassErrorCallbackShim
{
public:
    void run(GPConnection *conn, GPErrorArg *arg);
};

void BuddyThreadClass::errorCallback(GPConnection *conn, GPErrorArg *arg)
{
    ((BuddyThreadClassErrorCallbackShim *)this)->run(conn, arg);
}
