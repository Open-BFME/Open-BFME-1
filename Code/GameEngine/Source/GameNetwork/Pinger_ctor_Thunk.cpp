// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ??0Pinger@@: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp
// Open-BFME5: lift the Pinger constructor to clean C++.

#define Matrix4x4 Matrix4
#define _STLP_USE_STATIC_LIB
#include "PreRTS.h"
#include <queue>
#include <map>
#include <string>
#include "GameNetwork/GameSpy/PingThread.h"
#include "mutex.h"

class PingThreadClass;

class Pinger : public PingerInterface
{
public:
	virtual ~Pinger();
	Pinger();
	virtual void startThreads();
	virtual void endThreads();
	virtual Bool areThreadsRunning();
	virtual void addRequest(const PingRequest &);
	virtual Bool getRequest(PingRequest &);
	virtual void addResponse(const PingResponse &);
	virtual Bool getResponse(PingResponse &);
	virtual Bool arePingsInProgress();
	virtual Int getPing(AsciiString);
	virtual void clearPingMap();
	virtual AsciiString getPingString(Int);

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	MutexClass m_pingMapMutex;
	std::queue<PingRequest> m_requests;
	std::queue<PingResponse> m_responses;
	Int m_requestCount;
	Int m_responseCount;
	std::map<std::string, Int> m_pingMap;
	PingThreadClass *m_workerThreads[10];
	MutexClass m_workerMutex;
	Int m_workerCount;
};

// ??0Pinger@@QAE@XZ
Pinger::Pinger() : m_requestCount(0), m_responseCount(0), m_workerCount(0)
{
	for (Int index = 0; index < 10; ++index)
		m_workerThreads[index] = 0;
}
