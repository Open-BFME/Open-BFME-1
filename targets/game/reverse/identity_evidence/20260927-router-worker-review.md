# Review of retained router results, 2026-09-27

No workers were launched during this review. Accepted changes were independently
compiled, checked against retail, and gated with the repository hooks. Rejected
experiments remain in their retained router worktrees; they are not production
source or progress. The previous run had already integrated its approved results.

## Accepted

| RVA | Bytes | Verification |
| --- | ---: | --- |
| 00170200 | 261 | Full vector assignment starts40bytes before the old170228 lift; real body helper ABIs decoded independently; native STLport exact; boundary/name retraction documented separately. |
| 00082050 | 244 | Native map<AsciiString,list<AsciiString>> subscript; canonical string header; typed GameSpyLoginPreferences callers. Added real80410 lower_bound and80950 pair-destructor bindings after independent decoding; existing harvested pins targeted other instantiations. |

These replace465previously dumped bytes and recover40previously unclaimed
bytes. Authored source increases505bytes; total exact coverage increases40.

## Source experiments not accepted

Probe equality excludes relocation operands and cannot establish identities,
callee semantics or lifetime contracts. Sizes and differences below are fresh
parent measurements of the final saved production candidate, not worker scores.

| RVA | Result or blocker |
| --- | --- |
| 000DE2C0 | Native canonical AsciiString vector assignment is212B exact, and scoped gate passes after five helper repairs. Regression hook fails existing757C70 AsciiStringVectorInsert: its old clear binding actually destroys texture handles. Reverted the entire attempted integration; repair the linked identities together before landing. |
| 005671E0 | Worker171B tree copy models the mapped four bytes as POD. Raw7CCC0 invokes StringBase<char> copy twice, for offsets0and4. Its second member is nontrivial. The evidence also incorrectly describes W4 as warning suppression; it is an enum mangling component. Reconstruct the value type and adopt the canonical string header before gating. |
| 0077C000 | Worker289B shape manually redefines STL vector and invokes this->~vector(), then writes members after the object's lifetime ended. Restore a legitimate container clear/deallocation lifetime; prove the element type independently and annotate any thunk routes. |
| 0006A1D0 | Parent308B exact probe. Element copy uses a float head, whereas raw699F0 copies integer bits without x87 operations. Existing curve/time identity and canonical-element ownership remain unresolved; do not duplicate the entire sibling emitter merely to obtain different flags. |
| 00288340 | Parent225B exact probe and scoped gate (seven DIR32 references) after worker removed fake element implementations. All six array callbacks independently decoded: constructors288280/2882B0/2882E0 zero four words; destructors2882A0/2882D0/288300 tail-call887940. The base class/virtual surface still needs canonical-header review; callback-only matching does not settle it. |
| 00605380 | Parent245B exact probe. Candidate still adds derived fields to base ModuleData and calls event+78 volume and owner+10 scale without proof. Review found MaxUpdateRangeCap evidence that contradicts the volume narrative. Retain evidence, repair the derived data view and semantic claims. |
| 002BA040 | Parent190B exact probe. Fabricated interface anchor declarations, unsupported field names and AudioEventRTS(void*) contract remain. Canonical interface and constructor ABI review is incomplete; shape alone is insufficient. |
| 001F3390 | Parent379B exact probe. Worker documents a real112-byte BFME audio-event difference from the100-byte reference. Base virtual interfaces and audio-array callbacks still require full canonical/retail reconciliation before acceptance. |
| 000D4500 |273B versus273B, four non-relocation differences. Candidate tests the entire integer at+C8; retail loads a dword and tests AL. Overridable and Module views also incorrectly include derived storage. |
| 001FCEC0 |506B versus483B; not byte-exact. |
| 008C5360 |270B versus271B,83non-relocation differences and four misaligned relocation sites. |
| 0007DF70 |213B versus231B,142non-relocation differences and ten misaligned relocation sites. |
| 00895510 |304B versus308B,202non-relocation differences and seven misaligned relocation sites. |
| 00882BA0 |351B versus358B,277non-relocation differences and eight misaligned relocation sites. Allocate882960 is still a naked lift, so its433B/zero-relocation equality is not a recovery. |
| 000BDF20 | Saved specialization divides a typed vector pointer difference by3 again: the C++ pointer subtraction already returns the element count. This is a semantic error, irrespective of instruction similarity. |
| 008961E0 | Worker failure left no production change to integrate. |

## Shared blocker: false AsciiString container identity

The clear pin removed experimentally for DE2C0 was ILT1C9B8 ->7578F0.
That body calls ILT30652 ->5CC00 for each element. Raw5CC00 dereferences
a texture handle and releases the object; TextureHandleDestructor.cpp independently
corroborates that contract. Correct AsciiString clear630B0 instead calls
ILTD828 ->5EE90 ->887940 (StringBase<char>::releaseBuffer).

The existing757C70 overflow row relies on the wrong AsciiString spelling.
The hook correctly forced that dependent caller to be rebuilt and caught its
changed target. Do not restore a false semantic pin merely to make DE2C0 land.
Its caller and both helper families need a bounded identity repair together.

## Evidence locations

Local review outputs: build/final-worker-review/*.txt and results.json.
The automatic probe inventory initially selected sibling symbols for MemoryPool
and BoneFX; those two comparisons are invalid and were superseded by explicit
Allocate/Free and BoneFX-constructor probes reported above.
The complete DE2C0 attempted integration is archived locally under
build/final-worker-review/de2c0-blocked/, including its source, raw call-site
notes and patch. Other candidate sources remain in .git/opencode-router/worktrees/;
job-to-worktree mapping is saved in build/router-stop-handoff.json.
