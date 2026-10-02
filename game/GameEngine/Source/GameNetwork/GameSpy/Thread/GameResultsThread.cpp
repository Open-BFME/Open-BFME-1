// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?createNewMessageQueue@GameSpyBuddyMessageQueueInterface@@SAPAV1@XZ: game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: PingThread.cpp //////////////////////////////////////////////////////
// Ping thread
// Author: Matthew D. Campbell, August 2002

#define __PLACEMENT_VEC_NEW_INLINE
#include <queue>		// BFME uses STLport's node allocator for the results queues; parse it
						// before PreRTS.h enables the plain-new allocator.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include <winsock.h>	// This one has to be here. Prevents collisions with winsock2.h

#include "GameNetwork/GameSpy/GameResultsThread.h"
#include "mutex.h"
#include "thread.h"

#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"

namespace _STL
{
template <>
void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_push_back_aux_v(
	const GameResultsResponse &response);

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsRequestDestroyThunk.cpp
template void __destroy<
	_Deque_iterator<GameResultsRequest,
		_Nonconst_traits<GameResultsRequest> >,
	GameResultsRequest>(
	_Deque_iterator<GameResultsRequest,
		_Nonconst_traits<GameResultsRequest> >,
	_Deque_iterator<GameResultsRequest,
		_Nonconst_traits<GameResultsRequest> >,
	GameResultsRequest *);
}

//-------------------------------------------------------------------------

static const Int NumWorkerThreads = 1;

typedef std::queue<GameResultsRequest> RequestQueue;
typedef std::queue<GameResultsResponse> ResponseQueue;
class GameResultsThreadClass;

class GameResultsQueue : public GameResultsInterface
{
public:
	virtual ~GameResultsQueue();
	GameResultsQueue();

	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

	virtual void startThreads( void );
	virtual void endThreads( void );
	virtual Bool areThreadsRunning( void );

	virtual void addRequest( const GameResultsRequest& req );
	virtual Bool getRequest( GameResultsRequest& resp );

	virtual void addResponse( const GameResultsResponse& resp );
	virtual Bool getResponse( GameResultsResponse& resp );

	virtual Bool areGameResultsBeingSent( void );

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	Int m_requestCount;
	Int m_responseCount;

	GameResultsThreadClass *m_workerThreads[NumWorkerThreads];
};

GameResultsInterface* GameResultsInterface::createNewGameResultsInterface( void )
{
	return NEW GameResultsQueue;
}

GameResultsInterface *TheGameResultsQueue;

//-------------------------------------------------------------------------

// BFME's ThreadClass is 0x50 bytes wide: Thread_Function reads its worker lock
// pointer at this+0x50 (0x00641ED3), and the reference thread.h lays the base
// out 8 bytes wider, so the base is redeclared here to keep that offset.
class GameResultsThreadBase
{
public:
	virtual ~GameResultsThreadBase();
	void Execute();
	bool Is_Running();

protected:
	virtual void Thread_Function() = 0;
	char m_threadName[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_threadPriority;
};

class GameResultsThreadClass : public GameResultsThreadBase
{

public:
	GameResultsThreadClass() : GameResultsThreadBase() {}

	void Thread_Function();

private:
	MutexClass *m_lock;
	Int sendGameResults( UnsignedInt IP, UnsignedShort port, const std::string& results );
};


//-------------------------------------------------------------------------

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsQueueCtorThunk.cpp
// ??0GameResultsQueue@@QAE@XZ present-unmatched
GameResultsQueue::GameResultsQueue() : m_requestCount(0), m_responseCount(0)
{
	for (Int i=0; i<NumWorkerThreads; ++i)
	{
		m_workerThreads[i] = NULL;
	}

	startThreads();
}

// ??1GameResultsQueue@@UAE@XZ present-unmatched
GameResultsQueue::~GameResultsQueue()
{
	endThreads();
}

// ?startThreads@GameResultsQueue@@UAEXXZ present-unmatched
void GameResultsQueue::startThreads( void )
{
	endThreads();
	for (Int i=0; i<NumWorkerThreads; ++i)
	{
		m_workerThreads[i] = NEW GameResultsThreadClass;
		m_workerThreads[i]->Execute();
	}
}

// ?endThreads@GameResultsQueue@@UAEXXZ present-unmatched
void GameResultsQueue::endThreads( void )
{
	for (Int i=0; i<NumWorkerThreads; ++i)
	{
		if (m_workerThreads[i])
		{
			delete m_workerThreads[i];
			m_workerThreads[i] = NULL;
		}
	}
}

Bool GameResultsQueue::areThreadsRunning( void )
{
	for (Int i=0; i<NumWorkerThreads; ++i)
	{
		if (m_workerThreads[i])
		{
			// BFME's thread base is 0x50 bytes, narrower than the reference
			// ThreadClass, so the base is called through its own type: retail
			// reaches ThreadClass::Is_Running through this pointer.
			if (((ThreadClass *)m_workerThreads[i])->Is_Running())
				return true;
		}
	}
	return false;
}

void GameResultsQueue::addRequest( const GameResultsRequest& req )
{
	MutexClass::LockClass m(m_requestMutex);

	++m_requestCount;
	m_requests.push(req);
}

Bool GameResultsQueue::getRequest( GameResultsRequest& req )
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return false;

