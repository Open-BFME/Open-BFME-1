"""Run the production recovery TU with game calls mocked at their actual addresses.

This checks retry policy and the low-byte return contract, not retail pathfinding.
The freestanding i386 executable needs neither Wine nor 32-bit system libraries.
"""
import platform
import shutil
import subprocess
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]

HARNESS = r'''
#define __declspec(x)
#define __cdecl __attribute__((cdecl))
#define __stdcall __attribute__((stdcall))
#define __fastcall __attribute__((fastcall))
#if RETRY_VARIANT == 2
#include "mods/features/054-melee-target-goal/src/meleeprobe.cpp"
#elif RETRY_VARIANT
#include "mods/features/053-melee-retry/src/meleeprobe.cpp"
#else
#include "mods/features/052-meleeprobe/src/meleeprobe.cpp"
#endif

static unsigned char logic[0x80], attacker[0x400], target[0x400], outer[0x400];
static unsigned char ai[0x80], machine[0x80], structure[0x400], state[0x80];
static unsigned char hordeStorage[0x400], vtable[0x140];
static void *horde = hordeStorage + 0xAC;
static unsigned updateCalls, readyCalls, callOrder, readyResult, writeCalls;
static unsigned loggerFailures, debugFailures;
static unsigned plannerRecord[48], plannerRecords;
static int wrongCall, writeFails, structureKind = 1;
static int targetHorde = 1, relationship;
static void *lookupResult = outer;
static unsigned relationshipCalls, lookupCalls;

static void setword(void *base, int offset, unsigned value) {
    *(unsigned *)((char *)base + offset) = value;
}
static void setptr(void *base, int offset, void *value) {
    *(void **)((char *)base + offset) = value;
}
static void *__fastcall mock_goal(void *m, void *) {
    return m == machine ? structure : 0;
}
static int __fastcall mock_kind(void *goal, void *, int kind) {
    if (kind == 0x6C) return goal == target && targetHorde;
    return goal == structure && kind == 7 && structureKind;
}
static int __fastcall mock_relationship(void *member, void *, void *goal) {
    ++relationshipCalls;
    if (member != attacker || goal != target) wrongCall = 1;
    return relationship;
}
static void *__fastcall mock_lookup(void *game, void *, unsigned id) {
    ++lookupCalls;
    if (game != logic || id != 77) wrongCall = 1;
    return lookupResult;
}
static void __fastcall mock_update(void *h, void *, void *t) {
    ++updateCalls;
    if (h != horde || t != target || byte(h, 0x119) != 1 || callOrder != 0)
        wrongCall = 1;
    callOrder = 1;
}
static unsigned __fastcall mock_ready(void *h, void *, void *t) {
    ++readyCalls;
    if (h != horde || t != target || callOrder != 1) wrongCall = 1;
    callOrder = 2;
    return readyResult;
}
static int __cdecl mock_print(FILE *, const char *format, ...) {
    ++writeCalls;
    const char *prefix = ",\"call\":%u,\"start_frame\":";
    unsigned i = 0;
    while (prefix[i] && prefix[i] == format[i]) ++i;
    if (!prefix[i]) {
        __builtin_va_list args;
        __builtin_va_start(args, format);
        for (i = 0; i < 48; ++i) plannerRecord[i] = __builtin_va_arg(args, unsigned);
        __builtin_va_end(args);
        ++plannerRecords;
    }
    return writeFails ? -1 : 0;
}
static int __stdcall mock_counter(unsigned *counter) {
    counter[0] = 123; counter[1] = 0;
    return 1;
}
static void __stdcall mock_debug(const char *) { ++debugFailures; }
static int __stdcall mock_message(void *, const char *, const char *, unsigned) {
    ++loggerFailures;
    return 1;
}
static char *__cdecl mock_missing_env(const char *) { return 0; }

static int map_page(unsigned address, unsigned size) {
    // The payload's fixed addresses must exist before any production code runs.
    unsigned args[6] = {address, size, 7, 0x32, ~0u, 0};
    unsigned result;
    asm volatile("int $0x80" : "=a"(result) : "a"(90), "b"(args) : "memory");
    return result == address;
}
static void jump(unsigned address, void *function) {
    *(unsigned char *)address = 0xE9;
    *(unsigned *)(address + 1) = (unsigned)function - address - 5;
}

static int planner_case(unsigned scenario) {
    unsigned retryOut = 0x12345678, point[3] = {0x3F800000, 0xC0000000, 0x40400000};
    if (scenario == 14) {
        meleeprobe_plan_enter(attacker, target, &retryOut, 0xABCDFF);
        meleeprobe_plan_candidate();
        meleeprobe_plan_distance_pass(7);
        meleeprobe_plan_distance_pass(9);
        meleeprobe_plan_point(point);
        point[0] = 0xDEADBEEF;
        meleeprobe_plan_point_result(0xABCD00);
        meleeprobe_plan_point(point);
        meleeprobe_plan_point_result(0xABCD01);
        meleeprobe_plan_complete(0xABCD01, attacker, 0);
        if (s_plan.active || plannerRecords != 1 || plannerRecord[2] != 1 ||
            plannerRecord[10] != 255 || plannerRecord[11] != 1 ||
            plannerRecord[12] != 1 || plannerRecord[13] != retryOut) return 20;
        if (plannerRecord[14] != 1 || plannerRecord[15] != 2 || plannerRecord[16] != 7 ||
            plannerRecord[17] != 9 || plannerRecord[18] != 1 || plannerRecord[19] != 2 ||
            plannerRecord[20] != 1 || plannerRecord[24] != 1 ||
            plannerRecord[25] != 0x3F800000 || plannerRecord[26] != point[1] ||
            plannerRecord[27] != point[2]) return 21;
        meleeprobe_plan_enter(attacker, target, 0, 0);
        meleeprobe_plan_point_result(0x100);
        meleeprobe_plan_complete(0x100, attacker, 0);
        if (plannerRecord[11] || plannerRecord[12] || plannerRecord[13] ||
            plannerRecord[14] || plannerRecord[15] || plannerRecord[24] ||
            plannerRecord[25] || plannerRecord[26] || plannerRecord[27] ||
            plannerRecord[19] != 1 || plannerRecord[20] != 1) return 22;
    } else if (scenario == 15) {
        // Unpaired completions must never dereference a previous stack-frame output.
        meleeprobe_plan_enter(attacker, target, (void *)1, 0);
        meleeprobe_plan_complete(1, target, 0);
        if (plannerRecord[2] || plannerRecord[12] || plannerRecord[13]) return 23;
        meleeprobe_plan_complete(1, attacker, 0);
        if (plannerRecord[2] || plannerRecord[12] || plannerRecord[13]) return 24;
        meleeprobe_plan_enter(attacker, target, &retryOut, 0);
        meleeprobe_plan_enter(target, attacker, (void *)1, 0);
        meleeprobe_plan_complete(1, attacker, 0);
        if (plannerRecord[2] || plannerRecord[3] != 1 || plannerRecord[12] ||
            plannerRecord[13]) return 25;
    } else {
        meleeprobe_plan_enter(attacker, target, (void *)1, 0);
        meleeprobe_plan_point(point);
        if (scenario == 16) s_frame_events = 256;
        else s_failed = 1;
        meleeprobe_plan_complete(1, attacker, 0);
        if (s_plan.active || plannerRecords) return 26;
    }
    unsigned char saved[sizeof(s_plan)];
    for (unsigned i = 0; i < sizeof(s_plan); ++i) saved[i] = ((unsigned char *)&s_plan)[i];
    meleeprobe_plan_candidate();
    meleeprobe_plan_distance_pass(123);
    meleeprobe_plan_point((void *)1);
    meleeprobe_plan_point_result(0);
    meleeprobe_plan_passed_point();
    meleeprobe_plan_passed_line();
    meleeprobe_plan_chosen();
    for (unsigned i = 0; i < sizeof(s_plan); ++i)
        if (saved[i] != ((unsigned char *)&s_plan)[i]) return 27;
    return 0;
}

static int ignored_cells() {
    unsigned char saved[sizeof(s_plan)];
    for (unsigned i = 0; i < sizeof(s_plan); ++i) saved[i] = ((unsigned char *)&s_plan)[i];
    meleeprobe_cell_begin(123, 456);
    meleeprobe_cell_data((void *)1);
    meleeprobe_cell_reject();
    for (unsigned i = 0; i < sizeof(s_plan); ++i)
        if (saved[i] != ((unsigned char *)&s_plan)[i]) return 30;
    return 0;
}
static int cell_case(unsigned scenario) {
    unsigned point[3] = {1, 2, 3};
    unsigned cell[4] = {0, 0, 0, 0x3C}, info[9] = {0};
    cell[0] = (unsigned)info;
    info[5] = 0xAABBCCDD; info[6] = 0x11223344; info[8] = 0x55667788;
    if (ignored_cells()) return 31;
    meleeprobe_plan_enter(attacker, target, 0, 0);
    if (ignored_cells()) return 32;
    meleeprobe_plan_point(point);
    meleeprobe_cell_begin(3, 4);
    meleeprobe_cell_data(cell);
    if (s_plan.cellGoalId != info[5] || s_plan.cellPosId != info[6] ||
        s_plan.cellObstacleId != info[8]) return 33;
    if (scenario == 18 || scenario == 19) {
        if (scenario == 18) meleeprobe_cell_begin(7, ~0u);
        else meleeprobe_cell_data(0);
        meleeprobe_cell_reject();
        meleeprobe_plan_point_result(0);
        meleeprobe_plan_complete(0, attacker, 0);
        if (plannerRecord[28] != 1 || plannerRecord[29] != 1) return 34;
        if (scenario == 18 && (plannerRecord[30] != ~0u || plannerRecord[31] != 7)) return 35;
        for (unsigned i = 32; i <= 39; ++i)
            if (plannerRecord[i]) return 36;
    } else if (scenario == 20) {
        cell[0] = 1; cell[3] = 0;
        meleeprobe_cell_data(cell);
        if (s_plan.cellUnitsPresent || s_plan.cellGoalId || s_plan.cellPosId ||
            s_plan.cellObstacleId) return 37;
        cell[0] = 0; cell[3] = 0x3C;
        meleeprobe_cell_data(cell);
        if (s_plan.cellUnitsPresent || s_plan.cellGoalId || s_plan.cellPosId ||
            s_plan.cellObstacleId) return 38;
        cell[0] = (unsigned)info; cell[3] = 4;
        meleeprobe_cell_data(cell);
        if (s_plan.cellUnitsPresent || s_plan.cellGoalId || s_plan.cellPosId ||
            s_plan.cellObstacleId != info[8]) return 39;
        cell[3] = 8;
        meleeprobe_cell_data(cell);
        if (!s_plan.cellUnitsPresent || s_plan.cellGoalId != info[5] ||
            s_plan.cellPosId != info[6] || s_plan.cellObstacleId) return 40;
        meleeprobe_plan_point_result(1);
        meleeprobe_plan_point(point);
        if (s_plan.cellSeen || s_plan.cellDataPresent || s_plan.cellRejected ||
            s_plan.cell || s_plan.cellFlags || s_plan.cellInfo || s_plan.cellUnitsPresent ||
            s_plan.cellGoalId || s_plan.cellPosId || s_plan.cellObstacleId ||
            s_plan.cellX || s_plan.cellY) return 44;
    } else {
        meleeprobe_cell_reject();
        meleeprobe_plan_point_result(0);
        if (ignored_cells()) return 41;
        meleeprobe_plan_point(point);
        if (ignored_cells()) return 42;
        meleeprobe_plan_complete(0, attacker, 0);
        if (plannerRecord[37] != info[5] || plannerRecord[38] != info[6] ||
            plannerRecord[39] != info[8]) return 43;
    }
    return 0;
}

static int target_goal_case(unsigned scenario) {
    unsigned point[3] = {1, 2, 3}, info[9] = {0}, id = 77, expected = 77;
    void *query = attacker, *cellInfo = info;
    setword(attacker, 0x74, 123);
    setptr(outer, 0x214, target);
    setptr(machine, 0x1C, state);
    setword(state, 0, 0x0109A0C8);
    setword(state, 4, 50);
    state[0x45] = 1;
    info[5] = id;
    meleeprobe_plan_enter(attacker, target, 0, 0);
    meleeprobe_plan_point(point);
    switch (scenario) {
    case 22: expected = 0; break;
    case 23: s_plan.active = 0; cellInfo = (void *)1; break;
    case 24: s_plan.pointPending = 0; cellInfo = (void *)1; break;
    case 25: query = target; cellInfo = (void *)1; break;
    case 26: query = 0; cellInfo = (void *)1; break;
    case 27: s_plan.target = 0; cellInfo = (void *)1; break;
    case 28: id = expected = 0; cellInfo = (void *)1; break;
    case 29: id = expected = 123; cellInfo = (void *)1; break;
    case 30: cellInfo = 0; break;
    case 31: info[5] = 88; break;
    case 32: info[6] = 88; break;
    case 33: targetHorde = 0; break;
    case 34: structureKind = 0; break;
    case 35: relationship = 1; break;
    case 36: relationship = 2; break;
    case 37: game_logic = 0; break;
    case 38: lookupResult = 0; break;
    case 39: setptr(outer, 0x214, attacker); break;
    case 40: s_frame_events = 256; expected = 0; break;
    case 41: s_failed = 1; expected = 0; break;
    case 42:
        meleeprobe_plan_point_result(0);
        meleeprobe_plan_point(point);
        expected = 0; break;
    case 43: setptr(target, OBJECT_AI, 0); break;
    case 44: setword(state, 0, 0x12345678); break;
    case 45:
        setptr(target, OBJECT_AI, 0);
        setptr(target, OBJECT_OUTER, structure);
        setptr(structure, OBJECT_AI, ai);
        break;
    case 46: setptr(machine, 0x1C, 0); break;
    case 47: writeFails = 1; head("write-failure"); expected = 0; break;
    case 48: setword(state, 4, 51); break;
    case 49: setword(state, 4, 12); break;
    case 50: state[0x45] = 0; break;
    default: return 50;
    }
#if RETRY_VARIANT != 2
    expected = id;
#endif
    unsigned char *regions[] = {attacker, target, outer, ai, machine, structure, state, logic,
                               (unsigned char *)info};
    unsigned sizes[] = {sizeof(attacker), sizeof(target), sizeof(outer), sizeof(ai),
                        sizeof(machine), sizeof(structure), sizeof(state), sizeof(logic), sizeof(info)};
    unsigned char saved[9][0x400];
    for (unsigned i = 0; i < 9; ++i)
        for (unsigned j = 0; j < sizes[i]; ++j) saved[i][j] = regions[i][j];
    void *originalLogic = game_logic;
    unsigned result = meleeprobe_target_goal(id, cellInfo, query);
    if (result != expected || wrongCall) return 51;
    for (unsigned i = 0; i < 9; ++i)
        for (unsigned j = 0; j < sizes[i]; ++j)
            if (saved[i][j] != regions[i][j]) return 52;
    if (game_logic != originalLogic) return 53;
    unsigned overridden = id != 0 && expected == 0;
    if (s_plan.goalOverrides != overridden ||
        s_plan.goalFirstId != (overridden ? id : 0) ||
        s_plan.goalLastId != (overridden ? id : 0)) return 54;
#if RETRY_VARIANT != 2
    if (relationshipCalls || lookupCalls || s_plan.goalChecks) return 55;
#else
    if (scenario >= 48 && scenario <= 50 &&
        (s_plan.goalReject[GOAL_STATE] != 1 || !s_plan.goalStateSeen ||
         s_plan.goalStateVtableFirst != 0x0109A0C8 ||
         s_plan.goalStateIdFirst != word(state, 4) ||
         s_plan.goalStateAttackingFirst != state[0x45] || relationshipCalls || lookupCalls)) return 56;
#endif
    return 0;
}

extern "C" int run(int argc, char **argv) {
    if (argc != 2) return 90;
    unsigned scenario = 0;
    for (char *p = argv[1]; *p; ++p) scenario = scenario * 10 + *p - '0';
    if (!map_page(0x00400000, 0x00300000) || !map_page(0x012F0000, 0x00070000))
        return 91;
    jump(0x004A1490, (void *)mock_goal);
    jump(0x004A2CF0, (void *)mock_kind);
    jump(0x006440E0, (void *)mock_update);
    jump(0x006439F0, (void *)mock_ready);
    jump(0x005C7950, (void *)mock_relationship);
    jump(0x0049A510, (void *)mock_lookup);
    *(FPrintf *)0x013593C0 = mock_print;
    *(QueryCounter *)0x01358EB4 = mock_counter;
    *(DebugString *)0x01358EA8 = mock_debug;
    *(MessageBox *)0x0135903C = mock_message;
    *(GetEnv *)0x013593FC = mock_missing_env;
    game_logic = logic;
    setword(logic, 0x3C, 100);
    setword(state, 0x24, 100);
    setptr(target, OBJECT_AI, ai);
    setptr(ai, AI_STATE_MACHINE, machine);
    setptr(horde, 0, vtable);
    setword(vtable, 0x11C, 0x0042BE6D);
    setword(vtable, 0x124, 0x0042B5B7);
    *((unsigned char *)horde + 0x119) = 0xA5;
    s_opened = 1;
    s_file = (FILE *)1;
    s_run = "runtime-test";
    if (scenario >= 14 && scenario <= 17) return planner_case(scenario);
    if (scenario >= 18 && scenario <= 21) return cell_case(scenario);
    if (scenario >= 22 && scenario <= 50) return target_goal_case(scenario);
    readyResult = 0xABCD01;
    unsigned expectedAttempts = 1, expectedDeadline = 115;
    void *passedTarget = target;

    switch (scenario) {
    case 0: readyResult = 0xABCD00; expectedDeadline = 100; break;
    case 1: break;
    case 2:
        setword(logic, 0x3C, 99);
        expectedAttempts = 0; expectedDeadline = 100; break;
    case 3:
        structureKind = 0;
        expectedAttempts = 0; expectedDeadline = 100; break;
    case 4:
        setword(vtable, 0x11C, 0);
        expectedAttempts = 0; expectedDeadline = 100; break;
    case 5:
        passedTarget = 0;
        expectedAttempts = 0; expectedDeadline = 100; break;
    case 6: writeFails = 1; break;
    case 7: s_opened = 0; s_file = 0; break;
    case 8:
        setptr(target, OBJECT_AI, 0);
        setptr(target, OBJECT_OUTER, outer);
        setptr(outer, OBJECT_AI, ai);
        break;
    case 9:
        setptr(target, OBJECT_AI, 0);
        expectedAttempts = 0; expectedDeadline = 100; break;
    case 10:
        setword(vtable, 0x124, 0);
        expectedAttempts = 0; expectedDeadline = 100; break;
    case 11:
        setword(logic, 0x3C, 101);
        expectedDeadline = 116; break;
    case 12: s_failed = 1; break;
    case 13:
        setword(logic, 0x3C, 105);
        expectedAttempts = 0; expectedDeadline = 100; break;
    default: return 92;
    }
#if !RETRY_VARIANT
    expectedAttempts = 0;
    expectedDeadline = 100;
#endif
    unsigned char originalHorde[sizeof(hordeStorage)], originalState[sizeof(state)];
    for (unsigned i = 0; i < sizeof(hordeStorage); ++i) originalHorde[i] = hordeStorage[i];
    for (unsigned i = 0; i < sizeof(state); ++i) originalState[i] = state[i];
    if (scenario == 13) meleeprobe_ready(attacker, passedTarget, state, horde);
    else meleeprobe_not_ready(attacker, passedTarget, state, horde);
    if (updateCalls != expectedAttempts) return 1;
    if (readyCalls != expectedAttempts) return 2;
    if (wrongCall || callOrder != expectedAttempts * 2) return 3;
    if (word(state, 0x24) != expectedDeadline) return 4;
    if (byte(horde, 0x119) != (expectedAttempts ? 1u : 0xA5u)) return 5;
    if ((scenario == 6 || scenario == 7) &&
        (!s_failed || loggerFailures != 1 || debugFailures != 1)) return 6;
    if (scenario != 7 && scenario != 12 && !writeCalls) return 7;
    for (unsigned i = 0; i < sizeof(hordeStorage); ++i)
        if (i != 0xAC + 0x119 && hordeStorage[i] != originalHorde[i]) return 8;
    for (unsigned i = 0; i < sizeof(state); ++i)
        if ((i < 0x24 || i >= 0x28) && state[i] != originalState[i]) return 9;
    return 0;
}
asm(".global _start\n_start:\n"
    "xor %ebp,%ebp\n pop %eax\n mov %esp,%ecx\n and $-16,%esp\n sub $8,%esp\n"
    "push %ecx\n push %eax\n"
    "call run\n mov %eax,%ebx\n mov $1,%eax\n int $0x80\n");
'''


@pytest.fixture(scope="module")
def recovery(tmp_path_factory):
    compiler = shutil.which("g++")
    if platform.system() != "Linux" or platform.machine() not in ("x86_64", "i686") or not compiler:
        pytest.skip("Linux x86 and g++ required for the freestanding i386 harness")
    tmp = tmp_path_factory.mktemp("melee-retry-runtime")
    source = tmp / "recovery.cpp"
    source.write_text(HARNESS)
    binaries = {}
    for enabled in (0, 1, 2):
        binary = tmp / f"recovery-{enabled}"
        compiled = subprocess.run([
            compiler, "-std=c++98", "-m32", "-O2", "-nostdlib", "-fno-pie", "-no-pie",
            "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin",
            f"-DRETRY_VARIANT={enabled}", "-I", str(ROOT), str(source), "-o", str(binary),
        ], capture_output=True, text=True)
        assert compiled.returncode == 0, compiled.stdout + compiled.stderr
        binaries[enabled] = binary
    return binaries


@pytest.mark.parametrize("scenario", range(13), ids=[
    "false-al-with-nonzero-high-bits", "true-al-refreshes-deadline", "before-deadline",
    "non-structure-goal", "unsupported-update-slot", "null-target", "write-failed",
    "configuration-missing", "outer-structure-goal", "missing-target-ai",
    "unsupported-readiness-slot", "past-deadline", "logger-already-failed",
])
def test_retry_policy_executes_production_code(recovery, scenario):
    result = subprocess.run([str(recovery[1]), str(scenario)], capture_output=True, timeout=5)
    assert result.returncode == 0, f"harness assertion {result.returncode}; {result.stderr!r}"


