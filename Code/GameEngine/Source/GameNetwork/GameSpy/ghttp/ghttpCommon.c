// cl: /ICode/GameEngine/Source/GameNetwork/GameSpy/ghttp /DNDEBUG /DWIN32 /MD -Ireference/shims/gamespy
/* GameSpy SDK, 2004 vintage -- upstream C source PLUS a reconstruction of
   EA's own edits to THIS file, inferred from retail's bytes.  Not pristine:
   see PROVENANCE.txt, "What differs from upstream", which lists every such
   file and what changed.  Each changed site is also marked in place.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only. */
/*
GameSpy GHTTP SDK 
Dan "Mr. Pants" Schoenblum
dan@gamespy.com

Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com
*/

#include "ghttpCommon.h"

// Disable compiler warnings for issues that are unavoidable.
/////////////////////////////////////////////////////////////
#if defined(_MSC_VER) // DevStudio
// Level4, "conditional expression is constant". 
// Occurs with use of the MS provided macro FD_SET
#pragma warning ( disable: 4127 )
#endif // _MSC_VER

#ifdef WIN32
// A lock.
//////////
typedef void * GLock;

// The lock used by ghttp.
//////////////////////////
static GLock ghiGlobalLock;
#endif

// Proxy server.
////////////////
char * ghiProxyAddress;
unsigned short ghiProxyPort;

// Throttle settings.
/////////////////////
int ghiThrottleBufferSize = 125;
gsi_time ghiThrottleTimeDelay = 250;

#ifdef WIN32
// Creates a lock.
//////////////////
static GLock GNewLock(void)
{
	CRITICAL_SECTION * criticalSection;

	criticalSection = (CRITICAL_SECTION *)gsimalloc(sizeof(CRITICAL_SECTION));
	if(!criticalSection)
		return NULL;

	InitializeCriticalSection(criticalSection);

	return (GLock)criticalSection;
}

// Frees a lock.
////////////////
static void GFreeLock(GLock lock)
{
	CRITICAL_SECTION * criticalSection = (CRITICAL_SECTION *)lock;

	if(!lock)
		return;

	DeleteCriticalSection(criticalSection);

	gsifree(criticalSection);
}

// Locks a lock.
////////////////
static void GLockLock(GLock lock)
{
	CRITICAL_SECTION * criticalSection = (CRITICAL_SECTION *)lock;

	if(!lock)
		return;

	EnterCriticalSection(criticalSection);
}

// Unlocks a lock.
//////////////////
static void GUnlockLock(GLock lock)
{
	CRITICAL_SECTION * criticalSection = (CRITICAL_SECTION *)lock;

	if(!lock)
		return;

	LeaveCriticalSection(criticalSection);
}
#endif

// Creates the ghttp lock.
//////////////////////////
void ghiCreateLock(void)
{
#ifdef WIN32
	// We shouldn't already have a lock.
	////////////////////////////////////
	assert(!ghiGlobalLock);

	// Create the lock.
	///////////////////
	ghiGlobalLock = GNewLock();
#endif
}

// Frees the ghttp lock.
////////////////////////
void ghiFreeLock(void)
{
#ifdef WIN32
	if(!ghiGlobalLock)
		return;

	GFreeLock(ghiGlobalLock);
	ghiGlobalLock = NULL;
#endif
}

// Locks the ghttp lock.
////////////////////////
void ghiLock
(
	void
)
{
#ifdef WIN32
	if(!ghiGlobalLock)
		return;

	GLockLock(ghiGlobalLock);
#endif
}

// Unlocks the ghttp lock.
//////////////////////////
void ghiUnlock
(
	void
)
{
#ifdef WIN32
	if(!ghiGlobalLock)
		return;

	GUnlockLock(ghiGlobalLock);
#endif
}

// Logs traffic.
////////////////
#ifdef HTTP_LOG
void ghiLog(char * buffer, int len)
{
	FILE * file;

	if(!buffer || !len)
		return;

	file = fopen("http.log", "ab");
	if(file)
	{
		fwrite(buffer, 1, len, file);
		fclose(file);
	}
}
#endif

