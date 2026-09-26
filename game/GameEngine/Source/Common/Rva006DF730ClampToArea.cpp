// cl: /O2 /DNDEBUG /MD /EHsc
//
// 0x006DF730, 378 bytes, __thiscall returning void, `ret 4`.
//
// IDENTITY.  Same object again: +0x1C polygon pointer, +0x20 Coord3D, and the
// step helper it calls through the incremental-link thunk 0x0003A09E IS the
// body landed at 0x006DF420 in this batch, which is what fixes this as a
// member of the same class rather than a free function.  The shroud query,
// the two globals and the +0x1C predicate reuse pins other landed bodies
// already emit.  ONE NEW PIN: 0x0000C9AA (thunk to 0x0018FBF0) sits in the
// same 0x0018Fxxx block as the two predicates and the centre-point getter that
// are already pinned on this pointer, and this call passes it the centre, the
// target, an out-parameter and a flag -- so it is named address-derived, on
// the same address-derived class, and claims nothing beyond its arity.
//
// SHAPE.  Only when the target is FARTHER than 100 from the centre does the
// ring search run, walking the step from zero to 500 in increments of 30.
// Those three numbers are READ OUT OF RETAIL (0x00C7FAC4, 0x00C8615C,
// 0x00C83BBC hold 100.0f, 30.0f and 500.0f) and they have to be spelled as
// LITERALS, not as `extern float`: an extern makes MSVC load the global and
// fold the loop variable into the `fadd`, which is `fld K / fadd [step]` --
// retail has `fld [step] / fadd K`, the shape a literal operand produces.
// Those were the last five bytes.
//
// Two other spellings carry the rest.  The deltas are COPIED from the position
// and then subtracted in place, which is what pre-loads x and y onto the x87
// stack and spills dx while dy and dz stay in registers -- the same lever the
// sibling at 0x006DF420 needed.  And each shroud query re-reads the player
// index AND the manager global into its own locals: caching either across the
// two calls moves the loads past the argument pushes and rotates the register
// allocation of every struct copy that follows.
//
// The two shroud queries are ordered centre-first, target-second, and both run
// unconditionally -- the centre is copied over the target only when the centre
// is visible and the target is not.  The class and this member remain
// address-derived; only the three constants are recovered.

extern "C" double sqrt(double x);
#pragma intrinsic(sqrt)

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
	char bfmeClipSegment6DF730(const BfmeCoord6DF1F0 *from,
		const BfmeCoord6DF1F0 *to, BfmeCoord6DF1F0 *clipped, int flags) const;
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
	void bfmeClampToArea(Coord3D *position);

private:
	char m_pad00[0x1c];
	BfmePolygon6DF1F0 *m_polygon1c;
	Coord3D m_center20;
};

void Rva006DF550::bfmeClampToArea(Coord3D *position)
{
	if (m_polygon1c == 0)
		return;
	if (position == 0)
		return;

	Coord3D *center = &m_center20;
	Coord3D delta;
	delta.x = position->x;
	delta.y = position->y;
	delta.z = position->z;
	delta.x = delta.x - center->x;
	delta.y = delta.y - center->y;
	delta.z = delta.z - center->z;
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y +
		delta.z * delta.z);
	if (distance > 100.0f)
	{
		float step = 0.0f;
		do
		{
			if (bfmeProbeOffsets(position, step))
				return;
			step = step + 30.0f;
		}
		while (step < 500.0f);
	}

	int centerPlayer = g_rva005655C0PlayerList->m_localPlayer0c->m_index24;
	PartitionManager *centerShroud = TheShroudManager;
	bool centerVisible =
		centerShroud->getShroudStatusForPlayer(centerPlayer, center) != 2;
	int targetPlayer = g_rva005655C0PlayerList->m_localPlayer0c->m_index24;
	PartitionManager *targetShroud = TheShroudManager;
	bool targetVisible =
		targetShroud->getShroudStatusForPlayer(targetPlayer, position) != 2;
	if (centerVisible && !targetVisible)
	{
		*position = *center;
		return;
	}

	if (m_polygon1c->bfmeContains6DF1F0(*(const BfmeCoord6DF1F0 *)position))
	{
		*center = *position;
		return;
	}

	Coord3D clipped;
	if (m_polygon1c->bfmeClipSegment6DF730((const BfmeCoord6DF1F0 *)center,
			(const BfmeCoord6DF1F0 *)position, (BfmeCoord6DF1F0 *)&clipped, 1))
	{
		*position = clipped;
		*center = clipped;
		return;
	}

	*position = *center;
}
