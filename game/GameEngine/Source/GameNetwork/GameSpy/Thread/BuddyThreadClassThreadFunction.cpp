// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// BuddyThreadClass::Thread_Function, retail 0x0063EB00, 3533 bytes of code; its
// catch(...) funclet is 0x0063F8CD and its 11-case jump table 0x0063F8D4.
// Identity: ctor 0x0063C4F0 installs vtable 0x01118E60 whose slot 2 is ILT
// 0x0003CAD8 -> 0x0063EB00 (ThreadClass::Thread_Function override); the request
// switch is the Zero Hour BuddyThread.cpp dispatch, BFME adds the FESL login.
// Address-token types and slots make no claim about original names.
#define __PLACEMENT_VEC_NEW_INLINE
#include <string>
#include <memory>
#include <string.h>
#include "mutex.h"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

typedef void *GPConnection;
typedef void (*Rva00438CD0Callback)(GPConnection *,void *,void *);
void callbackWrapper(GPConnection *,void *,void *);
extern "C" {
int GSIStartAvailableCheckA(const char *);
int GSIAvailableCheckThink();
int gpInitialize(GPConnection *,int,int);
void gpDestroy(GPConnection *);
int gpSetCallback(GPConnection *,int,Rva00438CD0Callback,void *);
int gpProcess(GPConnection *);
int gpConnectA(GPConnection *,const char *,const char *,const char *,int,int,Rva00438CD0Callback,void *);
int gpConnectNewUserA(GPConnection *,const char *,const char *,const char *,const char *,const char *,int,int,Rva00438CD0Callback,void *);
int gpConnectPreAuthenticatedA(GPConnection *,const char *,const char *,int,int,Rva00438CD0Callback,void *);
void gpDisconnect(GPConnection *);
int gpDeleteProfile(GPConnection *);
int gpSetInfoMask(GPConnection *,int);
int gpSendBuddyMessageA(GPConnection *,int,const char *);
int gpSendBuddyRequestA(GPConnection *,int,const char *);
int gpDeleteBuddy(GPConnection *,int);
int gpAuthBuddyRequest(GPConnection *,int);
int gpDenyBuddyRequest(GPConnection *,int);
int gpSetStatusA(GPConnection *,int,const char *,const char *);
}
std::string WideCharStringToMultiByte(const unsigned short *);

