# Native COFF weak fallback truth: Smudge

This is a verifier classification repair. It changes no game source, header,
ledger row, pin, native identity or authored byte count. The native Smudge repair
was already published as `4931fc71b6121585d18494cd09e546a13fdcb7be`.
This isolated tool checkout started at `0f62c0533a41b9bd43e84ec722ba2b60ea6ff44f`.

## Independently observed native route

The freshly compiled native Smudge object contains storage-class 105
`??_ESmudgeManager@@UAEPAXI@Z`. Its actual auxiliary record uses TagIndex 165
and SEARCH_LIBRARY 2, pointing to the external
`??_GSmudgeManager@@UAEPAXI@Z`. That default is independently defined in
COMDAT section 119 (symbol 331), not inferred from the spelling of either name.
Its independently matched 30-byte body is RVA `0x005D44D0`, reached through
retail ILT `0x00045CAF`.

The native 20-byte vtable at retail VA `0x01110164` has five independently
checked routes: `45CAF -> 5D44D0` (30 bytes), `3D0BE -> 5D37F0` (1 byte),
`2DFAB -> 5D3F90` (163 bytes), `296DB -> 5D3AD0` (1 byte), and
`129D6 -> 5D3AE0` (1 byte). The latter slots use existing canonical native
header declarations. No new semantic callback identity is asserted for the
unrelated one-byte `Rva005D4500Noop`.

## Guarded classification

Only a validated direct SEARCH_LIBRARY auxiliary can authorize fallback. The
actual selected input context must have no primary definition, including
COMMON and the checked payload's newly introduced definitions. The default
must be unique, selected, independently retail-true, owned by a matched ledger
row, and unambiguously land on the retail operand or its independently decoded
ILT. A weak-promoted copy cannot become an independent default for a later
promotion. Missing, malformed, cyclic, unsupported, competing or wrong routes
remain unproven; ordinary relocation thresholds and ownership rules remain.

Census facts retain one immutable COFF snapshot, COMMON definitions and
independent verdicts. They are captured before the selection link and used by
both verdict passes. Full object-byte checks follow the link and precede
acceptance. Status/index serialization is staged privately; object, source,
truth and policy guards run again before any accepted artifacts are replaced.
A mutation rejects acceptance and preserves the previous status, index and
history. Native baseline bytes are checked against the compiler helper's
cached image; dependent native import/ledger route caches are rederived.
Official function rows retain the digest of the file that supplied them and
reject later ledger drift.

`weak_schema=4` carries the complete object inventory and current native/truth
fingerprint. A preview requires all indexed object bytes to remain current and
requires fresh, process-local, independent default-provider proof. The inventory
is bound to its normalized checkout root; each physical object path must remain
inside that checkout and have the recorded object name. The fresh provider must
use that same inventoried path. A copied or relocated index cannot establish
local primary absence by validating unchanged donor objects. Local primary and
competing-default regressions cover both copied root metadata and relabeled
metadata retaining donor paths. Actual selected MAP holders are retained even
when supplied by libraries or the census scaffold outside source facts. A
selected primary suppresses fallback unless the primary and independently
owned default share a positive selected address and the same complete raw
holder provenance. The parser retains full `Lib:Object` origin for weak proof;
a foreign library member cannot impersonate a source object with the same
basename. Repeated conflicting publics are ambiguous. Current-schema receipts
require complete, typed, matching keeper/address/provenance key sets and a
canonical persisted digest including ambiguity. Refresh preserves the digest
and never reseals jointly dropped primary evidence. Old semantic receipts and
serialized preview tokens cannot promote a new weak positive.
The fingerprint covers native EXE bytes, function/symbol/DIR32/data ledgers and
the participating verifier helpers. Relevant tool policy paths are census
inputs. Existing ordinary historical preview remains readable.

## Measurements and limits

The final focused suite passes **165 tests**: existing census/check/currency/data
controls plus actual auxiliary fixtures, both reproduced freshness regressions,
complete-context and cross-checkout drift, transitive proof reuse, truth drift, cached-baseline
mismatch and pre-acceptance/serialization mutation rejection.
The fresh official Smudge source gate passes **56/56 functions**. Actual native
DLL linking succeeds with all five slots checked and no fabricated unrelated
stubs; ten missing or unrelated-provider controls fail with exit 96.
The actual-object classifier changes the native table from `unknown` to
`retail` under the explicitly supplied complete single-object native context;
corrupted and missing native defaults remain `unknown`. An actual linked
negative fixture defines the primary using an unrelated real callback body:
link.exe selects that primary over the valid default (exit 0), and the verifier
correctly leaves the table `unknown`, including when source facts deliberately
omit the external primary provider and the actual MAP is its only witness.
The genuine native alias remains positive with the exact same MAP holder,
address and raw origin as its default. This is a scoped
fixture/context proof, not a current whole-image census.

The old accepted `5d21e9aecc` index remains unchanged. Earlier `0 -> 2187`
own-source-byte historical preview was conditional on that old context; it is
not claimed as a present whole-image gain. The new guard refuses weak promotion
from that historical context without a complete current inventory. This patch
adds **0 authored bytes, 0 headline matched bytes, and 0 measured newly linked
whole-image bytes**.

Proof logs and byte identities are in the isolated checkout's
`build/weak_fallback/proof_manifest.json`, including the native DLL/map, current
actual-object controls, final test transcript and scoped gate. Negative fixture
COFF edits are confined to ignored scratch and never become production symbols.
