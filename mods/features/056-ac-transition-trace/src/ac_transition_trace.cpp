// Diagnostic-only hooks; the 055 patch is built as a separate feature.
#include "../../055-ac-attack-view/src/predicate_gate.h"

enum { PROBE_CHAT_CODE_UNITS = 512 };
struct ProbeChatText {
    char text[PROBE_CHAT_CODE_UNITS * 6 + 1];
    unsigned codeUnits, truncated;
};

static void escape_chat_text(const unsigned short *text, ProbeChatText &out) {
    static const char hex[] = "0123456789abcdef";
    unsigned n = 0, used = 0;
    for (; text && n < PROBE_CHAT_CODE_UNITS && text[n]; ++n) {
        unsigned ch = text[n];
        if (ch == '"' || ch == '\\') {
            out.text[used++] = '\\';
            out.text[used++] = (char)ch;
        } else if (ch >= 32 && ch < 127) {
            out.text[used++] = (char)ch;
        } else {
            out.text[used++] = '\\';
            out.text[used++] = 'u';
            out.text[used++] = hex[(ch >> 12) & 15];
            out.text[used++] = hex[(ch >> 8) & 15];
            out.text[used++] = hex[(ch >> 4) & 15];
            out.text[used++] = hex[ch & 15];
        }
    }
    out.text[used] = 0;
    out.codeUnits = n;
    out.truncated = (unsigned)(text && text[n] != 0);
}

#define PROBE_VARIANT "056-ac-transition-trace"

