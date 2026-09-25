// cl: /O2 /Ob2 /DNDEBUG /MD
// 0x0086B860, 109 bytes. topicChanged slot in piSetChannelCallbacks;
// inRoom and names offsets agree with peerMainBlockingOperations.c.

#include <string.h>

typedef void *CHAT;
typedef void *PEER;
typedef int PEERBool;
typedef int RoomType;

typedef struct PEERConnection
{
	char reserved[0x390];
	int inRoom[3];
	char names[3][512];
} PEERConnection;

extern "C" PEERBool piRoomToType(PEER peer, const char *channel, RoomType *roomType);
extern "C" void piAddRoomNameChangedCallback(PEER peer, RoomType roomType);

extern "C" void piChannelTopicChangedA(
	CHAT chat, const char *channel, const char *topic, void *param)
{
	RoomType roomType;
	PEER peer = (PEER)param;
	PEERConnection *connection = (PEERConnection *)peer;

	(void)chat;
	if (!piRoomToType(peer, channel, &roomType))
		return;
	if (topic[0] == '\0')
		return;

	strncpy(connection->names[roomType], topic, 512);
	connection->names[roomType][511] = '\0';
	if (connection->inRoom[roomType] != 0)
		piAddRoomNameChangedCallback(peer, roomType);
}
