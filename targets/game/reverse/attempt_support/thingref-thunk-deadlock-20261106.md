# ThingRef/Rva0039B450Element: four-door deadlock (2026-11-06)

Repair item: `dir32,0x00448D42,??1ThingRef@@QAE@XZ` ("already recorded as
??1Rva0039B450Element@@QAE@XZ"), referenced once:
`??1Rva0039B560@@UAE@XZ +0x2d` (Rva0039B560Destructor.cpp, member-array
destruction through thunk VA 0x00448D42).

## Established facts (all probe/disasm-verified)

- Thunk `?j_00048d42` (gen row, matched) jumps to body RVA 0x0039B060, the
  matched 35-byte `??1ThingRef@@QAE@XZ` (GettingBuiltBehaviorModuleDataCtorThunk.cpp,
  RefCountedThing-release shape). VA 0x00448D42 is the thunk VA.
- The twin ctor thunk `?j_0003c0ba` jumps to RVA 0x0039B050, a 13-byte
  zeroing body (`mov [eax],0; mov byte [eax+4],0; ret`) with no ledger row;
  disassembly guesses IPEnumeration, unconfirmed.
- The 8-byte `m_words[2]` views (Rva0039B560Destructor, GlobalWeatherSystemConstructor)
  and the 4-byte `RefCountedThing*` view (GettingBuilt) share one dtor body,
  which only reads `[ecx]`.
- The `_pi*CallbackA` items nearby are a different, identity-disputed family;
  left alone.

## Why every door is closed

1. Reference the recorded name (rename TU class to Rva0039B450Element):
   commit hook refuses, descriptive-to-placeholder regression (ThingRef is
   established across deque/_STL/TU views). Reverted.
2. Retire the `??1Rva0039B450Element @ 0x00448D42` record for `??1ThingRef`:
   `dir32_record.py retire` refuses, NEW name not ledger-owned at the thunk
   RVA (no functions.csv row there). Same for the ctor record.
3. Pin `??1ThingRef` at thunk RVA 0x00048D42: `ilt_oracle` CONTRADICTS
   (p 1.1e-3; the twin ctor name too, p 9.1e-4). The grandfathered
   Rva00026AB2Vec12 pin also contradicts today, so no new thunk pin can land.
4. Leave the line: status quo, still 1 gate-debt line. Chosen.

## For the leads

The ledger cannot currently express "body name referenced through its ILT
thunk" when the body name is real: the retire guard wants a row AT the thunk
RVA, the oracle bans pins there, and the naming gate bans the placeholder.
The S3/thunk-name pattern (`?j_*` references, tasks 5-7) works only for
explicit address-taking, not compiler-generated member-dtor pointers.
Either the retire guard learns body-through-thunk (callee_twin proof
already exists in the check), or these member-dtor-thunk lines stay
baselined. Do NOT re-attempt without a rule change; all variants above were
reverted, nothing pushed.
