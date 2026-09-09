// ?onEnter@GiantBirdFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.84 date=2026-09-09
// 78/78 bytes; 23 non-reloc bytes differ (8 of ~26 instructions), all in the
// tail after the flags424 test.
// Identity is no longer just "follows the ctor": the state vtable at
// 0x010C79E0 (tools/vtable_lookup.py) resolves slot 4 (+0x10) through gap
// thunk gthunks_014.cpp straight to this RVA, alongside the already-matched
// slot 5 onExit (0x002BF3A0) and slot 6 update (0x002BF250). That is a
// matched-caller proof, not an inference.
// Residue (reconfirmed, not new): retail's tail places the FAILURE return
// (mov eax,-2; pop esi; ret, 7 bytes) as the fallthrough immediately after
// the flags424 test, with CONTINUE (the 14-byte or/xor/pop/ret block) placed
// last and reached only by a forward jump. Every source shape tried compiles
// to the OPPOSITE placement (CONTINUE inline, FAILURE pushed to the end),
// regardless of how the three FAILURE returns are merged:
//   - two sequential early-return ifs + a third "if (flags==0) return FAILURE;"
//   - the nested "if (a && b) { ...; if (c) { ...; return CONTINUE; } } return FAILURE;"
//     one-fallthrough-tail form from docs/shape_levers.md
//   - explicit goto with "failure:" label textually BEFORE "continue_path:"
// All three produced byte-identical output to each other and to the original
// switch/goto stash. /O1, /Os, /Ot, /Og-, /Ob0 (in place of the default /O2)
// were tried on the nested-if shape: /Ot and /Ob0 reproduce the same 23-byte
// diff, /O1, /Os and /Og- regress the whole function (front matches too).
// This looks like an MSVC 7.1 basic-block layout choice the front end makes
// independently of source branch order or label order; a lever that controls
// it (if one exists) was not found in this session.

typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class GiantBirdFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	bool updateWaypointGoal();

	char m_gap04[0x18];
	unsigned char *m_machine;
	char m_gap20[4];
	int m_counter;
};

#pragma comment(linker, "/alternatename:?updateWaypointGoal@GiantBirdFollowWaypointPathState@@QAE_NXZ=?j_00031b47@@YAXXZ")

StateReturnType GiantBirdFollowWaypointPathState::onEnter()
{
	m_counter = 0;
	unsigned char *object = *(unsigned char **)(m_machine + 0x10);
	unsigned char *ai = *(unsigned char **)(object + 0x204);

	if (ai != 0 && (*(unsigned char *)(object + 0x344) & 1) == 0)
	{
		if (!updateWaypointGoal())
			return STATE_SUCCESS;
		if (*(unsigned char *)(ai + 0x424) != 0)
		{
			*(UnsignedInt *)(ai + 0x3f0) |= 0x80;
			return STATE_CONTINUE;
		}
	}
	return STATE_FAILURE;
}
