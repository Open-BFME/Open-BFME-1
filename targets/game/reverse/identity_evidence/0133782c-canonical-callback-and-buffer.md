# Native callback and buffer storage views at 0133782C and 013378D0

Two existing C++ reference names now have one storage definition each in
`game/GameEngine/Source/Common/BfmeConv791.cpp`:

| Native VA | Existing COFF view | Proven storage |
| --- | --- | --- |
| `0x0133782C` | `?g_bfmeFreeDWF@@3P6AXPAX@ZA` | Four-byte callback cell; existing `__cdecl void(void*)` view |
| `0x013378D0` | `?g_bfmeBufDWG@@3PAXA` | Four-byte pointer cell; existing `void*` storage view |

The original vendor identifiers and owning translation unit remain unknown.
These are existing canonical reference views, not recovered original names.
No alternate reference name gains another storage definition, and no alias
redirect or speculative pin is added.

## Native initial bytes and size

The retail PE `.data` section starts at RVA `0x00EA5000`; its raw-backed bytes
end at `0x00EEE000`, and its virtual extent ends at `0x00F58000`. Both complete
four-byte cells lie in that zero-filled interval. Their initial native bytes
are `00 00 00 00`. This proof uses the PE virtual image; a naive file-offset
read of this tail does not describe initialized memory.

`tools/add_data_match.py` independently proves each symbol's `sizeof` and
allocation extent as four bytes under this source's normal compiler flags,
then verifies its own native zero-filled address. Before the repair there
was no tracked definition or overlapping data owner for either view. The
accepted historical `5d21e9aecc` index had no strong, COMDAT, or COMMON provider.
Both current declarations and the current data ledger were checked separately.

## Callback identity and ABI

Native installer RVA `0x00789440` contains this actual store at `0x0078944A`:

```text
C7 05 2C 78 33 01 F0 31 B8 00
mov DWORD PTR [0x0133782C], 0x00B831F0
```

RVA `0x007831F0` is a five-byte `E9 FB EC 0F 00` ILT route to
RVA `0x00881EF0`. The independently matched `operator delete[]` body there is
21 bytes: it reads one pointer at entry ESP+4, null-checks it, calls the real
pool free pointer with allocation type 2, uses caller cleanup, and returns
without callee stack cleanup. This supports the existing callback declaration
`void (__cdecl *)(void*)`. No unobserved callback arguments are invented.

The currently compiled installer is independently byte-verified over all
331 bytes and 66 DIR32 operands. Its actual operands at +0x0C and +0x10 are
still `?g_bfmeSlot01VB@@3P6AXXZA` and `?bfmeHandler01VB@@YAXXZ`.
Those legacy reference views are not the newly defined canonical symbol.
The native route proves this cell and callback identity; this repair does
not prove that the linked C++ initializer writes the selected canonical cell.

## Buffer identity and native consumer

The complete matched 30-byte body at RVA `0x00897150` is:

```text
A1 D0 78 33 01 85 C0 74 0A 50 FF 15 2C 78 33 01
83 C4 04 C7 05 D0 78 33 01 00 00 00 00 C3
```

It DWORD-loads the buffer from VA `0x013378D0`, tests for null, passes the
nonnull value to the callback cell at VA `0x0133782C`, and unconditionally
DWORD-clears the same buffer cell. Its compiled DIR32 operands are +1 and
+21 for the buffer and +12 for the callback. The original buffer type remains
unknown; the existing pointer declaration is a storage view.

The matched 40-byte initializer at RVA `0x00897120` independently stores an
allocated pointer to this cell at +0x12, then separately stores the cursor
and end cells at VA `0x013378D4` and `0x013378D8`. Its current C++ source uses
an `extern char* g_bfmeArenaStart` view. That alias remains a reference view
with no new storage definition or original-name claim. This repair does not
prove the buffer initializer's physical edge to the canonical linked cell.

## Verification and scoped linking result

The modified source and existing `Rva00893960ListClear.cpp` pass their normal
scoped gate: 4/4 functions, two data rows, and six DIR32 operands. No function
body or function-ledger row changes.

Fresh current objects were checked using normal `link_check.py` against the
immutable accepted census context `5d21e9aecc`:

| Source | Before | Callback only | Both cells |
| --- | ---: | ---: | ---: |
| `BfmeConv791.cpp` | 0 | 0; buffer still missing | 84 |
| `Rva00893960ListClear.cpp` | 0 | 45 | 45 |

This is a scoped preview gain of 129 existing source bytes, not a new accepted
whole-repository census, newly recovered C++ bytes, or a runtime result.

A strict MSVC 7.1 linker fixture uses both actual whole current objects and
the real Platform SDK `Gdi32.Lib`, with four actual function exports, no
`/FORCE`, no fabricated stubs, and no COFF slicing. The selected image contains
both canonical zero-filled cells exactly once. All 129 bytes of existing
native function code match outside the six actual DIR32 fields; those fields
point to the selected canonical cells or the real `GDI32.dll!DeleteObject`
IAT entry as appropriate.

Negative controls are required and passed: the original provider object and
objects missing either individual datum fail with LNK2019/LNK1120 (exit 96);
two actual provider copies fail with LNK2005/LNK1169 in both input orders
(exit 145). A provider initializing either cell to numeric one links, but the
actual selected cell is nonzero and the unchanged native data gate rejects
its initializer at +0. Input source, object, ledger, and baseline hashes are
unchanged across these fixture runs.

Scratch proofs: `build/free_provider/native_controls.json`, native linker
logs/maps, `final_scoped_gate.log`, `installer_gate.log`,
`buffer_initializer_gate.log`, and before/after per-file logs. Both initializer
alias limitations remain explicit; no callback initialization or runtime
closure is claimed.
