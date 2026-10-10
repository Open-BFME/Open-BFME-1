// cl: /O2 /DNDEBUG /MD /EHsc
//
// 0x006DF730, 378 bytes, __thiscall returning void, `ret 4`.
//
// IDENTITY.  Same object again: +0x1C polygon pointer, +0x20 Coord3D, and the
// step helper it calls through the incremental-link thunk 0x0003A09E IS the
// body landed at 0x006DF420 in this batch, which is what fixes this as a
// member of the same class rather than a free function.  The shroud query,
// the two globals reuse identities other landed bodies already emit.
// ILT 0x0000A7DB reaches PolygonTrigger's matched float-coordinate predicate
// at 0x0018FA20; ILT 0x0000C9AA reaches the opaque matched body at 0x0018FBF0.
// The latter takes four stack arguments, returns in AL and pops 16 bytes.
// One-word member-pointer views retain those thiscall ABIs while referencing
// the existing ledger symbols, without giving the opaque body a new name.
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

// The clipping caller's existing coordinate view; identical layout to Coord3D.
struct BfmeCoord6DF1F0
{
	float x;
	float y;
	float z;
};

class BfmePolygon6DF1F0
{
};

extern "C" void __cdecl __identifier("?bfmeContainsPointAt0018FA20@PolygonTrigger@@QBE_NAAUCoord3D@@@Z")();
extern "C" void __cdecl __identifier("?d_0018fbf0@@YAXXZ")();

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

// retail [0x012ED748] EA's `PlayerList *ThePlayerList;`; the TU-local view type
// above is cast to at each use so the decorated name is the canonical one.
class PlayerList;
extern PlayerList *ThePlayerList;

static __forceinline Rva005655C0PlayerList *thePlayers()
{
	return (Rva005655C0PlayerList *)ThePlayerList;
}

class ShroudManager;
extern ShroudManager *TheShroudManager;


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

	int centerPlayer = thePlayers()->m_localPlayer0c->m_index24;
	PartitionManager *centerShroud = (*reinterpret_cast<PartitionManager **>(&TheShroudManager));
	bool centerVisible =
		centerShroud->getShroudStatusForPlayer(centerPlayer, center) != 2;
	int targetPlayer = thePlayers()->m_localPlayer0c->m_index24;
	PartitionManager *targetShroud = (*reinterpret_cast<PartitionManager **>(&TheShroudManager));
	bool targetVisible =
		targetShroud->getShroudStatusForPlayer(targetPlayer, position) != 2;
	if (centerVisible && !targetVisible)
	{
		*position = *center;
		return;
	}

	union
	{
		void (__cdecl *symbol)();
		bool (BfmePolygon6DF1F0::*member)(Coord3D &) const;
	} contains;
	contains.symbol = &__identifier("?bfmeContainsPointAt0018FA20@PolygonTrigger@@QBE_NAAUCoord3D@@@Z");
	if ((m_polygon1c->*contains.member)(*position))
	{
		*center = *position;
		return;
	}

	Coord3D clipped;
	union
	{
		void (__cdecl *symbol)();
		char (BfmePolygon6DF1F0::*member)(const BfmeCoord6DF1F0 *,
			const BfmeCoord6DF1F0 *, BfmeCoord6DF1F0 *, int) const;
	} clip;
	clip.symbol = &__identifier("?d_0018fbf0@@YAXXZ");
	if ((m_polygon1c->*clip.member)((const BfmeCoord6DF1F0 *)center,
			(const BfmeCoord6DF1F0 *)position, (BfmeCoord6DF1F0 *)&clipped, 1))
	{
		*position = clipped;
		*center = clipped;
		return;
	}

	*position = *center;
}
