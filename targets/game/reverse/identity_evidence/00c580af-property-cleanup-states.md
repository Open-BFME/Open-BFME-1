# Property dispatch cleanup states at 008A73E0 and 008A7B00

All numeric addresses below are RVAs. Each action retains its opaque
address identity and is emitted by an unchanged tracked native parent.
Ghidra raw memory and independently decoded retail PE bytes agree.

## Native parents

- `008A73E0`: `game/Libraries/Source/EA/Apt/Rva008A73E0LoadVarsProperties.cpp`. Retail FuncInfo `00E47470` selects map `00E47438`; the native handler selects `$T956` then `$T961`.
- `008A7B00`: `game/Libraries/Source/EA/Apt/Rva008A7B00KeyboardProperties.cpp`. Retail FuncInfo `00E47500` selects map `00E474C0`; the native handler selects `$T2028` then `$T2052`.

## State selection

The parent prologue/handler chains are recorded in each outcome. Native
parent bytes and state stores pass the strict source gate. Cleanup byte
similarity alone is insufficient when several states emit identical code;
the state-specific compiler map relocation below selects the actual label.
Retail and native predecessor states were compared independently.

| Action | Size | Parent | State / predecessor | Retail map action dword | Native map relocation | Selected label | Shape candidates |
|---|---:|---|---|---|---|---|---:|
| 00C580AF | 15 | 008A73E0 | 1 / -1 | 00E47444 | `$T961+0xC` | `$L820` | 6 |
| 00C580FA | 15 | 008A73E0 | 6 / -1 | 00E4746C | `$T961+0x34` | `$L919` | 1 |
| 00C5817E | 15 | 008A7B00 | 2 / -1 | 00E474D4 | `$T2052+0x14` | `$L735` | 8 |
| 00C581C9 | 15 | 008A7B00 | 7 / -1 | 00E474FC | `$T2052+0x3C` | `$L740` | 8 |

## Concrete code and callees

Every selected label is in an executable COFF section (flags 0x60501020).
The exact retail extent ends at its RET; following cleanup/handler code is
separate and not counted. No byte-only data symbol qualifies as evidence.
Existing canonical/opaque callee contracts are retained without new aliases.

- `00C580AF`: 11 concrete bytes; final RET `00C580BD`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C580FA`: 11 concrete bytes; final RET `00C58108`; +0x7: `??3Rva008A9B00@@SAXPAXI@Z`.
- `00C5817E`: 11 concrete bytes; final RET `00C5818C`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.
- `00C581C9`: 11 concrete bytes; final RET `00C581D7`; +0x7: `??3Rva00897670HeaderedDelete@@SAXPAXI@Z`.

Each new row is independently verified by add_match, followed by the normal
commit hook. The associated full source gates preserve parent and sibling
claims and validate their existing string/constant/DIR32 references.
