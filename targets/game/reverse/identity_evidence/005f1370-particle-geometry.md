# RVA005F1370 particle geometry, unfinished native reconstruction

GPT-6, 2026-09-27. This is a complete algorithm bank, not a byte-match claim.
The preferred native draft emits4692 bytes against5096 retail bytes. There
are3962 masked positional differences and404 missing bytes; its honest score
is730/5096. Normalized instruction shape0.603 is diagnostic only. The native
frame1A8 differs from retail1D8. No game source, ledger ownership or pin was
changed. The older generated body remains available.

Read-only Ghidra and raw instructions were read from the verified identical
retail executable. Entry005F1370 has a complete SEH prologue. The final RET12
is at005F2739..273B. Seven DWORD switch targets occupy005F273C..2757; INT3
padding begins005F2758. The complete5096-byte extent is sound. The tool's
linear-disassembly warning at+13E7 is the last byte of this table, not a
truncated instruction or missing tail. Ghidra's shorter4973-byte estimate is
not substituted for the proven full extent. ILT0003EDBF jumps to this body.
The method's semantic identity is unproved and remains address-qualified.

## Contracts established independently of the desired byte shape

The receiver holds a ParticleSystem pointer at+4. Repeated null accesses call
the existing native bfmeNullSystemZA005CFF50. The name at system+10 uses the
canonical AsciiString/StringBase representation and the independently matched
005F6B60 owner view. First particle is+A0, next particle+3C. Position+1C and
velocity+10 are consumed as three floats; the bank retains address field
names rather than asserting a new class layout. System+7C equals11 and the
byte+80 controls the supplied field counter. Template type+8 selects seven
shader presets. The related Generals W3DParticleSys source explains this
general pattern but is not the source of the new BFME geometry branch.

All direct callees were inventoried before reconstruction. Particle visibility
is the independently native Particle::isInvisible005C31A0. The optional
float getters005C30A0/005C3120/005C3160 and color pointer005C3180 use existing
address-qualified declarations from Q2OptionalSourceFloats and
S2NullCheckedTailDispatch. The color accessor's existing declaration returns
an EAX-sized integer; the caller treats it as a pointer, preserving that ABI.
BFMEGetWaterTrackTexture0090E910 returns the existing four-byte owning handle.
Its destructor calls native TextureBaseClass::Release_Ref009EB7A0. Assignment
increments the low16 reference bits before releasing the previous texture.

D3DXMatrixRotationZ is the actual statically linked D3DX9 dispatcher. Call
005F17DB targets009FB93B, a six-byte indirect jump through012DBE78, whose
initial target009FB91F is the independently vendored init routine. It takes
an output matrix and float angle with RET8. No invented matrix callee or
replacement pin is added. The bank uses the existing D3DX declaration.

The renderer layout was independently reconstructed in the0090FEE0 lane:
no vptr, four buffer pointers at00/04/08/0C, count10, texture14, shader18,
default Vector4 color1C..28, total2C. Matched constructor0090F650 and buffer
initializer0090F760 are independent witnesses. Here, call005F26EB pushes
count, positions012F6DC8, colors012F6DCC and two null buffers to native
Rva0090F8C0Holder::set. Call005F26FE reloads ECX from012F6D88 and forwards
the first incoming stack argument to0090FEE0, proving its one-slot thiscall
contract. No semantic class name is invented from this association.

## Complete behavior and compiler findings

The body culls each visible particle against the supplied box, constructs
eight vertices as two adjoining quads, optionally rotates them around Z
using velocity, translates by the particle position, then transforms into
view space. It copies eight RGBA values, counting two primitives per
particle, and stops at512 primitives. Empty batches return without texture
work. All seven shader choices, texture lifetime, buffer submission and
final renderer call are retained. The view matrix uses canonical
DX8Wrapper::Get_Transform(D3DTS_VIEW). Existing WWMath owns the x87 sine and
cosine intrinsics; this investigation adds no assembly.

The velocity threshold is read as float0.0001 atVA0109BF40 and the angle
offset as double pi/2 atVA01113588. Culling uses WWMath's bitwise float
absolute value, as retail does; the velocity test uses x87 fabs. The native
StringBase::str definition is visible, avoiding a spurious out-of-line call.
Direct component color copies and a pointer cursor retain the scalar loop
contract. Canonical Matrix4 multiplication, Transform_Vector, separate
vectors versus an eight-vector array, translated temporaries and a distinct
initial empty-list return were measured. None recovered retail's full x87
scheduling and live vector storage. One4860-byte alternative has a somewhat
higher positional score but is not preferred: its culling spelling omits
retail's forced float rounding. The bank keeps the sounder bitwise culling
and direct color-copy source. Do not raise its score to the normalized shape.

Scratch receipts are build/round4-anon5096/{callees.txt,retail.asm,ghidra,
probe01.txt..probe12.txt,bank-probe.txt,bank-audit.txt}. Start from the bank;
the remaining lever is matrix/vector lifetime and x87 scheduling, not missing
geometry branches or speculative callee identities.
