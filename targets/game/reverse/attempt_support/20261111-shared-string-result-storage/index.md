# Explicit result storage reaches exact consumer bytes

Follow-up to [the ABI harness](../20261110-shared-string-return-storage/index.md).

## Evidence

BFME 1 baseline and provider evidence remain unchanged: producer 0x361960
returns its four-byte narrow-string result in caller storage (ECX producer,
stack output pointer, EAX output pointer, RET4). Both consumers call it through
ILT 0x1897B, release directly at 0x887940 on normal paths and unwind through
ILT 0xD828. The canonical header supplies the witnessed ushort-length layout.
The BFME 2 reference at 76f0baefa6f285d54bc1ca922397674312a5913f was reviewed;
no donor implementation was imported. The prior suppression recipe does not
resolve the return-object cleanup lifetime.

## New measured progress

| Variant | Result |
| --- | --- |
| Explicit-storage constructor, declaration-only canonical destructor | Both parents have identical instruction bytes, but their two normal-path calls go to ILT D828 instead of releaseBuffer. |
| Inline canonical destructor using direct release | Both parents pass scoped byte and relocation verification: 315 + 321 bytes. |
| Canonical AsciiString base with normal default initialization | Fails both parents: extra initialization changes instruction offsets. |
| Raw result storage, canonical header comparison and explicit AsciiString destruction | Both parents pass scoped verification, including empty-string relocations and all direct calls. |

The two linked diagnostic sources reproduce the last variant with MSVC 7.1,
/O2 /GR- /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc and STLport, using the normal
BFME 1 build context. They are diagnostic evidence, not production source.
The current diagnostic storage is char-aligned; an adoptable implementation
must preserve the native pointer alignment as well as its four-byte size.

## Remaining prerequisites

The exact variant's BFMERetailAsciiString storage view is not the canonical
AsciiString-derived C++ view used by the cleanup provider. Reconcile the
class and object lifetime contract before landing it. Including the canonical
header avoids another private StringBase declaration, but does not by itself
prove this manually managed result view is a valid shared class definition.

The current link preview remains UNKNOWN in the cold worktree: 22,806 changed
or new ledger objects are not available. It also reports a duplicate
BFMERetailAsciiString destructor against the existing strong provider, plus a
constructor COMDAT disagreement in one consumer. These must be resolved with
provider/consumer verification; exact parent bytes alone do not close the task.
No linked-byte credit is claimed. No pin, baseline, hatch or ledger identity
was changed. Both production sources were restored to their starting versions.

Do not repeat the return-PMF/converting-temporary trials already refuted in
the earlier note. The useful next step is an ABI-safe explicit-storage view
whose cleanup uses the proved provider without competing standalone emission.

Time approximately 12 minutes; model gpt-6.1-sol. Boundary: existing matched
315B and 321B parent extents. Blocker: shared class/result lifetime and
strong-versus-COMDAT destructor emission.
