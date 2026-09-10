// ?Thread_Function@BuddyThreadClass@@UAEXXZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/buddythread /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME BuddyThreadClass::Thread_Function, retail RVA 0x0063EB00.
// The BFME image has a larger thread object than the ZH BuddyThread.cpp class:
// the constructor at 0x0063C4F0 proves the five string members and the network
// lock at +0x9C.  This TU keeps that layout separate from the ZH implementation.
// ?rva0063eb00@Rva0063EB00BuddyThread@@QAEXXZ present-unmatched

#define Matrix4x4 Matrix4
#define _STLP_USE_STATIC_LIB

#include "PreRTS.h"
#include <string.h>

#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "Common/StackDump.h"
#include "thread.h"

class BFMENetworkLock;

class BFMENetworkThreadBase
{
public:
	BFMENetworkThreadBase(const char *name);
	virtual ~BFMENetworkThreadBase();
	virtual void Execute();
	virtual void Thread_Function() = 0;

private:
	char m_name[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_priority;
};

class CriticalSectionClass
{
public:
	CriticalSectionClass();
	~CriticalSectionClass();

	class LockClass
	{
	public:
		LockClass(CriticalSectionClass &criticalSection);
		~LockClass();

	private:
		char m_body[4];
	};

private:
	char m_body[8];
};

class BuddyOwnedLock
{
public:
	BuddyOwnedLock() : m_lock(0) {}
	~BuddyOwnedLock();

	CriticalSectionClass::LockClass *m_lock;
};

class BFMEAutoLockRef
{
public:
	BFMEAutoLockRef(BFMENetworkLock *lock, unsigned int timeout);
	__declspec(noinline) ~BFMEAutoLockRef();
	Bool failed() const { return m_failed; }

private:
	BFMENetworkLock *m_lock;
	Bool m_failed;
};

class BuddyThreadClass : public BFMENetworkThreadBase
{
public:
	virtual void Thread_Function();

private:
	bool m_isNewAccount;
	bool m_isConnecting;
	bool m_isConnected;
	int m_profileID;
	int m_lastErrorCode;
	bool m_isDeleting;
	_STL::string m_nick;
	_STL::string m_email;
	_STL::string m_password;
	_STL::string m_status;
	_STL::string m_error;
	BFMENetworkLock *m_networkLock;
	CriticalSectionClass m_criticalSection;
	BuddyOwnedLock m_ownedLock;
};

enum CallbackType
{
	CALLBACK_CONNECT,
	CALLBACK_ERROR,
	CALLBACK_RECVMESSAGE,
	CALLBACK_RECVREQUEST,
	CALLBACK_RECVSTATUS,
	CALLBACK_MAX
};

extern void callbackWrapper(GPConnection *con, void *arg, void *param);
extern void *createServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f);
extern int Rva007EB260Get(void);
extern unsigned char g_bfmeFlagAGA;
extern unsigned char g_bfmeFlagBGA;

extern _STL::string WideCharStringToMultiByte(const WideChar *orig);

