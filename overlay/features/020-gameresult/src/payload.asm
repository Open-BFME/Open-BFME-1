; 020-gameresult — append a per-machine JSONL record of how the match went.
;
; Detoured onto VictoryConditions::update (RVA 0x0035F920), which runs every
; logic frame on every machine, in game and in the shell.
;
; Why an event log and not one verdict object: a single write at game end is
; only produced by a machine that survives to game end. A crash, or a player
; who quits (reverse/game_end/FINDINGS.md: "The leaver that called quitGame
; does not wait: it posts MSG_CLEAR_GAME_DATA and is on the score screen a tick
; later"), leaves no trace at all — indistinguishable downstream from a game
; that never happened. So:
;   * a "start" record lands as soon as a local slot exists, which makes
;     "crashed mid-game" distinguishable from "never played";
;   * the "end" record carries every slot's PlayerLeaveStatus, not just the
;     local player's verdict, so a quitter's or a crasher's fate is recoverable
;     from any surviving machine's file;
;   * records are line-delimited and flushed, so a crash costs at most a torn
;     final line rather than the whole file.
;
; Entry contract: ecx = VictoryConditions* (thiscall). Every register and flag
; must survive — the stolen prologue runs immediately after us.
; Addresses are absolute: fixed-base 0x400000 image, no ASLR.

bits 32
org CODE_VA

%define IAT_fopen    0x013593BC
%define IAT_fprintf  0x013593C0
%define IAT_fclose   0x013593A0
%define IAT_fputs    0x013593C8
%define IAT_fflush   0x013593A8
%define IAT_getenv   0x013593FC
%define IAT_time     0x013594F0
%define IAT_sprintf  0x0135948C

%define TheGameLogic 0x012F0898         ; FINDINGS: GameLogic global
%define GL_DESYNC    0x6C               ; desync byte
%define GL_LEAVE     0x1B0              ; PlayerLeaveStatus[8], stride 0x1C
%define LEAVE_STRIDE 0x1C
%define LEAVE_SLOTS  8

; VictoryConditions layout (reverse/game_end/FINDINGS.md)
%define OFF_LOCALSLOT   0x94
%define OFF_ENDFRAME    0x98
%define OFF_DEFEATCOUNT 0xC0
%define VT_HASACHIEVEDVICTORY   0x24
%define OFF_PLAYERS     0x14            ; m_players[32]
%define OFF_ISDEFEATED  0x9C            ; m_isDefeated[32]
%define VT_ISLOCALALLIEDVICTORY 0x34
%define VT_ISLOCALALLIEDDEFEAT  0x38
%define VT_AMIOBSERVER          0x40

; Scratch/data laid out by modbuild.py; keep both sides in step.
%define d_started      (DATA_VA + 0)
%define d_ended        (DATA_VA + 4)
%define d_result       (DATA_VA + 8)
%define d_file         (DATA_VA + 12)
%define d_nameptr      (DATA_VA + 16)
%define d_pathbuf      (DATA_VA + 20)      ; 512 bytes
%define d_strings      (DATA_VA + 532)

%define s_fmt_start    (d_strings + OFF_FMT_START)
%define s_fmt_end      (d_strings + OFF_FMT_END)
%define s_fmt_slot     (d_strings + OFF_FMT_SLOT)
%define s_comma        (d_strings + OFF_COMMA)
%define s_tail         (d_strings + OFF_TAIL)
%define s_envname      (d_strings + OFF_ENVNAME)
%define s_appdata      (d_strings + OFF_APPDATA)
%define s_fmt_path     (d_strings + OFF_FMT_PATH)
%define s_mode         (d_strings + OFF_MODE)
%define s_victory      (d_strings + OFF_VICTORY)
%define s_defeat       (d_strings + OFF_DEFEAT)
%define s_undecided    (d_strings + OFF_UNDECIDED)
%define s_empty        (d_strings + OFF_EMPTY)
%define s_mid          (d_strings + OFF_MID)
%define s_fmt_player   (d_strings + OFF_FMT_PLAYER)

start:
    pushad
    pushfd

    mov  esi, ecx
%ifdef PROBE
    ; PROBE builds take the end path as soon as a local slot exists, so struct
    ; layouts can be read off a live game without playing a match to its finish.
    ; The d_ended latch still limits it to one record. Never ship a PROBE build.
    mov  eax, [esi + OFF_LOCALSLOT]
    test eax, eax
    js   .done
    jmp  .ended
%endif
    mov  eax, [esi + OFF_ENDFRAME]
    test eax, eax
    jnz  .ended

    ; ---- still playing (or in the shell) ----
    mov  dword [d_ended], 0
    mov  eax, [esi + OFF_LOCALSLOT]
    test eax, eax
    jns  .in_game
    mov  dword [d_started], 0         ; no local slot: back in the shell, re-arm
    jmp  .done
.in_game:
    cmp  dword [d_started], 0
    jne  .done
    mov  dword [d_started], 1
    call open_file
    test eax, eax
    jz   .done
    push dword [esi + OFF_LOCALSLOT]
    call now
    push eax
    push s_fmt_start
    push dword [d_file]
    call dword [IAT_fprintf]
    add  esp, 16
    call close_file
    jmp  .done

    ; ---- the game just ended ----
.ended:
    cmp  dword [d_ended], 0
    jne  .done
    mov  dword [d_ended], 1

    mov  ecx, esi
    mov  eax, [esi]
    call dword [eax + VT_ISLOCALALLIEDVICTORY]
    movzx eax, al
    mov  edi, s_undecided
    test eax, eax
    jz   .not_victory
    mov  edi, s_victory
    jmp  .have_result
.not_victory:
    mov  ecx, esi
    mov  eax, [esi]
    call dword [eax + VT_ISLOCALALLIEDDEFEAT]
    movzx eax, al
    test eax, eax
    jz   .have_result
    mov  edi, s_defeat
.have_result:
    mov  [d_result], edi

    call open_file
    test eax, eax
    jz   .done

    ; head: t, slot, frame, result, observer, desync, defeatCount
    mov  eax, [TheGameLogic]
    movzx eax, byte [eax + GL_DESYNC]
    mov  ebp, eax                      ; ebp = desync, kept across the call below
    mov  ecx, esi
    mov  eax, [esi]
    call dword [eax + VT_AMIOBSERVER]
    movzx eax, al

    push ebp                           ; desync
    push eax                           ; observer
    push dword [d_result]
    push dword [esi + OFF_ENDFRAME]
    push dword [esi + OFF_LOCALSLOT]
    call now
    push eax
    push s_fmt_end
    push dword [d_file]
    call dword [IAT_fprintf]
    add  esp, 32

    ; slots[]: every player's leave / defeat / victory frames
    xor  ebp, ebp
.slot_loop:
    test ebp, ebp
    jz   .no_comma
    push dword [d_file]                ; fputs(str, FILE*): stream is arg2,
    push s_comma                       ; so it is pushed FIRST, unlike fprintf
    call dword [IAT_fputs]
    add  esp, 8
.no_comma:
    mov  eax, [TheGameLogic]
    lea  edi, [eax + GL_LEAVE]
    mov  eax, ebp
    imul eax, eax, LEAVE_STRIDE
    add  edi, eax
    ; The record ends with a present byte at +0x10 and an AsciiString at +0x14
    ; (FINDINGS). The engine's AsciiString is one pointer to a refcounted block
    ; whose characters start at +8. Emit the raw pointer next to the decoded
    ; name so a wrong layout shows up as data rather than as a plausible lie.
    ; Record layout, read off a live game rather than assumed (a raw seven-dword
    ; dump showed the name pointer at +0x18, not the +0x14 a first reading of
    ; FINDINGS suggested):
    ;   +0x00 leave status   +0x04 leave frame   +0x08 defeat frame
    ;   +0x0C victory frame  +0x10 empty flag    +0x14 slot index, 255 = none
    ;   +0x18 AsciiString    -> one pointer to a refcounted block, chars at +8
    ; The raw pointer is emitted next to the decoded name so a wrong layout
    ; shows up as data instead of as a plausible-looking empty string.
    mov  eax, [edi + 0x18]
    mov  [d_nameptr], eax
    mov  edx, s_empty
    test eax, eax
    jz   .name_ready
    cmp  eax, 0x00400000               ; a plausible heap pointer, not a small int
    jb   .name_ready
    lea  edx, [eax + 8]
.name_ready:
    push edx                           ; name
    push dword [d_nameptr]             ; raw AsciiString pointer, for auditing
    push dword [edi + 0x14]            ; slot index, 255 when unassigned
    ; +0x0C (victory frame) is deliberately NOT emitted. It is machine-local --
    ; a player who left before it was written records 0 where the survivor
    ; records the real frame -- and it is never written at all in skirmish, so
    ; the AI that won one still showed 0. Everything it could convey is already
    ; carried by teamWon/defeated/leave/leaveFrame/defeatFrame, all of which
    ; agree across machines. A field that looks authoritative and is not is
    ; worse than an absent one.
    push dword [edi + 0x08]            ; defeat frame
    push dword [edi + 0x04]            ; leave frame
    push dword [edi + 0x00]            ; leave status: 1 graceful, 2 voted out
    push s_fmt_slot
    push dword [d_file]
    call dword [IAT_fprintf]
    add  esp, 32
    inc  ebp
    cmp  ebp, LEAVE_SLOTS
    jl   .slot_loop

    push dword [d_file]
    push s_mid
    call dword [IAT_fputs]
    add  esp, 8

    ; players[]: per-player defeat, and whether that player's SIDE won.
    ; hasAchievedVictory(p) is "one alliance remains and some undefeated player
    ; is p or p's ally", so it stays true for a player who quit or died while
    ; their team went on to win — which is exactly the 2v2-quitter question a
    ; reconciler has to answer. Indexed by VictoryConditions' own player array,
    ; which is NOT the network slot space that slots[] above uses; they are kept
    ; as separate arrays rather than merged on an assumed alignment.
    xor  ebp, ebp
.player_loop:
    test ebp, ebp
    jz   .p_no_comma
    push dword [d_file]
    push s_comma
    call dword [IAT_fputs]
    add  esp, 8
.p_no_comma:
    mov  eax, [esi + OFF_PLAYERS + ebp*4]
    mov  [d_nameptr], eax              ; reuse as the Player* scratch
    xor  edi, edi                      ; teamWon = 0 when the slot is empty
    test eax, eax
    jz   .p_have_won
    push eax
    mov  ecx, esi
    mov  eax, [esi]
    call dword [eax + VT_HASACHIEVEDVICTORY]
    movzx edi, al
.p_have_won:
    movzx eax, byte [esi + OFF_ISDEFEATED + ebp]
    push edi                           ; teamWon
    push eax                           ; defeated
    push dword [d_nameptr]             ; Player*, 0 when the slot is empty
    push s_fmt_player
    push dword [d_file]
    call dword [IAT_fprintf]
    add  esp, 20
    inc  ebp
    cmp  ebp, LEAVE_SLOTS
    jl   .player_loop

    push dword [d_file]
    push s_tail
    call dword [IAT_fputs]
    add  esp, 8
    call close_file

.done:
    popfd
    popad
    ; modbuild appends the relocated prologue after the WHOLE blob, so the exit
    ; has to jump past the helpers below rather than fall through into them.
    jmp  payload_end

; ---- helpers: all cdecl, all clobber eax/ecx/edx only ----------------
; open_file: append mode, so records accumulate instead of overwriting.
; Returns FILE* in eax (also stashed at d_file), 0 on failure.
; Two cases, not a fallback chain: an explicit BFME_RESULT_PATH wins, otherwise
; the record lands beside the player's replays in
;   %APPDATA%\My Battle for Middle-earth Files\GameResult.jsonl
; which is per-user, always writable, and per-wine-prefix -- so two clients on
; one host separate themselves with no configuration at all. The game's install
; directory (the process cwd) is the wrong default: it is shared between
; instances and read-only on a real Program Files install.
open_file:
    push s_envname
    call dword [IAT_getenv]
    add  esp, 4
    test eax, eax
    jnz  .got
    push s_appdata
    call dword [IAT_getenv]
    add  esp, 4
    push eax
    push s_fmt_path
    push d_pathbuf
    call dword [IAT_sprintf]
    add  esp, 12
    mov  eax, d_pathbuf
.got:
    push s_mode
    push eax
    call dword [IAT_fopen]
    add  esp, 8
    mov  [d_file], eax
    ret

; close_file: flush before close so a later crash cannot lose this record.
close_file:
    push dword [d_file]
    call dword [IAT_fflush]
    add  esp, 4
    push dword [d_file]
    call dword [IAT_fclose]
    add  esp, 4
    mov  dword [d_file], 0
    ret

; now: time(NULL) -> eax
now:
    push 0
    call dword [IAT_time]
    add  esp, 4
    ret

; The relocated original prologue is appended immediately after this label.
payload_end:
