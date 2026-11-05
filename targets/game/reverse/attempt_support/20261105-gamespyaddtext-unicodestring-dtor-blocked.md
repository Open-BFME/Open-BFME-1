# Blocked: ??1UnicodeString loser in GameSpyAddText.cpp (link #178)

Queue: `losers ??1UnicodeString@@QAE@XZ`, 109 B, file
`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/GameSpyAddText.cpp`.
Body `?GameSpyAddText@@YGXVUnicodeString@@W4GameSpyColors@@@Z` at 0x00538F00
(111 B) is matched; only the TU-local `~UnicodeString() {}` COMDAT loses to
retail's 5-byte 0x0005EEA0 body (matched in
`game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp`).

## Measured variants (all break the 111 B byte-match; original `{}` gates 1/1)

1. releaseBuffer-inline dtor (`{ ((StringBase<unsigned short>*)this)->releaseBuffer(); }`):
   SEH prologue appears that retail lacks. FAIL.
2. Declare-only dtor (`~UnicodeString();`): same prologue. FAIL.
3. Implicit dtor (removed): prologue gone, but by-value copy shape changes
   (the `mov [esp+0xC],esp` temp slot disappears; +0x21/+0x52
   `??0StringBase<G>` copy-ctor notes flip to unnamed). FAIL.

## Reading

Retail's body needs the `{}` dtor's exact stack dance (temp slot for the
by-value `message` copies) while emitting no dtor calls and no EH frame, and
VC7.1 keeps the inline COMDAT even though every call site inlines to nothing.
So the byte-match requires `{}` and the link requires no `{}` copy: a genuine
conflict in this TU. This is one of the "five views with a different
destructor spelling" left for later in 1d205a01ed.

## Resume conditions

- A lever that suppresses the unreferenced inline COMDAT without touching the
  dtor's spelling (none known).
- Proof retail built this TU under different flags/layouts that explain the
  dance, plus a matching respell.
- Do NOT re-try variants 1-3; do NOT touch the `{}` body (it is byte-true).
