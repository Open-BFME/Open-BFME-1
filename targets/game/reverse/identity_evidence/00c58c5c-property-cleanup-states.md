# Native property cleanup states at C58C5C and C58E5C

All numeric addresses below are RVAs. Each action retains its opaque
address identity and is emitted by an unchanged tracked native parent.
Ghidra raw memory and independently decoded retail PE bytes agree.

## Native parents

- `008B3C40`: `game/Libraries/Source/EA/Apt/NativeProperties008B3C40.cpp`. Retail FuncInfo `00E47ED0` selects map `00E47EA0`; the native handler selects `$T1274` then `$T1282`.
- `008B73B0`: `game/Libraries/Source/EA/Apt/Rva008B73B0Properties.cpp`. Retail FuncInfo `00E481A0` selects map `00E48078`; the native handler selects `$T1103` then `$T1107`.

## State selection

The parent prologue/handler chains are recorded in each outcome. Native
parent bytes and state stores pass the strict source gate. Cleanup byte
similarity alone is insufficient when several states emit identical code;
the state-specific compiler map relocation below selects the actual label.
Retail and native predecessor states were compared independently.

| Action | Size | Parent | State / predecessor | Retail map action dword | Native map relocation | Selected label | Shape candidates |
|---|---:|---|---|---|---|---|---:|
| 00C58C5C | 15 | 008B3C40 | 4 / -1 | 00E47EC4 | `$T1282+0x24` | `$L964` | 4 |
| 00C58E5C | 15 | 008B73B0 | 4 / -1 | 00E4809C | `$T1107+0x24` | `$L956` | 37 |
| 00C58EA7 | 15 | 008B73B0 | 9 / -1 | 00E480C4 | `$T1107+0x4C` | `$L961` | 37 |
| 00C58EF2 | 15 | 008B73B0 | 14 / -1 | 00E480EC | `$T1107+0x74` | `$L966` | 37 |

## Concrete code and callees

Every selected label is in an executable COFF section (flags 0x60501020).
The exact retail extent ends at its RET; following cleanup/handler code is
separate and not counted. No byte-only data symbol qualifies as evidence.
Existing canonical/opaque callee contracts are retained without new aliases.

- `00C58C5C`: 11 concrete bytes; final RET `00C58C6A`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C58E5C`: 11 concrete bytes; final RET `00C58E6A`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C58EA7`: 11 concrete bytes; final RET `00C58EB5`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C58EF2`: 11 concrete bytes; final RET `00C58F00`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.

Each new row is independently verified by add_match, followed by the normal
commit hook. The associated full source gates preserve parent and sibling
claims and validate their existing string/constant/DIR32 references.
