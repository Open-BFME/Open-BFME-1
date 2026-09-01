// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef int PEERBool;
typedef void *SBServer;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x60];
	char title[32];
	unsigned char pad_0080[0xB50 - 0x80];
	SBServer hostServer;
} PEERConnection;

typedef PEERConnection *PEER;

unsigned int SBServerGetPublicInetAddress(SBServer server);
unsigned int SBServerGetPrivateInetAddress(SBServer server);
int SBServerHasPrivateAddress(SBServer server);
unsigned short SBServerGetPrivateQueryPort(SBServer server);
unsigned short SBServerGetPublicQueryPort(SBServer server);
void piMangleStagingRoom(char *room, const char *title,
	unsigned int publicIP, unsigned int privateIP, unsigned short privatePort);
int piGetNextID(PEER peer);
void piJoinAutoMatchRoomCallback(void);
int piNewJoinRoomOperation(PEER peer, int roomType, const char *channel,
	const char *password, void *callback, void *param, int opID);
SBServer piSBCloneServer(SBServer server);

PEERBool piJoinAutoMatchRoom(PEER peer, SBServer server)
{
	unsigned int publicIP;
	unsigned int privateIP;
	unsigned short privatePort;
	char room[257];

	publicIP = SBServerGetPublicInetAddress(server);
	privateIP = SBServerGetPrivateInetAddress(server);
	if (SBServerHasPrivateAddress(server))
		privatePort = SBServerGetPrivateQueryPort(server);
	else
		privatePort = SBServerGetPublicQueryPort(server);

	if (!publicIP)
		return 0;

	piMangleStagingRoom(room, peer->title, publicIP, privateIP, privatePort);
	if (!piNewJoinRoomOperation(peer, 2, room, 0,
		(void *)piJoinAutoMatchRoomCallback, 0, piGetNextID(peer)))
		return 0;

	peer->hostServer = piSBCloneServer(server);
	return 1;
}
