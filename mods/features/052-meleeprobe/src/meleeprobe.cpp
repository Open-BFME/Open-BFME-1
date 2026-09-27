// Diagnostic wrapper keeps the attempted fix's behavior in one source file.
#include "../../051-structure-melee-gate/src/structure_melee_gate.cpp"

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
static unsigned s_seq, s_calls, s_events, s_dropped, s_frame_events;
static unsigned s_last_tick, s_loops;
static int s_last_frame = -2;
static const char *s_run;

static unsigned word(void *p, int offset) {
    return p ? *(unsigned *)((unsigned char *)p + offset) : 0;
}
static unsigned object_id(void *p) { return word(p, 0x74); }
static int frame() { return game_logic ? (int)word(game_logic, 0x3C) : -1; }
static unsigned skip_byte(void *p) {
    return p ? *((unsigned char *)p + OBJECT_PREDICATE_SKIP) : 0;
}
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
            "{\"ev\":\"startup\",\"schema\":1,\"probe\":\"052-meleeprobe-v1\","
            "\"run\":\"%s\",\"build\":\"%s\",\"pid\":%u,\"fix_enabled\":1,"
            "\"qfreqlo\":%u,\"qfreqhi\":%u,\"max_events_per_frame\":256}\n",
            s_run, build, c_pid(), freq[0], freq[1]));
        checked(c_fflush(s_file));
    }
    return s_file && !s_failed;
}
static int head(const char *event) {
    if (!output()) return 0;
    if (s_frame_events >= 256) { ++s_dropped; return 0; }
    ++s_frame_events;
    ++s_events;
    unsigned counter[2] = {0, 0};
    c_qpc(counter);
    checked(c_fprintf(s_file,
        "{\"ev\":\"%s\",\"run\":\"%s\",\"seq\":%u,\"f\":%d,\"qlo\":%u,\"qhi\":%u",
        event, s_run, ++s_seq, frame(), counter[0], counter[1]));
    return !s_failed;
}

struct Check {
    void *attacker, *target, *state;
    unsigned before, armed, owned, serial;
};
static Check s_check;

// Machine+0x1c is a State pointer; +0x20 is the goal ID. +0x214 remains raw.
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
static void before(void *attacker, void *target, void *state) {
    s_check.attacker = attacker;
    s_check.target = target;
    s_check.state = state;
    s_check.before = skip_byte(target);
    s_check.serial = ++s_calls;
    setPredicateSkipForStructureAttack(target);
    s_check.armed = skip_byte(target);
    s_check.owned = s_ownsPredicateSkipBit;
}
static void after(const char *event, unsigned result) {
    restorePredicateSkipAfterStructureAttackCheck();
    unsigned restored = skip_byte(s_check.target);
    if (!head(event)) return;
    context(s_check.attacker, s_check.target, s_check.state);
    const char *decision = s_check.owned ? "marked" :
        ((s_check.before & 1) ? "preexisting_skip_or_filter_rejected" : "filter_rejected");
    checked(c_fprintf(s_file,
        ",\"call\":%u,\"skip_before\":%u,\"skip_armed\":%u,\"skip_restored\":%u,"
        "\"owned\":%u,\"filter_decision\":\"%s\",\"predicate_al\":%u}\n",
        s_check.serial, s_check.before, s_check.armed, restored,
        s_check.owned, decision, result & 255));
}
static void event(const char *name, void *attacker, void *target, void *state) {
    if (!head(name)) return;
    context(attacker, target, state);
    checked(c_fprintf(s_file, "}\n"));
}

extern "C" __declspec(dllexport) void __cdecl meleeprobe_enter_before(void *a, void *t, void *s) { before(a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_update_before(void *a, void *t, void *s) { before(a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_enter_after(unsigned result) { after("enter_predicate",result); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_update_after(unsigned result) { after("update_predicate",result); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_begin(void *a, void *t, void *s) { event("begin_melee_call",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_update_target(void *a, void *t, void *s) { event("update_melee_target_call",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_stealth_fail(void *a, void *t, void *s) { event("update_stealth_fail",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_update_fail(void *a, void *t, void *s) { event("update_fail_minus2",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_ready(void *a, void *t, void *s) { event("update_ready",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_not_ready(void *a, void *t, void *s) { event("update_not_ready",a,t,s); }
extern "C" __declspec(dllexport) void __cdecl meleeprobe_enter_fail(void *a, void *t, unsigned rawEbx) {
    if (!head("enter_fail_minus2")) return;
    context(a,t,s_check.state);
    checked(c_fprintf(s_file, ",\"raw_ebx\":%u}\n", rawEbx));
}
extern "C" __declspec(dllexport) void __cdecl meleeprobe_distance(void *a, void *t, unsigned limit) {
    if (!head("enter_distance_check")) return;
    context(a,t,s_check.state);
    checked(c_fprintf(s_file, ",\"distance_limit\":%u}\n", limit));
}
extern "C" __declspec(dllexport) void __cdecl meleeprobe_enter_state(void *s) {
    void *m = read_pointer_field(s, 0x1C);
    event("enter_state", read_pointer_field(m, 0x10), c_get_goal_object(m,0), s);
}
extern "C" __declspec(dllexport) void __cdecl meleeprobe_update_state(void *s) {
    void *m = read_pointer_field(s, 0x1C);
    event("update_state", read_pointer_field(m, 0x10), c_get_goal_object(m,0), s);
}
extern "C" __declspec(dllexport) void __cdecl meleeprobe_loop(void) {
    ++s_loops;
    if (!output()) return;
    int f = frame();
    unsigned tick = c_ticks();
    if (f != s_last_frame || tick - s_last_tick >= 1000) {
        // Flush at a new logic frame; the wall heartbeat also works in menus or stalls.
        checked(c_fprintf(s_file,
            "{\"ev\":\"heartbeat\",\"run\":\"%s\",\"f\":%d,\"tick\":%u,"
            "\"loops\":%u,\"predicate_calls\":%u,\"events\":%u,\"dropped\":%u}\n",
            s_run, f, tick, s_loops, s_calls, s_events, s_dropped));
        checked(c_fflush(s_file));
        s_frame_events = 0;
        s_last_frame = f;
        s_last_tick = tick;
    }
}