struct BuddyRequest
{
    int kind;
    union {
        struct {
            char nick[31], email[51], password[31];
            bool hasFirewall;
            char m_76[0x200];
            char cdkey[65];
            bool m_2b7;
        } login;
        struct { int id; unsigned short text[128]; } message;
        struct { int status; char text[256], location[256]; } status;
        char storage[0x2b4];
    } arg;
};
enum Rva0063EB00Kind { RvaKind1=1, RvaKind5=5 };
enum Rva0063EB00Result { RvaResult4=4 };
enum Rva0063EB00Fatal { RvaFatal1=1 };
struct BuddyResponse
{
    Rva0063EB00Kind m_00;
    int m_04;
    Rva0063EB00Result m_08;
    int m_0c, m_10;
    char m_14[0x80];
    Rva0063EB00Fatal m_94;
    char m_98[0x7cc];
};
class GameSpyBuddyMessageQueueInterface
{
public:
    virtual ~GameSpyBuddyMessageQueueInterface();
    virtual void startThread();
    virtual void endThread();
    virtual bool isThreadRunning();
    virtual bool isConnected();
    virtual bool isConnecting();
    virtual void addRequest(const BuddyRequest &);
    virtual bool getRequest(BuddyRequest &);
    virtual void addResponse(const BuddyResponse &);
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

class Rva0063B080 { public: virtual void slot0(); };
class Gen_007e86c0 { public: void m(); };
class Rva007E8810Message { public: bool hasError(); };
class Gen_007e88b0 { public: int m(); };
class BfmeC994
{
    char m_opaque[0x34];
public:
    BfmeC994(char *,int);
    ~BfmeC994() { ((Gen_007e86c0*)this)->m(); }
    bool hasError() { return ((Rva007E8810Message*)this)->hasError(); }
    int error() { return ((Gen_007e88b0*)this)->m(); }
};
// Retail constructs and destroys a 0x330-byte frame object through the ledger's
// PeerResponse ctor/dtor (0x004DAB40/0x004DAC70 via ILT 0x00042069/0x00044733)
// and never reads it; only the size is modelled.
class PeerResponse
{
    char m_opaque[0x330];
public: PeerResponse(); ~PeerResponse();
};
class BfmeQ1279;
class BfmeA1279
{
public:
    BfmeA1279(BfmeQ1279 *a);
    BfmeQ1279 *m_bfme00;
    char m_bfme04[0x100];
    char m_bfme104[0x100];
};
class Rva007E9240SubAccounts
{
public:
    BfmeC994 *m_msg;
    int m_count;
    Rva007E9240SubAccounts(BfmeC994 *message) : m_msg(message), m_count(0) {}
    bool get(char *,int);
};
class Rva0063EB00ServicePump
{
public:
    virtual void slot0();
    virtual void slot1(BfmeC994 *,BfmeC994 *,int);
};
struct Rva007E9D70Cached
{
    virtual void slot0();
    virtual Rva0063EB00ServicePump *slot1();
    virtual void slot2();
    virtual void slot3(BfmeC994 *,const char *,const char *,int,int);
    virtual void slot4();
    virtual void slot5(BfmeC994 *,const char *);
    virtual void slot6(BfmeC994 *,const char *);
    virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12();
    virtual void slot13(); virtual void slot14();
    virtual void slot15(BfmeC994 *,const char *);
    virtual void slot16();
    virtual void slot17(BfmeC994 *);
    virtual void slot18();
    virtual void slot19(BfmeC994 *);
};
class Rva007E9D70 { public: Rva007E9D70Cached *get(); };
class Rva007EB6F0Object { public: void invoke(Rva0063B080 *,int); };
class Rva007EB700Object { public: void invoke(Rva0063B080 *); };
class BfmeThingUVA { public: void bfmeGoUVA(const char *,const char *,const char *); };
class Rva007EAD00 { public: void m(int); };
class Gen_007ea640 { public: void m(); };
class Gen_007ea2f0 { public: void m(); };
struct Rva007E9B70Obj { virtual void slot0(); virtual void slot1(int); };
Rva007E9B70Obj *Rva007E9B70Get();
int Rva007EB260Get();
int Rva007EB650Shutdown(int);
void Rva007EB270Shutdown();
class ServiceHubImpl;
ServiceHubImpl *createServiceHubImpl(void *,void *,void *,void *,void *,void *);
extern Rva007E9D70 *g_Rva012F71BC;
extern unsigned char g_Rva012F71B8, g_Rva012F71B9;

class BuddyThreadClass
{
public:
    virtual ~BuddyThreadClass();
    virtual void Execute();
    virtual void Thread_Function();
private:
    char m_unmodelled04[0x4c];
    bool m_isNewAccount, m_isConnecting, m_isConnected;
    int m_profileID, m_lastErrorCode;
    bool m_isDeleting;
    std::string m_nick, m_email, m_password, m_84, m_90;
    MutexClass *m_networkLock;
    CriticalSectionClass m_criticalSection;
    std::auto_ptr<CriticalSectionClass::LockClass> m_ownedLock;
};

void BuddyThreadClass::Thread_Function()
{
    m_ownedLock.reset();
    std::auto_ptr<Rva0063B080> callback(new Rva0063B080);
    if (g_Rva012F71BC == 0)
    {
        createServiceHubImpl((void*)"bfme",(void*)"14744",(void*)"en_US",(void*)"1.0",0,0);
        g_Rva012F71BC = (Rva007E9D70*)Rva007EB260Get();
        ((Rva007EB6F0Object*)g_Rva012F71BC->get())->invoke(callback.get(),0);
        ((BfmeThingUVA*)g_Rva012F71BC)->bfmeGoUVA("bfme.fesl.ea.com","","");
    }
    try
    {
        char game[12]; // Eight explicit retail stores; four following stack bytes are unused.
        game[0]='l'; game[1]='o'; game[2]='t'; game[3]='r';
        game[4]='b'; game[5]='m'; game[6]='e'; game[7]=0;
        GSIStartAvailableCheckA(game);
        int available;
        while ((available = GSIAvailableCheckThink()) == 0) Sleep(10);
        if (available == 1)
        {
            GPConnection gpCon;
            GPConnection *con = &gpCon;
            gpInitialize(con,0x2911,1);
            m_isConnected = m_isConnecting = false;
            gpSetCallback(con,0,callbackWrapper,(void*)1);
            gpSetCallback(con,3,callbackWrapper,(void*)2);
            gpSetCallback(con,1,callbackWrapper,(void*)3);
            gpSetCallback(con,2,callbackWrapper,(void*)4);
            int lastStatus = 0;
            std::string lastStatusString;
            BuddyRequest request;
            for (;;)
            {
                MutexClass::LockClass lock(*m_networkLock,1);
                if (!lock.Failed()) break;
                if (TheGameSpyBuddyMessageQueue->getRequest(request))
                {
                    switch (request.kind)
                    {
                    case 0:
                    {
                        m_isConnecting = true;
                        m_nick = request.arg.login.nick;
                        m_email = request.arg.login.email;
                        m_password = request.arg.login.password;
                        bool m_2b7 = request.arg.login.m_2b7;
                        __int64 start = timeGetTime();
                        ((Rva007EAD00*)g_Rva012F71BC)->m(0x466e);
                        while (!g_Rva012F71B8)
                        {
                            ((Gen_007ea640*)Rva007EB260Get())->m();
                            Rva007E9B70Get()->slot1(0x21);
                            __int64 now = timeGetTime();
                            if (now-start > 15000)
                            {
                                BuddyResponse timedOut;
                                timedOut.m_00=RvaKind1; timedOut.m_08=RvaResult4; timedOut.m_10=0x101; timedOut.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(timedOut);
                                break;
                            }
                        }
                        if (!g_Rva012F71B8) break;
                        if (g_Rva012F71B9)
                        {
                            m_isConnecting=m_isConnected=false;
                            BuddyResponse failed;
                            failed.m_00=RvaKind1; failed.m_08=RvaResult4; failed.m_10=6; failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        char requestData[1024], resultData[1024], extraData[1024];
                        BfmeC994 serviceRequest(requestData,1024);
                        BfmeC994 serviceResult(resultData,1024);
                        BfmeC994 extraRequest(extraData,1024);
                        char email[256] = {0};
                        char password[256] = {0};
                        strncpy(email,m_email.c_str(),255);
                        strncpy(password,m_password.c_str(),255);
                        g_Rva012F71BC->get()->slot3(&serviceRequest,email,password,0,0);
                        g_Rva012F71BC->get()->slot1()->slot1(&serviceRequest,&serviceResult,10000);
                        PeerResponse unusedResponse;
                        if (serviceResult.hasError())
                        {
                            m_isConnecting=m_isConnected=false;
                            BuddyResponse failed;
                            failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        g_Rva012F71BC->get()->slot17(&extraRequest);
                        g_Rva012F71BC->get()->slot1()->slot1(&extraRequest,&serviceResult,10000);
                        bool found = false;
                        if (!serviceResult.hasError())
                        {
                            Rva007E9240SubAccounts accounts(&serviceResult);
                            char name[32] = {0};
                            while (!found && accounts.get(name,32))
                                if (strcmp(m_nick.c_str(),name) == 0) found=true;
                        }
                        if (m_2b7)
                        {
                            if (!found)
                            {
                                BuddyResponse failed;
                                failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=0x26ac; failed.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(failed);
                                break;
                            }
                            g_Rva012F71BC->get()->slot6(&extraRequest,m_nick.c_str());
                            g_Rva012F71BC->get()->slot1()->slot1(&extraRequest,&serviceResult,10000);
                            if (serviceResult.hasError())
                            {
                                BuddyResponse failed;
                                failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(failed);
                                break;
                            }
                            BuddyResponse failed;
                            failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=0x26ad; failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        if (!found)
                        {
                            g_Rva012F71BC->get()->slot5(&extraRequest,m_nick.c_str());
                            g_Rva012F71BC->get()->slot1()->slot1(&extraRequest,&serviceResult,10000);
                            if (serviceResult.hasError())
                            {
                                BuddyResponse failed;
                                failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(failed);
                                break;
                            }
                        }
                        g_Rva012F71BC->get()->slot15(&serviceRequest,m_nick.c_str());
                        g_Rva012F71BC->get()->slot1()->slot1(&serviceRequest,&serviceResult,10000);
                        if (serviceResult.hasError())
                        {
                            m_isConnecting=m_isConnected=false;
                            BuddyResponse failed;
                            failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        g_Rva012F71BC->get()->slot19(&serviceRequest);
                        g_Rva012F71BC->get()->slot1()->slot1(&serviceRequest,&serviceResult,10000);
                        BfmeA1279 authentication((BfmeQ1279 *)&serviceResult);
                        m_84 = authentication.m_bfme04;
                        m_90 = authentication.m_bfme104;
                        if (gpConnectPreAuthenticatedA(con,authentication.m_bfme04,authentication.m_bfme104,
                                request.arg.login.hasFirewall?1:0,0,callbackWrapper,0))
                        {
                            BuddyResponse failed;
                            failed.m_00=RvaKind1; failed.m_94=RvaFatal1;
                            m_isConnecting=false;
                            failed.m_08=RvaResult4; failed.m_10=0x107;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                        }
                        break;
                    }
                    case 1:
                        m_isConnecting=true;
                        m_isConnected=(gpConnectA(con,m_nick.c_str(),m_email.c_str(),m_password.c_str(),1,1,callbackWrapper,0)==0);
                        m_isConnecting=false;
                        break;
                    case 10:
                        m_isDeleting=true;
                        gpDeleteProfile(con);
                        break;
                    case 2:
                        m_isConnecting=m_isConnected=false;
                        gpDisconnect(con);
                        break;
                    case 3:
                    {
                        std::string message=WideCharStringToMultiByte(request.arg.message.text);
                        gpSendBuddyMessageA(con,request.arg.message.id,message.c_str());
                        break;
                    }
                    case 4:
                        m_isConnecting=true;
                        m_nick=request.arg.login.nick;
                        m_email=request.arg.login.email;
                        m_password=request.arg.login.password;
                        m_isNewAccount=true;
                        m_isConnected=(gpConnectNewUserA(con,request.arg.login.nick,request.arg.login.nick,
                            request.arg.login.email,request.arg.login.password,request.arg.login.cdkey,
                            request.arg.login.hasFirewall?1:0,1,callbackWrapper,0)==0);
                        if (m_isNewAccount) gpSetInfoMask(con,0);
                        m_isConnecting=false;
                        break;
                    case 5:
                    {
                        std::string message=WideCharStringToMultiByte(request.arg.message.text);
                        gpSendBuddyRequestA(con,request.arg.message.id,message.c_str());
                        break;
                    }
                    case 6: gpDeleteBuddy(con,request.arg.message.id); break;
                    case 7: gpAuthBuddyRequest(con,request.arg.message.id); break;
                    case 8: gpDenyBuddyRequest(con,request.arg.message.id); break;
                    case 9:
                        if (lastStatus==2 && lastStatusString=="Loading" && request.arg.status.status==1) break;
                        gpSetStatusA(con,request.arg.status.status,request.arg.status.text,request.arg.status.location);
                        lastStatus=request.arg.status.status;
                        lastStatusString=request.arg.status.text;
                        break;
                    }
                }
                gpProcess(con);
                if (g_Rva012F71BC) ((Gen_007ea640*)g_Rva012F71BC)->m();
            }
            gpDestroy(con);
        }
    }
    catch (...) {}
    if (g_Rva012F71BC)
    {
        ((Rva007EB700Object*)g_Rva012F71BC->get())->invoke(callback.get());
        ((Gen_007ea2f0*)g_Rva012F71BC)->m();
        Rva007EB650Shutdown(0);
        Rva007EB270Shutdown();
        g_Rva012F71B9=0;
        g_Rva012F71B8=0;
        g_Rva012F71BC=0;
    }
}
