// ?rva006A3200@W3DGameClient@@QAEXI@Z
// partial score=0.89 date=2026-09-12
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006A3200. thiscall on W3DGameClient: if the argument is >= 5,
// createVideoPlayer, stamp two fields, and push_back a 12-byte list node
// onto the circular list whose sentinel lives at this+0x4C.

class VideoPlayerInterface
{
public:
	unsigned m_flag;
	unsigned m_pad;
	int m_kind;
};

namespace _STL
{
	struct __new_alloc
	{
		static void *allocate(unsigned int n);
	};
}

struct Rva006A3200Node
{
	Rva006A3200Node *m_next;
	Rva006A3200Node *m_prev;
	VideoPlayerInterface *m_player;
};

class W3DGameClient
{
public:
	VideoPlayerInterface *createVideoPlayer(void);
	void rva006A3200(unsigned int kind);

	char m_pad[0x4C];
	Rva006A3200Node *m_sentinel;
};

void W3DGameClient::rva006A3200(unsigned int kind)
{
	VideoPlayerInterface *player;
	Rva006A3200Node *sent;
	if (kind < 5)
		return;

	player = createVideoPlayer();
	player->m_kind = kind;
	player->m_flag = 1;

	sent = m_sentinel;
	Rva006A3200Node *node = (Rva006A3200Node *)_STL::__new_alloc::allocate(0xC);
	if (&node->m_player)
		node->m_player = player;
	Rva006A3200Node *prev = sent->m_prev;
	node->m_next = sent;
	node->m_prev = prev;
	prev->m_next = node;
	sent->m_prev = node;
}
