# Handoff: ParticleInfo virtual destructor at 0x005CE890 banked, refused by ilt_guard (2026-11-04)

Gate: the repoint of row 8206 from the placeholder `??1Rva005CE890Object@@QAE@XZ` to
the pinned name `??1ParticleInfo@@UAE@XZ` was executed and byte-verified, then the
commit was refused by the pre-commit `ilt_guard` and fully reverted. The ledger keeps
the placeholder. Banked, not landed (user decision 2026-11-04: bank as false-reject
blocker).

## Proven facts (all verified this session, then reverted)

- The 73-byte EH-guarded body at 0x005CE890 is the virtual (member) destructor of
  ParticleInfo. Body shape (retail, /EHsc SEH frame, __thiscall, no stack args, does
  NOT return this in eax): derived-vptr store 0x0110FE78, `lea ecx,[esi+0x3C]`,
  ehState=0, `call` thunk 0x000381E5 (confirmed E9 -> member destructor 0x005CE820),
  base-vptr store 0x01073744, SEH epilogue/ret.
- The symbols.csv pin `??1ParticleInfo@@UAE@XZ,0x00029BF9` (line 9192) resolves
  through ILT slot 0x00029BF9 (VA 0x00429BF9), a confirmed `E9` jmp to 0x005CE890.
  `tools/pin_consistency.py --symbol` -> consistent.
- Virtuality + the `UAE` mangling letter: the matched scalar-deleting destructor
  `??_GParticleInfo@@UAEPAXI@Z` (30 B, retail 0x005CF020) `call`s ILT 0x00029BF9
  (the 73 B body) at +0x03, tests the deallocate flag, then `call`s operator delete
  `??3` (0x00881EB0) at +0x10 -- the standard virtual-destructor dispatch. Verified
  against the correct file offset (file offset = RVA in this image).
- Vtable cluster: 0x0110FE78 is a 4-slot vtable; slot 0 `??_GParticleInfo` via ILT
  0x004446F2, slot 1 `?loadPostProcess@ParticleInfo` (0x005BD3F0), slot 2 the name
  getter (0x005BDC50, returns "FXParticleInfo"), slot 3 -> 0x005BDC70; then a null
  word and the adjacent `Particle` vtable at 0x0110FE8C; the string pool holds
  "FXParticleInfo". No vtable slot references the 73 B body or its ILT -- expected,
  since MSVC x86 does not place the member destructor in a vtable slot (confirmed
  against a probe .obj: `??_7ParticleInfo@@6B@` holds only `?slot@ParticleInfo@@UAEXXZ`
  and `??_EParticleInfo@@UAEPAXI@Z`).
- Byte match: with `struct ParticleInfo : public Q3EhBaseOne { char m_lead[0x3C-8];
  Q3EhMember005CE820 m_sub; virtual void slot(); virtual ~ParticleInfo(); };` plus an
  empty `~ParticleInfo() {}` in the Q3 TU (replacing the `BFME_EH_DTOR_PADDED(
  Rva005CE890, Q3EhBaseOne, Q3EhMember005CE820, 0x3C )` macro call), the scoped
  build byte-verifies the 73 B body (masked .obj vs retail = MATCH, 28 B mask). The
  probe .obj is at build/pi_test.obj; the hand-written source variant lives only in
  the evidence md, not in game/.
- Full evidence: identity_evidence/005ce890-q3-dtor-particleinfo-vftable.md.

## Why it cannot land

- `ilt_guard` refuses the new row name `??1ParticleInfo@@UAE@XZ` at 0x005CE890:
  `tools/ilt_oracle.py check` returns CONTRADICTED p_false=3.91e-04 -- the name's
  link.exe vhash bucket is 17855, 2857 buckets below the window
  [20712, 20717] of the ILT slot that routes to the body (thunk 0x00029BF9;
  oracle slot index 33380 in ilt_windows.tsv, target 0x005CE890).
- The whole ParticleInfo/Particle family is contradicted the same way: `??_G`
  4.83e-03, `?loadPostProcess` 4.57e-04, `??0Particle` (const ParticleInfo*) 1.96e-04,
  the honest placeholder ctor `??0U1Zero_0110FE78` 1.17e-03, `??1Particle` 1.30e-03,
  `??_GParticle` 1.04e-03. The baseline ilt_contradicted_baseline.txt already holds
  8917 grandfathered keys, is shrink-only, and the guard has no bypass or override;
  bypassing hooks is forbidden.
- `tools/ilt_oracle.py repair` (24288 T1-access tests, 59618-entry class dictionary)
  produced 7420 repairs, none for slot 33380 and no ParticleInfo spelling at all --
  the name is not recoverable to a fitting bucket by any tested decoration.
- This is a documented false-reject class (a right name fails only if a neighbour
  anchor is wrong; a free-text name passing the oracle is never identity evidence
  either way). The pin + the matched `??_G` caller + the byte match make the identity
  strongly supported, but the hard gate stands.

## Resume path

Once the ILT window/anchors for slot 33380 are repaired (ilt_repair-style evidence)
or the name is ILT-verified, re-apply in one commit:
1. In game/GameEngine/Source/Common/Q3GuardedMemberDestructors.cpp, replace the
   `BFME_EH_DTOR_PADDED( Rva005CE890, Q3EhBaseOne, Q3EhMember005CE820, 0x3C )` macro
   call (currently line 87) with the hand-written ParticleInfo struct exactly as
   documented in the evidence md (member at +0x3C, base Q3EhBaseOne, `virtual`
   dtor, `virtual void slot();`, empty body).
2. Repoint: `py -3 tools/add_match.py '??1ParticleInfo@@UAE@XZ' 0x005CE890 73
   game/GameEngine/Source/Common/Q3GuardedMemberDestructors.cpp --replace-rva
   0x005CE890 --correct-identity '??1Rva005CE890Object@@QAE@XZ' --identity-evidence
   targets/game/reverse/identity_evidence/005ce890-q3-dtor-particleinfo-vftable.md
   --model <model>`.
3. Verify `tools/ilt_oracle.py check '??1ParticleInfo@@UAE@XZ' 0x005CE890` returns
   CONSISTENT before committing; otherwise the guard will refuse again.

Do NOT re-probe: the byte match, the ILT chain, the virtuality and the vtable
cluster are settled. model=qwen38-27b-ninfer, t=120min.