def test_diagnostic_control_never_calls_recovery_or_changes_deadline(recovery):
    result = subprocess.run([str(recovery[0]), "1"], capture_output=True, timeout=5)
    assert result.returncode == 0, f"harness assertion {result.returncode}; {result.stderr!r}"


@pytest.mark.parametrize("enabled", (0, 1), ids=["diagnostic", "retry"])
@pytest.mark.parametrize("scenario", range(13, 18), ids=[
    "ready-snapshot-does-not-mutate-game-state", "planner-al-dword-copy-and-reset",
    "unpaired-completion-cannot-read-stale-output", "dropped-completion-ends-capture",
    "failed-logger-completion-ends-capture",
])
def test_diagnostic_capture_safety(recovery, enabled, scenario):
    result = subprocess.run([str(recovery[enabled]), str(scenario)], capture_output=True, timeout=5)
    assert result.returncode == 0, f"harness assertion {result.returncode}; {result.stderr!r}"


@pytest.mark.parametrize("enabled", (0, 1), ids=["diagnostic", "retry"])
@pytest.mark.parametrize("scenario", range(18, 22), ids=[
    "bounds-rejection-clears-previous-occupancy", "null-cell-clears-previous-occupancy",
    "info-union-reads-require-flags-and-pointer", "callbacks-respect-query-lifetime",
])
def test_cell_capture_safety(recovery, enabled, scenario):
    result = subprocess.run([str(recovery[enabled]), str(scenario)], capture_output=True, timeout=5)
    assert result.returncode == 0, f"harness assertion {result.returncode}; {result.stderr!r}"


