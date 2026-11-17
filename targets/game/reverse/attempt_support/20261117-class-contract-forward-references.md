# Class-contract inspection: forward references are not layout votes

At input `f85160db0383f60ba060ec2324fbed22e7001bcd`, the native
`class_contract.py --class NAME --sample 12 --jobs 14` inspection raises
`KeyError: 'size'` for both ParticleSystemTemplate and VideoBuffer. This resolves
the tool prerequisite recorded in `20261117-native-contract-size-keyerror.md`;
it is not a game crash or a byte-match repair.

`class_layouts.CodeView.classes()` deliberately reports an unresolved forward
reference as `{"fwd": true}`. It has no size, fields, bases or virtual-slot
evidence. `class_contract.decide()` previously admitted it to the complete-view
vote simply because it had no `error` entry. Both the size counter and the other
layout decisions must receive only actual definitions. Exclude `fwd` records
alongside errors; do not invent size zero or borrow a different source's layout.
The existing `view_errors` count includes these unavailable layout views.

## Reference review

BFME 2 reference revision `0630f0ef47d0a818bb2e97583b43cfb1ecd35491`:
`tools/class_contract.py`, `layout_error`, `aggregate` and `decide`; commit
`a1959ef1f21be36ff286c4fcf3c70af7a66d5ff9`. Its refusal propagation supports
keeping invalid layout evidence out of votes. That revision does not itself
exclude a top-level forward-only record in `decide`. The narrow BFME 1 fix is
established by its own CodeView reader, reproduced exceptions and regression
tests. No donor layouts, names, retail addresses or broader inference rules
are imported.

## Validation

Before the fix, the new test file has four failures and two passes. Afterwards
all six pass; 51 related class/layout/header-adoption tests pass together.
Cases include a real forward-reference record without a size, a forward-only
record carrying misleading layout attributes, all-forward inputs, conflicting
complete sizes, normal complete input and a failed compile. All-forward or
conflicting complete evidence still produces a queued size question and a
nonzero CLI result; no acceptance condition is relaxed.

The same twelve-source samples were inspected before and after the change:

| Class | Complete views after | Unavailable after | Forward-only | Open questions after |
| --- | ---: | ---: | ---: | ---: |
| ParticleSystemTemplate | 6 | 6 | 1 | 0 |
| VideoBuffer | 11 | 1 | 1 | 7 |
| Coord3D | 12 | 0 | 0 | 0 |
| Vector3 | 12 | 0 | 0 | 0 |
| Thing | 12 | 0 | 0 | 8 |

The latter three complete contract objects are unchanged, including Thing's
eight questions. The first two now return normal inspection results instead of
exceptions. Their sampled private views are not proof of the full retail ABI;
in particular the reported partial-view sizes do not establish retail object
sizes. No contract was frozen, header changed, source adopted or runtime object
modified by this tool fix. Row/relocation/byte/link verification remains required
for any subsequent adoption. No linked-byte, gameplay or memory-fix gain is claimed.
