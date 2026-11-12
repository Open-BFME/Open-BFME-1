# BFME 1 DXErr9 Summer 2003 lookup source recovery

## Native identity, ABI and extent (BFME 1 facts)

This is **library-to-source**, not newly discovered executable coverage. The four
existing native identities and complete extents are unchanged:

| Native symbol | BFME 1 RVA | Full section bytes | Reachable instruction bytes | Embedded switch-table bytes |
|---|---:|---:|---:|---:|
| `_DXGetErrorString9A@4` | `0x00AD548E` | 70599 | 46657 | 23942 |
| `_DXGetErrorString9W@4` | `0x00AE6855` | 70612 | 46670 | 23942 |
| `_DXGetErrorDescription9A@4` | `0x00AF7C29` | 10933 | 9086 | 1847 |
| `_DXGetErrorDescription9W@4` | `0x00AFA6DE` | 10933 | 9086 | 1847 |

The original ledger owns these through `inputs/vendor/dxerr9/dxerr9.lib`, member
`obj\i386\dxerr9.obj`; the archive's tracked `PROVENANCE.txt` establishes the
Summer 2003 SDK identity and retail placement. The actual archive SHA256 is
`07f40f6799edceffb1d9532a5a42d1e8177bbf5a60f5e1b0c9975b9c2cfcb1b5`.
The extracted 2299299-byte member SHA256 is
`2ef7a47b374b4c76c5966e02860c9a0f41852eb2babb5684624c0aebdcc48e77`.
Each symbol is the original external symbol at offset zero in its own executable
COFF section; section sizes are exactly the existing ledger extents above.
`ret 4`, one stack HRESULT argument, no calls, and independent ANSI/UTF-16 literal
references establish stdcall ABI and A/W identity. `tools/callees.py` independently
reports zero direct callees for every full extent. No aliases, pins or imports
are added. This family starts **after** the paused D3DX9 region ending
`0x00AD5401`; no D3DX9 row is changed.

The full 163077-byte union contains 111499 reachable instruction bytes and 51578
compiler-generated switch-table bytes. None of these source rows previously
pointed at actual C/C++ source. These counts distinguish code from embedded data;
normal full-extent gates must verify both. There are no alignment gaps between
claimed ranges added to the totals. Complete-domain traversal classifies every
byte as a reachable instruction or a read switch-table byte: zero unclassified
bytes. The existing `progress.real_split` convention excludes **all** `0xCC` bytes,
even those inside genuine instructions/tables. On that frozen rule the unique
source delta is **162756 bytes**: 111307 instruction bytes + 51449 table bytes;
321 bytes excluded. This is exclusively archive-to-source, with zero new
unclaimed executable bytes and zero new game-algorithm bytes. The current path
classifier calls these reconstructed Microsoft switches authored; that must not
be mistaken for game-class/algorithm recovery. Publication and independent metric
acceptance are separate from source verification.

## Donor provenance and explicit translation

Reviewed donor: official Open-BFME/Open-BFME-2 master
`9ace59152e2ce8f6a512859817dc98d0c1fef5f5` (checked 2026-11-12).
Relevant donor evidence: `reverse/attempt_support/dxerr-lookups-20261018.md` and
`Code/Libraries/Source/DirectX/dxerr{string,description}{a,w}.cpp`.
Those bodies reconstruct **August 2005** DXErr9. They supply the semantic guide
(switch on HRESULT, grouped labels, literal return, explicit default), not
BFME 1 case membership, values, addresses, sizes or source-line proof.
The donor's Microsoft DXUT semantic guide is commit
`2c3ad3ceaf99a7aaff5278dabc2cc952c727d8c1`, `Core/dxerr.cpp`; its MIT notice
is preserved in local `game/Libraries/Source/DirectX/license.dxut.txt`.

