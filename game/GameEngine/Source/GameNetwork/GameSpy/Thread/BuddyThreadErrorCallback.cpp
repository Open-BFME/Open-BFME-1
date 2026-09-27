// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gamespy /Igame/GameEngine/Source/GameNetwork/GameSpy /Iinputs/reference/shims/sweep

// Native BuddyThreadClass::errorCallback, 0063D210..0063DCB0 (2720 bytes).
// Identity and full extent:
// targets/game/reverse/identity_evidence/0063d210-error-callback-native.md. The SDK supplies the
// real GP enum values and pointer/argument types. Keep the original diagnostic result formatting:
// DEBUG_LOG uses it in debug builds. Retail's release optimizer eliminates that work; removing its
// source changes the register allocation of the surviving error-code switch.
#include <string.h>
#include "gp/gp.h"
#include "Common/Debug.h"
class PeerRequest {
  public:
    PeerRequest();
    ~PeerRequest();
    int peerRequestType;
    char rva04[0x190];
};
struct BuddyResponse {
    enum Kind { Login, Disconnect, Message, Request, Status, RvaKind5, RvaKind6 } buddyResponseType;
    int profile;
    GPResult result;
    int rva0C;
    GPErrorCode errorCode;
    char errorString[128];
    GPEnum fatal;
    char rva98[0x7cc];
};
typedef char PeerRequestSize[sizeof(PeerRequest) == 0x194 ? 1 : -1];
typedef char BuddyResponseSize[sizeof(BuddyResponse) == 0x864 ? 1 : -1];
class GameSpyBuddyMessageQueueInterface {
  public:
    virtual ~GameSpyBuddyMessageQueueInterface();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void addResponse(const BuddyResponse &);
};
class GameSpyPeerMessageQueueInterface {
  public:
    virtual ~GameSpyPeerMessageQueueInterface();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void addRequest(const PeerRequest &);
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class BuddyThreadClass {
  public:
    void errorCallback(GPConnection *, GPErrorArg *);
    char rva00[0x50];
    bool m_isNewAccount, m_isConnecting, m_isConnected;
    int m_profileID, m_lastErrorCode;
    bool m_isdeleting;
};
void BuddyThreadClass::errorCallback(GPConnection *con, GPErrorArg *arg) {
    DEBUG_LOG(("GPErrorCallback\n"));
    m_lastErrorCode = arg->errorCode;
    char errorCodeString[256];
    char resultString[256];
#define RESULT(x)                                                                                  \
    case x:                                                                                        \
        strcpy(resultString, #x);                                                                  \
        break;
    switch (arg->result) {
        RESULT(GP_NO_ERROR)
        RESULT(GP_MEMORY_ERROR)
        RESULT(GP_PARAMETER_ERROR)
        RESULT(GP_NETWORK_ERROR)
        RESULT(GP_SERVER_ERROR)
    default:
        strcpy(resultString, "Unknown result!");
    }
#undef RESULT
#define ERRORCODE(x)                                                                               \
    case x:                                                                                        \
        strcpy(errorCodeString, #x);                                                               \
        break;
    switch (arg->errorCode) {
        ERRORCODE(GP_GENERAL)
        ERRORCODE(GP_PARSE)
        ERRORCODE(GP_NOT_LOGGED_IN)
        ERRORCODE(GP_BAD_SESSKEY)
        ERRORCODE(GP_DATABASE)
        ERRORCODE(GP_NETWORK)
        ERRORCODE(GP_FORCED_DISCONNECT)
        ERRORCODE(GP_CONNECTION_CLOSED)
        ERRORCODE(GP_LOGIN)
        ERRORCODE(GP_LOGIN_TIMEOUT)
        ERRORCODE(GP_LOGIN_BAD_NICK)
        ERRORCODE(GP_LOGIN_BAD_EMAIL)
        ERRORCODE(GP_LOGIN_BAD_PASSWORD)
        ERRORCODE(GP_LOGIN_BAD_PROFILE)
        ERRORCODE(GP_LOGIN_PROFILE_DELETED)
        ERRORCODE(GP_LOGIN_CONNECTION_FAILED)
        ERRORCODE(GP_LOGIN_SERVER_AUTH_FAILED)
        ERRORCODE(GP_NEWUSER)
        ERRORCODE(GP_NEWUSER_BAD_NICK)
        ERRORCODE(GP_NEWUSER_BAD_PASSWORD)
        ERRORCODE(GP_NEWUSER_UNIQUENICK_INUSE)
        ERRORCODE(GP_UPDATEUI)
        ERRORCODE(GP_UPDATEUI_BAD_EMAIL)
        ERRORCODE(GP_NEWPROFILE)
        ERRORCODE(GP_NEWPROFILE_BAD_NICK)
        ERRORCODE(GP_NEWPROFILE_BAD_OLD_NICK)
        ERRORCODE(GP_UPDATEPRO)
        ERRORCODE(GP_UPDATEPRO_BAD_NICK)
        ERRORCODE(GP_ADDBUDDY)
        ERRORCODE(GP_ADDBUDDY_BAD_FROM)
        ERRORCODE(GP_ADDBUDDY_BAD_NEW)
        ERRORCODE(GP_ADDBUDDY_ALREADY_BUDDY)
        ERRORCODE(GP_AUTHADD)
        ERRORCODE(GP_AUTHADD_BAD_FROM)
        ERRORCODE(GP_AUTHADD_BAD_SIG)
        ERRORCODE(GP_STATUS)
        ERRORCODE(GP_BM)
        ERRORCODE(GP_BM_NOT_BUDDY)
        ERRORCODE(GP_GETPROFILE)
        ERRORCODE(GP_GETPROFILE_BAD_PROFILE)
        ERRORCODE(GP_DELBUDDY)
        ERRORCODE(GP_DELBUDDY_NOT_BUDDY)
        ERRORCODE(GP_DELPROFILE)
        ERRORCODE(GP_DELPROFILE_LAST_PROFILE)
        ERRORCODE(GP_SEARCH)
        ERRORCODE(GP_SEARCH_CONNECTION_FAILED)
    default:
        strcpy(errorCodeString, "Unknown error code!");
    }
#undef ERRORCODE
    if (arg->fatal) {
        DEBUG_LOG(("-----------\n"));
        DEBUG_LOG(("GP FATAL ERROR\n"));
        DEBUG_LOG(("-----------\n"));
    } else {
        DEBUG_LOG(("-----\n"));
        DEBUG_LOG(("GP ERROR\n"));
        DEBUG_LOG(("-----\n"));
    }
    DEBUG_LOG(("RESULT: %s (%d)\n", resultString, arg->result));
    DEBUG_LOG(("ERROR CODE: %s (0x%X)\n", errorCodeString, arg->errorCode));
    DEBUG_LOG(("ERROR STRING: %s\n", arg->errorString));
    if (arg->fatal == GP_FATAL && arg->errorCode != GP_LOGIN_BAD_NICK &&
        arg->errorCode != GP_LOGIN_BAD_EMAIL) {
        BuddyResponse response;
        response.buddyResponseType = arg->errorCode == GP_FORCED_DISCONNECT
                                         ? BuddyResponse::RvaKind6
                                         : BuddyResponse::Disconnect;
        response.result = arg->result;
        response.errorCode = arg->errorCode;
        response.fatal = arg->fatal;
        strncpy(response.errorString, arg->errorString, 128);
        response.errorString[127] = 0;
        strncpy(response.errorString, errorCodeString, 127);
        m_isConnecting = m_isConnected = false;
        TheGameSpyBuddyMessageQueue->addResponse(response);
        if (m_isdeleting) {
            PeerRequest req;
            req.peerRequestType = 1;
            TheGameSpyPeerMessageQueue->addRequest(req);
            m_isdeleting = false;
        }
    }
}
