# Native property cleanup states19 through34

All numeric addresses below are RVAs. Each action retains its opaque
address identity and is emitted by an unchanged tracked native parent.
Ghidra raw memory and independently decoded retail PE bytes agree.

## Native parents

- `008B73B0`: `game/Libraries/Source/EA/Apt/Rva008B73B0Properties.cpp`. Retail FuncInfo `00E481A0` selects map `00E48078`; the native handler selects `$T1103` then `$T1107`.

## State selection

The parent prologue/handler chains are recorded in each outcome. Native
parent bytes and state stores pass the strict source gate. Cleanup byte
similarity alone is insufficient when several states emit identical code;
the state-specific compiler map relocation below selects the actual label.
Retail and native predecessor states were compared independently.

| Action | Size | Parent | State / predecessor | Retail map action dword | Native map relocation | Selected label | Shape candidates |
|---|---:|---|---|---|---|---|---:|
| 00C58F3D | 15 | 008B73B0 | 19 / -1 | 00E48114 | `$T1107+0x9C` | `$L971` | 37 |
| 00C58F88 | 15 | 008B73B0 | 24 / -1 | 00E4813C | `$T1107+0xC4` | `$L976` | 37 |
| 00C58FD3 | 15 | 008B73B0 | 29 / -1 | 00E48164 | `$T1107+0xEC` | `$L981` | 37 |
| 00C5901E | 15 | 008B73B0 | 34 / -1 | 00E4818C | `$T1107+0x114` | `$L986` | 37 |

## Concrete code and callees

Every selected label is in an executable COFF section (flags 0x60501020).
The exact retail extent ends at its RET; following cleanup/handler code is
separate and not counted. No byte-only data symbol qualifies as evidence.
Existing canonical/opaque callee contracts are retained without new aliases.

- `00C58F3D`: 11 concrete bytes; final RET `00C58F4B`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C58F88`: 11 concrete bytes; final RET `00C58F96`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C58FD3`: 11 concrete bytes; final RET `00C58FE1`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C5901E`: 11 concrete bytes; final RET `00C5902C`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.

Each new row is independently verified by add_match, followed by the normal
commit hook. The associated full source gates preserve parent and sibling
claims and validate their existing string/constant/DIR32 references.
