// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerGlobalCallbacks.c */

#include <string.h>

typedef void *PEER;

typedef struct chatChannelCallbacks
{
	void *channelMessage;
	void *kicked;
	void *userJoined;
	void *userParted;
	void *userChangedNick;
	void *topicChanged;
	void *channelModeChanged;
	void *userModeChanged;
	void *userListUpdated;
	void *newUserList;
	void *broadcastKeyChanged;
	void *param;
} chatChannelCallbacks;

void piChannelMessageA(void);
void piChannelKickedA(void);
void piChannelUserJoinedA(void);
void piChannelUserPartedA(void);
void piChannelUserChangedNickA(void);
void piChannelTopicChangedA(void);
void piChannelNewUserListA(void);
void piBroadcastKeyChangedA(void);
void piUserModeChangedA(void);
void piChannelModeChangedA(void);

void piSetChannelCallbacks(PEER peer, chatChannelCallbacks *channelCallbacks)
{
	memset(channelCallbacks, 0, sizeof(chatChannelCallbacks));
	channelCallbacks->param = peer;
	channelCallbacks->channelMessage = piChannelMessageA;
	channelCallbacks->kicked = piChannelKickedA;
	channelCallbacks->userJoined = piChannelUserJoinedA;
	channelCallbacks->userParted = piChannelUserPartedA;
	channelCallbacks->userChangedNick = piChannelUserChangedNickA;
	channelCallbacks->topicChanged = piChannelTopicChangedA;
	channelCallbacks->newUserList = piChannelNewUserListA;
	channelCallbacks->broadcastKeyChanged = piBroadcastKeyChangedA;
	channelCallbacks->userModeChanged = piUserModeChangedA;
	channelCallbacks->channelModeChanged = piChannelModeChangedA;
}
