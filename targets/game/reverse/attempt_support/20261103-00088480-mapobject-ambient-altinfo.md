# 0x00088480 MapObject::ambientAudio00088480 (1019 B): structural fixes, 591 -> 203 diffs

Bank: `targets/game/reverse/attempts/0x00088480.cpp` (this session's variant `vk`).
Probe: 1013/1019 B, 203 non-relocation byte diffs, shape 0.975, 7 structural
differences. Previous bank: 1007 B, 591 diffs, shape 0.946. Compiler/flags as
in the bank header (`/DNDEBUG /MD /EHsc`), Wine 11, tree c429ec5fa.

## Retail facts established (dis_retail 0x00088480 1019)

- The two addAudioEvent blocks are NOT nested: `je +0x311` after the
  `current` test (+0x2cd) lands on the `alternate` test. Source shape:
  `if (current) {...}` then `if (alternate) {...}`.
- Each block builds a named local event: retail passes `lea eax,[esp+0x28]`
  to addAudioEvent, not the ctor's return value (`&AudioEventRTS(...)`
  temporary gave `push eax`).
- After the slot-0x5b block retail keeps the alternate info in EDI across
  the switch, and case 3 calls ready() on EDI without reloading after the
  first ready() call: a register local, not the escaped Ref member.
  Spelling (all levers measured; each fixed bytes):
  `AudioEventInfo *altInfo = 0;` declared between `current` and `alternate`
  (gives retail's `xor edi,edi` at +0xFD), `altInfo = alternate.m_ptr;` after
  each assignment, `else altInfo = alternate.m_ptr;` on the no-0x5b path,
  `if (current.m_ptr || altInfo)` and `altInfo` in case 3.

## Remaining residue (one register decision)

1. +0xFF: retail stores the alternate ctor zero from EDI
   (`mov [esp+18],edi`), ours from EBP.
2. +0x311: retail reloads `mov edi,[esp+18]; cmp edi,ebp` for the second
   block (a memory read), ours tests the EDI local directly. With the second
   test spelled `alternate.m_ptr` the early `xor edi,edi` disappears and the
   layout falls back to 612 diffs (variants m/o/p), so the two retail facts
   pull in opposite directions under every spelling tried.
3. Tail: because EDI holds the alternate pointer at the dtor, retail loads
   InterlockedDecrement into EBP (zero register dies) and the four inlined
   Ref dtors use `test esi,esi`; ours keeps EBP zero, uses EDI for the import
   and `cmp esi,ebp`. This is a consequence of item 2.

## Measured and rejected this session

altInfo declared at function top / before `current` (209-612 diffs);
`AudioEventInfo *altInfo = alternate.m_ptr;` after `alternate` (212);
`*const` altInfo after the if (606); `!= 0` spelling (612); assigning altInfo
only after the if (`c`, 606: compiler loads at the join instead of hoisting
into the inner check); direct `TheAudio->getInfoForAudioEvent` (423).

## Next

Look for a spelling where the second block reads memory but altInfo stays
live (e.g. altInfo used again after the event blocks), or a Ref accessor that
returns the pointer by value; callee pin work from the 20260928 bank header
(0x87720/0x877B0/0x877E0/0x87860 names) is still needed before landing.

## Resolved 2026-11-10

Landed byte-exact. The `altInfo` register local was the wrong model: retail
reads `alternate.m_ptr` from memory everywhere and the ready test 0x000874E0
is an in-class `__declspec(noinline)` member, which lets the value survive the
call in EDI (docs/shape_levers.md, 2026-11-10 entry). Two further retail facts:
the re-fetched slot 0x5B info is assigned to `current`, and case 3 breaks out
after the first ready hit.
