// cl: /DNDEBUG /MD /GX

// Retail 0x00685240, LANAPI vtable slot 54 (table at 0x0111AF50).
// The slot-54 thunk at 0x0041B9DC targets this body.  BFME looks up a lobby
// player by its address pair, treating a zero requested port as an IP-only
// match.  The list and LANPlayer offsets are shared with the already-matched
// RequestSetName reconstruction.

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct BfmeNetAddress
{
	Bool operator==(const BfmeNetAddress &that) const
	{
		return m_ip == that.m_ip && m_port == that.m_port;
	}

	UnsignedInt m_ip;
	unsigned short m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class Rva00685240LANPlayer
{
public:
	unsigned char m_bfmeHead[0x10];
	Rva00685240LANPlayer *m_next; // +0x10
	BfmeNetAddress m_address;     // +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class Rva00685240LANAPI
{
public:
	virtual Rva00685240LANPlayer *lookupPlayerByAddress(BfmeNetAddress *address);

protected:
	unsigned char m_bfmeHead[4];
	Rva00685240LANPlayer *m_lobbyPlayers; // +0x08
};

Rva00685240LANPlayer *Rva00685240LANAPI::lookupPlayerByAddress(BfmeNetAddress *address)
{
	Rva00685240LANPlayer *player = m_lobbyPlayers;
	while (player && !(player->m_address == *address
		|| (address->m_port == 0 && address->m_ip == player->m_address.m_ip)))
	{
		player = player->m_next;
	}

	return player;
}