	if (m_requests.empty())
		return false;
	req = m_requests.front();
	m_requests.pop();
	return true;
}

void GameResultsQueue::addResponse( const GameResultsResponse& resp )
{
	{
		MutexClass::LockClass m(m_responseMutex);

		++m_responseCount;
		m_responses.push(resp);
	}
}

Bool GameResultsQueue::getResponse( GameResultsResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex, 0);
	if (m.Failed())
		return false;

	if (m_responses.empty())
		return false;
	resp = m_responses.front();
	m_responses.pop();
	return true;
}

Bool GameResultsQueue::areGameResultsBeingSent( void )
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return true;

	return m_requestCount > 0;
}

//-------------------------------------------------------------------------

// Retail asks the queue for a request through vtable slot 0x34 (0x00641F2E):
// the Generals header reaches getRequest at 0x28, so BFME's
// SubsystemInterface carries three more virtuals than the reference one. The
// slots are named by index because nothing in the image names them; the shape
// is fixed by the call site and by GameResultsQueue::getRequest (0x00642440)
// which pops a request and returns the bool the caller tests.
struct Rva00641F2EQueueSlots
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual Bool slot34(GameResultsRequest &req);
};

// Replaces the naked __emit lift that used to live in
// game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThreadClass_Thread_FunctionMethodThunk.cpp
void GameResultsThreadClass::Thread_Function()
{
	try {
	GameResultsRequest req;

	WSADATA wsaData;

	// Fire up winsock (prob already done, but doesn't matter)
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSAStartup( wVersionRequested, &wsaData );

	// The worker lock is held by whoever tears the thread down, so once we can
	// take it ourselves the loop is over.
	while (true)
	{
		MutexClass::LockClass lock(*m_lock, 1);
		if (!lock.Failed())
			break;

		// deal with requests
		if (TheGameResultsQueue && ((Rva00641F2EQueueSlots *)TheGameResultsQueue)->slot34(req))
		{
			// resolve the hostname
			const char *hostnameBuffer = req.hostname.c_str();
			UnsignedInt IP = 0xFFFFFFFF;
			if (isdigit(hostnameBuffer[0]))
			{
				IP = inet_addr(hostnameBuffer);
				in_addr hostNode;
				hostNode.s_addr = IP;
				DEBUG_LOG(("sending game results to %s - IP = %s\n", hostnameBuffer, inet_ntoa(hostNode) ));
			}
			else
			{
				HOSTENT *hostStruct;
				in_addr *hostNode;
				hostStruct = gethostbyname(hostnameBuffer);
				if (hostStruct == NULL)
				{
					DEBUG_LOG(("sending game results to %s - host lookup failed\n", hostnameBuffer));

					// Even though this failed to resolve IP, still need to send a
					//   callback.
					IP = 0xFFFFFFFF;   // flag for IP resolve failed
				}
				hostNode = (in_addr *) hostStruct->h_addr;
				IP = hostNode->s_addr;
				DEBUG_LOG(("sending game results to %s IP = %s\n", hostnameBuffer, inet_ntoa(*hostNode) ));
			}

			Int result = sendGameResults( IP, req.port, req.results );
			GameResultsResponse resp;
			resp.hostname = req.hostname;
			resp.port = req.port;
			resp.sentOk = (result == req.results.length());
		}
	}

	WSACleanup();
	} catch ( ... ) {
		DEBUG_CRASH(("Exception in results thread!"));
	}
}

//-------------------------------------------------------------------------

#ifdef DEBUG_LOGGING
#define CASE(x) case (x): return #x;

