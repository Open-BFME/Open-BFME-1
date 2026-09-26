// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?errorCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPErrorArg@@@Z: game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp

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
