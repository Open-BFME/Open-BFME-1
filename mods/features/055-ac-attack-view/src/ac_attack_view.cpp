#include "predicate_gate.h"

#define game_logic (*(void **)0x012F0898)
#include "view_goal.h"

extern "C" __declspec(dllexport) unsigned __cdecl ac_attack_view_goal(
    unsigned positionId, void *cellInfo, void *attacker) {
    return ac_attack_view_candidate(positionId, cellInfo, attacker, 0);
}

extern "C" __declspec(dllexport) unsigned __cdecl ac_allow_ordered_horde_member_path(
    unsigned retailStatus, void *state, void *member) {
    if (!(retailStatus & 255) || !state || !member) return retailStatus;
    void *owningHorde = read_pointer_field(member, OBJECT_OUTER);
    void *machine = read_pointer_field(state, 0x1C);
    void *target = machine ? c_get_goal_object(machine, 0) : 0;
    void *targetHorde = target ? read_pointer_field(target, OBJECT_OUTER) : 0;
    if (!owningHorde || !targetHorde ||
        !c_is_kind_of(owningHorde, 0, 0x6C) ||
        !c_is_kind_of(targetHorde, 0, 0x6C))
        return retailStatus;
    void *owningAi = read_pointer_field(owningHorde, OBJECT_AI);
    void *owningMachine = owningAi ? read_pointer_field(owningAi, AI_STATE_MACHINE) : 0;
    void *owningState = owningMachine ? read_pointer_field(owningMachine, 0x1C) : 0;
    if (!owningState || ac_view_word(owningState, 0) != 0x0109A0C8 ||
        ac_view_word(owningState, 4) != 50 ||
        c_get_goal_object(owningMachine, 0) != targetHorde) return retailStatus;
    typedef int (__fastcall *Relationship)(void *, void *, void *);
    if (((Relationship)0x005C7950)(member, 0, targetHorde) != 0) return retailStatus;
    // Retail refuses both path computation and reacquisition for this member.
    return retailStatus & ~255u;
}
