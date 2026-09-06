// cl: /DNDEBUG /MD /GX

// LANAPI::lookupPlayerByAddress, retail 0x00685240, LANAPI vtable slot 54
// (table at 0x0111AF50); the slot-54 thunk at 0x0041B9DC targets this body.
// BFME looks up a lobby player by its address pair, treating a zero requested
// port as an IP-only match.
//
// The class names are the ones the already-matched RequestSetName body
// (0x00688220, LANAPI_RequestSetName.cpp) fixes from the same vtable: LANPlayer
// with m_next at +0x10 and the address pair at +0x14, chained from LANAPI's
// m_lobbyPlayers at +0x08.  The METHOD name stays descriptive: this slot sits
// at the end of BFME's vtable and takes an address pair, not Zero Hour's
// LookupPlayer(UnsignedInt) slot, so no retail name is claimed for it.

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

class LANPlayer
{
public:
	unsigned char m_bfmeHead[0x10];
	LANPlayer *m_next; // +0x10
	BfmeNetAddress m_address;     // +0x14
};

class LANAPI
{
public:
	virtual LANPlayer *lookupPlayerByAddress(BfmeNetAddress *address);

protected:
	unsigned char m_bfmeHead[4];
	LANPlayer *m_lobbyPlayers; // +0x08
};

LANPlayer *LANAPI::lookupPlayerByAddress(BfmeNetAddress *address)
{
	LANPlayer *player = m_lobbyPlayers;
	while (player && !(player->m_address == *address
		|| (address->m_port == 0 && address->m_ip == player->m_address.m_ip)))
	{
		player = player->m_next;
	}

	return player;
}
