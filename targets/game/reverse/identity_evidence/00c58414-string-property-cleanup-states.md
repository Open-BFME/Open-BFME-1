# String property cleanup states at 008AB0E0

All numeric addresses below are RVAs. Each action retains its opaque
address identity and is emitted by an unchanged tracked native parent.
Ghidra raw memory and independently decoded retail PE bytes agree.

## Native parents

- `008AB0E0`: `game/Libraries/Source/EA/Apt/StringProperties008AB0E0.cpp`. Retail FuncInfo `00E477B8` selects map `00E47750`; the native handler selects `$T958` then `$T963`.

## State selection

The parent prologue/handler chains are recorded in each outcome. Native
parent bytes and state stores pass the strict source gate. Cleanup byte
similarity alone is insufficient when several states emit identical code;
the state-specific compiler map relocation below selects the actual label.
Retail and native predecessor states were compared independently.

| Action | Size | Parent | State / predecessor | Retail map action dword | Native map relocation | Selected label | Shape candidates |
|---|---:|---|---|---|---|---|---:|
| 00C58414 | 15 | 008AB0E0 | 5 / -1 | 00E4777C | `$T963+0x2C` | `$L833` | 12 |
| 00C5845F | 15 | 008AB0E0 | 10 / -1 | 00E477A4 | `$T963+0x54` | `$L838` | 12 |

## Concrete code and callees

Every selected label is in an executable COFF section (flags 0x60501020).
The exact retail extent ends at its RET; following cleanup/handler code is
separate and not counted. No byte-only data symbol qualifies as evidence.
Existing canonical/opaque callee contracts are retained without new aliases.

- `00C58414`: 11 concrete bytes; final RET `00C58422`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C5845F`: 11 concrete bytes; final RET `00C5846D`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.

Each new row is independently verified by add_match, followed by the normal
commit hook. The associated full source gates preserve parent and sibling
claims and validate their existing string/constant/DIR32 references.