struct FILE;
typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int (__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int (__cdecl *FFlush)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
typedef unsigned (__stdcall *GetUnsigned)(void);
typedef int (__stdcall *QueryCounter)(unsigned *);
typedef void (__stdcall *DebugString)(const char *);
typedef int (__stdcall *MessageBox)(void *, const char *, const char *, unsigned);
#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_getenv (*(GetEnv *)0x013593FC)
#define c_pid (*(GetUnsigned *)0x01358D74)
#define c_ticks (*(GetUnsigned *)0x01358E0C)
#define c_qpc (*(QueryCounter *)0x01358EB4)
#define c_qpf (*(QueryCounter *)0x01358EB8)
#define c_debug (*(DebugString *)0x01358EA8)
#define c_message (*(MessageBox *)0x0135903C)
#define game_logic (*(void **)0x012F0898)

static FILE *s_file;
static int s_opened, s_failed;
static unsigned s_seq, s_events, s_dropped, s_frame_events, s_chat_events;
static unsigned s_last_tick, s_loops;
static int s_last_frame = -2;
static const char *s_run;
static void failure(const char *why);
struct WatchedMember {
    unsigned id, seen, alive, victim, goal, state, stateId, path;
};
static WatchedMember s_watched_members[512];
static unsigned s_watched_count;

static void watch_member(unsigned id) {
    if (!id) return;
    for (unsigned i = 0; i < s_watched_count; ++i)
        if (s_watched_members[i].id == id) return;
    if (s_watched_count < 512) s_watched_members[s_watched_count++].id = id;
    else failure("AC trace: watched-member capacity exceeded. Capture is incomplete.");
}

static int watched_member(unsigned id) {
    for (unsigned i = 0; i < s_watched_count; ++i)
        if (s_watched_members[i].id == id) return 1;
    return 0;
}

static unsigned word(void *p, int offset) {
    return p ? *(unsigned *)((unsigned char *)p + offset) : 0;
}
static unsigned object_id(void *p) { return word(p, 0x74); }
static int frame() { return game_logic ? (int)word(game_logic, 0x3C) : -1; }
static void failure(const char *why) {
    if (s_failed) return;
    s_failed = 1;
    c_debug(why);
    c_message(0, why, "BFME AC probe capture failed", 0x10);
}
static int token(const char *s) {
    if (!s || !*s) return 0;
    unsigned n = 0;
    for (; *s; ++s, ++n) {
        if (n >= 128 || !((*s >= 'a' && *s <= 'z') ||
            (*s >= 'A' && *s <= 'Z') || (*s >= '0' && *s <= '9') ||
            *s == '-' || *s == '_' || *s == '.')) return 0;
    }
    return 1;
}
static void checked(int result) {
    if (result < 0) failure("AC probe: JSONL write failed. Capture is incomplete.");
}
static int output() {
    if (!s_opened) {
        s_opened = 1;
        const char *path = c_getenv("BFME_AC_PATH");
        s_run = c_getenv("BFME_AC_RUN");
        const char *build = c_getenv("BFME_AC_BUILD");
        if (!path || !*path || !token(s_run) || !token(build)) {
            failure("AC probe: require BFME_AC_PATH and simple BFME_AC_RUN/BFME_AC_BUILD tokens.");
            return 0;
        }
        s_file = c_fopen(path, "a");
        if (!s_file) {
            failure("AC probe: cannot append BFME_AC_PATH. Check the capture directory.");
            return 0;
        }
        unsigned freq[2] = {0, 0};
        c_qpf(freq);
        checked(c_fprintf(s_file,
            "{\"ev\":\"startup\",\"schema\":4,\"probe\":\"%s\","
            "\"run\":\"%s\",\"build\":\"%s\",\"pid\":%u,\"diagnostic_only\":1,"
            "\"qfreqlo\":%u,\"qfreqhi\":%u,\"max_combat_events_per_frame\":256,\"max_chat_code_units\":512}\n",
            PROBE_VARIANT, s_run, build, c_pid(), freq[0], freq[1]));
        checked(c_fflush(s_file));
    }
    return s_file && !s_failed;
}
static int head(const char *event, int marker = 0) {
    if (!output()) return 0;
    if (!marker) {
        if (s_frame_events >= 256) {
            ++s_dropped;
            failure("AC trace: per-frame event capacity exceeded. Capture is incomplete.");
            return 0;
        }
        ++s_frame_events;
    }
    ++s_events;
    unsigned counter[2] = {0, 0};
    c_qpc(counter);
    checked(c_fprintf(s_file,
        "{\"ev\":\"%s\",\"run\":\"%s\",\"seq\":%u,\"f\":%d,\"qlo\":%u,\"qhi\":%u",
        event, s_run, ++s_seq, frame(), counter[0], counter[1]));
    return !s_failed;
}

static void scan_watched_members() {
    if (!game_logic) return;
    typedef void *(__fastcall *FindObject)(void *, void *, unsigned);
    for (unsigned i = 0; i < s_watched_count; ++i) {
        WatchedMember *watch = &s_watched_members[i];
        void *member = ((FindObject)0x0049A510)(game_logic, 0, watch->id);
        void *ai = member ? read_pointer_field(member, OBJECT_AI) : 0;
        void *machine = ai ? read_pointer_field(ai, AI_STATE_MACHINE) : 0;
        void *state = machine ? read_pointer_field(machine, 0x1C) : 0;
        unsigned alive = member != 0;
        unsigned victim = word(ai, 0x40);
        unsigned goal = word(machine, 0x20);
        unsigned stateVtable = word(state, 0);
        unsigned stateId = word(state, 4);
        unsigned path = word(ai, 0x140);
        if (watch->seen && watch->alive == alive && watch->victim == victim &&
            watch->goal == goal && watch->state == stateVtable &&
            watch->stateId == stateId && watch->path == path) continue;
        if (head("member_change")) {
            checked(c_fprintf(s_file,
                ",\"member_id\":%u,\"alive\":%u,\"victim_id\":%u,\"goal_id\":%u,"
                "\"state_vtable\":%u,\"state_id\":%u,\"path\":%u}\n",
                watch->id, alive, victim, goal, stateVtable, stateId, path));
        }
        watch->seen = 1;
        watch->alive = alive;
        watch->victim = victim;
        watch->goal = goal;
        watch->state = stateVtable;
        watch->stateId = stateId;
        watch->path = path;
    }
}

static void chat_text(const char *key, const unsigned short *text) {
    static ProbeChatText escaped;
    escape_chat_text(text, escaped);
    checked(c_fprintf(s_file,
        ",\"%s\":\"%s\",\"%s_code_units\":%u,\"%s_truncated\":%u",
        key, escaped.text, key, escaped.codeUnits, key, escaped.truncated));
}

extern "C" __declspec(dllexport) void __cdecl ac_trace_chat(
    void *message, const unsigned short *displayed, void *manager) {
    // Delivered chat must survive a saturated combat interval and a subsequent crash.
    if (!head("chat", 1)) return;
    ++s_chat_events;
    void *data = read_pointer_field(message, 0x1C);
    const unsigned short *raw = data ? (const unsigned short *)((char *)data + 8) : 0;
    checked(c_fprintf(s_file,
        ",\"sender_slot\":%u,\"recipient_mask\":%u,\"local_slot\":%u",
        word(message, 0x0C), word(message, 0x20), word(manager, 0x12028)));
    chat_text("text", raw);
    chat_text("displayed_text", displayed);
    checked(c_fprintf(s_file, "}\n"));
    checked(c_fflush(s_file));
}

static void context(void *attacker, void *target, void *state) {
    void *machine = state ? read_pointer_field(state, 0x1C) : 0;
    void *goal = machine ? c_get_goal_object(machine, 0) : 0;
    void *ai = target ? read_pointer_field(target, OBJECT_AI) : 0;
    void *targetMachine = ai ? read_pointer_field(ai, AI_STATE_MACHINE) : 0;
    void *targetGoal = targetMachine ? c_get_goal_object(targetMachine, 0) : 0;
    checked(c_fprintf(s_file,
        ",\"attacker\":%u,\"attacker_id\":%u,\"target\":%u,\"target_id\":%u,"
        "\"state\":%u,\"machine\":%u,\"current_state\":%u,\"goal_id\":%u,"
        "\"goal\":%u,\"goal_object_id\":%u,\"target_raw_214\":%u,"
        "\"target_ai\":%u,\"target_machine\":%u,\"target_goal_id\":%u,"
        "\"target_goal\":%u,\"target_goal_object_id\":%u,\"target_goal_is_structure\":%d,\"wait_until\":%u",
        attacker, object_id(attacker), target, object_id(target), state, machine,
        word(machine, 0x1C), word(machine, 0x20), goal, object_id(goal),
        word(target, 0x214), ai, targetMachine, word(targetMachine, 0x20),
        targetGoal, object_id(targetGoal),
        targetGoal ? c_is_kind_of(targetGoal, 0, KINDOF_STRUCTURE) : -1, word(state, 0x24)));
}
static void event(const char *name, void *attacker, void *target, void *state) {
    if (!head(name)) return;
    context(attacker, target, state);
    checked(c_fprintf(s_file, "}\n"));
}


extern "C" __declspec(dllexport) void __cdecl ac_trace_command(void *commandInterface, void *parms) {
    unsigned command = word(parms, 0);
    if (command != 0 && command != 5 && command != 0x0B && command != 0x0C &&
        command != 0x0E && command != 0x0F) return;
    if (!head("command_dispatch")) return;
    void *owner = read_pointer_field(commandInterface, -0x18);
    void *machine = read_pointer_field(commandInterface, 0x10);
    void *target = read_pointer_field(parms, 0x14);
    checked(c_fprintf(s_file,
        ",\"owner\":%u,\"owner_id\":%u,\"machine\":%u,\"command\":%u,\"source\":%u,"
        "\"target\":%u,\"target_id\":%u,\"position_x_bits\":%u,\"position_y_bits\":%u,\"position_z_bits\":%u}\n",
        owner, object_id(owner), machine, command, word(parms, 4),
        target, (command == 0x0B || command == 0x0C) ? object_id(target) : 0, word(parms, 8), word(parms, 0x0C), word(parms, 0x10)));
}
static int melee_state(void *state) {
    unsigned vtable = word(state, 0);
    return vtable == 0x0109A540 || vtable == 0x01097B68 || vtable == 0x01097BE0;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_transition(void *machine, void *next) {
    void *previous = read_pointer_field(machine, 0x1C);
    void *owner = read_pointer_field(machine, 0x10);
    // A watched member can leave melee for any state, including idle.
    if (!watched_member(object_id(owner)) && !melee_state(previous) && !melee_state(next)) return;
    if (!head("state_transition")) return;
    void *ai = owner ? read_pointer_field(owner, OBJECT_AI) : 0;
    checked(c_fprintf(s_file,
        ",\"owner\":%u,\"owner_id\":%u,\"machine\":%u,\"goal_id\":%u,"
        "\"victim_id\":%u,\"path\":%u,"
        "\"previous_state\":%u,\"previous_state_id\":%u,\"previous_state_vtable\":%u,"
        "\"next_state\":%u,\"next_state_id\":%u,\"next_state_vtable\":%u}\n",
        owner, object_id(owner), machine, word(machine, 0x20),
        word(ai, 0x40), word(ai, 0x140),
        previous, word(previous, 4), word(previous, 0), next, word(next, 4), word(next, 0)));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_reacquire_throttle(void *state) {
    void *machine = read_pointer_field(state, 0x1C);
    void *owner = read_pointer_field(machine, 0x10);
    if (!watched_member(object_id(owner)) || !head("reacquire_throttle")) return;
    checked(c_fprintf(s_file,
        ",\"member_id\":%u,\"goal_id\":%u,\"last_acquire_frame\":%u}\n",
        object_id(owner), word(machine, 0x20), word(state, 0x24)));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_reacquire_fail(void *state, void *owner) {
    if (!watched_member(object_id(owner)) || !head("reacquire_fail")) return;
    void *machine = read_pointer_field(state, 0x1C);
    checked(c_fprintf(s_file,
        ",\"member_id\":%u,\"goal_id\":%u,\"last_acquire_frame\":%u,"
        "\"owner_status_94\":%u,\"owner_field_214\":%u,\"machine_present\":%u}\n",
        object_id(owner), word(machine, 0x20), word(state, 0x24),
        word(owner, 0x94), word(owner, 0x214), (unsigned)(machine != 0)));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_engage_enter_fail(
    void *state, void *owner) {
    if (!watched_member(object_id(owner)) || !head("engage_enter_fail")) return;
    void *machine = read_pointer_field(state, 0x1C);
    void *goal = machine ? c_get_goal_object(machine, 0) : 0;
    checked(c_fprintf(s_file,
        ",\"member_id\":%u,\"goal_id\":%u,\"goal_object_id\":%u,"
        "\"owner_status_94\":%u,\"owner_contained_by_id\":%u,"
        "\"owner_path\":%u}\n",
        object_id(owner), word(machine, 0x20), object_id(goal),
        word(owner, 0x94), object_id(read_pointer_field(owner, 0x214)),
        word(read_pointer_field(owner, OBJECT_AI), 0x140)));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_engage_horde_range_refusal(
    void *state, void *owner) {
    if (!watched_member(object_id(owner)) || !head("engage_horde_range_refusal")) return;
    void *machine = read_pointer_field(state, 0x1C);
    checked(c_fprintf(s_file,
        ",\"member_id\":%u,\"goal_id\":%u,\"containing_horde_id\":%u}\n",
        object_id(owner), word(machine, 0x20),
        object_id(read_pointer_field(owner, 0x214))));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_damage_result(void *victim, void *info) {
    if (!head("damage_result")) return;
    checked(c_fprintf(s_file,
        ",\"victim\":%u,\"victim_id\":%u,\"body\":%u,\"source_id\":%u,"
        "\"actual_damage_bits\":%u,\"clipped_damage_bits\":%u,\"no_effect\":%u}\n",
        victim, object_id(victim), word(victim, 0x200), word(info, 8),
        word(info, 0x50), word(info, 0x54), (unsigned)*((unsigned char *)info + 0x58)));
}

struct PlannerTrace {
    void *member, *target, *retryOut;
    unsigned memberId, targetId, arg7, serial, active;
    int startFrame;
    unsigned candidates, distancePasses, layerFirst, layerLast, layerChanges;
    unsigned pointQueries, pointRejected, passedPoint, passedLine, chosen;
    unsigned point[3], firstRejected[3], pointPending, firstRejectedPresent;
    unsigned cellSeen, cellDataPresent, cellRejected, cell, cellFlags, cellInfo;
    unsigned cellUnitsPresent, cellGoalId, cellPosId, cellObstacleId;
    int cellX, cellY;
};
static PlannerTrace s_plan;
static unsigned s_plan_calls, s_plan_overwritten;

static void reset_cell(void) {
    s_plan.cellSeen = s_plan.cellDataPresent = s_plan.cellRejected = 0;
    s_plan.cell = s_plan.cellFlags = s_plan.cellInfo = 0;
    s_plan.cellUnitsPresent = s_plan.cellGoalId = s_plan.cellPosId = s_plan.cellObstacleId = 0;
    s_plan.cellX = s_plan.cellY = 0;
}

extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_enter(
    void *member, void *target, void *retryOut, unsigned arg7) {
    if (s_plan.active) ++s_plan_overwritten;
    s_plan.member = member;
    s_plan.target = target;
    s_plan.retryOut = retryOut;
    s_plan.memberId = object_id(member);
    s_plan.targetId = object_id(target);
    s_plan.arg7 = arg7 & 255;
    s_plan.serial = ++s_plan_calls;
    s_plan.startFrame = frame();
    s_plan.active = 1;
    s_plan.candidates = s_plan.distancePasses = s_plan.layerChanges = 0;
    s_plan.layerFirst = s_plan.layerLast = 0;
    s_plan.pointQueries = s_plan.pointRejected = 0;
    s_plan.passedPoint = s_plan.passedLine = s_plan.chosen = 0;
    s_plan.pointPending = s_plan.firstRejectedPresent = 0;
    reset_cell();
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_candidate(void) {
    if (s_plan.active) ++s_plan.candidates;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_distance_pass(unsigned layer) {
    if (!s_plan.active) return;
    if (!s_plan.distancePasses) s_plan.layerFirst = layer;
    else if (s_plan.layerLast != layer) ++s_plan.layerChanges;
    s_plan.layerLast = layer;
    ++s_plan.distancePasses;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_point(void *coord) {
    if (!s_plan.active) return;
    s_plan.point[0] = word(coord, 0);
    s_plan.point[1] = word(coord, 4);
    s_plan.point[2] = word(coord, 8);
    s_plan.pointPending = coord != 0;
    if (!s_plan.firstRejectedPresent) reset_cell();
}
static int tracing_cell(void) {
    return s_plan.active && s_plan.pointPending && !s_plan.firstRejectedPresent;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_cell_begin(unsigned y, unsigned x) {
    if (!tracing_cell()) return;
    reset_cell();
    s_plan.cellSeen = 1;
    s_plan.cellX = (int)x;
    s_plan.cellY = (int)y;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_cell_data(void *cell) {
    if (!tracing_cell()) return;
    s_plan.cellDataPresent = cell != 0;
    s_plan.cell = (unsigned)cell;
    s_plan.cellFlags = word(cell, 0x0C);
    s_plan.cellInfo = word(cell, 0);
    s_plan.cellUnitsPresent = (s_plan.cellFlags & 0x38) && s_plan.cellInfo;
    s_plan.cellGoalId = s_plan.cellPosId = s_plan.cellObstacleId = 0;
    if (s_plan.cellUnitsPresent) {
        s_plan.cellGoalId = word((void *)s_plan.cellInfo, 0x14);
        s_plan.cellPosId = word((void *)s_plan.cellInfo, 0x18);
    }
    if ((s_plan.cellFlags & 7) == 4 && s_plan.cellInfo)
        s_plan.cellObstacleId = word((void *)s_plan.cellInfo, 0x20);
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_cell_reject(void) {
    if (tracing_cell()) s_plan.cellRejected = 1;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_point_result(unsigned result) {
    if (!s_plan.active) return;
    ++s_plan.pointQueries;
    if (!(result & 255)) {
        ++s_plan.pointRejected;
        if (!s_plan.firstRejectedPresent && s_plan.pointPending) {
            s_plan.firstRejected[0] = s_plan.point[0];
            s_plan.firstRejected[1] = s_plan.point[1];
            s_plan.firstRejected[2] = s_plan.point[2];
            s_plan.firstRejectedPresent = 1;
        }
    }
    s_plan.pointPending = 0;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_passed_point(void) {
    if (s_plan.active) ++s_plan.passedPoint;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_passed_line(void) {
    if (s_plan.active) ++s_plan.passedLine;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_chosen(void) {
    if (s_plan.active) ++s_plan.chosen;
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_plan_complete(unsigned result, void *member, void *slot) {
    unsigned paired = s_plan.active && s_plan.member == member;
    s_plan.active = 0;
    if (!head("melee_plan")) return;
    checked(c_fprintf(s_file,
        ",\"call\":%u,\"start_frame\":%d,\"paired\":%u,\"overwritten_total\":%u,"
        "\"member\":%u,\"member_id\":%u,\"entry_member\":%u,\"entry_member_id\":%u,"
        "\"target\":%u,\"target_id\":%u,\"arg7_low_byte\":%u,\"result_al\":%u,"
        "\"retry_out_present\":%u,\"retry_out\":%u,\"candidates\":%u,\"distance_passes\":%u,"
        "\"layer_first\":%u,\"layer_last\":%u,\"layer_changes\":%u,"
        "\"point_queries\":%u,\"point_rejected\":%u,\"passed_point\":%u,\"passed_line\":%u,\"chosen\":%u,"
        "\"first_rejected_present\":%u,\"first_rejected_x_bits\":%u,\"first_rejected_y_bits\":%u,\"first_rejected_z_bits\":%u,"
        "\"first_rejected_cell_captured\":%u,\"cell_seen\":%u,\"cell_x\":%d,\"cell_y\":%d,"
        "\"cell_data_present\":%u,\"cell\":%u,\"cell_flags\":%u,\"cell_info\":%u,"
        "\"cell_units_present\":%u,\"cell_goal_unit_id\":%u,\"cell_pos_unit_id\":%u,\"cell_obstacle_id\":%u,"
        "\"slot\":%u,\"slot_raw_phase_before\":%u,\"slot_raw_10_before\":%u,\"slot_retry_until_before\":%u",
        s_plan.serial, s_plan.startFrame, paired, s_plan_overwritten,
        member, object_id(member), s_plan.member, s_plan.memberId, s_plan.target, s_plan.targetId,
        s_plan.arg7, result & 255, (unsigned)(paired && s_plan.retryOut != 0),
        paired && s_plan.retryOut ? word(s_plan.retryOut, 0) : 0,
        s_plan.candidates, s_plan.distancePasses, s_plan.layerFirst, s_plan.layerLast, s_plan.layerChanges,
        s_plan.pointQueries, s_plan.pointRejected, s_plan.passedPoint, s_plan.passedLine, s_plan.chosen,
        s_plan.firstRejectedPresent, s_plan.firstRejectedPresent ? s_plan.firstRejected[0] : 0,
        s_plan.firstRejectedPresent ? s_plan.firstRejected[1] : 0, s_plan.firstRejectedPresent ? s_plan.firstRejected[2] : 0,
        (unsigned)(s_plan.firstRejectedPresent && s_plan.cellRejected), s_plan.cellSeen,
        s_plan.cellX, s_plan.cellY, s_plan.cellDataPresent, s_plan.cell, s_plan.cellFlags, s_plan.cellInfo,
        s_plan.cellUnitsPresent, s_plan.cellGoalId, s_plan.cellPosId, s_plan.cellObstacleId,
        slot, word(slot, 0), slot ? (unsigned)*((unsigned char *)slot + 0x10) : 0, word(slot, 0x14)));
    checked(c_fprintf(s_file, "}\n"));
}

extern "C" __declspec(dllexport) void __cdecl ac_trace_begin(void *a, void *t, void *s) { event("begin_melee_call",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl ac_trace_update_target(void *a, void *t, void *s) { event("update_melee_target_call",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl ac_trace_stealth_fail(void *a, void *t, void *s) { event("update_stealth_fail",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl ac_trace_update_fail(void *a, void *t, void *s) { event("update_fail_minus2",a,t,s); }
static int supported_horde(void *horde) {
    void *vtable = horde ? read_pointer_field(horde, 0) : 0;
    return word(vtable, 0x11C) == 0x0042BE6D && word(vtable, 0x124) == 0x0042B5B7;
}
static unsigned byte(void *p, int offset) {
    return p ? *((unsigned char *)p + offset) : 0;
}
static void wait_context(void *a, void *t, void *s) {
    checked(c_fprintf(s_file,
        ",\"attacker\":%u,\"attacker_id\":%u,\"target\":%u,\"target_id\":%u,"
        "\"state\":%u,\"machine\":%u,\"wait_until\":%u",
        a, object_id(a), t, object_id(t), s, word(s, 0x1C), word(s, 0x24)));
}
static void readiness_snapshot(const char *stage, void *a, void *t, void *s, void *horde) {
    if (!head("readiness_snapshot")) return;
    wait_context(a,t,s);
    int supported = supported_horde(horde);
    checked(c_fprintf(s_file, ",\"stage\":\"%s\",\"horde\":%u,\"interface_supported\":%d",
        stage, horde, supported));
    if (!supported) { checked(c_fprintf(s_file, "}\n")); return; }
    unsigned begin = word(horde, 0xF4), end = word(horde, 0xF8);
    int valid = end >= begin && (end - begin) % 0x1C == 0 && (begin || end == 0);
    unsigned total = valid ? (end - begin) / 0x1C : 0;
    checked(c_fprintf(s_file,
        ",\"cached_target_id\":%u,\"cache_until\":%u,\"raw_4\":%u,\"raw_5\":%u,"
        "\"raw_118\":%u,\"raw_119\":%u,\"slots_begin\":%u,\"slots_end\":%u,"
        "\"slots_valid\":%d,\"slots_total\":%u,\"slots_truncated\":%u,\"slots\":[",
        word(horde, 0x100), word(horde, 0x104), byte(horde, 4), byte(horde, 5),
        byte(horde, 0x118), byte(horde, 0x119), begin, end, valid, total, (unsigned)(total > 32)));
    unsigned i;
    for (i = 0; i < total && i < 32; ++i) {
        void *slot = (void *)(begin + i * 0x1C);
        checked(c_fprintf(s_file,
            "%s{\"index\":%u,\"raw_phase\":%u,\"raw_10\":%u,\"retry_until\":%u,\"raw_18_frame\":%u}",
            i ? "," : "", i, word(slot, 0), byte(slot, 0x10), word(slot, 0x14), word(slot, 0x18)));
    }
    void *sentinel = read_pointer_field(horde, -0xAC);
    void *node = sentinel ? read_pointer_field(sentinel, 0) : 0;
    checked(c_fprintf(s_file, "],\"members_available\":%u,\"members\":[", (unsigned)(sentinel != 0)));
    for (i = 0; node && node != sentinel && i < 32; ++i) {
        void *member = read_pointer_field(node, 8);
        watch_member(object_id(member));
        void *ai = member ? read_pointer_field(member, OBJECT_AI) : 0;
        void *machine = ai ? read_pointer_field(ai, AI_STATE_MACHINE) : 0;
        void *state = machine ? read_pointer_field(machine, 0x1C) : 0;
        checked(c_fprintf(s_file,
            "%s{\"member\":%u,\"member_id\":%u,\"ai\":%u,\"victim_id\":%u,"
            "\"state\":%u,\"state_vtable\":%u,\"state_id\":%u,\"goal_id\":%u,\"path\":%u,\"raw_ai_1d8\":%u}",
            i ? "," : "", member, object_id(member), ai, word(ai, 0x40),
            state, word(state, 0), word(state, 4), word(machine, 0x20), word(ai, 0x140), word(ai, 0x1D8)));
        node = read_pointer_field(node, 0);
    }
    checked(c_fprintf(s_file,
        "],\"members_count\":%u,\"members_truncated\":%u,\"members_broken_link\":%u}\n",
        i, (unsigned)(node && node != sentinel), (unsigned)(sentinel && !node)));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_ready(void *a, void *t, void *s, void *horde) {
    event("update_ready",a,t,s);
    if (supported_horde(horde)) readiness_snapshot("ready",a,t,s,horde);
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_not_ready(void *a, void *t, void *s, void *horde) {
    event("update_not_ready",a,t,s);
    if (supported_horde(horde)) readiness_snapshot("not_ready",a,t,s,horde);
    unsigned now = (unsigned)frame();
    unsigned deadline = word(s, 0x24);
    if (now < deadline) return;
    readiness_snapshot("before",a,t,s,horde);
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_enter_fail(void *a, void *t, unsigned rawEbx) {
    if (!head("enter_fail_minus2")) return;
    context(a,t,0);
    checked(c_fprintf(s_file, ",\"raw_ebx\":%u}\n", rawEbx));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_distance(void *a, void *t, unsigned limit) {
    if (!head("enter_distance_check")) return;
    context(a,t,0);
    checked(c_fprintf(s_file, ",\"distance_limit\":%u}\n", limit));
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_enter_state(void *s) {
    void *m = read_pointer_field(s, 0x1C);
    event("enter_state", read_pointer_field(m, 0x10), c_get_goal_object(m,0), s);
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_update_state(void *s) {
    void *m = read_pointer_field(s, 0x1C);
    event("update_state", read_pointer_field(m, 0x10), c_get_goal_object(m,0), s);
}
extern "C" __declspec(dllexport) void __cdecl ac_trace_loop(void) {
    ++s_loops;
    if (!output()) return;
    int f = frame();
    unsigned tick = c_ticks();
    if (f != s_last_frame || tick - s_last_tick >= 1000) {
        if (f != s_last_frame) scan_watched_members();
        // Flush at a new logic frame; the wall heartbeat also works in menus or stalls.
        checked(c_fprintf(s_file,
            "{\"ev\":\"heartbeat\",\"run\":\"%s\",\"f\":%d,\"tick\":%u,"
            "\"loops\":%u,\"events\":%u,\"dropped\":%u,\"chat_events\":%u}\n",
            s_run, f, tick, s_loops, s_events, s_dropped, s_chat_events));
        checked(c_fflush(s_file));
        s_frame_events = 0;
        s_last_frame = f;
        s_last_tick = tick;
    }
}
