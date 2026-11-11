# Canonical name-VSF cleanup reference

Bounded startup consumer handoff approved by parent: only the stale declaration
and use in Rva00C6GapCallbacks.cpp change. All8 existing rows retain their
identities. No provider/header/global/alias/pin or layout change.

Native cleanup C6FC60 (10B) loads ECX=VA012ED4EC and tail-jumps through the
existing AsciiString destructor route. Its dynamic initializer C6A8F0 (22B)
constructs that same location and registers this callback. The existing recorded
primary is `_g_bfmeNameVSF` at012ED4EC. The consumer's C++-linkage opaque name
had no provider and the DIR32 checker correctly rejected it.

Existing Rva012ED4ECGlobal.cpp owns exactly one4-byte .bss `_g_bfmeNameVSF`;
its class default construction and native initializer establish the value and
lifetime. Native RVA00EED4EC contains00000000, matching static zero-initialization.
This datum has a recorded DIR32 owner, NOT a formal data_rows.csv entry. No
new data row is claimed or required for this bounded reference correction.
Existing BfmeConv1575.cpp and ConnectionManagerAttachPlayers.cpp already use
the canonical extern-C name and remain unchanged.

Paired proof (`build/startup-global-proof.py/.json`) preserves all32 nondebug
sections: bytes, flags, definitions and normalized relocations are identical
except the expected undefined reference change
`?g_rva012ED4EC@@3VAsciiString@@A` -> `_g_bfmeNameVSF`. No definition is removed
(the stale variable was extern only), no initializer/COMDAT is added/removed,
and no other undefined symbol changes. Source/objects and proof retained under
build/startup-global-before and build/startup-global-*.

Normal4-source baseline:11/11 functions but stale-global DIR32 FAIL1.
Repaired4-source provider/all-current-consumer gate:11/11 functions,18 DIR32
references, no unverified/skipped refs or baselined findings. These include
all8 cleanup-file rows plus the existing initializer and2 other consumers.
No actual linked-byte gain/census closure is claimed.

BFME 1 input832811202e; native retail SHA256
1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.
This repair follows the existing BFME 1 recorded owner and independently
matched native initializer/callback, not a donor name or address. Compiler
MSVC7.1 13.10.3077, original /O2 /MD context and private approved WoW64 prefix,
WINEARCH=win64, BUILD_POOL=2. Parent review required before publication.
