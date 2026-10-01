// cl: /GS
// The 'RESV' category serializes user IDs, a timeout and an optional ACTION.

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class Rva007E8AC0
{
public:
	void run();                                                   // 0x007E8AC0
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *one, void *two );                       // 0x007E8A10
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *one, void *two );                       // 0x007E88D0
};

class Rva007E8810Message
{
public:
	char m_head[0x1c];
	unsigned int m_category;
	char m_tail[0x0c];
	int m_depth;
};

void Rva00800040JoinI64(const __int64 *parts, unsigned count,
	char *dest, unsigned destSize, char separator);

void __stdcall Rva007FCDA0ReserveRequest(Rva007E8810Message *message,
	const __int64 *ids, unsigned count, int action, int timeout)
{
	char text[0x100];
	reinterpret_cast< Rva007E8AC0 * >( message )->run();
	message->m_category = 'RESV';
	message->m_depth = 3;
	text[0] = 0;
	Rva00800040JoinI64(ids, count, text, sizeof(text), ';');
	reinterpret_cast< BfmeThingCIC * >( message )->bfmeGoCIC( (void *)"UIDS", (void *)text );
	reinterpret_cast< BfmeThingCIB * >( message )->bfmeGoCIB( (void *)"TIMO", (void *)timeout );
	switch (action)
	{
	case 0: reinterpret_cast< BfmeThingCIC * >( message )->bfmeGoCIC( (void *)"ACTION", (void *)"HLD" ); break;
	case 1: reinterpret_cast< BfmeThingCIC * >( message )->bfmeGoCIC( (void *)"ACTION", (void *)"REL" ); break;
	case 2: reinterpret_cast< BfmeThingCIC * >( message )->bfmeGoCIC( (void *)"ACTION", (void *)"RAL" ); break;
	}
}
