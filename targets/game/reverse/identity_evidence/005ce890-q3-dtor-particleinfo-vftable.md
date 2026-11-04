# 0x005CE890 = ??1ParticleInfo@@UAE@XZ (ParticleInfo virtual destructor)

The 73-byte EH-guarded body at 0x005CE890 is the virtual (member) destructor of
the class ParticleInfo, established by the evidence below. The repoint from the
address-derived placeholder `??1Rva005CE890Object@@QAE@XZ` to the pinned name
`??1ParticleInfo@@UAE@XZ` (one body, one identity; the placeholder would be
retired) is BYTE-VERIFIED but BANKED, not landed: the pre-commit `ilt_guard`
(tools/ilt_oracle.py) contradicts the name -- its link.exe hash bucket is 17855,
~2857 below the slot's window [20712, 20717] -- and it contradicts the whole
ParticleInfo/Particle family, so the real name cannot be committed yet. The
ledger keeps the placeholder. See the handoff at
attempt_support/005ce890-particleinfo-dtor-ilt-blocked.md for the blocker and
how to resume. Same 73-byte extent, same TU.

## Body facts (retail 0x005CE890, 73 bytes)
A `__thiscall` with no stack arguments, wrapped in an SEH frame (`/EHsc`), and
NOT returning `this` in eax -- which is what separates it from a constructor:

- `mov [esi], 0x0110FE78`    // derived vptr (DIR32 site; ParticleInfo vtable)
- `lea ecx, [esi+0x3C]`      // member sub-object at +0x3C
- ehState = 0
- `call` thunk 0x000381E5    // -> member destructor 0x005CE820 (confirmed E9)
- `mov [esi], 0x01073744`    // base vptr (DIR32 site; Q3EhBaseOne vtable)
- SEH epilogue / ret

The derived-vptr store names the vftable the class stamps (0x0110FE78), and the
base-vptr store (0x01073744) is the inlined base destructor.

## Pin / ILT chain
- symbols.csv pin: `??1ParticleInfo@@UAE@XZ,0x00029BF9`.
- ILT slot 0x00029BF9 (VA 0x00429BF9) is a confirmed `E9` thunk routing to the
  body at 0x005CE890.
- `tools/pin_consistency.py --symbol '??1ParticleInfo@@UAE@XZ'` -> consistent.

## Virtuality and name: the ??_G call pattern
The matched scalar-deleting destructor `??_GParticleInfo@@UAEPAXI@Z` (30 bytes,
retail 0x005CF020) routes to the 73-byte body through ILT 0x00029BF9 and then
to `operator delete` (`??3`). A scalar-deleting destructor is only emitted for a
class with a VIRTUAL destructor, and it dispatches to the member destructor
`??1` before freeing. This establishes:
- the class name is ParticleInfo (an established retail name, also proven by the
  matched ctor at 0x005CEFC0 -- see
  identity_evidence/005cefc0-u1zero-ctor-particleinfo-vftable.md -- by
  `?loadPostProcess@ParticleInfo`, and by the name slot returning
  "FXParticleInfo");
- the 73-byte body is the virtual (member) destructor `??1`, not a plain
  non-virtual dtor; and
- the pin's `U` (public-virtual) mangling letter is correct, even though a
  non-virtual `QAE` would compile to the same bytes.

## Vtable / name-slot cluster
0x0110FE78 is a 4-slot vtable (ParticleInfo's); each slot is backed by a matched
committed row:
- slot 0: `??_GParticleInfo@@UAEPAXI@Z` (0x005CF020 via ILT 0x004446F2)
- slot 1: `?loadPostProcess@ParticleInfo@@MAEXXZ` (0x005BD3F0 via ILT 0x0040614F)
- slot 2: `?name@Rva005BDC50Named@@QBEPBDXZ` (0x005BDC50 via ILT 0x00421DAA; the
  literal getter returning "FXParticleInfo")
- slot 3: -> 0x005BDC70
Then a null word, then the adjacent `Particle` class vtable at 0x0110FE8C (slot 0
`??_GParticle@@MAEPAXI@Z` @0x005CF050 via ILT 0x0043F558; matched
`??1Particle@@MAE@XZ` @0x005CE990), then the string pool ("FXParticleInfo" at
VA 0x0110FEA0, "Particle system: could not create render object named '",
"--nullsystem").

## Byte match
With `/EHsc` and the member/base destructor pattern (member at +0x3C, base
vptr 0x01073744), the 73-byte ParticleInfo dtor is byte-identical to retail on
all non-relocated bytes (masked .obj vs retail = MATCH; the mask covers the 28
relocated bytes).

## Mangling
Empirically, `struct ParticleInfo : public Q3EhBaseOne { ...; virtual
~ParticleInfo(); };` mangles to `??1ParticleInfo@@UAE@XZ` (project cl.exe),
matching the pin. The `UAE` vs the macro's `QAE` is the public-virtual vs
public-non-virtual classification letter; it changes the name, not the bytes.

## Vtable-slot honesty note
No retail vtable slot references the 73-byte body or its ILT 0x00429BF9. This is
expected: MSVC x86 does not place the member destructor (`??1`) in a vtable
slot; deletion dispatch goes `delete` -> `??_G` (in the vtable) -> the member
destructor `??1` directly. Confirmed against a probe .obj compiled with the same
shape: the `??_7ParticleInfo@@6B@` vtable contains only the user virtual
`?slot@ParticleInfo@@UAEXXZ` and the virtual-deleting function
`??_EParticleInfo@@UAEPAXI@Z`; `??1ParticleInfo@@UAE@XZ` is in no slot. Identity
therefore rests on the pin + the `??_G` call + the byte match, not on vtable
slot position.
