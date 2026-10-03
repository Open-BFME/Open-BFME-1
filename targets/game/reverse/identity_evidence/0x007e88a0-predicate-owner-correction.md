# Retail predicate owner correction: 0x007E88A0 / 11

Target: BFME 1 retail 1.03 unpacked game, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
This corrects identities of existing clean C++ rows. It adds no recovered code
or data bytes and does not establish a fresh whole-program link.

## Independent refutation of the W3D identity

The eleven native bytes are `8b512433c085d20f95c0c3`: load the receiver word
at +0x24, zero EAX, test the word, set AL if nonzero, and return. ECX is the
receiver; no stack argument is read or removed. The result is Boolean.

The matched address-owned constructor at RVA 0x007E8810 / 60 clears +0x24
and installs VA 0x011296B0. Its receiver is distinct from the independently
identified BFME W3DVideoBuffer, whose matched constructor is at 0x0073A230.
That constructor is reached from a matched W3DDisplay caller allocating
0x4C bytes, and installs VA 0x0112165C. Its documented BFME prefix has the
format word at +0x24 and texture/surface storage at +0x34/+0x38.

Retail W3D vtable VA 0x0112165C + 0x18 contains VA 0x0041C0EE. That five-byte
ILT routes to RVA 0x00739F80 / 32, which tests +0x34/+0x38. This contrasts
with the disputed eleven-byte body; it does not rename the existing opaque
0x00739F80 row. The copied Zero Hour W3DVideoBuffer::valid source reads a
texture at the donor's +0x24. Its eleven-byte match is a layout coincidence,
not evidence that BFME's different class owns 0x007E88A0.

The existing EA provenance row for 0x007E88A0 names the W3D source solely as
`zh`. The inherited handwritten 0x007F5A80 source assumes a W3D argument
because of that same row. It is not an independent class witness.

## Honest replacements and caller contract

Use `Rva007E88A0::method` with its native thiscall/no-argument Boolean ABI.
The source accesses only the proven +0x24 word. No semantic receiver name,
full object extent, or meaningfully named field is asserted.

RVA 0x007F5A80 / 58 tests that predicate on its one pointer argument and
forwards the value through receiver +0x1C, virtual slot 19. Both paths replace
the original stack argument and tail-jump; neither contains an in-body RET.
The actual child's return contract is unresolved. Therefore this change does
NOT correct that outer row's historical semantic identity, formal type or int
return declaration. It retains its existing source/view and changes only the
independently proven predicate callee. Its existing W3D argument and semantic
method name remain explicit historical debt; neither is new identity evidence.
An exact opaque 58-byte candidate is banked without identity/source-byte credit.

The supported native caller graph reports 24 bodies in 20 source TUs for
0x007E88A0. Migration changes their callee views/calls only. Outer caller
names, argument types, extents, behavior and existing throw() contracts stay
unchanged. The existing 58-byte outer row is retained as unresolved identity debt.
No shared header or canonical W3D type is edited. No new hasError identity,
ICF assertion, alternate name, raw code lift or literal address call is added.

## Orphan source retirement

The old W3D TU owns only the disputed eleven-byte functions.csv row and no
data row. All its function bodies equal pristine GeneralsMD W3DVideoBuffer.cpp.
Differences are only compiler comments, two compile-adapter macros, two
stlport comments and eight pre-existing unmatched annotation comments.
The exact adapted game source SHA-256 is
`6e6c3e7b6623797ff6206bc1caa136ef08174ffc456b49844953e8772c5335e4`;
pristine GeneralsMD SHA-256 is
`a2312e0a6c6cc93ca50964507d0f6dd1779c99dddd3947d4e89418c9746b8159`.
The retained SmallGaps source owns only the unresolved 58-byte row;
its exact SHA-256 is
`dbb872209c9cfef4ecfbc79c483a3641e429052ab8e9d205b72e4357c89f4305`.

Preserve both exact adapted snapshots in the ignored run bank and Git history.
After the supported verified eleven-byte replacement, freshly prove that the
old W3D source has no live function/data owner or source-bound pin, then retire
that orphan TU. Retain the old SmallGaps source and its original row. Pristine inputs remain unchanged. This avoids retaining a ZERO-row
source or inventing unmatched markers or a whitelist exception.

Use add_match.py --replace-rva --correct-identity with this evidence for the
eleven-byte replacement, retaining its generated deleted_rows tombstone. Name-regression
corrections must bind the exact actual source/ledger snapshots and actual
Findings to this evidence; no reusable exception or baseline expansion is valid.
