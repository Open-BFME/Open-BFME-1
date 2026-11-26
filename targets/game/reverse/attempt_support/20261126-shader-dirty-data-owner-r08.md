# Existing ShaderDirty byte: data-owner-only admission

Baseline283d0922b3a28474d38b5a02d8bf97ecde2384ff. This task admits exactly
one already emitted datum. SourceTask0/DataOwnerTask1; SourceCPP and header
remain byte-identical. No new global, function, body, initializer, emitted
storage, alias, pin, flag, access change, helper or consumer convergence.

Actual owner is `?ShaderDirty@ShaderClass@@1_NA` in
game/Libraries/Source/WWVegas/WW3D2/shader.cpp102:
`bool ShaderClass::ShaderDirty=true;`. shader.h473 declares the protected
static bool; its existing public Invalidate at356 writes true. The ordinary
current COFF defines one EXTERNAL strong symbol, section3/value0/type0, with
initial byte01 in writable data. Original VA012D6DFC/RVA00ED6DFC also holds01.
No current data row overlaps this byte. Allocation padding is not treated as
the bool size: the normal compiler sizeof/derived protected scope must prove1.

Independent original access evidence: complete Invert_Backface_Culling
RVA00910DF0 writes one byte at+10 (`c605fc6d2d0101` at00910DF8). Complete Apply
RVA00911020 reads the same byte at+24 (`8a0dfc6d2d01` at00911036), writes zero
at+88 (`c605fc6d2d0100` at00911076), and writes one at+2177
(`c605fc6d2d0101` at0091189F). Full body hashes, exact operands, current
Source/header/object hashes and actual typed definitions are frozen privately.
This establishes the one-byte shader-state role without inferring it merely
from an adjacent constant or copying a donor address.

Mandatory BFME2 reference pass: readonly historical donor
e2e99959950e6eebfe1ced5663aa05de320afc52,
Code/Libraries/Source/WWVegas/WW3D2/ShaderClassApply.cpp507/550/563/1132 and
ShaderClass.h305/342. The actual post-refactor provider is ShaderClassApply,
not old shader.cpp or a missing shader.h. Its existing bool/init/public API
support this role. BFME1 original byte and operations establish the BFME1 VA;
no donor offset, header, layout, aliases or compiler profile are imported.

Whole existing owning TU:22 matched function rows and5 retained data rows.
The normal unchanged control passes22/22,5 data,68 DIR32,56 literals plus one
empty reference,one float constant and no baselined body findings. Existing
170 runtime nodes,832 FPO bytes,89 numeric locals,2 SafeSEH entries and all
COFF metadata are retained. Entire header/Source/dependency sidecar bytes stay
identical. The native data frontdoor normally recompiles the unchanged owner:
both COFFs are37230 bytes, with only actual IMAGE_FILE_HEADER.TimeDateStamp
bytes4..7 changed (1794832159->1795659181). EVERY other37226 bytes, including
CV, all symbols, section auxiliaries, runtime graph, EH and FPO, is identical.
The initial overbroad raw-identity assertion is preserved as a refusal; this
one exact metadata field is reported, not hidden by a generic filter. No
Source/profile/gate retry or compiler-context variation was used.

Before-link legacy42237 preview remains0->0 (345.5s), with old Flag0133F42F,
Set_DX8_Texture_Stage_State duplicate/wrong-copy debt and six selection-currency
UNKNOWN names. One new data row does not establish a current selection census,
full-image link, startup, runtime, performance or crash improvement.

Old34-TU/free/public2-name ShaderDirty convergence and retirement are explicitly
out of scope. All existing DIR32/symbol/hatch/function metadata remains exact;
only the sole native add_data_match writer appends the verified1B row.
Actual ordinary admission passed: original byte01, zero target relocations,
sizeof(::ShaderClass::ShaderDirty)=1 under the existing build profile via its
normal protected derived access scope (allocation extent4 includes padding).
Normal post-admission control passes22/22,6 data,68 DIR32 and unchanged body,
literal and constant checks. No Source/Function task or allocation4B credit.
Actual after-link is also0->0 (343.0s;own filtered bytes4504), with exactly
the same old unresolved/duplicate/COMDAT/selection-UNKNOWN findings as before.
This does not claim LINKED gain. Independent review confirms every raw byte
outside the exact timestamp, all170 runtime nodes,89 locals,2 SafeSEH and832
FPO unchanged. It also confirms no timestamp-sensitive NEWEST(7) COMDAT:
the actual selections are ANY(2)x101, ASSOCIATIVE(5)x56 and NODUPLICATES(1)x9.
This is evidence for these exact objects, never a generic timestamp allowance.
Normal commit/publication hooks and fenced claim cleanup remain required.

Private evidence root:
diagnostics/ten-rounds-20261125-2054/bfme1/r08. Compact receipt hashes will bind
the actual ordinary admission, complete object proof, independent review and
before/after logs. This is one positive data-coverage task, not source conversion.
