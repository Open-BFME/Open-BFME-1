// cl: /O2 /DNDEBUG /MD /EHsc
//
// 0x006DF420, 237 bytes, __thiscall returning a byte, `ret 8`.
//
// IDENTITY.  Same object as 0x006DF550 / 0x006DF090 / 0x006DF650: the fields
// touched are the pointer at +0x1C and the three floats at +0x20, which is
// exactly what the constructor at 0x006DF550 zeroes.  The predicate on that
// pointer is the already-pinned thunk 0x0000A7DB, and the shroud query is the
// already-pinned ?getShroudStatusForPlayer@PartitionManager@@... at 0x008F7430
// reached through ?TheShroudManager@@3PAVPartitionManager@@A (0x012ED5BC) with
// the local player's index out of 0x012ED748.  No new name is minted here: the
// two globals, the shroud query and the polygon predicate all reuse pins that
// other landed bodies already emit, and the enclosing class and this member
// stay address-derived because neither is recovered.
//
// SHAPE.  Two nested -1..1 loops over a step scaled by the float argument,
// skipping the (0,0) centre.  The candidate's z is copied straight through
// while x and y each take `fild` of the loop counter, so the counters are
// signed ints, not floats.  `m_polygon1c == 0` short-circuits both tests and
// takes the accept path directly -- that is the `je` out of the middle of the
// x87 sequence, scheduled there because the load of +0x1C is free while the
// FPU is busy.
//
// THE ONE SPELLING THAT MATTERS.  Retail loads position->x and position->y
// onto the x87 stack BEFORE it stores anything, adds into them with
// non-popping `fadd st(2)` / `fadd st(1)`, and then pops both with two dead
// `fstp st(0)`.  Writing the obvious `candidate.x = position->x + row * step;`
// gives `fild` first and folds the base into a memory `fadd` -- 229 bytes, and
// no ordering, aliasing or local-variable variant moved it.  Copying the
// position across FIRST and then adding into the copy is what reproduces
// retail: the three copies are dead stores the compiler deletes, but the two
// float LOADS it had already hoisted for them stay on the FPU stack, which is
// where the non-popping adds and the two dead pops come from.  That is a
// byte-level fact about the shape, not a claim that retail wrote these exact
// five statements.

struct Coord3D
{
	float x;
	float y;
	float z;
};

// The spelling the 0x0000A7DB pin already carries; identical layout to Coord3D.
struct BfmeCoord6DF1F0
{
	float x;
	float y;
	float z;
};

class BfmePolygon6DF1F0
{
public:
	char bfmeContains6DF1F0(const BfmeCoord6DF1F0 &point) const;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex,
		const Coord3D *point) const;
};

struct Rva005655C0Player
{
	char m_padding00[0x24];
	int m_index24;
};

struct Rva005655C0PlayerList
{
	char m_padding00[0x0c];
	Rva005655C0Player *m_localPlayer0c;
};

extern Rva005655C0PlayerList *g_rva005655C0PlayerList;
extern PartitionManager *TheShroudManager;

class Rva006DF550
{
public:
	bool bfmeProbeOffsets(Coord3D *position, float step);

private:
	char m_pad00[0x1c];
	BfmePolygon6DF1F0 *m_polygon1c;
	Coord3D m_center20;
};

bool Rva006DF550::bfmeProbeOffsets(Coord3D *position, float step)
{
	if (position == 0)
		return false;

	Coord3D candidate;
	for (int row = -1; row <= 1; row++)
	{
		for (int column = -1; column <= 1; column++)
		{
			if (row == 0 && column == 0)
				continue;

			candidate.x = position->x;
			candidate.y = position->y;
			candidate.z = position->z;
			candidate.x = candidate.x + row * step;
			candidate.y = candidate.y + column * step;

			if (m_polygon1c != 0)
			{
				int playerIndex = g_rva005655C0PlayerList->m_localPlayer0c->m_index24;
				if (TheShroudManager->getShroudStatusForPlayer(playerIndex,
						&candidate) == 2)
					continue;
				if (!m_polygon1c->bfmeContains6DF1F0(
						*(const BfmeCoord6DF1F0 *)&candidate))
					continue;
			}

			*position = candidate;
			m_center20 = candidate;
			return true;
		}
	}

	return false;
}
