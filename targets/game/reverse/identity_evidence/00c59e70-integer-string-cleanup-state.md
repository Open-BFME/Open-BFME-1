# Native integer-string cleanup state0

All numeric addresses below are RVAs. Each action retains its opaque
address identity and is emitted by an unchanged tracked native parent.
Ghidra raw memory and independently decoded retail PE bytes agree.

## Native parents

- `008C7F70`: `game/Libraries/Source/EA/Apt/IntegerString008C7F70.cpp`. Retail FuncInfo `00E48E7C` selects map `00E48E6C`; the native handler selects `$T581` then `$T584`.

## State selection

The parent prologue/handler chains are recorded in each outcome. Native
parent bytes and state stores pass the strict source gate. Cleanup byte
similarity alone is insufficient when several states emit identical code;
the state-specific compiler map relocation below selects the actual label.
Retail and native predecessor states were compared independently.

| Action | Size | Parent | State / predecessor | Retail map action dword | Native map relocation | Selected label | Shape candidates |
|---|---:|---|---|---|---|---|---:|
| 00C59E70 | 15 | 008C7F70 | 0 / -1 | 00E48E70 | `$T584+0x4` | `$L503` | 1 |

## Concrete code and callees

Every selected label is in an executable COFF section (flags 0x60501020).
The exact retail extent ends at its RET; following cleanup/handler code is
separate and not counted. No byte-only data symbol qualifies as evidence.
Existing canonical/opaque callee contracts are retained without new aliases.

- `00C59E70`: 11 concrete bytes; final RET `00C59E7E`; +0x7: `??3Rva008A9B00@@SAXPAXI@Z`.

Each new row is independently verified by add_match, followed by the normal
commit hook. The associated full source gates preserve parent and sibling
claims and validate their existing string/constant/DIR32 references.
