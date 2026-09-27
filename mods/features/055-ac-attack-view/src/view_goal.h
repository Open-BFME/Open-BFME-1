#pragma once

// Attack-view search misses members whose cells hold only a goal reservation.
static unsigned ac_view_word(void *base, unsigned offset) {
    return *(unsigned *)((unsigned char *)base + offset);
}

static unsigned ac_attack_view_candidate(unsigned positionId, void *cellInfo,
                                         void *attacker, unsigned *stage) {
    if (stage) *stage = 0;
    if (positionId || !cellInfo || !attacker || !game_logic) return positionId;
    if (stage) *stage = 1;
    unsigned goalId = ac_view_word(cellInfo, 0x14);
    // Keep native obstacle candidates visible when both IDs share a cell.
    if (!goalId || ac_view_word(cellInfo, 0x20) ||
        goalId == ac_view_word(attacker, 0x74)) return positionId;
    if (stage) *stage = 2;
    typedef void *(__fastcall *FindObject)(void *, void *, unsigned);
    void *owner = ((FindObject)0x0049A510)(game_logic, 0, goalId);
    if (!owner) return positionId;
    if (stage) *stage = 3;
    void *targetHorde = read_pointer_field(owner, 0x214);
    if (!targetHorde || !c_is_kind_of(targetHorde, 0, 0x6C)) return positionId;
    if (stage) *stage = 4;
    if (!has_structure_attack_goal(targetHorde)) return positionId;
    if (stage) *stage = 5;
    void *targetAi = read_pointer_field(targetHorde, OBJECT_AI);
    void *targetMachine = targetAi ? read_pointer_field(targetAi, AI_STATE_MACHINE) : 0;
    void *targetState = targetMachine ? read_pointer_field(targetMachine, 0x1C) : 0;
    if (!targetState || ac_view_word(targetState, 0) != 0x0109A0C8 ||
        ac_view_word(targetState, 4) != 50 ||
        !*((unsigned char *)targetState + 0x45)) return positionId;
    if (stage) *stage = 6;
    typedef int (__fastcall *Relationship)(void *, void *, void *);
    if (((Relationship)0x005C7950)(attacker, 0, targetHorde) != 0) return positionId;
    if (stage) *stage = 7;
    return goalId;
}
