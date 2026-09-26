// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ??0Pinger@@: game/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp
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
