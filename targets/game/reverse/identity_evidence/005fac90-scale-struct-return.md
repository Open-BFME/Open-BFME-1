# 0x005FAC90 Rva005FAC90Owner::scale returns Coord3D by value

Same body and same member name; only the signature spelling changes from
`void scale(Coord3D *out, ...)` to `Coord3D scale(...)`.

## ABI proof

Retail 0x005FAC90 (78 bytes) ends `mov eax,[esp+0x10]` (the first stack
argument), stores the three scaled floats through eax, then
`add esp,0xC; ret 0x14`: the result pointer is live in eax at the return,
which is the MSVC 7.1 struct-return convention. Its only caller,
the matched ParticleSystem::computeParticleVelocity (0x005C3630, via ILT
0x00008814), forwards its own hidden sret pointer as that first argument and
returns eax without a copy, which MSVC only emits for a struct-returning
callee (see ParticleSystemComputeParticleVelocity.cpp).

## Byte proof

`Coord3D Rva005FAC90Owner::scale(void *, const Coord3D *, float, void *)`
returning `Coord3D(x, y, z)` compiles to all 78 retail bytes
(`./build.sh game/GameEngine/Source/Common/Rva005FAC90Scale.cpp`).
The caller previously spelled the same callee `?rva005FAC90@Rva005FAC90Owner`,
a name nothing defined.
