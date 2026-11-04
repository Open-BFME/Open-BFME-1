# dir32 0x004046F6 ??1Rva006967A0: identity proven, unlandable (ilt_guard contradiction)

## Debt
`dir32,0x004046F6,??1Rva006967A0@@QAE@XZ,the name encodes 0x006967A0 but retail reads 0x004046F6`
in `MilesAudioManagerConstructor.cpp` (m_ad0[3] ehvec dtor push reads `0x004046F6`).

## Proven (retail bytes, build tooling)
- Retail ctor `??0MilesAudioManager` +0x371 pushes `0x004046F6`, +0x376 pushes
  `0x00431EDF`, then count 3 / size 4 / `&m_ad0` / `__ehvec_ctor`: the element
  dtor is reached through ILT thunk `0x46F6` (`e9 75216900` -> `0x00696870`).
- `0x00696870` carries matched `??1PlayingAudioRef@@QAE@XZ` (35B, row 7843,
  `identity_evidence/00696870-playingaudio-return-cleanup.md`, `ILT46F6->696870`).
- Element ctor thunk `0x31EDF` (`e9 bc486600`) reaches `0x006967A0` (9B,
  gen-small `?m@Gen_006967a0`, settles no identity).
- Renaming the TU-local class to the real `PlayingAudioRef` view (same 4-byte
  handle, out-of-line decls, no COMDAT emitted) keeps all 20 rows byte-verified
  (scoped build green; 9 funclet `$L` repins via `eh_state_pins --fix`).

## Why blocked: two gates contradict
- `pin_consistency --check` refuses a placeholder pin at the thunk
  (`??1Rva006967A0 @ 0x46F6`): the reached body already carries the real name.
- `ilt_guard` refuses the real-name pin (`??1PlayingAudioRef @ 0x46F6`,
  `??0PlayingAudioRef @ 0x31EDF`): oracle CONTRADICTED, outside the target's
  hash windows (dtor slots 2813:2957-2960, ctor slots 40082:24251-24261).
- `route=` refused (target carries a different ledger name); `abi-view=`
  inadmissible (thunk below `.text`; ctor body has no matched `??0` row).
- Recording in `dir32_addresses.csv` is refused by the same callee_twin rule.
- Precedent: `??1ParticleInfo 0x005CE890` blocked identically
  (`blocker=identity/identity-window-contradiction`, handoff
  `005ce890-particleinfo-dtor-ilt-blocked.md`).

## Resume
Needs either an ilt_oracle window repair covering these slots, or a sanctioned
exemption for thunk pins whose body identity is ledger-proven. Do not repeat
the pin/route/abi-view/source-rename trials. Sibling line 39
(`??0Rva006967A0 @ 0x00431EDF`) shares the root cause; the ctor body at
`0x006967A0` is a future `??0PlayingAudioRef` recovery (`add_match
--replace-rva` over gen-small `?m@Gen_006967a0`).
