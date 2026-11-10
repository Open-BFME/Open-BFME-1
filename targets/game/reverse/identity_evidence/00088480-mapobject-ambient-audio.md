# 0x00088480 MapObject ambient-audio body (1019 B)

Class: MapObject. MapObject::duplicate (matched, WorldHeightMap.cpp) calls this
body on the freshly built MapObject through ILT 0x00031FCF; bfmeGoEYE
(BfmeConv888.cpp) stores the mode global 0x012ED5D8 and walks the MapObject list
(next pointer at +0x04, as in the matched MapObject destructor) calling it. The
members it touches (+0x18 thing template, +0x24 properties Dict, +0x44 runtime
flags, +0x54/+0x58 audio handles, +0x5C ref) agree with the matched destructor.

Method name: unproven, kept opaque with the address (ambientAudio00088480). The
" MapObjectAmb %d %s" literal (0x0107C7E4) and the AudioManager addAudioEvent
(+0x44) / getInfoForAudioEvent (+0xAC) calls show only that it builds the object's
ambient audio events.

2026-09-28 rewrite: the earlier bank modelled every callee as a raw j_ thunk with
cast member pointers and named its stack locals (m_current, m_audioInfo,
m_data, slot, call) after roles it guessed. The rewrite replaces that scaffolding
with one ref-counted pointer class (members m_ptr) whose operator=/raw-pointer
ctor are the 0x00087750/0x00087720 bodies, the AsciiString header type in place
of the BFMERetailAsciiString shim, the ledger's own Rva00087BD0::get for the
template's indexed sound lookup, and the ledger's gen00087C30 for the stop call
at 0x00087C30. No descriptive name was replaced by a guess; the old names were
scaffolding for a different decomposition, not evidence about these members.

## 2026-11-10 landing (clean C++, byte-exact)

### BFME 1 target evidence

- Boundary: entry 0x00088480 (REL32 target of ILT 0x00031FCF), single `ret`
  at +0x3FA followed by INT3 padding; 1019 bytes.
- Owner class MapObject: the matched `MapObject::duplicate` (0x00089390,
  WorldHeightMap.cpp) calls this body on the new MapObject through ILT
  0x00031FCF; `bfmeGoEYE` (BfmeConv888.cpp) stores the mode global 0x012ED5D8
  and walks the MapObject list calling it; members +0x18 (thing template),
  +0x24 (property Dict), +0x44 (runtime flags), +0x54/+0x58 (audio handles)
  and +0x5C (custom info reference) agree with the matched MapObject rows.
- Behaviour: reads the ambient-audio properties (0x000B6030), renames a
  customized info with the literal " MapObjectAmb %d %s" and the counter at
  0x012ED5E8, picks the template audio slots 0x57 and 0x5B, decides by the
  mode (1 always, 2 the enabled property, 3 the infos' ready test
  0x000874E0), and starts (AudioManager slot +0x44) or stops (0x00087C30) the
  two events.
- Name: the method name is NOT recovered. `ilt_oracle check` CONTRADICTS
  `?validate@MapObject@@QAEXXZ` and the pinned BFME 2 donor spelling
  `?bfmeRunEYE@BfmeNodeEYE@@QAEXXZ` at this address, so the row keeps the
  address-derived `?ambientAudio00088480@MapObject@@QAEXXZ` (placeholder tier).

### Carried from the BFME 2 donor (lead only)

Open-BFME-2 @59e3f8f8 `Code/GameEngine/Source/Common/BfmeMapObjectAmbientEYE.cpp`
(retail 0x0030DEAE there) is the single-slot twin: same literal, same mode
switch, same start/stop split. It confirmed the overall control flow; BFME 1
keeps two template slots, different helpers and its own layout, so no donor
body or name was imported.

### Compiler facts that decided the match (measured, VC7.1 /O2 /MD /EHsc)

- The ready test must be an in-class `__declspec(noinline)` member in this
  TU. Opaque declaration: alternate.m_ptr is re-read from memory after each
  call (591 diffs). Out-of-line definition in the TU: the compiler also uses
  its register summary and keeps the pointer in EDX across the call (703
  diffs). In-class COMDAT: no reload and a callee-saved register, retail's
  shape (exact).
- Retail assigns the re-fetched slot 0x5B info to `current`
  (`lea ecx,[esp+0x14]` at +0x22C); the source keeps that.
- Case 3 needs `if (current ready) { enable = true; break; }` followed by the
  alternate test so that case 1 tail-merges into the first `enable = true`
  block (je +0x265).

### Callee 0x00087860 (73 B): own copy-assign, not an alias

Boundary 0x00087860..0x000878A9 (`ret 4`, INT3 padding), byte-identical to
0x00087750 but a separate retail body with its own ILT thunk 0x00043C07.
0x00088480 calls it at +0x2C4 with `this = &MapObject+0x5C` and the parsed
custom-info reference as the argument. The row was a `gen-alias` of
`??4Rva00087750Ref` under `?dup_00087860@@YAXXZ`; it is now the copy-assign of
its own address-named reference class `Rva00087860Ref` (same source file,
real second definition). The class name stays address-derived: nothing proves
which EA reference type either twin belongs to.

### Callee 0x000877B0 (35 B): reference release, row unchanged

0x00088480 constructs a stack temporary with the matched raw-pointer
constructor `??0Rva00087720Ptr@@QAE@PAURva00087720Target@@@Z` (call at +0x1AD,
EH state 4) and releases the same object through ILT 0x000362FF -> 0x000877B0
(call at +0x1D0). The 0x000877B0 row stays the `gen-alias`
`?dup_000877b0@@YAXXZ`: symbols.csv also pins that body as
`??1AudioEventInfoRef@@QAE@XZ`, which `ilt_oracle check` contradicts, and
pin_consistency refuses a second address-derived row name beside it. The
MapObject TU reaches the body through the address-named `abi-view=` pin
`?Rva000877B0@Rva000877B0Ref@@QAEXXZ` at the ILT; resolving the row's identity is open.
