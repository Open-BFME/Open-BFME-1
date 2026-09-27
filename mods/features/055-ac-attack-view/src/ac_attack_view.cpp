#include "predicate_gate.h"

#define game_logic (*(void **)0x012F0898)
#include "view_goal.h"

extern "C" __declspec(dllexport) unsigned __cdecl ac_attack_view_goal(
    unsigned positionId, void *cellInfo, void *attacker) {
    return ac_attack_view_candidate(positionId, cellInfo, attacker, 0);
}
