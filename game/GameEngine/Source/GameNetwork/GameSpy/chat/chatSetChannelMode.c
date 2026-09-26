// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Chat SDK chatSetChannelModeA, retail 0x00860BF0. */

#include <stdio.h>
#include <string.h>

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
} ciConnection;

typedef struct CHATChannelMode
{
	int InviteOnly;
	int Private;
	int Secret;
	int Moderated;
	int NoExternalMessages;
	int OnlyOpsChangeTopic;
	int OpsObeyChannelLimit;
	int Limit;
} CHATChannelMode;

void ciSocketSendf(void *socket, const char *format, ...);

void chatSetChannelModeA(CHAT chat, const char *channel,
	CHATChannelMode *mode)
{
	char buffer[64];
	ciConnection *connection = (ciConnection *)chat;

	if(!chat || !connection->connected)
		return;

	strcpy(buffer, "XiXpXsXmXnXtXlXe");
	buffer[0] = mode->InviteOnly ? '+' : '-';
	buffer[2] = mode->Private ? '+' : '-';
	buffer[4] = mode->Secret ? '+' : '-';
	buffer[6] = mode->Moderated ? '+' : '-';
	buffer[8] = mode->NoExternalMessages ? '+' : '-';
	buffer[10] = mode->OnlyOpsChangeTopic ? '+' : '-';
	buffer[12] = mode->Limit > 0 ? '+' : '-';
	buffer[14] = mode->OpsObeyChannelLimit ? '+' : '-';

	if(mode->Limit > 0)
		sprintf(&buffer[strlen(buffer)], " %d", mode->Limit);

	ciSocketSendf(&connection->chatSocket, "MODE %s %s", channel, buffer);
}
