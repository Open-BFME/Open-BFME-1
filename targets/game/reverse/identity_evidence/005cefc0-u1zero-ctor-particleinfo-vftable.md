# 0x005CEFC0 keeps its address-derived name, aligned to the vftable it stores

`??0U1Zero_005CEFC0@@QAE@XZ` is corrected to `??0U1Zero_0110FE78@@QAE@XZ`: the
class in game/GameEngine/Source/Common/U1ZeroingCtorAndInserters.cpp is renamed
from the body's RVA to the VA of the vftable the body stamps. Same 77B extent,
same TU, byte-verified. This is a placeholder-spelling alignment, not a claim
that the class is ParticleInfo (see the last bullet).

- The 77-byte body (retail 0x005CEFC0) is a constructor returning `this`:
  `mov eax,ecx / xor ecx,ecx`, then zero stores through eax, then a MID-BODY
  vftable store `mov [eax], 0x0110FE78` at +0x2E (a DIR32 operand copied from
  retail), then further zero stores and a bare `ret`. The store at [eax] (the
  derived vptr at +0) names the table this class stamps.
- 0x0110FE78 is ParticleInfo's vftable. Its slot 0 is the ILT stub
  0x004446F2, whose `jmp rel32` reaches 0x005CF020, the matched non-generated
  `??_GParticleInfo@@UAEPAXI@Z`
  (game/GameEngine/Source/GameClient/System/ParticleInfoDeletingDestructor.cpp).
  A class's deleting destructor sits only in that class's own primary vtable
  (the vtable rule in tools/dir32_record_guard.py), and the
  `function_owner_problem(??_7ParticleInfo@@6B@, 0x0110FE78)` check passes
  against the retail table; the table's remaining slots route through ILT
  thunks to matched rows, including 0x005BD3F0
  `?loadPostProcess@ParticleInfo@@MAEXXZ`, and no other class's deleting
  destructor. The two
  placeholder dir32 lines at 0x0110FE78 are retired for `??_7ParticleInfo@@6B@`
  in the same commit; the full gate records it.
- The body's own identity is NOT recovered (the TU's IDENTITY IS NOT RECOVERED
  note). It is not renamed to `??0ParticleInfo@@QAE@XZ`: no matched row of that
  spelling exists (ParticleSys.cpp's 276B ctor is a ZH-view
  present-unmatched phantom that would define a strong duplicate), and the
  vftable store proves the table's identity, not that this 77B zeroing body is
  ParticleInfo's own constructor. The class therefore keeps an address-derived
  placeholder in this file's `U1<shape>_<addr>` family, now named for the
  vftable it stores: `U1Zero_0110FE78`.
