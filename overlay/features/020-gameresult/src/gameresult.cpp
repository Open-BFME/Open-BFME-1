// 020-gameresult — append a per-machine JSONL record of how the match went.
//
// Two detours, one translation unit. `gameresult_update` rides
// VictoryConditions::update (RVA 0x0035F920), which runs every logic frame on
// every machine, in game and in the shell. `gameresult_leave` rides
// ConnectionManager::sendPlayerLeaveCommands (RVA 0x00665C10). They share the
// latches and the file helpers below, which is the whole reason they are one
// file: the pair of hand-written blobs this replaced could not see each other's
// symbols and duplicated both.
//
// Why an event log and not one verdict object: a single write at game end is
// only produced by a machine that survives to game end. A crash, or a player
// who quits (reverse/game_end/FINDINGS.md: "The leaver that called quitGame
// does not wait: it posts MSG_CLEAR_GAME_DATA and is on the score screen a tick
// later"), leaves no trace at all — indistinguishable downstream from a game
// that never happened. So:
//   * a "start" record lands as soon as a local slot exists, which makes
//     "crashed mid-game" distinguishable from "never played";
//   * a "leave" record lands when this machine walks out of a match that had
//     not resolved here, which makes "quit" distinguishable from "crashed";
//   * the "end" record carries every slot's PlayerLeaveStatus, not just the
//     local player's verdict, so a quitter's or a crasher's fate is recoverable
//     from any surviving machine's file;
//   * records are line-delimited and flushed, so a crash costs at most a torn
//     final line rather than the whole file.
//
// There is no loader and no CRT here: tools/cave.py drops this into a section
// appended to the retail image and jumps into it from mid-function. Nothing may
// need a static initializer, an exception, or a runtime-library helper — see
// modbuild.py's undefined-externals check, which fails the build on one.
// Addresses are absolute: fixed-base 0x400000 image, DllCharacteristics 0x0000,
// so no ASLR.

// ---- the game's own CRT, called through its import table ------------------
// One indirection, exactly as the retail code calls them: the IAT slot holds
// the address ntdll wrote at load time.
struct FILE;

typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int(__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int(__cdecl *FPuts)(const char *, FILE *);
typedef int(__cdecl *FFlush)(FILE *);
typedef int(__cdecl *FClose)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
typedef int(__cdecl *SPrintf)(char *, const char *, ...);
typedef long(__cdecl *Time)(long *);

#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fputs (*(FPuts *)0x013593C8)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_fclose (*(FClose *)0x013593A0)
#define c_getenv (*(GetEnv *)0x013593FC)
#define c_sprintf (*(SPrintf *)0x0135948C)
#define c_time (*(Time *)0x013594F0)

// ---- the engine's globals and struct layouts -----------------------------
#define TheGameLogic (*(void **)0x012F0898)
#define TheVictoryConditions (*(void **)0x012F079C)

enum {
    GL_FRAME = 0x3C,   // current logic frame
    GL_DESYNC = 0x6C,  // desync byte
    GL_LEAVE = 0x1B0,  // PlayerLeaveStatus[8]
    LEAVE_STRIDE = 0x1C,
    LEAVE_SLOTS = 8
};

// VictoryConditions layout and vtable slots (reverse/game_end/FINDINGS.md).
enum {
    VC_PLAYERS = 0x14,     // m_players[32]
    VC_LOCALSLOT = 0x94,   // < 0 when this machine has no seat
    VC_ENDFRAME = 0x98,    // non-zero once the match resolved here
    VC_ISDEFEATED = 0x9C,  // m_isDefeated[32], one byte each
    VT_HASACHIEVEDVICTORY = 0x24,
    VT_ISLOCALALLIEDVICTORY = 0x34,
    VT_ISLOCALALLIEDDEFEAT = 0x38,
    VT_AMIOBSERVER = 0x40
};

// MSVC 7.1 rejects the __thiscall keyword ("reserved for future use"), so the
// engine's thiscall methods are declared __fastcall with an unused edx. Same
// registers, same callee-cleans-the-stack rule, so the two are the same ABI for
// every arity used here.
typedef unsigned char(__fastcall *Predicate)(void *self, void *edx);
typedef unsigned char(__fastcall *PlayerPredicate)(void *self, void *edx, void *player);

static const unsigned char *at(const void *base, int offset) {
    return (const unsigned char *)base + offset;
}
static unsigned u32(const void *base, int offset) { return *(const unsigned *)at(base, offset); }
static int i32(const void *base, int offset) { return *(const int *)at(base, offset); }
static unsigned char u8(const void *base, int offset) { return *at(base, offset); }
static void *ptr(const void *base, int offset) { return *(void **)at(base, offset); }

static unsigned char call_predicate(void *self, int slot) {
    return (*(Predicate *)at(ptr(self, 0), slot))(self, 0);
}
static unsigned char call_predicate(void *self, int slot, void *player) {
    return (*(PlayerPredicate *)at(ptr(self, 0), slot))(self, 0, player);
}

// ---- where the records land ----------------------------------------------
static const char PATH_ENV[] = "BFME_RESULT_PATH";
static const char PATH_FMT[] = "%s\\My Battle for Middle-earth Files\\GameResult.jsonl";

static int s_started;  // a start record has been written for this match
static int s_ended;    // an end record has been written for this match
static int s_left;     // a leave record has been written for this match
static FILE *s_file;
static char s_path[512];

// Append mode, so records accumulate instead of overwriting. Two cases, not a
// fallback chain: an explicit BFME_RESULT_PATH wins, otherwise the record lands
// beside the player's replays in
//   %APPDATA%\My Battle for Middle-earth Files\GameResult.jsonl
// which is per-user, always writable, and per-wine-prefix — so two clients on
// one host separate themselves with no configuration at all. The game's install
// directory (the process cwd) is the wrong default: it is shared between
// instances and read-only on a real Program Files install.
static FILE *open_file() {
    const char *path = c_getenv(PATH_ENV);
    if (path == 0) {
        c_sprintf(s_path, PATH_FMT, c_getenv("APPDATA"));
        path = s_path;
    }
    s_file = c_fopen(path, "a");
    return s_file;
}

// Flush before close so a later crash cannot lose this record.
static void close_file() {
    c_fflush(s_file);
    c_fclose(s_file);
    s_file = 0;
}

static long now() { return c_time(0); }

// ---- the end record's two arrays -----------------------------------------
// Every player's leave / defeat frames, indexed by network slot. Record layout
// read off a live game rather than assumed (a raw seven-dword dump showed the
// name pointer at +0x18, not the +0x14 a first reading of FINDINGS suggested):
//   +0x00 leave status   +0x04 leave frame   +0x08 defeat frame
//   +0x0C victory frame  +0x10 empty flag    +0x14 slot index, 255 = none
//   +0x18 AsciiString    -> one pointer to a refcounted block, chars at +8
//
// +0x0C (victory frame) is deliberately NOT emitted. It is machine-local — a
// player who left before it was written records 0 where the survivor records
// the real frame — and it is never written at all in skirmish, so the AI that
// won one still showed 0. Everything it could convey is already carried by
// teamWon/defeated/leave/leaveFrame/defeatFrame, all of which agree across
// machines. A field that looks authoritative and is not is worse than an
// absent one.
static void write_slots() {
    for (int slot = 0; slot < LEAVE_SLOTS; ++slot) {
        if (slot != 0) {
            c_fputs(",", s_file);
        }
        const unsigned char *record = at(TheGameLogic, GL_LEAVE + slot * LEAVE_STRIDE);
        // The raw AsciiString pointer is emitted next to the decoded name so a
        // wrong layout shows up as data instead of as a plausible-looking empty
        // string. Below the image base it is a small int, not a heap block.
        unsigned name_ptr = u32(record, 0x18);
        const char *name = name_ptr >= 0x00400000 ? (const char *)(name_ptr + 8) : "";
        c_fprintf(s_file,
                  "{\"leave\":%d,\"leaveFrame\":%d,\"defeatFrame\":%d,"
                  "\"slotIndex\":%d,\"namePtr\":%d,\"name\":\"%s\"}",
                  u32(record, 0x00),  // leave status: 1 graceful, 2 voted out
                  u32(record, 0x04), u32(record, 0x08), u32(record, 0x14), name_ptr, name);
    }
}

// Per-player defeat, and whether that player's SIDE won. hasAchievedVictory(p)
// is "one alliance remains and some undefeated player is p or p's ally", so it
// stays true for a player who quit or died while their team went on to win —
// which is exactly the 2v2-quitter question a reconciler has to answer. Indexed
// by VictoryConditions' own player array, which is NOT the network slot space
// write_slots() uses; they are kept as separate arrays rather than merged on an
// assumed alignment.
static void write_players(void *vc) {
    for (int index = 0; index < LEAVE_SLOTS; ++index) {
        if (index != 0) {
            c_fputs(",", s_file);
        }
        void *player = ptr(vc, VC_PLAYERS + index * 4);
        unsigned char won = 0;  // an empty slot won nothing
        if (player != 0) {
            won = call_predicate(vc, VT_HASACHIEVEDVICTORY, player);
        }
        c_fprintf(s_file, "{\"player\":%d,\"defeated\":%d,\"teamWon\":%d}", (unsigned)player,
                  u8(vc, VC_ISDEFEATED + index), won);
    }
}

static void write_end(void *vc) {
    const char *result = "undecided";
    if (call_predicate(vc, VT_ISLOCALALLIEDVICTORY)) {
        result = "victory";
    } else if (call_predicate(vc, VT_ISLOCALALLIEDDEFEAT)) {
        result = "defeat";
    }
    if (open_file() == 0) {
        return;
    }
    unsigned char desync = u8(TheGameLogic, GL_DESYNC);
    c_fprintf(s_file,
              "{\"ev\":\"end\",\"t\":%d,\"slot\":%d,\"frame\":%d,\"result\":\"%s\","
              "\"observer\":%d,\"desync\":%d,\"slots\":[",
              now(), i32(vc, VC_LOCALSLOT), u32(vc, VC_ENDFRAME), result,
              call_predicate(vc, VT_AMIOBSERVER), desync);
    write_slots();
    c_fputs("],\"players\":[", s_file);
    write_players(vc);
    c_fputs("]}\n", s_file);
    close_file();
}

// ---- the detour entry points ---------------------------------------------
// Both are reached from the shim tools/cave.py generates, which has already
// saved every register and flag and hands over the `this` the hooked function
// was called with. Neither may assume anything else about the machine state.

// VictoryConditions::update, every logic frame, in game and in the shell.
extern "C" __declspec(dllexport) void __cdecl gameresult_update(void *vc) {
#ifdef PROBE
    // PROBE builds take the end path as soon as a local slot exists, so struct
    // layouts can be read off a live game without playing a match to its
    // finish. The s_ended latch still limits it to one record per match.
    // Never ship a PROBE build.
    if (i32(vc, VC_LOCALSLOT) >= 0) {
#else
    if (u32(vc, VC_ENDFRAME) != 0) {
#endif
        if (s_ended == 0) {
            s_ended = 1;
            write_end(vc);
        }
        return;
    }

    // Still playing, or in the shell.
    s_ended = 0;
    int slot = i32(vc, VC_LOCALSLOT);
    if (slot < 0) {
        s_started = 0;  // no local slot: back in the shell, re-arm
        return;
    }
    if (s_started != 0) {
        return;
    }
    s_started = 1;
    // One leave record per match: gameresult_leave sets s_left, and this — the
    // single frame a match's start record is written on — is the only thing
    // that clears it.
    s_left = 0;
    if (open_file() == 0) {
        return;
    }
    c_fprintf(s_file, "{\"ev\":\"start\",\"t\":%d,\"slot\":%d}\n", now(), slot);
    close_file();
}

// ConnectionManager::sendPlayerLeaveCommands — the leave entry an in-game exit
// actually takes. Network::quitGame is the one the ledger points at, and a
// four-client probe recorded it firing zero times: its only in-game caller
// (0x0056982C, in the QuitMenu teardown) is behind `TheGameLogic->getFrame() <
// 6`, and the rest are the disconnect screen, the CRC mismatch and the
// DisconnectManager, none of which is a quit.
//
// The difficulty is that this entry fires on a departure from a FINISHED match
// too — measured firing on all three survivors of a 2v2, twenty-six frames
// after they wrote their end record. So the gate cannot be "am I leaving":
// every one of them was. It is VictoryConditions' own end frame, which is
// non-zero exactly when this machine has already seen the match resolve; a
// departure after that is walking out of a score screen, not quitting a game.
// Gating on anything that merely says "a match was in progress" — the s_started
// latch, or the network status, which is still 1 on the score screen — appends
// a spurious leave line to the file of every player who finishes a match, and
// destroys the distinction this record exists to make.
//
// `this` is unused: the hook is only the trigger, and everything the record
// carries it reads from the globals, so its slot is the field the start record
// used.
extern "C" __declspec(dllexport) void __cdecl gameresult_leave(void *connection_manager) {
    (void)connection_manager;
    if (s_left != 0) {
        return;  // one record per match
    }
    void *vc = TheVictoryConditions;
    if (vc == 0) {
        return;  // nothing to read a slot or an end from
    }
    int slot = i32(vc, VC_LOCALSLOT);
    if (slot < 0) {
        return;  // no seat here, so no match to leave
    }
    if (u32(vc, VC_ENDFRAME) != 0) {
        return;  // already resolved here: leaving a score screen, not quitting
    }
    void *logic = TheGameLogic;
    if (logic == 0) {
        return;  // no GameLogic, so no frame
    }
    unsigned frame = u32(logic, GL_FRAME);

    s_left = 1;
    if (open_file() == 0) {
        return;
    }
    c_fprintf(s_file, "{\"ev\":\"leave\",\"t\":%d,\"slot\":%d,\"frame\":%d}\n", now(), slot, frame);
    close_file();
}
