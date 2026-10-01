# 0089ECD0 bank: an address-bound string state view

This evidence covers only the replacement of the nonmatching bank at
`targets/game/reverse/attempts/0x0089ecd0.cpp`. It does not rename a published
EAString sibling, alter a symbol pin, or assert that another native class owns
this body. The pool type remains declared under its existing spelling.

## Exact source snapshots

- Before SHA-256:
  `19ddb90cb529c9bf42b1cc15b7afdf06c34a9b2bd819d5a715f6af63a46c1271`.
- After SHA-256:
  `c2a6559bef45e48ee70a08e24dfcc2e72e20d3bbdf186002449c3dea69f54348`.
- The after source is exactly the `source` string in
  `targets/game/reverse/attempt_history/0x0089ecd0/c2a6559bef45e48ee70a08e24dfcc2e72e20d3bbdf186002449c3dea69f54348.json`.
  That receipt records measured score `0.7273`. Equal emitted length and
  normalized instruction shape do not make this a byte match.

## Independent retail facts

The baseline is
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses below are RVAs unless identified as absolute pointer operands.
The 275-byte body occupies `[0x0089ECD0,0x0089EDE3)`, with SHA-256
`46ce7048f86da554ea7a012cccd54c5a1d5f794eda4a8a007319b64950d74d18`.
It ends with RET at `0x0089EDE2`, followed by INT3. All 101 opcode lines
in the retained body disassembly were compared directly with that PE.

At entry the format pointer is the second stacked parameter: after the
initial push it is read at `[esp+0xC]` (`0x0089ECD1`). The source receiver
is the first stacked parameter: after three pushes it is read at
`[esp+0x10]` (`0x0089ECE1`). This is the physical stack transport of a
cdecl variadic member view; it does not imply an ECX receiver contract.
The state word at `[receiver]` points at an eight-byte prefix whose word
offsets `0,2,4,6` are accessed before byte storage beginning at `+8`.

Both indirect callback routes read the same absolute global `0x01337A30`:
`0x0089ED27` loads the table and `0x0089ED3A` calls its slot `+0` with
one stacked allocation-size word, returning the new pointer in EAX.
`0x0089ED86` loads the same table and `0x0089ED8C` calls slot `+4`
with the old pointer. Both sites have explicit four-byte caller cleanup.
This contradicts the older bank's use of a separately declared allocator
global pinned at `0x00F37A30`; it proves the concrete table/address route,
not the original callback type or pool class name. No shared pin is changed.

The direct formatter call at `0x0089EDAB` goes to `0x009F6EC0`, followed
by `add esp,0x10`. Four preceding pushes supply destination, count, format
and the address of subsequent argument words. At `0x009F6EC0`, retail
bytes `FF 25 60 93 35 01` jump through absolute IAT address `0x01359360`;
`targets/game/reverse/imports.csv` identifies this as `MSVCR71.dll!_vsnprintf`.
The six-byte thunk SHA-256 is
`43b7d997604885bb829ef4432a998478866bfa97739db7b0c48ded2e4ed4bff8`.
The bank now uses the native CRT declaration for that four-argument import
contract rather than a guessed private callee alias.

## Owner and method spelling remain uncertain

There is genuine evidence for the library/file family:
`ea_evidence.csv` assigns RVA `0x0089ECD0` to
`Libraries/Source/Apt/string/EAString.cpp`. Existing pins name an
`EAStringC::ChangeBuffer` body at `0x0089E570` and address-qualified
EAStringC-family siblings. This evidence is retained as a lead and is not
disproved by the correction. `name_oracle.py --class EAStringC` returned
status 2, no witnessed layout; no export or independent method-name witness
for `appendFormat0089ECD0` was found.

The older bank introduced a local one-pointer `EAStringC` class and labelled
this unconverted body `appendFormat0089ECD0`. Compatible record layouts,
the formatting algorithm and the Apt file family do not independently
establish that this local class declaration is the native owner declaration
or that the hybrid method spelling was the retail method name.
The bank's `Rva0089ECD0::rva0089ECD0` is a borrowed physical state view,
with the address preserved and no construction, complete object-size,
ownership or lifetime claim. The correction removes the unsupported
identity certainty from this bank; it does not claim that the body cannot
belong to the EAString family or prove a competing owner.

## The retained pool warning is a false pairing

`BfmeStringPool3AF0` is declared in both exact snapshots, and the after
snapshot still declares `extern BfmeStringPool3AF0 *g_bfmeStringPool1284`.
Its `free` slot remains. Its first slot is now the allocation callback
observed at the same concrete table in retail. It is not renamed or moved
into `Rva0089ECD0`.

The regression detector's layout parser records only `m_unused` (four
bytes at offset zero) for the old pool; it omits function-pointer members.
The after pool consists of function-pointer members and is therefore absent
from the detector's measured layouts. That gives the old pool the same
measured one-word shape as the new receiver view and causes the invented
`BfmeStringPool3AF0 -> Rva0089ECD0` carrier pairing. The two retained pool
declarations positively refute that rename; no pool identity is retired.

The three exact correction pairs are `EAStringC -> Rva0089ECD0`,
`appendFormat0089ECD0 -> rva0089ECD0`, and the false detector pairing
`BfmeStringPool3AF0 -> Rva0089ECD0`. They apply only to the source hashes
above. Existing published sibling identities, ledger rows and pins are
unchanged. The bank and its outcome provide zero recovered or linked bytes.
