// cl: /O2 /Ob2 /DNDEBUG /MD

#include <stdlib.h>
#include <string.h>

typedef void *PEER;
typedef int PEERBool;
enum
{
	PEERFalse,
	PEERTrue
};
typedef enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
} RoomType;

typedef struct piPlayer
{
	char nick[0x40];
	int inRoom[3];
	int local;
	unsigned int IP;
	int profileID;
	int gotIPAndProfileID;
	int flags[3];
} piPlayer;

typedef struct piConnection
{
	unsigned char pad0[0x80];
	char rooms[3][0x101];
	void *enteringRoom[3];
	void *inRoom[3];
	unsigned char pad39C[0xAB0 - 0x39C];
	int stayInTitleRoom;
	void *players;
	int numPlayers[3];
	int padAC4;
	int doPings;
	int lastPingTimeMod;
	int pingRoom[3];
	int xpingRoom[3];
	void *xpings;
	int lastXpingSend;
	unsigned char padAF0[0xB40 - 0xAF0];
	int hosting;
	int playing;
	unsigned char padB48[0xB50 - 0xB48];
	void *hostServer;
} piConnection;

class BfmeThingBW
{
public:
	char m_bfmeHead[0x48];
	int m_bfmeReady;
	char m_bfmeGap[0x18];
	int m_bfmeFlags;
};

extern "C"
{
	extern char piUTMCommand[];
	extern char piUTMParameters[];

	void piSetLocalFlags(PEER peer);
	void piAddGameStartedCallback(PEER peer, void *server, const char *params);
	PEERBool peerIsAutoMatching(PEER peer);
	void piSetAutoMatchStatus(PEER peer, int status);
	unsigned int piDemangleIP(const char *buffer);
	piPlayer *piFindPlayerByIP(PEER peer, unsigned int IP);
	void piUpdateXping(PEER peer, const char *nick1, const char *nick2, int ping);
	void piAddCrossPingCallback(PEER peer, const char *nick1, const char *nick2, int ping);
}

extern int __cdecl bfmeMask(BfmeThingBW *thing);
extern __declspec(dllimport) int __cdecl strcmpi(const char *left, const char *right);

#define PI_UTM_MATCH(text) (strncmp(piUTMCommand, text, 2) == 0)

extern "C" static __declspec(noinline) void piProcessUTM(PEER peer, piPlayer *player,
	PEERBool inRoom, RoomType roomType)
{
	char *params = piUTMParameters;
	piConnection *connection = (piConnection *)peer;

	if (PI_UTM_MATCH("GML"))
	{
		if (!connection->inRoom[StagingRoom])
			return;
		if (inRoom && (roomType != StagingRoom))
			return;
		if (!inRoom && !player->inRoom[StagingRoom])
			return;
		if (connection->hosting)
			return;
		if (!bfmeMask((BfmeThingBW *)player))
			return;

		connection->playing = 1;
		piSetLocalFlags(peer);
		piAddGameStartedCallback(peer, connection->hostServer, params);
		if (peerIsAutoMatching(peer))
			piSetAutoMatchStatus(peer, 5);
	}
	else if (PI_UTM_MATCH("PNG"))
	{
		piPlayer *other;
		int ping;
		unsigned int IP;

		if (inRoom && !connection->xpingRoom[roomType])
			return;
		if (!params[0])
			return;

		IP = piDemangleIP(params);
		ping = atoi(params + 11);
		other = piFindPlayerByIP(peer, IP);
		if (!other)
			return;
		if (strcmpi((const char *)player, (const char *)other) == 0)
			return;
		if (inRoom && !player->inRoom[roomType])
			return;
		if (!inRoom)
		{
			int i;
			PEERBool success = PEERFalse;

			for (i = 0; i < 3; i++)
			{
				if (connection->xpingRoom[i] && connection->inRoom[i] &&
					player->inRoom[i] && other->inRoom[i])
					success = PEERTrue;
			}
			if (!success)
				return;
		}

		piUpdateXping(peer, (const char *)player, (const char *)other, ping);
		piAddCrossPingCallback(peer, (const char *)player,
			(const char *)other, ping);
	}
}

__declspec(dllimport) int __cdecl bfmeCmp1026(char *left, char *right, int count);
extern char *(__cdecl *g_bfmeStrStrVMZ)(const char *text, const char *find);

static void Rva0086B2F0(char *text, piPlayer *player)
{
	int length = (int)strlen(text);
	if (bfmeCmp1026(text + length - 2, "X\\", 2) == 0)
		return;
	if (!player->inRoom[2])
		return;
	char *flags = g_bfmeStrStrVMZ(text, "\\$flags$\\");
	if (!flags)
		return;
	flags += 9;
	char value = *flags;
	if (!value)
		goto clearFlag;
	do
	{
		if (value == '\\')
			goto clearFlag;
		++flags;
		if (value == 'r')
			goto setFlag;
		value = *flags;
	} while (value);
clearFlag:
	player->flags[2] &= ~2;
	return;
setFlag:
	player->flags[2] |= 2;
}


extern "C" unsigned int strlen(const char *text);
#pragma intrinsic(strlen)

// Three markers and something other than a blank behind them.
static __declspec(noinline) int __fastcall bfmeIsTag(int unused, const char *text)
{
	if (text == 0)
		return 0;
	if (strlen(text) < 4)
		return 0;

	if (text[0] != '@' || text[1] != '@' || text[2] != '@' || text[3] == ' ')
		return 0;
	return 1;
}


extern "C" {
 piPlayer *piGetPlayer(PEER peer, const char *nick);
 void piAddPlayerMessageCallback(PEER peer, const char *nick, const char *message, int mode);
 void piAddPlayerUTMCallback(PEER peer, const char *nick, const char *command, const char *parameters, int authenticated);
 PEERBool piParseUTM(const char *message);
}

// Retail 0x0086B360. The private helpers remain in this TU so MSVC can
// reproduce their witnessed register conventions without assembly adapters.
extern "C" void __declspec(noinline) __cdecl Rva0086B360Dispatch(
	void *chat, const char *nick, const char *message, int mode, PEER peer)
{
	piPlayer *player;
	(void)chat;
	if (!nick || !nick[0])
		return;

	if (bfmeIsTag(0, message))
	{
		if (_strnicmp(message, "@@@NFO", 6) != 0)
			return;
		player = piGetPlayer(peer, nick);
		if (player)
			Rva0086B2F0((char *)message, player);
		return;
	}

	if (mode != 3 && mode != 4)
	{
		piAddPlayerMessageCallback(peer, nick, message, mode);
	}
	else if (piParseUTM(message))
	{
		player = piGetPlayer(peer, nick);
		if (player)
			piProcessUTM(peer, player, PEERFalse, TitleRoom);
		piAddPlayerUTMCallback(peer, nick, piUTMCommand, piUTMParameters,
			mode == 4);
	}
}

extern "C" __declspec(noinline) void piProcessUTM_anchor(PEER peer, piPlayer *player)
{
	piProcessUTM(peer, player, PEERFalse, TitleRoom);
}

// absent-from-retail: This caller makes MSVC pass both pointers in registers.
void Rva0086B2F0PrivateCallAnchor(char *text, piPlayer *player, int enabled)
{
	if (enabled)
		Rva0086B2F0(text, player);
}
