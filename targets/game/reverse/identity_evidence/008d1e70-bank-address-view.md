# 0x008D1E70: remove an unwitnessed bank member identity

## What is being corrected

The historical attempt `targets/game/reverse/attempts/0x008d1e70.cpp`
uses `Rva008D1E70Node::atLevel(int)`. Its own opening comment explicitly says
"Address-derived" and describes offsets `m_4c` and `m_8`. The two outcome
rows are duplicate partial attempts from 2026-09-06, not published named
retail source. Their evidence describes chain traversal and a register/branch
mismatch; neither cites an EA declaration, vtable owner, named caller or
upstream member called `atLevel`.

Thus the bank itself refutes treating `atLevel` as an established **native
identity**. It was the attempt author's descriptive spelling for inferred
behavior. This correction does not claim that no original member could have
that spelling; its original spelling remains unknown. It removes the unsupported
identity claim instead of substituting another plausible member name. The
address-derived owner remains `Rva008D1E70Node`, and the method now carries
the exact independently proven retail address as `rva008D1E70`.

## Independent checks

- `python3 tools/callers_of.py 0x008D1E70` reports no named caller reaching the
  body directly. No such caller supplies an independent `atLevel` identity.
- Narrow searches for `atLevel` and `008D1E70` in `symbols.csv`, `exports.csv`
  and the two game Apt source directories find only this newly recovered
  address-view source; no pin/export identifies that member.
- `name_oracle.py --class Rva008D1E70Node --offset 0x4C` exits2: no witnessed
  native owner layout. Nearby count-links and contains recoveries use their
  own separate address views, so adjacency supplies no shared owner identity.
- Retail has INT3 padding through `0x008D1E6F`; entry is `0x008D1E70`.
  It loads `[ECX+0x4C]`, counts successive links, reads a signed stack word,
  and returns `[selected_pointer+8]` or all-ones. Both exits use `RET4`.
  The final return ends at `0x008D1EAD`; three INT3 bytes separate the next
  body at `0x008D1EB0`. These operations prove an address and physical ABI,
  not an original source-level method name, owner, declared types or lifetime.

Selected retail instructions (RVAs, independently decoded):

```text
008D1E70 mov eax,[ecx+4c]
008D1E73 xor edx,edx
008D1E80 mov eax,[eax+4c]
008D1E83 inc edx
008D1E88 push esi
008D1E89 mov esi,[esp+8]
008D1E8D cmp esi,edx
008D1E91 or eax,ffffffff
008D1E95 ret 4
008D1E98 cmp edx,esi
008D1E9A mov eax,ecx
008D1E9E sub edx,esi
008D1EA0 dec edx
008D1EA1 mov eax,[eax+4c]
008D1EA6 mov eax,[eax+8]
008D1EAA ret 4
008D1EAD int3
008D1EB0 next independent body
```

## Exact snapshot scope and byte evidence

The single correction entry covers only the removed bank snapshot and the
new source snapshot, and only `atLevel` -> `rva008D1E70`:

- Before SHA-256: `ed9768231381929596524ab96afce96987bebdbed5475196901e89b46e4ca4e1`
- After SHA-256: `8a7aa2553a111982512ff75d2573589aa255c40c4e0a3cb1e32143b69f2b1257`

The old bank compiles to60 bytes against61 retail bytes. Merging the final
field-load tail and decrementing the existing depth before following each
link recovers all61 bytes in ordinary C++, with zero relocations. Official
`add_match.py` strict source gate passed1/1; affected original dump passed7/7.
The source remains explicitly a borrowed address view with no native owner,
declared field/return types, lifetime or construction claim. No semantic
renaming of another body, header, pin or generated source is involved.

This is the snapshot-specific correction mechanism documented in
`docs/naming_evidence.md`, not a naming baseline change or reusable exemption.
