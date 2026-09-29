# 0x005C3630 identity evidence

## What the body is

Retail 0x005C3630-0x005C3695, 104 bytes, `ret 8`. Decoded:

```
005c3630  mov  eax, ecx            ; this
005c3632  mov  ecx, [eax+0x1c0]    ; receiver, stays in ECX for the thiscall
005c3638  xor  edx, edx
005c363a  cmp  ecx, edx
005c363c  push esi
005c363d  je   0x5c3688            ; -> zero-return tail
005c363f  mov  esi, [eax+0x1c4]    ; the +0x1C4 pointer
005c3645  cmp  esi, edx
005c3647  je   0x5c3688
005c3649  cmp  esi, edx            ; redundant re-test, deliberately kept
005c364b  je   0x5c3650
005c364d  lea  edx, [esi+0x18]     ; the +0x18 slot address
005c3650  mov  esi, [esp+8]        ; hidden sret pointer, reused as the `out` arg
005c3654  push edx
005c3655  mov  edx, [0x12ed5c8]    ; GlobalData
005c365b  fld  dword [edx+0xab4]
005c3661  push ecx                 ; scratch argument slot, overwritten by the fstp
005c3662  fadd dword [0x1075334]
005c3668  add  eax, 0x134
005c366d  fmul dword [0x107533c]
005c3673  fstp dword [esp]
005c3676  push eax                ; this+0x134, the factors Coord3D
005c3677  mov  eax, [esp+0x18]
005c367b  push eax
005c367c  push esi                ; the sret pointer, as the callee's first arg
005c367d  call 0x005fac90
005c3682  mov  eax, esi
005c3684  pop  esi
005c3685  ret  8
005c3688  mov  eax, [esp+8]
005c368c  mov  [eax], edx          ; zero tail: three dword stores of the zero reg
005c368e  mov  [eax+4], edx
005c3691  mov  [eax+8], edx
005c3694  pop  esi
005c3695  ret  8
```

## The class and member names are proven by a matched caller

The only call site is `0x005D0530 +0xA2` (ILT 0x0000C2BB), inside the
**matched** body `?generateParticleInfo@ParticleSystem@@IAEPAVParticleInfo@@HH@Z`
at 0x005D0530. That body's own matched source is
`game/GameEngine/Source/GameClient/System/ParticleSystem_generateParticleInfo_BFME.cpp`,
and it declares and calls the member as:

```cpp
Coord3D computeParticleVelocity(const Coord3D *pos);   ///< 0x005C3630
...
info.m_vel = computeParticleVelocity(&info.m_pos);
```

The caller pushes an sret slot and `&info.m_pos`, matching the body's
`mov esi,[esp+8]` forwarding and its `ret 8`. A matched caller naming the
symbol is the strongest identity evidence available here, so the real class
and member names are used. AGENTS.md: "A matched caller naming the symbol is
the strongest evidence."

