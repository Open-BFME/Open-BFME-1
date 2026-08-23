; 020-gameresult, second payload — append a "leave" record when this client
; leaves a match it was still playing.
;
; Without it, a 2v2 quitter whose team fights on writes a "start" record and
; nothing else: the match does not end under it, so VictoryConditions::update
; never reaches its end path. That is exactly the shape a client killed with
; SIGKILL leaves behind, so from the departing machine's own file quitting and
; crashing are the same event. This record is the difference: start alone means
; crashed, start+leave means left.
;
; Where this is hooked, and why not Network::quitGame. quitGame is the leave
; entry the ledger points at, and it is not the one an in-game exit takes -- a
; four-client run with an ungated probe on both entries recorded quitGame firing
; zero times, on the quitter and on the three survivors alike. Its only in-game
; caller (0x0056982C, in the QuitMenu teardown) is behind
; `TheGameLogic->getFrame() < 6`; the rest are the disconnect screen, the CRC
; mismatch and the DisconnectManager, none of which is a quit. What the quit
; actually takes is the second entry of reverse/game_end/FINDINGS.md:
; MSG_CLEAR_GAME_DATA posted while the network status is 1, consumed by
; GetCommandsFromCommandList, which calls ConnectionManager::
; sendPlayerLeaveCommands -- RVA 0x00665C10, hooked here. In that same run it
; fired on the quitter at frame 42 and on each survivor at frame 153.
;
; Which is the whole difficulty: it fires on a departure from a FINISHED match
; too. Those three survivors had already written their end record, at frame 127.
; So the gate cannot be "am I leaving" -- every one of them was. It is
; VictoryConditions' own end frame: non-zero means this machine has already seen
; the match resolve, and a departure after that is walking out of a score
; screen, not quitting a game. Gating on anything that merely says "a match was
; in progress" -- the 020 payload's d_started latch, or the network status,
; which is still 1 on the score screen -- appends a spurious leave line to the
; file of every player who finishes a match, and destroys the distinction this
; record exists to make.
;
; Entry contract: thiscall on ConnectionManager, but the payload does not use
; `this`: the hook is only the trigger, and everything it records it reads from
; the globals, so the record's slot is the same field the start record used.
; Every register and flag must survive -- the stolen prologue runs immediately
; after us. Addresses are absolute: fixed-base 0x400000 image, no ASLR.

bits 32
org CODE_VA

%define IAT_fopen    0x013593BC
%define IAT_fprintf  0x013593C0
%define IAT_fclose   0x013593A0
%define IAT_fflush   0x013593A8
%define IAT_getenv   0x013593FC
%define IAT_time     0x013594F0
%define IAT_sprintf  0x0135948C

%define TheGameLogic          0x012F0898
%define GL_FRAME              0x3C
%define TheVictoryConditions  0x012F079C
%define VC_LOCALSLOT          0x94       ; < 0 when this machine has no seat
%define VC_ENDFRAME           0x98       ; non-zero once the match resolved here

; The scratch block is shared with payload.asm and laid out by modbuild.py,
; which emits every offset used here.
%define d_file         (DATA_VA + OFF_D_FILE)
%define d_left         (DATA_VA + OFF_D_LEFT)
%define d_pathbuf      (DATA_VA + OFF_D_PATHBUF)
%define d_strings      (DATA_VA + OFF_STRINGS)

%define s_fmt_leave    (d_strings + OFF_FMT_LEAVE)
%define s_envname      (d_strings + OFF_ENVNAME)
%define s_appdata      (d_strings + OFF_APPDATA)
%define s_fmt_path     (d_strings + OFF_FMT_PATH)
%define s_mode         (d_strings + OFF_MODE)

start:
    pushad
    pushfd

    cmp  dword [d_left], 0
    jne  .done                         ; one record per match
    mov  esi, [TheVictoryConditions]
    test esi, esi
    jz   .done                         ; nothing to read a slot or an end from
    mov  edi, [esi + VC_LOCALSLOT]
    test edi, edi
    js   .done                         ; no seat here, so no match to leave
    cmp  dword [esi + VC_ENDFRAME], 0
    jne  .done                         ; already resolved here: leaving a score
                                       ; screen, not quitting a live match
    mov  eax, [TheGameLogic]
    test eax, eax
    jz   .done                         ; no GameLogic, so no frame
    mov  esi, [eax + GL_FRAME]
    mov  dword [d_left], 1

    call open_file
    test eax, eax
    jz   .done
    push esi                           ; frame
    push edi                           ; local slot
    call now
    push eax
    push s_fmt_leave
    push dword [d_file]
    call dword [IAT_fprintf]
    add  esp, 20
    call close_file

.done:
    popfd
    popad
    ; modbuild appends the relocated prologue after the WHOLE blob, so the exit
    ; has to jump past the helpers below rather than fall through into them.
    jmp  payload_end

; ---- helpers ---------------------------------------------------------
; Duplicated from payload.asm rather than called: yasm -f bin exports no
; symbols, so the two blobs cannot see each other's labels. They do share the
; data block, so both write the same file through the same d_file slot.
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

close_file:
    push dword [d_file]
    call dword [IAT_fflush]
    add  esp, 4
    push dword [d_file]
    call dword [IAT_fclose]
    add  esp, 4
    mov  dword [d_file], 0
    ret

now:
    push 0
    call dword [IAT_time]
    add  esp, 4
    ret

; The relocated original prologue is appended immediately after this label.
payload_end:
