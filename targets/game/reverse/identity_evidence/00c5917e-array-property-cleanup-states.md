# Native array property cleanup states2 and7

All numeric addresses below are RVAs. Each action retains its opaque
address identity and is emitted by an unchanged tracked native parent.
Ghidra raw memory and independently decoded retail PE bytes agree.

## Native parents

- `008BA0B0`: `game/Libraries/Source/EA/Apt/ArrayProperties008BA0B0.cpp`. Retail FuncInfo `00E48348` selects map `00E482E8`; the native handler selects `$T922` then `$T927`.

## State selection

The parent prologue/handler chains are recorded in each outcome. Native
parent bytes and state stores pass the strict source gate. Cleanup byte
similarity alone is insufficient when several states emit identical code;
the state-specific compiler map relocation below selects the actual label.
Retail and native predecessor states were compared independently.

| Action | Size | Parent | State / predecessor | Retail map action dword | Native map relocation | Selected label | Shape candidates |
|---|---:|---|---|---|---|---|---:|
| 00C5917E | 15 | 008BA0B0 | 2 / -1 | 00E482FC | `$T927+0x14` | `$L802` | 12 |
| 00C591C9 | 15 | 008BA0B0 | 7 / -1 | 00E48324 | `$T927+0x3C` | `$L807` | 12 |

## Concrete code and callees

Every selected label is in an executable COFF section (flags 0x60501020).
The exact retail extent ends at its RET; following cleanup/handler code is
separate and not counted. No byte-only data symbol qualifies as evidence.
Existing canonical/opaque callee contracts are retained without new aliases.

- `00C5917E`: 11 concrete bytes; final RET `00C5918C`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C591C9`: 11 concrete bytes; final RET `00C591D7`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.

Each new row is independently verified by add_match, followed by the normal
commit hook. The associated full source gates preserve parent and sibling
claims and validate their existing string/constant/DIR32 references.
