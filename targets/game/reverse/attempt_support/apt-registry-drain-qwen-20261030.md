# Apt registry-drain caller binding

Base: c27b8371d (2026-10-30). Primary claim 0x008CA890, followed by the
compatible 0x008CCED0, 0x00897360 and 0x008CD130 caller sweep. This repairs
callee binding in existing matched source; it recovers no additional body.

## Native identity and ABI

The full 141-byte GotoFrame extent ends at 0x008CA91D. Its JMP at 0x008CA917
reaches the existing 62-byte `Rva00899560Pool::rva008A30C0` provider. ECX was
loaded from VA 0x01337810, the existing data-row owner
`g_rva01337810GcRoots`; no argument is pushed or receiver adjusted.
The provider consumes count+4 and items+8 and returns with plain RET. It drains
registered values through their existing flags and vslot 2. Its address-derived
owner is retained; this does not establish an original EA class name.

Complete native decodes also confirm the same receiver and no-argument call
at 0x008CD034 (runner), 0x0089736A and 0x00897446 (cleanup), and 0x008CD1D9
(named dispatch). Existing callee inventories identify the provider directly.
Replace only the stale `Rva8CD130IdleHook::run` binding, retaining the existing
global, inline field views, compiler flags and other calls. No allocation,
replacement global, alias, pin, header or ledger row is introduced.

## BFME 2 donor review

Reviewed donor b5a7b8290a0c4c20b03a3664609d434904e228eb, including
`Code/Libraries/Source/Apt/AptValue/AptValueVector.cpp` and
`AptValueVectorReleaseBFME2.cpp`, relevant consumers and existing ownership.
The latter's `ReleaseValues` supports the structural count/array/refcount/drain
relationship. Its target-specific assertions, 16-byte vector with high-water
storage and proven BFME 2 semantic names are not BFME 1 identity/layout proof.
No donor layout or semantic rename is imported. The BFME 1 native target and
existing global/provider rows establish this repair independently.

## Verification and limits

Normal five-source gate passes 7/7 rows, 26 DIR32 references and one string.
The six caller/helper rows retain all 1,259 raw bytes. Exactly five REL32
referents change from the old run spelling to the existing pool drain;
all other relocation records are identical. The unchanged provider's 62 bytes
also pass. Defined-unmatched preflight passes (existing inline-only adapters
retain their prior absent-from-retail annotations).

Paired frozen-index preview at 1d5131d3f1 (2026-10-30 12:21) changes GotoFrame
0 -> 141 authored bytes and retains the provider's 62: 62 -> 203 for that pair.
The three additional units lose this unresolved name, but retain their other
existing createString/global/callback blockers, so no extra linked-byte gain is
claimed. Ordinary current-object preview is UNKNOWN: 22,727 current ledger
objects are unavailable for selection verification. These previews are not a
new census or proof of current full-image closure.

The sweep also found the same old spelling in Rva0089BBF0InitGlobals.cpp.
Its unchanged control passes body bytes but fails DIR32 identity checks for
`d_008c66a0` and `d_008c6ad0` at +0x3D6/+0x5AC. That file is untouched and
its claim released. Revisit with an independently supported identity repair;
do not repeat the unchanged control or add aliases to pass it.

## Local helper pilot

Qwen2.5-Coder-7B-Instruct GGUF Q4_K_M, revision
13fb94bfda8c8cf22497dc57b78f391a9acb426a, was a suggestion/review helper.
Its initial suggestion replaced the real pool global with a newly allocated
idle-hook object. It was rejected without application. The host established
and wrote the minimal repair; a subsequent constrained review correctly
described the preserved global/receiver and the need for separate link proof.
This is neither independent naming evidence nor proof of autonomous repair.

Reproducible local request/result receipts are outside Git under
`W:/OpenBFME/diagnostics/qwen-helper-20261030-191640`; scoped gate, native
decode, COFF comparisons and before/after previews are under
`build/qwen-helper-20261030-191640`. No benchmark claims a development-time saving.
