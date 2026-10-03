// The call at 0x0004461B is the 5-byte ILT thunk that jumps to the body at
// 0x004AD4C0, which the ledger owns as
// ?drawForeground@ControlBarScheme@@QAEXUCoord2D@@UICoord2D@@@Z (game/
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

struct BfmePairLA
{
	void *m_bfmeFirstLA;
	void *m_bfmeLastLA;
};

class ControlBarScheme
{
public:
	void drawForeground(Coord2D multi, ICoord2D offset);
};

class BfmeOwnLA
{
public:
	void bfmeFwdLA(BfmePairLA pair);

	ControlBarScheme *m_bfmeTgtLA;
	Coord2D m_bfmeMultiLA;
};

void BfmeOwnLA::bfmeFwdLA(BfmePairLA pair)
{
	if (m_bfmeTgtLA)
	{
		ICoord2D offset;
		// The assignment order is load-bearing: it is what puts the pair's
		// last word in the first register retail loads before the two pushes.
		offset.y = (int)pair.m_bfmeLastLA;
		offset.x = (int)pair.m_bfmeFirstLA;
		m_bfmeTgtLA->drawForeground(m_bfmeMultiLA, offset);
	}
}