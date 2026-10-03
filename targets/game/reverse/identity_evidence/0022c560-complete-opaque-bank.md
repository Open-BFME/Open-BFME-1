# Full opaque draft for 0x0022C560

Retail is 1253 bytes, with final RET8 at 0x0022CA42 and INT3 at
0x0022CA45. Ghidra create/decompile and independent Capstone decoding agree.
Existing identity notes disagree over the concrete owner; neither is silently
chosen. The two ExitInterface tables share ILT0003B674; the draft keeps an
address-qualified receiver with module at this-0x30. The complete retail source
path names SiegeEngineContain.cpp, but is not treated as unique class proof.

The draft covers all three real paths: filter224/count228 ejection with a
normalized displacement of50; special-module ladder deployment using Ladder04,
model-condition word+118 sign-bit clearing, transform/layer17 and AI hunt/idle;
and ordinary deployment with radius, layer-height,20/40 offsets and two-point
exit paths. It includes the qualified base fallback. Native Object/Thing,
Coord3D/Coord2D/Matrix3D and STLport vector declarations are included.
The owner, remaining virtual slot and raw ABI call view keep their addresses.

## Measurements and attempted levers

Initial complete draft:1225B,802 non-relocation differences; setup had been
outlined. Forced inlining of the actual repeated setup body restores the calls
and moves this to1290B/728diff. Direct typed ILT member-pointer calls preserve
file/line argument pushes ahead of the layer lookup: best1282B/743diff versus
retail1253B, quality0.3607, structural similarity0.936. This is not near-exact.

The first+15 frame operand is6c versus64. Listing shows first and second
vector locals using different slots; retail shares them. Scalar first-position
copy matches the retail floating Z load; whole Coord3D copy did not. Native
Coord3D::set, a three-component direction local, nested delta lifetime,
copy-construction versus assignment, mutually exclusive if/else structure,
and a shared forced-inline path helper did not improve the best byte score.
Remaining x87 differences start+106 (50-times pair), and+354 (radius lifetime),
followed by20/40 arithmetic and duplicated cleanup/return tail. No assembly,
volatile accesses or barriers were introduced.

## Remaining promotion requirements

All27 direct targets were inventoried using callees.py before writing. The
bank uses existing ILT spellings and typed single-inheritance call adapters.
No new pins were added. j_00023d49 is not a current ledger thunk spelling:
replace its draft binding with the existing bfmeTwo941F identity before strict
verification. The new body cannot be promoted without a full exact scoped
build and reference checks; masked score cannot validate these adapters.
Canonical Object flags currently use its raw-storage fallback; adopt existing
BitFlags<320> before promotion, retaining witnessed bit95 rather than guessing
its semantic enum name. Preserve the native normalized-coordinate and vector
lifetimes while resolving the stack/x87 shape.