// Does a select on a socket. BFME returns the raw select result, including
// SOCKET_ERROR, despite the legacy GHTTPBool return typedef.
/////////////////////////////
GHTTPBool ghiSocketSelect
(
	SOCKET socket,
	GHTTPBool * readFlag,
	GHTTPBool * writeFlag,
	GHTTPBool * exceptFlag
)
{
#if 1
	fd_set writeSet;
	fd_set readSet;
	fd_set exceptSet;
	fd_set * readfds = NULL;
	fd_set * writefds = NULL;
	fd_set * exceptfds = NULL;
	int rcode;
	struct timeval timeout = { 0, 0 };

	assert(socket != INVALID_SOCKET);

	// Setup the parameters.
	////////////////////////
	if(readFlag != NULL)
	{
		FD_ZERO(&readSet);
		FD_SET(socket, &readSet);
		readfds = &readSet;
	}
	if(writeFlag != NULL)
	{
		FD_ZERO(&writeSet);
		FD_SET(socket, &writeSet);
		writefds = &writeSet;
	}
	if(exceptFlag != NULL)
	{
		FD_ZERO(&exceptSet);
		FD_SET(socket, &exceptSet);
		exceptfds = &exceptSet;
	}



	// Get the write info.
	//////////////////////
	rcode = select(FD_SETSIZE, readfds, writefds, exceptfds, &timeout);
	if(rcode == SOCKET_ERROR)
		return rcode;

	// Check results.
	/////////////////
	if(readFlag != NULL)
	{
		if(rcode > 0 && FD_ISSET(socket, readfds))
			*readFlag = GHTTPTrue;
		else
			*readFlag = GHTTPFalse;
	}
	if(writeFlag != NULL)
	{
		if(rcode > 0 && FD_ISSET(socket, writefds))
			*writeFlag = GHTTPTrue;
		else
			*writeFlag = GHTTPFalse;
	}
	if(exceptFlag != NULL)
	{
		if(rcode > 0 && FD_ISSET(socket, exceptfds))
			*exceptFlag = GHTTPTrue;
		else
			*exceptFlag = GHTTPFalse;
	}

	return rcode;
#else
    if( exceptFlag )
    {
        *exceptFlag = GHTTPFalse;
    }
    if( writeFlag ) 
    {
        *writeFlag = abstract_CanSend( socket );
    }
    if( readFlag )
    {
        *readFlag = abstract_CanReceive( socket );
    }
    return GHTTPTrue;
#endif
}

// Receive some data.
/////////////////////
GHIRecvResult ghiDoReceive
(
	GHIConnection * connection,
	char buffer[],
	int * bufferLen
)
{
	int rcode;
	int len;

	// How much to try and receive.
	///////////////////////////////
	len = (*bufferLen - 1);

	// Are we throttled?
	////////////////////
	if(connection->throttle)
	{
		unsigned long now;

		// Don't receive too often.
		///////////////////////////
		now = current_time();
		if(now < (connection->lastThrottleRecv + ghiThrottleTimeDelay))
			return GHINoData;

		// Update the receive time.
		///////////////////////////
		connection->lastThrottleRecv = now;

		// Don't receive too much.
		//////////////////////////
		len = min(len, ghiThrottleBufferSize);
	}

	// Receive some data.
	/////////////////////
	rcode = recv(connection->socket, buffer, len, 0);

	// There was an error.
	//////////////////////
	if(rcode == SOCKET_ERROR)
	{
        int socketError;
        GHTTPBool trueFlag;

        // Get the error code.
		//////////////////////
		socketError = WSAGetLastError();

		// Check for nothing waiting.
		/////////////////////////////
		if((socketError == WSAEWOULDBLOCK) || (socketError == WSAEINPROGRESS) || (socketError == WSAETIMEDOUT))
			return GHINoData;

		// There was a real error.
		//////////////////////////
		trueFlag = GHTTPTrue;
		connection->completed = trueFlag;
		connection->socketError = socketError;
		connection->result = GHTTPSocketFailed;
		connection->connectionClosed = trueFlag;

		return GHIError;
	}

	// The connection was closed.
	/////////////////////////////
	if(rcode == 0)
	{
		connection->connectionClosed = GHTTPTrue;
		return GHIConnClosed;
	}

	// Cap the buffer.
	//////////////////
	buffer[rcode] = '\0';
	*bufferLen = rcode;

	// We got data.
	///////////////
	return GHIRecvData;
}