static const char *getWSAErrorString( Int error )
{
	switch (error)
	{
		CASE(WSABASEERR)
		CASE(WSAEINTR)
		CASE(WSAEBADF)
		CASE(WSAEACCES)
		CASE(WSAEFAULT)
		CASE(WSAEINVAL)
		CASE(WSAEMFILE)
		CASE(WSAEWOULDBLOCK)
		CASE(WSAEINPROGRESS)
		CASE(WSAEALREADY)
		CASE(WSAENOTSOCK)
		CASE(WSAEDESTADDRREQ)
		CASE(WSAEMSGSIZE)
		CASE(WSAEPROTOTYPE)
		CASE(WSAENOPROTOOPT)
		CASE(WSAEPROTONOSUPPORT)
		CASE(WSAESOCKTNOSUPPORT)
		CASE(WSAEOPNOTSUPP)
		CASE(WSAEPFNOSUPPORT)
		CASE(WSAEAFNOSUPPORT)
		CASE(WSAEADDRINUSE)
		CASE(WSAEADDRNOTAVAIL)
		CASE(WSAENETDOWN)
		CASE(WSAENETUNREACH)
		CASE(WSAENETRESET)
		CASE(WSAECONNABORTED)
		CASE(WSAECONNRESET)
		CASE(WSAENOBUFS)
		CASE(WSAEISCONN)
		CASE(WSAENOTCONN)
		CASE(WSAESHUTDOWN)
		CASE(WSAETOOMANYREFS)
		CASE(WSAETIMEDOUT)
		CASE(WSAECONNREFUSED)
		CASE(WSAELOOP)
		CASE(WSAENAMETOOLONG)
		CASE(WSAEHOSTDOWN)
		CASE(WSAEHOSTUNREACH)
		CASE(WSAENOTEMPTY)
		CASE(WSAEPROCLIM)
		CASE(WSAEUSERS)
		CASE(WSAEDQUOT)
		CASE(WSAESTALE)
		CASE(WSAEREMOTE)
		CASE(WSAEDISCON)
		CASE(WSASYSNOTREADY)
		CASE(WSAVERNOTSUPPORTED)
		CASE(WSANOTINITIALISED)
		CASE(WSAHOST_NOT_FOUND)
		CASE(WSATRY_AGAIN)
		CASE(WSANO_RECOVERY)
		CASE(WSANO_DATA)
		default:
			return "Not a Winsock error";
	}
}

#undef CASE

#endif
//-------------------------------------------------------------------------

Int GameResultsThreadClass::sendGameResults( UnsignedInt IP, UnsignedShort port, const std::string& results )
{
	int error = 0;

	// create the socket
	Int sock = socket( AF_INET, SOCK_STREAM, 0 );
	if (sock < 0)
	{
		DEBUG_LOG(("GameResultsThreadClass::sendGameResults() - socket() returned %d(%s)\n", sock, getWSAErrorString(sock)));
		return sock;
	}

	// fill in address info
	struct sockaddr_in sockAddr;
	memset( &sockAddr, 0, sizeof( sockAddr ) );
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = IP;
	sockAddr.sin_port = htons(port);

	// Start the connection process....
	if( connect( sock, (struct sockaddr *)&sockAddr, sizeof( sockAddr ) ) == -1 )
	{
		error = WSAGetLastError();
		DEBUG_LOG(("GameResultsThreadClass::sendGameResults() - connect() returned %d(%s)\n", error, getWSAErrorString(error)));
		if( ( error == WSAEWOULDBLOCK ) || ( error == WSAEINVAL ) || ( error == WSAEALREADY ) )
		{
			return( -1 );
		}

		if( error != WSAEISCONN )
		{
			closesocket( sock );
			return( -1 );
		}
	}

	if (send( sock, results.c_str(), results.length(), 0 ) == SOCKET_ERROR)
	{
		error = WSAGetLastError();
		DEBUG_LOG(("GameResultsThreadClass::sendGameResults() - send() returned %d(%s)\n", error, getWSAErrorString(error)));
		closesocket(sock);
		return WSAGetLastError();
	}

	closesocket(sock);

	return results.length();
}


//-------------------------------------------------------------------------

#pragma optimize("gty", on)
namespace _STL
{
template <>
void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_push_back_aux_v(
	const GameResultsResponse &response)
{
	GameResultsResponse responseCopy = response;
	_M_reserve_map_at_back();
	*(this->_M_finish._M_node + 1) = this->_M_map_size.allocate(this->buffer_size());
	_Construct(this->_M_finish._M_cur, responseCopy);
	this->_M_finish._M_set_node(this->_M_finish._M_node + 1);
	this->_M_finish._M_cur = this->_M_finish._M_first;
}
}

// 0x009EEA50: the front-side twin of _M_reserve_map_at_back (0x009EEA20),
// directly after it; it calls this deque's _M_reallocate_map with add_at_front.
namespace _STL
{
template void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_reserve_map_at_front(size_t);
}