The Zero Hour twin corroborates the name and the one argument:
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/.../ParticleSys.cpp:1395`
`const Coord3D *ParticleSystem::computeParticleVelocity( const Coord3D *pos )`,
called at line 1749 as `info.m_vel = *computeParticleVelocity( &info.m_pos );`.

## The pin's `I` (virtual) qualifier is unproven and is NOT used

`targets/game/reverse/symbols.csv` pins
`?computeParticleVelocity@ParticleSystem@@IAE?AUCoord3D@@PBU2@@Z` at this
address. The leading `I` asserts the member is **virtual**. Nothing proves
that, and the landed name drops it:

* The one call site is a direct `call` through an ILT thunk, not a vtable
  slot load. A virtual call would load the table and index a slot.
* `python3 tools/vtable_lookup.py --target 0x005C3630` finds no installed
  table reaching this body within the slot cap. That does not prove the
  member is non-virtual, but it leaves the `I` unsupported.
* The matched caller's own source declares the member in a `protected:`
  block of a class with no vtable, as an ordinary non-virtual method.

MSVC 7.1 mangles the landed definition
`?computeParticleVelocity@ParticleSystem@@QAE?AUCoord3D@@PBU2@@Z`
(`Q` = public member, `A` = __thiscall, `E` = not const). Per AGENTS.md a
pin is a candidate and "a wrong pin still matches", so the unsupported `I`
is retired in favour of the name the evidence supports. The
`computeParticlePosition` pin at 0x005C36C0 carries the same unproven `I`
and has the same story; that body is landed under an address-derived name.

## The callee

The single call target 0x00008814 is a 5-byte ILT thunk that jumps to
0x005FAC90, the **matched** body
`?scale@Rva005FAC90Owner@@QAEXPAUCoord3D@@PAXPBU2@M1@Z`
(`game/GameEngine/Source/Common/Rva005FAC90Scale.cpp`), a thiscall taking
`(Coord3D *out, void *context, const Coord3D *factors, float amount,
void *extra)`. Retail pushes the sret pointer, the forwarded `pos`, the
this+0x134 Coord3D, the x87 amount and the +0x18 slot address in exactly that
order. Nothing about the callee's identity is open.

## The one spelling for 0x005FAC90: the call-site ABI is pinned at the ILT

A session was asked to pick ONE spelling for 0x005FAC90, because this caller
emits the call in a struct-return (sret) form while the matched row at
0x005FAC90 is `void` + an explicit out pointer. Both were measured.

**Option (a), call the existing `scale()` spelling: refuted.** Declaring the
callee `void scale(Coord3D *out, ...)` and returning a local emits 147 bytes
against retail's 104. The documented lever from `docs/shape_levers.md`
("A float pair written through an out pointer: return it by value" -- give the
result type a field-wise copy constructor) does not rescue it either: the same
spelling with that copy constructor is still 147. MSVC materialises a local and
copies it into the return slot, which is precisely the code retail does not
have.

**Option (b), re-spell 0x005FAC90 itself to the sret form: refuted.** The two
views are indistinguishable from the callee's own bytes -- its stack layout and
its `ret 0x14` are identical either way -- so the re-spelling has to be tested
against the callee's 78 bytes. Three sret bodies (named local field-wise; a
3-arg constructor return; a named local with separate `float` temporaries)
measure 101, 100 and 102 bytes. The `void` + out-pointer body is the only
spelling that reproduces 78/78, so the matched row is correct as it stands and
must not be re-spelled. Re-spelling it would also have had to update every
matched caller, and `python3 tools/callers_of.py 0x005FAC90` reports none.

**What is actually landed, and why it is not a second name.** The sret form is
a property of the CALL SITE's ABI view, not of the callee's identity, so it is
pinned where the call site is: at the ILT thunk 0x00008814, in a row of its
own,

    ?rva005FAC90@Rva005FAC90Owner@@QAE?AUCoord3D@@PAXPBU2@M0@Z,0x00008814

That is the shape the landed sibling 0x005C36C0 already uses for its callee
0x005FAE40 (`?rva005FAE40@Rva005FAE40Receiver@@...`, pinned at 0x0002F4AA).
`python3 tools/pin_consistency.py` judges both rows `consistent` and resolves
0x00008814 -> 0x005FAC90, `extent=78 (matched)`, owned by the single
`?scale@Rva005FAC90Owner@@...` row. One name per body is intact: 0x005FAC90
keeps exactly its one real identity, and the sret spelling is a distinct,
address-keyed, ILT-addressed row rather than a second claim on the body.

## Conversion notes

See the header comment of
`game/GameEngine/Source/GameClient/System/ParticleSystemComputeParticleVelocity.cpp`.
The load-bearing result: the +0x18 slot helper takes the pointer **by
reference**. Every by-value spelling folds retail's redundant second null
test; the by-reference one does not, and all 104 bytes match.

Landed 2026-09-29 as
`?computeParticleVelocity@ParticleSystem@@IAE?AUCoord3D@@PBU2@@Z` over
`game/GameEngine/Source/GameClient/System/ParticleSystemComputeParticleVelocity.cpp`,
replacing the `game/gen_asm/d_005b3e30.asm` scaffold row at the same 104-byte
extent.
