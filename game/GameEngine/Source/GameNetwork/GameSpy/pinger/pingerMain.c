// cl: /Igame/GameEngine/Source/GameNetwork/GameSpy/pinger /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Ping SDK response-trip implementation. */

#include <winsock.h>
#include <assert.h>
#include <string.h>

typedef int PINGERBool;
typedef void *DArray;
typedef unsigned short uint16;

#define PI_MAGIC 0x91
#define PI_VERSION 1
#define PI_DATA_MAX_LEN 24
#define PI_TRIP2_TIMEOUT 10000

typedef void (*pingerGotPing)(unsigned int, unsigned short, int,
	const char *, int, void *);
typedef void (*pingerSetData)(unsigned int, unsigned short, char *, int,
	void *);

typedef struct piUDPPing
{
	unsigned char magic;
	unsigned char version;
	uint16 trip;
	uint16 ID_A;
	uint16 ID_B;
} piUDPPing;

typedef struct piActivePing
{
	PINGERBool originator;
	uint16 ID;
	uint16 expectedTrip;
	unsigned int timestamp;
	unsigned int timeout;
	unsigned int remoteIP;
	unsigned short remotePort;
	pingerGotPing reply;
	void *replyParam;
} piActivePing;

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

static PINGERBool piSettingData;
static SOCKET piSocket = INVALID_SOCKET;
static PINGERBool piInitialized;
static pingerGotPing piPingerPinged;
static void *piPingerPingedParam;
static pingerSetData piPingerSetData;
static void *piPingerSetDataParam;
static PINGERBool piUDPEnabled;
static uint16 piNextID;
static DArray piActivePingList;
static unsigned int piLastThinkTime;
static DArray piCallbacks;

static uint16 piGetNextID(void)
{
	uint16 ID = piNextID;

	if (piNextID == 0xFFFF)
		piNextID = 1;
	else
		piNextID++;

	return ID;
}

static int piSendPing(SOCKADDR_IN *to, unsigned short trip,
	unsigned short ID_A, unsigned short ID_B, const char *data);
void ArrayAppend(DArray array, const void *newElem);
unsigned int current_time(void);
int CanReceiveOnSocket(SOCKET sock);

static __declspec(noinline) PINGERBool piBytesToPing(unsigned char *buffer,
	piUDPPing *udpPing, char *data)
{
	assert(buffer != 0);
	assert(udpPing != 0);
	assert(data != 0);

	udpPing->magic = *buffer++;
	udpPing->version = *buffer++;
	udpPing->trip = (unsigned short)(*buffer++ << 8);
	udpPing->trip |= *buffer++;
	udpPing->ID_A = (unsigned short)(*buffer++ << 8);
	udpPing->ID_A |= *buffer++;
	udpPing->ID_B = (unsigned short)(*buffer++ << 8);
	udpPing->ID_B |= *buffer++;

	if (udpPing->magic != PI_MAGIC)
		return 0;
	assert(udpPing->version == PI_VERSION);
	if (udpPing->version != PI_VERSION)
		return 0;
	assert((udpPing->trip >= 1) && (udpPing->trip <= 3));
	if ((udpPing->trip < 1) || (udpPing->trip > 3))
		return 0;

	memcpy(data, buffer, PI_DATA_MAX_LEN);
	return 1;
}

static __declspec(noinline) void piProcessTrip1(piUDPPing *udpPing,
	const char *data, SOCKADDR_IN *from, unsigned int recvTime)
{
	char dataOut[PI_DATA_MAX_LEN];
	uint16 ID;

	assert(udpPing->trip == 1);
	if (udpPing->ID_A == 0)
		return;
	assert(udpPing->ID_B == 0);
	if (udpPing->ID_B != 0)
		return;

	if (piPingerPinged != 0)
		ID = piGetNextID();
	else
		ID = 0;

	memset(dataOut, 0, PI_DATA_MAX_LEN);
	if (piPingerSetData != 0)
	{
		piSettingData = 1;
		piPingerSetData(from->sin_addr.s_addr, from->sin_port, dataOut,
			PI_DATA_MAX_LEN, piPingerSetDataParam);
		piSettingData = 0;
	}

	piSendPing(from, 2, udpPing->ID_A, ID, dataOut);

	if (piPingerPinged != 0)
	{
		piActivePing activePing;

		activePing.originator = 0;
		activePing.ID = ID;
		activePing.expectedTrip = 3;
		activePing.timestamp = current_time();
		activePing.timeout = activePing.timestamp + PI_TRIP2_TIMEOUT;
		activePing.remoteIP = from->sin_addr.s_addr;
		activePing.remotePort = from->sin_port;
		activePing.reply = 0;
		activePing.replyParam = 0;
		ArrayAppend(piActivePingList, &activePing);
	}

	(void)data;
	(void)recvTime;
}

