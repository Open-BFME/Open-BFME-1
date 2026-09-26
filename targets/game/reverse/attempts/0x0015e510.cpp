// ?update@AIGuardIdleState@@UAE?AW4StateReturnType@@XZ  (0x0015E510, 290B)
// partial score=0.35 date=2026-09-09
// Compiles against the real headers in Code/GameEngine/Source/GameLogic/AI/AIGuard.cpp
// (the ZH-ported TU already includes GameLogic/AIGuard.h, Common/Team.h, etc.), inserted
// in place of the present-unmatched AIGuardIdleState::update body there.
//
// Identity and field offsets are solid, derived by hand-decoding the retail bytes via
// tools/probe.py --all against the pristine (un-edited) source first:
//   - now=TheGameLogic->m_frame at [TheGameLogic+0x3c]; m_nextEnemyScanTime at this+0x24;
//     m_guardeePos (Coord3D) at this+0x28 -- all via the real State/AIGuardIdleState headers.
//   - crate check: machine=this->m_machine (this+0x20 in the REAL State layout, not the
//     +0x1c used by the standalone AIGuardOuterState_update_Bfme.cpp reconstruction --
//     that file redeclares its own simplified State class with different padding, so its
//     offsets do not transfer here); owner=machine->getOwner() (machine+0x10);
//     ai=owner->getAIUpdateInterface() (owner+0x204); ai->getCrateID() (ai+0x218);
//     INVALID_ID == 0 confirmed by retail's `test eax,eax`.
//   - lookForInnerTarget: pinned callee 0x000317A5, called directly on m_machine
//     (cast to AIGuardMachine*), matches the sibling AIGuardOuterState::update.
//   - BFME added team-guard support absent from the ZH header: AIGuardMachine gained
//     TeamID m_teamToGuard right after ObjectID m_targetToGuard (0x44), so it sits at
//     0x48 -- confirmed directly in this body's own disassembly (mov edx,[esi+0x48])
//     and matches the already-landed AIGuardOuterState::update's own m_teamToGuard use.
//   - TeamFactory::findTeamByID(TeamID) matches the real vendored signature byte-for-byte
//     (ecx=TheTeamFactory (VA 0x012ED810), push id, call ILT 0x00044C2E, eax=Team*).
//   - The team-position callee at ILT 0x000241FE takes an out Coord3D* (three stack
//     dwords are built at the call site and reloaded after) -- a DIFFERENT ABI from
//     GeneralsMD's Team::getEstimateTeamPosition() (which takes no args and returns
//     const Coord3D*). Named through a TU-local "BfmeTeamXQ::bfmeEstimateXQ" shape
//     instead of touching the vendored Team class; this exact mangled name is already
//     pinned in reverse/symbols.csv (from the matched BfmeConv2090 step), so no new
//     symbols.csv entry was needed for it.
//   - The 400.0f float constant at VA 0x01096418 is 4*PATHFIND_CELL_SIZE_F^2
//     (PATHFIND_CELL_SIZE_F == 10.0f, GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h).
//
// Residue: 233 of 301 compiled bytes differ from retail's 290, ALL of it one class of
// symptom, present even before the team-guard extension was added (the pristine ZH-only
// body probes the same way): the very first `if (now < m_nextEnemyScanTime) return
// STATE_SLEEP(...);` guard compiles with the return code MOVED OUT OF LINE (a forward
// `jb` to a copy of the return sequence placed near the function's end) instead of
// retail's compact inline early-return (`jae` skips 9 bytes of ret code that sits right
// after the compare, main body starts at +0x1e). Caching `StateMachine *machine =
// getMachine();` up front changed nothing (byte-identical output). Rewriting the whole
// body as `if (now >= m_nextEnemyScanTime) { ...single trailing return... }` (the "one
// fall-through tail" shape_levers.md lever) made it WORSE: all three callee-saved
// registers (ebx/esi/edi) got pushed at the top instead of retail's staggered
// shrink-wrapped pushes (edi immediately, esi at first crate-check use, ebx only at the
// team lookup). Retail's three near-identical `return STATE_SLEEP(m_nextEnemyScanTime -
// now)` tails (initial guard, crate branch, final fallback) are NOT byte-identical in
// retail because each sits at a different point in the callee-saved push sequence (1, 2,
// then 3 registers live) -- something about the exact shape of the crate/inner-target
// blocks between them keeps MSVC 7.1 from unifying the register footprint the way it did
// here. Untried: forcing the crate-branch and final-fallback returns apart from the
// initial one via distinct locals/side effects, or reordering the AIUpdateInterface/
// getCrateID access to change the register pressure at the first guard specifically.
// t=90min model=sonnet-5

// -- reconstruction body (drop-in replacement for the present-unmatched stub in
//    Code/GameEngine/Source/GameLogic/AI/AIGuard.cpp, after AIGuardIdleState::onEnter) --

class BfmeTeamXQ
{
public:
	void bfmeEstimateXQ(Coord3D *out);
};

StateReturnType AIGuardIdleState::update( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return STATE_SLEEP(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

	StateMachine *machine = getMachine();
	Object *owner = machine->getOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if (ai->getCrateID() != INVALID_ID)
	{
		machine->setState(AI_GUARD_GET_CRATE);
		return STATE_SLEEP(m_nextEnemyScanTime - now);
	}

	if (getGuardMachine()->lookForInnerTarget())
	{
		return STATE_SUCCESS;
	}

	Object* targetToGuard = getGuardMachine()->findTargetToGuardByID();
	TeamID teamToGuard = *reinterpret_cast<TeamID *>(reinterpret_cast<char *>(getGuardMachine()) + 0x48);
	Team* targetTeam = TheTeamFactory->findTeamByID(teamToGuard);

	if (targetToGuard || targetTeam)
	{
		Coord3D pos;
		if (targetToGuard)
			pos = *targetToGuard->getPosition();
		else
			((BfmeTeamXQ *)targetTeam)->bfmeEstimateXQ(&pos);

		Real delta = m_guardeePos.x-pos.x;
		if (delta*delta > 4*PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F) {
			m_guardeePos = pos;
			return STATE_FAILURE;
		}
		delta = m_guardeePos.y-pos.y;
		if (delta*delta > 4*PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F) {
			m_guardeePos = pos;
			return STATE_FAILURE;
		}
	}
	return STATE_SLEEP(m_nextEnemyScanTime - now);
}
