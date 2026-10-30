# 0x000B2430 weighted-sound choice: parameter order (range, count, logical)

Old ledger name: `?bfmeWeightedChoiceB2430@@YAHIPBUWeightedSoundRangeB2430@@_N@Z`
(count, range, logical). New: `?bfmeWeightedChoiceB2430@@YAHPBUWeightedSoundRangeB2430@@I_N@Z`
(range, count, logical). Same address-derived file-static helper in
game/GameEngine/Source/Common/Audio/AudioEventRTSWeightedChoice.cpp; the body,
its compiler-private EAX=count / EDX=range / CL=logical convention and its two
generatePlayInfo call sites are unchanged.

BFME 1 target evidence:

- Retail AudioEventRTS::generateFilename 0x000B3970 calls the helper with both
  arguments already in callee-saved registers and sets them up as
  `mov cl,[esi+0x42]; mov eax,ebx; mov edx,edi` (+0xD7..+0xDD). MSVC 7.1 emits
  register-argument moves in its right-to-left argument order, so with
  (count, range, logical) the clean body emits `mov edx,edi; mov eax,ebx`
  (2 bytes off, everything else exact; eleven other spellings of the loop,
  locals, casts and an inline wrapper were byte-identical).
- With (range, count, logical) generateFilename, generatePlayInfo 0x000B3C60
  and the helper 0x000B2430 are all exact in one TU (`./build.sh` scoped).
  generatePlayInfo's call sites are forced either way (the range arrives in EAX
  from the accessor call, so EDX must be written first).

The helper has no external callers (file static); only the gen_asm dump of
0x000B3970, which this change replaces, named the old spelling. Model:
claude-opus-5-5, session 491, 2026-10-30.
