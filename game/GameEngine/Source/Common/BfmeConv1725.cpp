// The call at 0x00010B72 is the 5-byte ILT thunk that jumps to the body at
// 0x004AD600, which the ledger owns as
// ?drawBackground@ControlBarScheme@@QAEXUCoord2D@@UICoord2D@@@Z (game/
// GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme_drawBackground.cpp).
// Both arguments are 8-byte by-value structures on the stack and the callee
// cleans them, which is the call shape retail encodes here, so this TU names
// the two structures the way that definition names them.
struct Coord2D
{
	Coord2D(const Coord2D &other) throw()
	{
		x = other.x;
		y = other.y;
	}
	~Coord2D() throw() {}

	float x;
	float y;
};

struct ICoord2D
{
	int x;
	int y;
};

struct BfmePairLB
{
	void *m_bfmeFirstLB;
	void *m_bfmeLastLB;
};

class ControlBarScheme
{
public:
	void drawBackground(Coord2D multi, ICoord2D offset);
};

class BfmeOwnLB
{
public:
	void bfmeFwdLB(BfmePairLB pair);

	ControlBarScheme *m_bfmeTgtLB;
	Coord2D m_bfmeMultiLB;
};

void BfmeOwnLB::bfmeFwdLB(BfmePairLB pair)
{
	if (m_bfmeTgtLB)
	{
		ICoord2D offset;
		offset.y = (int)pair.m_bfmeLastLB;
		offset.x = (int)pair.m_bfmeFirstLB;
		m_bfmeTgtLB->drawBackground(m_bfmeMultiLB, offset);
	}
}