int ghiDoSend
(
	struct GHIConnection * connection,
	const char * buffer,
	int len
)
{
	int rcode;

	// Do the send.
	///////////////
	rcode = send(connection->socket, buffer, len, 0);

	// Check for an error.
	//////////////////////
	if(rcode == SOCKET_ERROR)
	{
		int error;

		// Would block just means 0 bytes sent.
		///////////////////////////////////////
		error = WSAGetLastError();
		if((error == WSAEWOULDBLOCK) || (error == WSAEINPROGRESS) || (error == WSAETIMEDOUT))
			return 0;

		connection->socketError = error;
		connection->completed = GHTTPTrue;
		connection->result = GHTTPSocketFailed;
		return SOCKET_ERROR;
	}

	if(connection->state == GHTTPPosting)
		connection->postingState.bytesPosted += rcode;

	return rcode;
}

GHITrySendResult ghiTrySendThenBuffer
(
	GHIConnection * connection,
	const char * buffer,
	int len
)
{
	int rcode = 0;

	// If we already have something buffered, don't send.
	/////////////////////////////////////////////////////
	if(!connection->sendBuffer.len)
	{
		// Try and send.
		////////////////
		rcode = ghiDoSend(connection, buffer, len);
		if(rcode == SOCKET_ERROR)
			return GHITrySendError;

		// Was it all sent?
		///////////////////
		if(rcode == len)
			return GHITrySendSent;
	}

	// Buffer whatever wasn't sent.
	///////////////////////////////
	if(!ghiAppendDataToBuffer(&connection->sendBuffer, buffer + rcode, len - rcode))
		return GHITrySendError;

	return GHITrySendBuffered;
}

GHTTPBool ghiSetProxy
(
	const char * server
)
{
	// Free any existing proxy address.
	///////////////////////////////////
	if(ghiProxyAddress)
	{
		gsifree(ghiProxyAddress);
		ghiProxyAddress = NULL;
	}
	ghiProxyPort = 0;

	if(server && *server)
	{
		char * strPort;

		// Copy off the server address.
		///////////////////////////////
		ghiProxyAddress = goastrdup(server);
		if(!ghiProxyAddress)
			return GHTTPFalse;

		// Check for a port.
		////////////////////
		if((strPort = strchr(ghiProxyAddress, ':')) != NULL)
		{
			*strPort++ = '\0';

			// Try getting the port.
			////////////////////////
			ghiProxyPort = (unsigned short)atoi(strPort);
			if(!ghiProxyPort)
			{
				gsifree(ghiProxyAddress);
				ghiProxyAddress = NULL;
				return GHTTPFalse;
			}
		}
		else
		{
			ghiProxyPort = GHI_DEFAULT_PORT;
		}
	}

	return GHTTPTrue;
}

void ghiThrottleSettings
(
	int bufferSize,
	gsi_time timeDelay
)
{
	ghiThrottleBufferSize = bufferSize;
	ghiThrottleTimeDelay = timeDelay;
}

#ifdef UNDER_CE
// CE doesn't have isspace().
/////////////////////////////
static int isspace(int c)
{
	if((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'))
		return 1;
	return 0;
}
#endif

// Re-enable previously disabled compiler warnings
///////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma warning ( default: 4127 )
#endif // _MSC_VER

