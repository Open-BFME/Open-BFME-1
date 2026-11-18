# Three private enum leads refused by the native target gate

At BFME1 3feff183611, private wrapper-before/after trials accepted these
NameKeyType leads. They did not establish retail parity: the mandatory actual
source build subsequently refused three rows in cohort106. All three source
edits were restored from their exact captured originals and are not counted.

- DrawableStartAmbientSound.cpp: cleanup0x00C20820,11B, old $L1128 no
  longer identifies it; $L1132 and $L1130 match equally in its parent group.
- GenerateGameSpyGameResultsPacket.cpp: cleanup0x00C41512 has a shifted
  local-label/body selection; the emitted excerpt begins with two AsciiString
  cleanup jumps instead of the target flag test. No replacement pin is guessed.
- DrawableReaction0041EBD0.cpp: the actual-source retail row0x0041EBD0
  differs in the order of adjacent loads (`mov esi,[esp+10h]` and
  `mov edi,[esp+2Ch]`). A private wrapper is compiler discovery, not a
  substitute for the actual-source gate. No equivalence waiver is used.

The private source/ordinary objects and initial native log remain in
build/codex-20261116-fivehundred/batch-106 and its diagnostics folder. The
exact withdrawn patch is encoded in the adjacent .patch.json. The original
source compiler flags and paths are retained in that patch. The reviewed
BFME2 reference remains0630f0ef47d0a818bb2e97583b43cfb1ecd35491.

Identity, relocation, byte and EH gates remain unchanged. No native verifier,
symbol/funclet pin, CSV row or baseline was edited. Native reuse requires
independent unwind-state identity or a supported compiler-context repair;
these unchanged trials are excluded from later selection. No crash, memory,
new authored-byte, full-image link or runtime result is inferred.
