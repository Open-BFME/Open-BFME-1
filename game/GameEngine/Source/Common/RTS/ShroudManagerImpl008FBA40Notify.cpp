// cl: /O2 /Ob0 /EHs-c-
// ShroudManagerImpl008FBA40::notify, retail 0x008F9440 (150 bytes).
//
// The public PartitionManager::notify delegate at 0x008F7420 loads its
// implementation at +0x0c and tail-jumps here.  The implementation owns the
// 0x68-byte shroud-element array and the CDE-node list at +0x30.  BfmeThingCDE
// is declared with the fields exercised by this method: its second intrusive
// link is +0x10 and its per-player state array is +0x24.  The complete CDE
// constructor at 0x008F78B0 initializes both arrays (and the related links),
// so these are data-bearing views rather than empty ABI surrogates.

typedef void (__cdecl *ShroudRefreshCallback)(int x, int y, int status);

struct ShroudPlayerState
{
	unsigned short status;
	unsigned short counters[2];
};

struct ShroudElement008FBA40
{
	char m_cellNodes[4];
	ShroudPlayerState m_playerStates[16];
	int m_unknown64;
};

struct BfmeThingCDE
{
	char m_head[0x10];
	BfmeThingCDE *m_link1;
	char m_links[0x10];
	int m_playerState[16];
	char m_tail[0x40];
};

class ShroudManagerImpl008FBA40
{
public:
	__declspec(noinline) void notify();

private:
	char m_head[0x24];
	unsigned int m_width;
	unsigned int m_height;
	ShroudElement008FBA40 *m_elements;
	BfmeThingCDE *m_nodes;
	char m_betweenNodesAndPlayer[0x30];
	int m_activePlayer;
	char m_enabled[4];
	ShroudRefreshCallback m_refreshCallback;
};

void ShroudManagerImpl008FBA40::notify()
{
	if (m_activePlayer < 0 || m_activePlayer >= 16)
		return;

	ShroudElement008FBA40 *element = m_elements;
	ShroudElement008FBA40 *end = element + m_width * m_height;
	int y = 0;
	int x = 0;
	while (element != end)
	{
		unsigned short state = element->m_playerStates[m_activePlayer].status;
		int status = state == 0xffff ? 2 : state == 0;
		m_refreshCallback(x, y, status);

		++x;
		if (x == m_width)
		{
			x = 0;
			++y;
		}
		++element;
	}

	for (BfmeThingCDE *node = m_nodes; node; node = node->m_link1)
		node->m_playerState[m_activePlayer] = 0;
}