int ArraySearch(DArray array, const void *elem,
	int (__cdecl *compare)(const void *, const void *), int startIndex,
	int sorted);
void *ArrayNth(DArray array, int index);
void ArrayDeleteAt(DArray array, int index);
void ArrayAppend(DArray array, const void *newElem);
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

static int piSendPing(SOCKADDR_IN *to, unsigned short trip,
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

static int __cdecl piFindActivePingCompareFn(const void *elem1,
	const void *elem2)
{
	const piActivePing *activePing1 = (const piActivePing *)elem1;
	const piActivePing *activePing2 = (const piActivePing *)elem2;
	return activePing1->ID - activePing2->ID;
}

static __declspec(noinline) piActivePing *piFindActivePing(uint16 ID, int *index)
{
	piActivePing key;
	int n;

	key.ID = ID;
	n = ArraySearch(piActivePingList, &key, piFindActivePingCompareFn, 0, 0);
	if (index != 0)
		*index = n;
	if (n == -1)
		return 0;
	return (piActivePing *)ArrayNth(piActivePingList, n);
}

static void piProcessTrip2(piUDPPing *udpPing,
	const char *data, SOCKADDR_IN *from, unsigned int recvTime)
{
	char dataOut[24];
	int index;
	piActivePing *activePing;

	if (udpPing->ID_A == 0)
		return;

	activePing = piFindActivePing(udpPing->ID_A, &index);
	if (activePing == 0)
		return;

	memset(dataOut, 0, 24);
	if (piPingerSetData != 0)
	{
		piSettingData = 1;
		piPingerSetData(from->sin_addr.s_addr, from->sin_port, dataOut, 24,
			piPingerSetDataParam);
		piSettingData = 0;
	}

	if (udpPing->ID_B != 0)
		piSendPing(from, 3, 0, udpPing->ID_B, dataOut);

	if (activePing->reply != 0)
	{
		int ping = (int)(recvTime - activePing->timestamp);
		piQueueCallback(from->sin_addr.s_addr, from->sin_port, ping, data, 24,
			activePing->replyParam, activePing->reply);
	}

	ArrayDeleteAt(piActivePingList, index);
}

static int piCalculatePing(unsigned int sendTime, unsigned int recvTime)
{
	return (int)(recvTime - sendTime);
}

static __declspec(noinline) void piProcessTrip3(piUDPPing *udpPing,
	const char *data, SOCKADDR_IN *from, unsigned int recvTime)
{
	int index;
	piActivePing *activePing;

	assert(udpPing->trip == 3);
	assert(udpPing->ID_A == 0);
	if (udpPing->ID_A != 0)
		return;
	assert(udpPing->ID_B != 0);
	if (udpPing->ID_B == 0)
		return;

	activePing = piFindActivePing(udpPing->ID_B, &index);
	if (activePing == 0)
		return;

	assert(piPingerPinged != 0);
	if (piPingerPinged != 0)
	{
		int ping = piCalculatePing(activePing->timestamp, recvTime);

		piPingerPinged(from->sin_addr.s_addr, from->sin_port, ping, data,
			PI_DATA_MAX_LEN, piPingerPingedParam);
	}

	ArrayDeleteAt(piActivePingList, index);
}

/* Local spelling disambiguates this pingerMain helper from peerPing.c's
 * unrelated static piProcessPing. */
static void pingerProcessPing(piUDPPing *udpPing,
	const char *data, SOCKADDR_IN *from, unsigned int recvTime)
{
	if (udpPing->trip == 1)
		piProcessTrip1(udpPing, data, from, recvTime);
	else if (udpPing->trip == 2)
		piProcessTrip2(udpPing, data, from, recvTime);
	else if (udpPing->trip == 3)
		piProcessTrip3(udpPing, data, from, recvTime);
}

static __declspec(noinline) void piProcessIncoming(void)
{
	int rcode;
	unsigned char buffer[32];
	SOCKADDR_IN from;
	int len;
	unsigned int recvTime;
	piUDPPing udpPing;
	char data[24];

	while (piInitialized && CanReceiveOnSocket(piSocket))
	{
		len = sizeof(SOCKADDR_IN);
		rcode = recvfrom(piSocket, (char *)buffer, 32, 0,
			(SOCKADDR *)&from, &len);

		if (rcode == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEMSGSIZE)
				rcode = 32;
			else
				return;
		}
		else if (rcode < 32)
			return;

		recvTime = current_time();
		if (piBytesToPing(buffer, &udpPing, data))
			pingerProcessPing(&udpPing, data, &from, recvTime);
	}

	piLastThinkTime = current_time();
}

static void (*const piProcessIncomingAnchor)(void) = piProcessIncoming;
