// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define _STLP_USE_STATIC_LIB

#include "PreRTS.h"
#include <winsock.h>
#include <string>

#include "Common/StackDump.h"

class PingRequest
{
public:
	_STL::string hostname;
	Int repetitions;
	Int timeout;
};

class PingResponse
{
public:
	_STL::string hostname;
	Int avgPing;
	Int repetitions;
};

class PingerInterface
{
public:
	virtual ~PingerInterface() {}
	virtual void startThreads() = 0;
	virtual void endThreads() = 0;
	virtual Bool areThreadsRunning() = 0;
	virtual void addRequest(const PingRequest &) = 0;
	virtual Bool getRequest(PingRequest &) = 0;
	virtual void addResponse(const PingResponse &) = 0;
	virtual Bool getResponse(PingResponse &) = 0;
	virtual Bool arePingsInProgress() = 0;
	virtual Int getPing(AsciiString) = 0;
	virtual void clearPingMap() = 0;
	virtual AsciiString getPingString(Int) = 0;
};

extern PingerInterface *ThePinger;

class BFMENetworkLock
{
};

class BFMENetworkThreadBase
{
public:
	virtual ~BFMENetworkThreadBase();
	virtual void start();

protected:
	char m_threadName[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_threadPriority;
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

class PingThreadClass : public BFMENetworkThreadBase
{
public:
	virtual void Thread_Function();

private:
	BFMENetworkLock *m_lock;
	Int doPing(UnsignedInt IP, Int timeout);
};

void PingThreadClass::Thread_Function()
{
	try {
	PingRequest req;
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSAStartup(wVersionRequested, &wsaData);

	while (true) {
		BFMEAutoLockRef lock(m_lock, 1);
		if (!lock.failed())
			break;

		if (ThePinger->getRequest(req)) {
			const char *hostnameBuffer = req.hostname.c_str();
			UnsignedInt IP = 0xFFFFFFFF;
			if (isdigit(hostnameBuffer[0])) {
				IP = inet_addr(hostnameBuffer);
				in_addr hostNode;
				hostNode.s_addr = IP;
				DEBUG_LOG(("pinging %s - IP = %s\n", hostnameBuffer, inet_ntoa(hostNode)));
			} else {
				HOSTENT *hostStruct = gethostbyname(hostnameBuffer);
				in_addr *hostNode;
				if (hostStruct == NULL) {
					DEBUG_LOG(("pinging %s - host lookup failed\n", hostnameBuffer));
					IP = 0xFFFFFFFF;
				}
				hostNode = (in_addr *)hostStruct->h_addr;
				IP = hostNode->s_addr;
				DEBUG_LOG(("pinging %s IP = %s\n", hostnameBuffer, inet_ntoa(*hostNode)));
			}

			Int totalPing = 0;
			Int goodReps = 0;
			Int reps = req.repetitions;
			while (reps-- && IP != 0xFFFFFFFF) {
				BFMEAutoLockRef pingLock(m_lock, 1);
				if (!pingLock.failed())
					break;
				Int ping = doPing(IP, req.timeout);
				if (ping >= 0) {
					totalPing += ping;
					++goodReps;
				}
			}

			if (!goodReps)
				totalPing = -1;
			else
				totalPing = totalPing / goodReps;

			PingResponse resp;
			resp.hostname = req.hostname;
			resp.avgPing = totalPing;
			resp.repetitions = goodReps;
			ThePinger->addResponse(resp);
		}
	}

	WSACleanup();
	} catch (...) {
		DEBUG_CRASH(("Exception in ping thread!"));
	}
}