@pytest.mark.parametrize("scenario", range(22, 51), ids=[
    "eligible-target-reservation", "inactive", "outside-point-query", "different-query-object",
    "null-query-object", "null-target", "empty-goal", "self-reservation", "null-cell-info",
    "goal-id-mismatch", "physical-occupant", "building-target", "non-structure-order",
    "neutral-target", "allied-target", "missing-game-logic", "missing-reservation-owner",
    "other-horde-reservation", "logging-capped", "logging-failed", "first-rejection-already-captured",
    "missing-target-ai", "non-attack-state", "only-outer-has-structure-goal", "missing-target-state",
    "logging-write-failure", "forced-attack-state-51", "follow-state-12", "not-attacking-object",
])
def test_target_goal_exception_policy_and_memory_safety(recovery, scenario):
    result = subprocess.run([str(recovery[2]), str(scenario)], capture_output=True, timeout=5)
    assert result.returncode == 0, f"harness assertion {result.returncode}; {result.stderr!r}"


@pytest.mark.parametrize("enabled", (0, 1), ids=["diagnostic", "retry"])
def test_target_goal_exception_is_disabled_in_comparison_variants(recovery, enabled):
    result = subprocess.run([str(recovery[enabled]), "22"], capture_output=True, timeout=5)
    assert result.returncode == 0, f"harness assertion {result.returncode}; {result.stderr!r}"