void BuddyThreadClass::Thread_Function()
{
	try
	{
		_set_se_translator(DumpExceptionInfo);

		// The BFME service hub is initialized before the GP connection.  The
		// literal is the product string loaded by the retail body, not the ZH
		// product-id path used by BuddyThread.cpp.
		if (Rva007EB260Get() == 0)
			createServiceHubImpl((void *)"lotrbme", 0, 0, 0, 0, 0);

		GPConnection gpCon;
		GPConnection *con = &gpCon;
		gpInitialize(con, 0);
		m_isConnected = false;
		m_isConnecting = false;

		gpSetCallback(con, GP_ERROR, callbackWrapper, (void *)CALLBACK_ERROR);
		gpSetCallback(con, GP_RECV_BUDDY_MESSAGE, callbackWrapper,
			(void *)CALLBACK_RECVMESSAGE);
		gpSetCallback(con, GP_RECV_BUDDY_REQUEST, callbackWrapper,
			(void *)CALLBACK_RECVREQUEST);
		gpSetCallback(con, GP_RECV_BUDDY_STATUS, callbackWrapper,
			(void *)CALLBACK_RECVSTATUS);

		GPEnum lastStatus = GP_OFFLINE;
		char lastStatusString[GP_STATUS_STRING_LEN] = { 0 };
		BuddyRequest incomingRequest;

		while (!m_isDeleting)
		{
			BFMEAutoLockRef lock(m_networkLock, 1);
			if (lock.failed())
			{
				ThreadClass::Switch_Thread();
				continue;
			}

			// The BFME callback bridge publishes these event flags on the same
			// queue consumed below.  Consume each flag while the network lock is
			// held so the service state and the thread fields move together.
			if (g_bfmeFlagAGA)
			{
				m_isConnected = false;
				m_isConnecting = false;
				g_bfmeFlagAGA = 0;
			}
			if (g_bfmeFlagBGA)
			{
				m_isConnected = true;
				g_bfmeFlagBGA = 0;
			}

			if (TheGameSpyBuddyMessageQueue->getRequest(incomingRequest))
			{
				switch (incomingRequest.buddyRequestType)
				{
				case BuddyRequest::BUDDYREQUEST_LOGIN:
					m_isConnecting = true;
					m_nick = incomingRequest.arg.login.nick;
					m_email = incomingRequest.arg.login.email;
					m_password = incomingRequest.arg.login.password;
					m_isConnected = (gpConnect(con, m_nick.c_str(), m_email.c_str(),
						m_password.c_str(),
						incomingRequest.arg.login.hasFirewall ? GP_FIREWALL : GP_NO_FIREWALL,
						GP_BLOCKING, callbackWrapper, (void *)CALLBACK_CONNECT) == GP_NO_ERROR);
					m_isConnecting = false;
					break;

				case BuddyRequest::BUDDYREQUEST_RELOGIN:
					m_isConnecting = true;
					m_isConnected = (gpConnect(con, m_nick.c_str(), m_email.c_str(),
						m_password.c_str(), GP_FIREWALL, GP_BLOCKING,
						callbackWrapper, (void *)CALLBACK_CONNECT) == GP_NO_ERROR);
					m_isConnecting = false;
					break;

				case BuddyRequest::BUDDYREQUEST_DELETEACCT:
					m_isDeleting = true;
					gpDeleteProfile(con);
					break;

				case BuddyRequest::BUDDYREQUEST_LOGOUT:
					m_isConnected = false;
					m_isConnecting = false;
					gpDisconnect(con);
					break;

				case BuddyRequest::BUDDYREQUEST_MESSAGE:
				{
					_STL::string message =
						WideCharStringToMultiByte(incomingRequest.arg.message.text);
					gpSendBuddyMessage(con, incomingRequest.arg.message.recipient,
						message.c_str());
				}
				break;

				case BuddyRequest::BUDDYREQUEST_LOGINNEW:
					m_isConnecting = true;
					m_nick = incomingRequest.arg.login.nick;
					m_email = incomingRequest.arg.login.email;
					m_password = incomingRequest.arg.login.password;
					m_isNewAccount = true;
					m_isConnected = (gpConnectNewUser(con, m_nick.c_str(), m_email.c_str(),
						m_password.c_str(), incomingRequest.arg.login.hasFirewall ? GP_FIREWALL : GP_NO_FIREWALL,
						GP_BLOCKING, callbackWrapper, (void *)CALLBACK_CONNECT) == GP_NO_ERROR);
					if (m_isNewAccount)
						gpSetInfoMask(con, GP_MASK_NONE);
					m_isConnecting = false;
					break;

				case BuddyRequest::BUDDYREQUEST_ADDBUDDY:
				{
					_STL::string message =
						WideCharStringToMultiByte(incomingRequest.arg.addbuddy.text);
					gpSendBuddyRequest(con, incomingRequest.arg.addbuddy.id, message.c_str());
				}
				break;

				case BuddyRequest::BUDDYREQUEST_DELBUDDY:
					gpDeleteBuddy(con, incomingRequest.arg.profile.id);
					break;

				case BuddyRequest::BUDDYREQUEST_OKADD:
					gpAuthBuddyRequest(con, incomingRequest.arg.profile.id);
					break;

				case BuddyRequest::BUDDYREQUEST_DENYADD:
					gpDenyBuddyRequest(con, incomingRequest.arg.profile.id);
					break;

				case BuddyRequest::BUDDYREQUEST_SETSTATUS:
					if (!(lastStatus == GP_PLAYING &&
						strcmp(lastStatusString, "Loading") == 0 &&
						incomingRequest.arg.status.status == GP_ONLINE))
					{
						gpSetStatus(con, incomingRequest.arg.status.status,
							incomingRequest.arg.status.statusString,
							incomingRequest.arg.status.locationString);
						lastStatus = incomingRequest.arg.status.status;
						strncpy(lastStatusString, incomingRequest.arg.status.statusString,
							sizeof(lastStatusString) - 1);
						lastStatusString[sizeof(lastStatusString) - 1] = 0;
						m_status = incomingRequest.arg.status.statusString;
					}
					break;
				}
			}

			GPEnum isConnected = GP_CONNECTED;
			if (gpIsConnected(con, &isConnected) == GP_NO_ERROR &&
				isConnected == GP_CONNECTED)
				gpProcess(con);

			ThreadClass::Switch_Thread();
		}

		gpDestroy(con);
	}
	catch (...)
	{
		DEBUG_CRASH(("Exception in BFME buddy thread!"));
	}
}
