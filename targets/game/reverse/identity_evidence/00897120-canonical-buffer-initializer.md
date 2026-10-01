# Canonical buffer store in the existing initializer

This is a linkage repair to the already matched `?bfmeArenaInit@@YAXI@Z`
at RVA `0x00897120`, extent 40 bytes. It adds no recovered C++ or native data
bytes. Its original vendor name remains unproved. The source continues to
use its existing function name and pointer arithmetic.

## Native and existing storage evidence

The complete native body is:

```
6800400000ff15287833018b4c240883c404a3d0783301a3d478330103c1a3d8783301e908ffffff
```

The native operands and actual compiler object independently agree:

| Body offset | Kind | Native target |
| --- | --- | --- |
| `+0x07` | DIR32 | Allocator cell VA `0x01337828` |
| `+0x13` | DIR32 | Buffer cell VA `0x013378D0` |
| `+0x18` | DIR32 | Cursor cell VA `0x013378D4` |
| `+0x1F` | DIR32 | End cell VA `0x013378D8` |
| `+0x24` | REL32 | Tail jump to RVA `0x00897050` |

Commit `10cf3281630cd48f9ae48caa292b5f7181fdffc8` published the unique
4-byte, zero-filled native buffer owner `?g_bfmeBufDWG@@3PAXA` in
`BfmeConv791.cpp`. Its separate 30-byte native cleanup at RVA `0x00897150`
loads and clears that same cell. The old `g_bfmeArenaStart` declaration was
another reference view, with no storage definition. The published datum
evidence is in `0133782c-canonical-callback-and-buffer.md`.

Only that extern declaration and its single store change: the initializer
now declares the existing canonical `void*` view and assigns `block` to it.
The standard `char*` to `void*` conversion adds no code. `block` remains a
`char*`, preserving the existing end arithmetic. No datum, pin, header,
function identity, cursor cell or end cell is added or changed.

## Scoped gates and physical store edge

The normal whole-source byte gate passes both existing functions, 141 source
bytes, and all five DIR32 references. The canonical buffer pin consistency
check is consistent at RVA `0x00F378D0`. No pin was added.

The first strict whole-object link failed on the unrelated constructor's
delete/constructor/EH machinery. It was not forced through. The successful
bounded fixture therefore preserves the actual compiler-produced initializer
section's 40 bytes and all five relocations exactly, excluding the unrelated
constructor and EH sections. It links that actual section against the whole
actual canonical provider object and real `Gdi32.Lib`, without `/FORCE`.

Scratch-only stand-ins satisfy `WideAllocPtr`, `g_bfmeArenaCursor`,
`g_bfmeArenaEnd`, and `bfmeArenaReady`. These stand-ins are unproved, are never
executed, and supply no native-provider or runtime evidence. The fixture's
claim covers only the canonical buffer store edge.

The linked initializer's operand `+0x13` selects exactly one zero-filled
canonical buffer definition from the real provider. The actual provider's
30-byte cleanup loads and clears that exact same selected cell. All
initializer bytes outside its five relocation operands agree with the native
40-byte body. No old ArenaStart alias appears in the selected image.

Controls:

- Positive actual section/provider link exits 0 and verifies the canonical
  store edge and shared cleanup cell.
- The original initializer object section still referring to ArenaStart
  fails with exit 96 and the unresolved legacy alias.
- Removing the actual canonical provider fails with exit 96 and unresolved
  canonical buffer.
- A scratch compiler-produced 40-byte initializer that stores to the other
  published callback cell links successfully but fails the canonical buffer
  edge predicate. Its masked bytes alone do not establish the right target.
- Tracked source, actual objects, datum ledger and native baseline hashes
  agree before and after the controls.

Reproducible fixture and JSON are `build/arena_initializer/controls.py` and
`controls.json` in the contributing checkout. They record every selected
operand and explicitly identify the stand-ins and section boundary.

## Limits and accounting

The fresh initializer object plus fresh actual canonical provider, against
the immutable accepted `5d21e9aecc` index, removes the ArenaStart/canonical
buffer blocker. The initializer TU remains blocked by the independent
allocator, cursor, end, and constructor-delete names: linked 0 to 0 bytes.
The provider's existing 84 bytes remain linkable; that was already credited
to the published datum repair. This is not a fresh accepted whole census.

One canonical initialization **store edge** is repaired. The allocator,
cursor/end storage, actual Ready path and constructor dependencies still
prevent a whole-TU or whole-graph claim. The callback initializer's 33 legacy
slot/handler pairs are unchanged. No runtime initialization closure, new C++
bytes, new data bytes, headline gain or authored-card gain is claimed.