Donor `Code/Libraries/Source/DirectX/` maps to the same library subdivision under
local `game/`. The new self-contained TUs include no donor/shared headers, use no
nested references and add no class layouts. BFME 1 remains built against its own
tracked inputs and normal compiler APIs. A direct private compile of the donor's
`dxerrdescriptiona.cpp` with BFME 1's compiler succeeded but produced no retail
placement, confirming that source reuse needs BFME 1-specific adaptation.
The donor's `// compiler: vc71-ddk-4035` override and hotpatch/frame flags are
**not inherited**. The original Summer 2003 object's CodeView record reports
13.0.9176 frontend / 13.0.9178 backend; BFME 1's normal MSVC **13.10.3077**
reproduces the recovered switches with `/O1 /G6 /MT /DNDEBUG`.

Unlike the donor, the Summer 2003 object has **no legacy COFF line-number table**.
No source-line claim is transferred. Original HRESULT macro spellings and full
original source order are unknown. Numeric constants are independently witnessed
HRESULT values, not guessed image addresses.

## Complete target behavior and compiler shape

A read-only bounded interpreter traverses the target's reachable CFG, starting
with the **entire** unsigned 32-bit HRESULT domain. It tracks affine input values,
partitions each signed/unsigned comparison exactly, enumerates only proven finite
jump-table domains and reads the pointed-to native literals. Every path must stay
inside the existing full extent, end at `ret 4` with an in-image literal pointer,
and encounter only an explicitly supported instruction. Unknown instructions,
unbounded indices, unmapped reads and incomplete/overlapping input partitions
raise errors. Each completed traversal proves a disjoint partition of all
4294967296 inputs; this is not a scan of a guessed case list or linear decoding of
the embedded tables.

| Function | Nondefault HRESULTs | Reachable instructions | Proven input-domain size |
|---|---:|---:|---:|
| String9A | 5318 | 9817 | 4294967296 |
| String9W | 5319 | 9821 | 4294967296 |
| Description9A | 619 | 1982 | 4294967296 |
| Description9W | 619 | 1982 | 4294967296 |

The ANSI and wide functions are recovered independently. They are **not** assumed
to have identical case membership. Defaults are `"Unknown"` and `"n/a"`.
The donor differs materially: String9A has 97 target-only cases and two changed
literals; String9W has 115 target-only cases and one changed literal; both
descriptions have 18 target-only cases. All emitted data comes from BFME 1.

For name switches, cases sharing a witnessed immediate-pointer return are grouped
and ordered by that return's target instruction offset. This yields ordinary C++
and reproduces the native return-block ordering; it is not claimed as recovered
original source order. Description switches retain compatible donor source groups,
remove absent cases and add independently witnessed target-only groups at their
supported HRESULT-family position. `Invalid flags` and `Invalid group` use
separate, semantically identical return statements for their two API families:
grouping their labels produces different native shared tails (+6 bytes).
The complete D3DRM description group belongs together after the existing Direct3D
`Not found` group, ordered by witnessed D3DRM HRESULT values; keeping older donor
D3DRM groups in their 2005 locations left ten wrong literal bindings despite an
exact relocation-copied instruction comparison. These adaptations
preserve target semantics and full native jump-table/literal binding.

Private diagnostic relocation-copied instruction comparisons reached exact extent
and byte equality for all four candidates. That is discovery evidence only:
normal admission must independently check every embedded jump-table label and
literal; no mask or acceptance rule is changed.

## Verification and publication

All four normal `add_match.py --replace-existing` admissions passed, followed by
one combined scoped `build.sh` gate: 4/4 functions, **8183 literal references**,
**11256 jump-table entries**, zero baselined findings, zero unverified/skipped
literals. There are no runtime calls, external globals, float constants or local
readonly loads requiring additional ownership. No archive-member masking mode is
used after replacement. Normal CSV/source-claim checks and commit hooks apply;
independent review and explicit parent publication approval remain required.

The exact requested/launch model is `openai/gpt-6.1-sol:high` (high reasoning).
The first admission refused that metadata token because the normal writer's
existing grammar excludes `:`; no ledger write occurred. The parent explicitly
approved the established ledger token `gpt-6.1-sol` solely as metadata, with exact
runtime identity retained in every row. No model, tool or admission rule changed.
Reproducible recovery/test artifacts and detailed gate results accompany this
record in `targets/game/reverse/attempt_support/dxerr9-summer2003/`.
