// cl: /DNDEBUG /MD /EHsc /GS
// Open-BFME: compact FESL transaction message sender, retail 0x00804010.
//
// The message object and its fixed-buffer constructor are the same retail
// type recovered in BfmeConv994.cpp.  This method supplies the transaction
// category and depth, appends the integer transaction id, and submits it.
// Retail 0x007E86C0: the shared seven-byte cleanup the FESL message bodies call
// (store the base vtable 0x01129358 into *this, then ret).  It is defined under
// this name in game/gen_small/fun_005.cpp, so the post-send cleanups spell it
// through this neutral declaration rather than a member of the local view.
class Gen_007e86c0
{
public:
	void m();
};

class BfmeC994
{
public:
	BfmeC994(char *buffer, int capacity);
	void addString(const char *key, const char *value);

	char m_beforeCategory[0x1C];
	int m_category;
	int m_depth;
	char m_tail[0x10];
};

// Retail 0x007E88D0 is the integer field writer (callees.py), matched as
// BfmeThingCIB::bfmeGoCIB.
class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *key, void *value);
};

// Retail 0x008038F0 is the sink submit (callees.py), matched as
// Rva008038F0Sender::send.
class Rva008038F0Sender
{
public:
	void send(BfmeC994 *message);
};

class BfmeSinkSKA
{
public:
	void bfmeSendSKA(int category, int transactionId, int depth);
	void sendCreateGameRequest(int transactionId, int gameId,
		int maxPlayers, const char *userGameId);
};

void BfmeSinkSKA::bfmeSendSKA(int category, int transactionId, int depth)
{
	char buffer[32];
	BfmeC994 message(buffer, sizeof(buffer));
	message.m_category = category;
	message.m_depth = depth;
	((BfmeThingCIB *)&message)->bfmeGoCIB((void *)"TID", (void *)transactionId);
	((Rva008038F0Sender *)this)->send(&message);
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
}

// Wire category and field vocabulary identify this as the FESL create-game
// request: CGAM with TID/GID/LID/MAX-PLAYERS/UGID/SECRET fields.
void BfmeSinkSKA::sendCreateGameRequest(int transactionId, int gameId,
	int maxPlayers, const char *userGameId)
{
	char buffer[64];
	BfmeC994 message(buffer, sizeof(buffer));
	message.m_category = 'CGAM';
	((BfmeThingCIB *)&message)->bfmeGoCIB((void *)"TID", (void *)transactionId);
	((BfmeThingCIB *)&message)->bfmeGoCIB((void *)"GID", (void *)gameId);
	((BfmeThingCIB *)&message)->bfmeGoCIB((void *)"LID", (void *)(-2));
	((BfmeThingCIB *)&message)->bfmeGoCIB((void *)"MAX-PLAYERS", (void *)maxPlayers);
	message.addString("UGID", userGameId);
	message.addString("SECRET", "0");
	((Rva008038F0Sender *)this)->send(&message);
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
}
