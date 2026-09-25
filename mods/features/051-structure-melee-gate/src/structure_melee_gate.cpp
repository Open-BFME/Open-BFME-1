// 051-structure-melee-gate — attempted bypass for melee attacks against a structure-
// attacking battalion. The in-game result has not been verified.
//
// PATCH HYPOTHESIS. Retail behavior and the unverified attempt are documented
// in mods/features/051-structure-melee-gate/README.md.
// bfmeMeleeHordeTargetInvalid (0x00175820) returns 0 immediately when bit 0
// of the byte at Object+0x344 is set, before it looks at facing. Otherwise a
// slow target whose back is toward the attacker is invalid, and
// AIAttackMeleeHordeWaitState returns -2. The machine at 0x001812B0 treats
// that as failure and bounces approach -> wait -> path-wait forever, so
// beginMelee / updateMeleeTarget never run. A battalion facing a building
// holds that condition for the whole order. A unit that is running does not:
// its goal is not a structure, and this hook leaves it alone.
//
// WHY THIS SHAPE. The shim cave.py generates restores every register, so the
// payload cannot clear al and have test al see it. The predicate already has
// the exit, the same way flush already had the list guard 042-tracksfix
// borrows. Set the bit for the duration of the call, put it back before
// test al. Do not change the predicate itself: approach onEnter uses a
// "not invalid" result to leave the attack machine when melee is already
// ready.
//
// No loader and no CRT. Fixed-base image, so the absolute calls below are
// safe. MSVC 7.1 has no __thiscall; the fastcall edx is the unused one.

typedef int Int;

typedef void *(__fastcall *GetGoalObject)(void *machine, void *edx);
typedef Int (__fastcall *IsKindOf)(void *object, void *edx, Int kind);

// StateMachine::getGoalObject, retail 0x000A1490. Reads the id at
// StateMachine+0x20 and resolves it through TheGameLogic.
#define c_get_goal_object ((GetGoalObject)0x004A1490)
// Thing::isKindOf. Kind 7 is KINDOF_STRUCTURE: updateNemesis at 0x000F90D0
// tests structure / infantry / vehicle with 7, 8 and 9.
#define c_is_kind_of ((IsKindOf)0x004A2CF0)

enum {
    OBJECT_AI = 0x204,
    OBJECT_OUTER = 0x214,
    OBJECT_PREDICATE_SKIP = 0x344,
    AI_STATE_MACHINE = 0x30,
    KINDOF_STRUCTURE = 7,
    PREDICATE_SKIP_BIT = 1
};

// The byte this call marked, so restore clears only a bit it set. One logic
// thread: the setter returns before the predicate runs, and restore is the next
// instruction after that call.
static unsigned char *s_ownedPredicateSkipByteAddress;
static int s_ownsPredicateSkipBit;

static void *read_pointer_field(void *base, int offset)
{
    return *(void **)((unsigned char *)base + offset);
}

static int has_structure_attack_goal(void *predicateTarget)
{
    void *ai;
    void *machine;
    void *goal;

    if (predicateTarget == 0)
        return 0;
    ai = read_pointer_field(predicateTarget, OBJECT_AI);
    if (ai == 0)
        return 0;
    machine = read_pointer_field(ai, AI_STATE_MACHINE);
    if (machine == 0)
        return 0;
    goal = c_get_goal_object(machine, 0);
    if (goal == 0)
        return 0;
    return c_is_kind_of(goal, 0, KINDOF_STRUCTURE) != 0;
}

static int predicate_target_or_outer_has_structure_attack_goal(void *predicateTarget)
{
    void *outerCandidate;

    if (has_structure_attack_goal(predicateTarget))
        return 1;
    if (predicateTarget == 0)
        return 0;
    outerCandidate = read_pointer_field(predicateTarget, OBJECT_OUTER);
    if (outerCandidate == 0 || outerCandidate == predicateTarget)
        return 0;
    return has_structure_attack_goal(outerCandidate);
}

extern "C" __declspec(dllexport) void __cdecl setPredicateSkipForStructureAttack(void *predicateTarget)
{
    unsigned char *predicateSkipByteAddress;

    s_ownsPredicateSkipBit = 0;
    if (predicateTarget == 0 ||
        !predicate_target_or_outer_has_structure_attack_goal(predicateTarget))
        return;
    predicateSkipByteAddress = (unsigned char *)predicateTarget + OBJECT_PREDICATE_SKIP;
    if ((*predicateSkipByteAddress & PREDICATE_SKIP_BIT) != 0)
        return;
    *predicateSkipByteAddress = (unsigned char)(*predicateSkipByteAddress | PREDICATE_SKIP_BIT);
    s_ownedPredicateSkipByteAddress = predicateSkipByteAddress;
    s_ownsPredicateSkipBit = 1;
}

extern "C" __declspec(dllexport) void __cdecl restorePredicateSkipAfterStructureAttackCheck(void)
{
    if (!s_ownsPredicateSkipBit)
        return;
    *s_ownedPredicateSkipByteAddress =
        (unsigned char)(*s_ownedPredicateSkipByteAddress & (unsigned char)~PREDICATE_SKIP_BIT);
    s_ownsPredicateSkipBit = 0;
}
