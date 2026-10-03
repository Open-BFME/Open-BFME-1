# ParticleEmitterDefClass::Read_Extra_Info returns bool

The old enum-returning26B row cuts MOV [EDX+14],ECX at98C9B8. The actual
body is67B, endingRET4 at98C9E0, followed byINT3. Independent direct retail
and Ghidra function creation agree on this span.

Retail zeroes40 bytes at receiver+1E0, calls ChunkLoadClass::Read at9E15C0
with that address and size40, then sets AL to1 if EAX==40 and0 otherwise.
Upper EAX remains from Read; this positively refutes the enum return ABI.

The independently matched native caller Load_W3D (98C1D0/268B) explicitly
calls Read_Extra_Info in its W3D_CHUNK_EMITTER_EXTRA_INFO arm. Its actual
instruction at98C2A5 calls vtable slot56 (+E0), then98C2AB copies AL toBL;
the loop tests BL at98C250. Vtable VA0113F908 slot56 (VA0113F9E8) contains
VA00D8C9A0 directly. This is the table whose independently aligned accessor
family is documented in particle-emitter-def-vtable.md (that old note writes
the table RVA00D3F908). No ILT indirection or inferred slot shift is needed.
The GeneralsMD part_ldr.cpp/.h twin supplies the method/member identity, but
BFME's byte return and true-success value come from retail and its caller.

Reuse the existing bool-ABI caller TU rather than redeclaring another owner.
It already declares the correct protected virtual bool Read_Extra_Info.
Extend only its local storage view through m_ExtraInfo at1E0; the canonical
W3dEmitterExtraInfoStruct from w3d_file.h is40B. name_oracle has no BFME
witness for this owner; its ZH1E0 offset is a hint independently corroborated
by the function's LEA. Remove the wrong enum definition from part_ldr.cpp,
retaining all other rows. Both source files must pass their normal strict
gates; the original caller must still match all268 bytes.
