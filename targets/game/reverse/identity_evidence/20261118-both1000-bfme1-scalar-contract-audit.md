# One thousand further scalar-contract operations

Tasks 2582-3581 comprise 1000 grouped alias-contract operations in 1000
consumer files, preserving 465,049 distinct retail-row bytes. Each task
replaces one file's private primitive typedef group with the existing EA/BFME1
contract in Common/ScalarTypes.h. Individual typedefs are not counted as tasks.
These are source-maintenance operations; newly reconstructed function bytes
and newly LINKED coverage added by these operations are not claimed.

The header contains nine identical aliases already present in BFME1's
Precompiled/PreRTS.h and EA GeneralsMD/Lib/BaseType.h. Original provider contexts
remain intact. Primitive spelling is exact: plain char is not treated as signed
char, and int is not treated as unsigned int merely because their sizes match.
No macro, runtime helper, platform widening or guessed semantic type is added.

Every counted file has actual-original-filename ordinary/Z7 controls before
edits, the normal retail byte gate afterwards, and a fresh ordinary object
equal to the normal build object. Whole ordinary inventories retain code,
data, definitions, relocations, raw directives, weak references and aliases.
All original complete class and enum contracts remain identical. Real-header
include traces and opened-input hashes establish the actual inputs. Private
appended pointer-binding/sizeof witnesses retain exact symbols and bodies for
every adopted alias. They are diagnostic code only, never a shipped function.

A negative control proves why ordinary byte identity alone is insufficient:
changing unused Int from int to unsigned int preserves ordinary runtime, while
the exact primitive-binding witness rejects the change. Ten actual-source
control compiles also equal native objects and preserve runtime under Z7.
CPP-included sources are excluded without independent parent/namespace proof.
Failed trials and supporting measurement/reference records are not counted.

|Alias|Consumers whose grouped declarations include it|
|---|---:|
|Bool|637|
|Byte|1|
|Char|9|
|Int|629|
|Real|288|
|Short|3|
|UnsignedByte|84|
|UnsignedInt|385|
|UnsignedShort|100|

At the initial check, new hosted census 44310978336 was still running.
It has an independent runner checkout, so local source-only verification does
not modify its measured snapshot. No newer final LINKED result is presumed.
The local provider preview remains UNKNOWN without a current native index.

The latest completed native full-image measurement precedes this batch. Its input
is `45cda0e209`; its project-wide counters include other contributors.
See [the measurement report](20261118-followup-native-link-census.md). Source
cleanup is not promoted to new authored-byte credit. Missing native dependency
receipts remain UNKNOWN for provider freshness. No verifier, baseline, pin,
manual EH label or alias is changed to force a pass. No full game-start,
memory/leak, crash-fix, 64-bit, multicore or FPS benefit is inferred.

|Cohort|Operations|Detailed evidence|
|---|---:|---|
|137|10|[20261118-round-scalar-contracts-137.md](20261118-round-scalar-contracts-137.md)|
|138|64|[20261118-round-scalar-contracts-138.md](20261118-round-scalar-contracts-138.md)|
|139|64|[20261118-round-scalar-contracts-139.md](20261118-round-scalar-contracts-139.md)|
|140|65|[20261118-round-scalar-contracts-140.md](20261118-round-scalar-contracts-140.md)|
|141|65|[20261118-round-scalar-contracts-141.md](20261118-round-scalar-contracts-141.md)|
|142|63|[20261118-round-scalar-contracts-142.md](20261118-round-scalar-contracts-142.md)|
|143|59|[20261118-round-scalar-contracts-143.md](20261118-round-scalar-contracts-143.md)|
|144|59|[20261118-round-scalar-contracts-144.md](20261118-round-scalar-contracts-144.md)|
|145|53|[20261118-round-scalar-contracts-145.md](20261118-round-scalar-contracts-145.md)|
|146|38|[20261118-round-scalar-contracts-146.md](20261118-round-scalar-contracts-146.md)|
|147|34|[20261118-round-scalar-contracts-147.md](20261118-round-scalar-contracts-147.md)|
|148|29|[20261118-round-scalar-contracts-148.md](20261118-round-scalar-contracts-148.md)|
|149|22|[20261118-round-scalar-contracts-149.md](20261118-round-scalar-contracts-149.md)|
|150|18|[20261118-round-scalar-contracts-150.md](20261118-round-scalar-contracts-150.md)|
|151|14|[20261118-round-scalar-contracts-151.md](20261118-round-scalar-contracts-151.md)|
|152|13|[20261118-round-scalar-contracts-152.md](20261118-round-scalar-contracts-152.md)|
|153|18|[20261118-round-scalar-contracts-153.md](20261118-round-scalar-contracts-153.md)|
|154|65|[20261118-round-scalar-contracts-154.md](20261118-round-scalar-contracts-154.md)|
|155|64|[20261118-round-scalar-contracts-155.md](20261118-round-scalar-contracts-155.md)|
|156|65|[20261118-round-scalar-contracts-156.md](20261118-round-scalar-contracts-156.md)|
|157|65|[20261118-round-scalar-contracts-157.md](20261118-round-scalar-contracts-157.md)|
|158|53|[20261118-round-scalar-contracts-158.md](20261118-round-scalar-contracts-158.md)|

Local complete manifests and compiler evidence are under
W:/OpenBFME/diagnostics/continue-20261116-fivehundred/batch-137 through batch-158.
Session discovery and control evidence: W:\OpenBFME\diagnostics\continue-20261118-both1000\bfme1. The PC stays on.
