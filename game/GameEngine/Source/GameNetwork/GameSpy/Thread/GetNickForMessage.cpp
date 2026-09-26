// cl: /DNDEBUG /MD /EHsc
// Retail 0x0063A8E0: receive the looked-up nickname for a buddy message.
#include <string.h>
class GPConnection;
struct GPGetInfoResponseArg
{
	int m_beforeNick[2];
	char nick[32];
};
struct BuddyResponse
{
	char m_beforeMessageNick[16];
	char nick[32];
};

void getNickForMessage(GPConnection *, GPGetInfoResponseArg *arg, void *param)
{
	BuddyResponse *response = (BuddyResponse *)param;
	strcpy(response->nick, arg->nick);
}
