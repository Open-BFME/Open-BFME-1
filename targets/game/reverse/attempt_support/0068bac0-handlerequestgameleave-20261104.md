# 0x0068BAC0 LANAPI::handleRequestGameLeave (999 B): fresh rewrite, 999/999 B, shape 0.974

Bank: targets/game/reverse/attempts/0x0068bac0.cpp (replaces the 881 B / shape 0.575
opaque-name draft). Flags `/DNDEBUG /MD /EHsc`, no includes; TU-local views only.

Identity (target evidence): the matched LANAPI::update (LANAPIUpdate.cpp, 0x006870F0)
calls `?handleRequestGameLeave@LANAPI@@IAEXPAULANMessage@@ABUIPAddr@@_N@Z`, pinned at
0x0068BAC0; ret 0xC at +0x3E4. Body follows the Zero Hour LANAPIhandlers.cpp twin with
BFME differences read off retail: IP/port pair compare, LookupPlayer(getLocalAddress())
(vtable +0xD8/+0xDC), requestSerializedGameInfo(false, sender) at +0x54 instead of
RequestGameOptions, the lobby branch acts only when the Bool argument is set and clears
m_currentGame when it is the removed game, inline wide compare against msg+0x22.

Levers that moved bytes:
- Inline `compare(const WideChar *)` must be `__forceinline` (otherwise an out-of-line call).
- Call the checked slot getter directly as `((Rva0068D3E0Arr *)m_currentGame)->at(player)`
  (the ledger name of 0x0068D3E0) instead of through an inline getLANSlot wrapper: the
  wrapper adds an EH state-4 store around the call; the direct call gives retail's single
  state store (-1) before it (shape 0.961 -> 0.974). Declaring at() `throw()` removes both
  stores and costs 16 bytes (983 B).
- GameSlotConnectInfo with a `: m_ip(0), m_port(0)` ctor and the default argument
  `&GameSlotConnectInfo()` (the WOLLobbyMenuUpdate.cpp spelling); POD value-init zeroes
  8 bytes instead of retail's dword+word.

Remaining residue (10 structural differences):
1. Ours hoists a zero register (`xor ebp,ebp`) to the entry and uses `cmp reg,ebp` for the
   m_currentGame / player==0 / lobby null tests; retail uses `test` and materialises zero
   in EBX only inside the host-left path (+0x89), where the sender pointer (EBX) is dead.
   The extra byte of `[ebp]` addressing for the sender removes retail's loop-alignment nop
   at +0x4F, so positional diffs read 624 although instructions align.
   Inert: local copy of m_currentGame, Bool member/accessor forms, `!player`, `!= 0` /
   `== false` spellings, `break` vs `return`, loop-scoped player, LANPlayer ctor in body,
   NULL casts. Diagnostic: dropping the m_currentGame null test (semantics change) is the
   only edit that removes the entry zero.
2. Lobby loop: retail keeps the game in EBP (spilled at [esp+0x10]) and msg+0x22 in EBX
   (spilled at [esp+0x18], reloaded at a rotated loop top reached by `jmp +0x2F0`); ours
   swaps game into EBX and loads the name pointer into EDI. Inert: four compare spellings
   (while/for/diff-flag/static helper), for/while/result-local/hoisted-name loop forms.

Scratch drivers (untracked): build/scr59/gengl*.py.
