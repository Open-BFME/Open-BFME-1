// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK pinger shutdown path.  The globals are kept TU-local in
   the original SDK; they are extern here so the matcher can pin their retail
   addresses while the remainder of peerPing.c is recovered. */

#include <winsock.h>
#include <stdlib.h>
#include <string.h>

typedef int GSIBool;
typedef void *DArray;

typedef void (*pingerGotPing)(unsigned int, unsigned short, int, const char *, int, void *);

typedef struct piQueuedCallback
{
	unsigned int IP;
	unsigned short port;
	int ping;
	char *data;
	int len;
	void *param;
	pingerGotPing callback;
} piQueuedCallback;

typedef struct piActivePing
{
	GSIBool originator;
	unsigned short ID;
	unsigned short expectedTrip;
	unsigned int timestamp;
	unsigned int timeout;
	unsigned int remoteIP;
	unsigned short remotePort;
	pingerGotPing reply;
	void *replyParam;
} piActivePing;

static GSIBool piInitialized;
static GSIBool piSettingData;
static SOCKET piSocket = INVALID_SOCKET;
static DArray piActivePingList;
static DArray piCallbacks;
static void *piPingerPinged;
static void *piPingerPingedParam;
static void *piPingerSetData;
static void *piPingerSetDataParam;
static GSIBool piUDPEnabled;
static unsigned short piNextID;
static int piLastThinkTime;

int __stdcall closesocket(SOCKET socket);
void SocketStartUp(void);
void SocketShutDown(void);
static int piSocketInit(const char *localAddress, unsigned short localPort)
{
	int rcode;
	SOCKADDR_IN sockaddr;
	int bFlag;

	SocketStartUp();

	memset(&sockaddr, 0, sizeof(SOCKADDR_IN));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(localPort);
	if (localAddress != 0)
	{
		unsigned int IP;
		IP = inet_addr(localAddress);
		if (IP == INADDR_NONE)
		{
			HOSTENT *hostent;
			hostent = gethostbyname(localAddress);
			if (hostent == 0)
				goto fail;
			IP = *(unsigned int *)hostent->h_addr_list[0];
		}
		sockaddr.sin_addr.s_addr = IP;
	}
	else
	{
		sockaddr.sin_addr.s_addr = INADDR_ANY;
	}

	piSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (piSocket == INVALID_SOCKET)
		goto socket_error;

	bFlag = 1;
	rcode = setsockopt(piSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&bFlag, sizeof(bFlag));

	rcode = bind(piSocket, (SOCKADDR *)&sockaddr, sizeof(SOCKADDR_IN));
	if (rcode == -1)
	{
socket_error:
		WSAGetLastError();
fail:
		return 0;
	}

	return 1;
}
DArray ArrayNew(int elemSize, int numElemsToAllocate, void *elemFreeFn);
void ArrayAppend(DArray array, const void *newElem);
int ArrayLength(DArray array);
void *ArrayNth(DArray array, int index);
int ArraySearch(DArray array, const void *elem, int (__cdecl *compare)(const void *, const void *), int startIndex, int sorted);
void ArrayDeleteAt(DArray array, int index);
void ArrayFree(DArray array);
void piProcessIncoming(void);
static void piCheckTimeouts(void);
static void piCallCallbacks(void);
unsigned int current_time(void);

static void piQueueCallback(unsigned int IP, unsigned short port, int ping,
	const char *data, int len, void *param, pingerGotPing callbackFunc)
{
	piQueuedCallback callback;

	if (!callbackFunc)
		return;

	callback.IP = IP;
	callback.port = port;
	callback.ping = ping;
	callback.len = len;
	callback.param = param;
	callback.callback = callbackFunc;

	if (data)
	{
		callback.data = (char *)malloc((unsigned int)len);
		if (!callback.data)
			return;
		memcpy(callback.data, data, (unsigned int)len);
	}
	else
	{
		callback.data = 0;
	}

	ArrayAppend(piCallbacks, &callback);
}

static void piCallCallbacks(void)
{
	piQueuedCallback *callback;
	piQueuedCallback callbackCopy;

	while (ArrayLength(piCallbacks) > 0)
	{
		callback = (piQueuedCallback *)ArrayNth(piCallbacks, 0);
		if (!callback)
			return;

		callbackCopy = *callback;
		callback = &callbackCopy;
		ArrayDeleteAt(piCallbacks, 0);
		callback->callback(callback->IP, callback->port, callback->ping,
			callback->data, callback->len, callback->param);
		free(callback->data);
	}
}

static void piCheckTimeouts(void)
{
	unsigned int now;
	piActivePing *activePing;
	int len;
	int n;

	len = ArrayLength(piActivePingList);
	if (len == 0)
		return;

	now = current_time();
	for (n = len - 1; n >= 0; --n)
	{
		activePing = (piActivePing *)ArrayNth(piActivePingList, n);
		if (activePing != 0 && activePing->timeout != 0 && activePing->timeout <= now)
		{
			if (activePing->originator && activePing->reply != 0)
			{
				piQueueCallback(activePing->remoteIP, activePing->remotePort, -1,
					0, 0, activePing->replyParam, activePing->reply);
			}
			ArrayDeleteAt(piActivePingList, n);
		}
	}
}

int pingerInit(register const char *localAddress, register unsigned short localPort, void *pinged,
	void *pingedParam, void *setData, void *setDataParam)
{
	if (piInitialized)
		return 0;

	if (localAddress != 0 && localAddress[0] == '\0')
		localAddress = 0;

	piPingerPinged = pinged;
	piPingerPingedParam = pingedParam;
	piPingerSetData = setData;
	piPingerSetDataParam = setDataParam;
	piSettingData = 0;
	piUDPEnabled = (localPort != 0);
	piNextID = 1;
	piLastThinkTime = 0;

	piActivePingList = ArrayNew(0x20, 0, 0);
	if (piActivePingList == 0)
		return 0;

	piCallbacks = ArrayNew(0x1C, 0, 0);
	if (piCallbacks == 0)
	{
		ArrayFree(piActivePingList);
		return 0;
	}

	if (piUDPEnabled && !piSocketInit(localAddress, localPort))
	{
		if (piSocket != INVALID_SOCKET)
		{
			closesocket(piSocket);
			piSocket = INVALID_SOCKET;
		}

		SocketShutDown();
		ArrayFree(piActivePingList);
		ArrayFree(piCallbacks);
		return 0;
	}

	piInitialized = 1;
	return 1;
}

void pingerShutdown(void)
{
	if (!piInitialized || piSettingData)
		return;

	if (piSocket != INVALID_SOCKET)
	{
		closesocket(piSocket);
		piSocket = INVALID_SOCKET;
	}

	SocketShutDown();
	ArrayFree(piActivePingList);
	ArrayFree(piCallbacks);
	piInitialized = 0;
}

void pingerThink(void)
{
	if (!piInitialized || piSettingData)
		return;

	piProcessIncoming();
	piCheckTimeouts();
	piCallCallbacks();
}

static int __cdecl piFindActivePingCompareFn(const void *elem1, const void *elem2)
{
	const piActivePing *activePing1 = (const piActivePing *)elem1;
	const piActivePing *activePing2 = (const piActivePing *)elem2;
	return activePing1->ID - activePing2->ID;
}

static piActivePing *piFindActivePing(unsigned short ID)
{
	piActivePing key;
	int index;

	key.ID = ID;
	index = ArraySearch(piActivePingList, &key, piFindActivePingCompareFn, 0, 0);
	if (index == -1)
		return 0;
	return (piActivePing *)ArrayNth(piActivePingList, index);
}

typedef struct piUDPPing
{
	unsigned char magic;
	unsigned char version;
	unsigned short trip;
	unsigned short ID_A;
	unsigned short ID_B;
} piUDPPing;

static void piPingToBytes(piUDPPing *udpPing, unsigned char *buffer)
{
	*buffer++ = udpPing->magic;
	*buffer++ = udpPing->version;
	*buffer++ = (unsigned char)((udpPing->trip & 0xFF00) >> 8);
	*buffer++ = (unsigned char)(udpPing->trip & 0x00FF);
	*buffer++ = (unsigned char)((udpPing->ID_A & 0xFF00) >> 8);
	*buffer++ = (unsigned char)(udpPing->ID_A & 0x00FF);
	*buffer++ = (unsigned char)((udpPing->ID_B & 0xFF00) >> 8);
	*buffer++ = (unsigned char)(udpPing->ID_B & 0x00FF);
}

static GSIBool piSendPing(SOCKADDR_IN *to, unsigned short trip,
	unsigned short ID_A, unsigned short ID_B, const char *data)
{
	unsigned char buffer[32];
	piUDPPing udpPing;
	int rcode;

	udpPing.magic = 0x91;
	udpPing.version = 1;
	udpPing.trip = trip;
	udpPing.ID_A = ID_A;
	udpPing.ID_B = ID_B;
	piPingToBytes(&udpPing, buffer);
	if (data != 0)
		memcpy(buffer + sizeof(piUDPPing), data, 32 - sizeof(piUDPPing));
	else
		memset(buffer + sizeof(piUDPPing), 0, 32 - sizeof(piUDPPing));
	rcode = sendto(piSocket, (char *)buffer, 32, 0,
		(SOCKADDR *)to, sizeof(SOCKADDR_IN));
	if (rcode != 32)
		return 0;
	return 1;
}

void msleep(unsigned int milliseconds);

void pingerPing(unsigned int IP, unsigned short port, pingerGotPing reply,
	void *replyParam, GSIBool blocking, unsigned int timeout)
{
	SOCKADDR_IN to;
	unsigned short ID;

	if (piSettingData)
		return;

	memset(&to, 0, sizeof(SOCKADDR_IN));
	to.sin_family = AF_INET;
	to.sin_port = htons(port);
	to.sin_addr.s_addr = IP;

	ID = piNextID;
	if (piNextID == 0xFFFF)
		piNextID = 1;
	else
		piNextID++;

	if (piSendPing(&to, 1, ID, 0, 0))
	{
		piActivePing activePing;

		activePing.originator = 1;
		activePing.ID = ID;
		activePing.expectedTrip = 2;
		activePing.timestamp = current_time();
		if (timeout == 0)
			activePing.timeout = 0;
		else
			activePing.timeout = activePing.timestamp + timeout;
		activePing.remoteIP = IP;
		activePing.remotePort = port;
		activePing.reply = reply;
		activePing.replyParam = replyParam;
		ArrayAppend(piActivePingList, &activePing);
	}

	if (blocking)
	{
		while (piFindActivePing(ID) != 0)
		{
			pingerThink();
			msleep(1);
		}
		piCallCallbacks();
	}
}
