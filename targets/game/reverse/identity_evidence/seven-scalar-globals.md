# Seven scalar globals with competing spellings

The retail evidence supports three completed datum consolidations without changing function identities: the highlight color slot at VA `0x012F1400`, the file lookup order flag at `0x0134CB4C`, and the shared lazy ID counter at `0x012F1030`. The glow settings refresh flag at `0x012F13FC` is understood but its attempted export fails the byte gate. The two Apt switches and render clock remain unchanged because their main writers are generated assembly. The selected spellings are existing repository names. They describe the witnessed role or preserve an existing neutral spelling; this report does not claim that any of them is EA's original global identifier.

## Retail storage and access widths

All seven ranges lie in the virtual, zero-initialized tail of retail's `.data` section. Each byte or dword initially reads as zero. The direct instruction accesses below establish the scalar width. `retail-probe-v2.log` prints the PE section boundaries, each extent's bytes, nearby DIR32 names, every exact-address occurrence in `.text`, and the filtered data ledger overlap check. No other data row overlaps an extent and no DIR32 name starts strictly inside one. Names at the same starting address are competing spellings, not interior objects. The writable stores rule out compiler constants.

| VA | Physical representation | Size | Initial value | Selected spelling or unresolved disposition |
|---|---|---:|---:|---|
| `0x012F13FC` | Boolean byte, retain `Bool` / `bool` | 1 | false | Unchanged; exporting the owner fails the byte gate |
| `0x012F1400` | Dword color table index; chosen C++ type `unsigned int` | 4 | 0 | `HighlightColorIndex` |
| `0x0133781C` | Byte copied from Apt configuration offset `0x4C` | 1 | 0 | Unchanged; main writer is generated assembly |
| `0x0133781D` | Byte copied from Apt configuration offset `0x4D` | 1 | 0 | Unchanged; main writer is generated assembly |
| `0x012F8064` | Dword render synchronization clock; reference uses `UnsignedInt` | 4 | 0 | Unchanged; main writer is generated assembly |
| `0x0134CB4C` | Boolean-valued `char` scalar | 1 | 0 | `g_rva00061DE0` |
| `0x012F1030` | Integer counter | 4 | 0 | Existing `g_rva012F1030` |

## VA 0x012F13FC: glow settings refresh

Retail RVA `0x00421DE0` copies nine dwords from the saved glow settings at `0x012B4FF8` to active settings at `0x012B501C` and stores 1 to the flag. RVA `0x00421EE0` performs the same initial copy, parses into the active block, stores 1 to the flag, and conditionally copies the active settings back. The EA INI block table at VA `0x012A8580` contains the string pointer `0x01082BFC` (`GlowEffect`) and callback `0x004343C9`. That callback is the five-byte ILT jump `e9 12 db 3e 00` to VA `0x00821EE0`. This independently anchors the parser's glow role.

RVA `0x007D6BE0` returns the raw flag byte in AL. RVA `0x007D6BD0` clears it. The matched `ScreenHilightFilter::preRender` at RVA `0x007D6E40` tests the flag, obtains the active glow settings, copies a six-word snapshot into the filter, and clears the flag. The second filter preRender at RVA `0x007D74D0` performs the same refresh-and-clear operation. These are all exact-address references found by the retail probe. This is a shared dirty flag for glow settings snapshots, rather than a per-drawable selection bit.

The datum has no receiver or arguments. The parser is a free `INI *` callback, with the INI argument loaded from the stack. The filter consumers use ECX as their receiver and update receiver-owned snapshots. The getter returns a byte and the clear function takes no arguments. `Drawable.cpp` already owns storage as `static Bool s_glowEffectChanged`. Exporting that storage as `HighlightRefresh` fails the parser's byte gate both with an unsigned char representation and with the original Boolean representation: the store moves before the INI load-type read and comparison. Raw refusals are in `uchar-build-Drawable.log` and `bool-build-Drawable.log`. Restoring the original static owner passes all 100 rows in `baseline-build-Drawable.log`. Every candidate source and ledger edit was restored before proceeding with the three independent corrections. This address remains unchanged; a storage consolidation retaining the original parser instruction order would settle the implementation blocker. No wrapper or alias is introduced.

Zero Hour's `GameEngine/Source/GameClient/Drawable.cpp` and W3D client source were searched for `highlight`, `hilight`, and the filter role. The reference has terrain bib highlighting, but supplies no corresponding glow refresh global. `HighlightRefresh` is an existing descriptive spelling, not an asserted upstream identifier. A parser table routed to a different callback, a snapshot consumer reading a different address, or any altered matched instruction would refute the consolidation.

## VA 0x012F1400: highlight color slot

The setter at RVA `0x0073A610` takes an integer stack argument, rejects `-1`, and writes the argument to the datum. RVA `0x0073E050` also writes the slot, including literal values 1 and 2. The free functions at RVAs `0x00746DA0` and `0x00746DE0` take an explicit slot as their final stack argument; `-1` selects this global. They shift the selected index left by four and write or read the three dwords at color entry offsets in the table starting at `0x012B4FC8`.

The matched `ScreenHilightFilter::postRender` at RVA `0x007D7040` loads this same index, multiplies it by 16, reads three floats from `0x012B4FC8`, subtracts 1 from each, and passes the result into its pixel constant update. The receiver is in ECX. Its use establishes a color table slot, not a frame count or pointer. All eight exact-address references are in the setter, RVA `0x0073E050`, the two free color accessors, and postRender. The dedicated setter's source, `Rva0073A610Set.cpp`, owns the consolidated unsigned integer datum. These accesses prove the four-byte width but do not distinguish the original signed or unsigned declaration. The chosen `unsigned int` agrees with the existing `HighlightColorIndex` declaration and passes each affected source's byte gate. The signed setter argument and the `-1` sentinel remain unchanged.

The Zero Hour highlight search finds no equivalent screen highlight color slot. `HighlightColorIndex` is already a repository spelling at this address and correctly describes the retail table use. A different scaled table base, pointer dereference of the datum itself, or a changed setter sentinel contract would refute this role. A type correction is accepted only when the affected functions retain identical bytes.

## VAs 0x0133781C and 0x0133781D: Apt configuration switches

The sole direct writer of both bytes is RVA `0x00894800`. It accepts an optional parameter block on the stack, constructs a default block when the argument is null, reads bytes at parameter offsets `0x4C` and `0x4D`, and stores them independently to `0x0133781C` and `0x0133781D`. The default block constructor is VA `0x008659D0`, reached through ILT `0x00448D65` with bytes `e9 66 cc 41 00`. The caller at RVA `0x0046C5F0` constructs that parameter block and sets offset `0x4C` to 1 before configuring the Apt subsystem. The existing configurator pin is `?configureWindowParameters@@YAXPAVGen_004659D0@@@Z`; it is not additional evidence for an original global identifier.

The first byte gates the packed two-integer send operations at RVAs `0x00892080` and `0x008A07A0`, the preparation pass at `0x008BBDB0`, encoded input routing at `0x008BCCC0`, channel creation at `0x008AE7C0`, node routing at `0x008BD910`, and cleanup at `0x008C3F10`. The second byte participates in channel creation and node routing, and RVA `0x008BD6B0` copies it into a constructed object's byte field. These reads establish configuration-controlled Apt dispatch paths, but do not establish an original global name or the complete semantic meaning of the secondary switch. In particular, the secondary reader stores a flag value rather than exposing a named reference field.

The Zero Hour reference file inventory contains no Apt source that supplies these global identities. The writer is owned by `game/gen_asm/d_0088a430.asm`; the run forbids editing that file or introducing a wrapper or alias identity. Both addresses therefore remain unchanged. A real C++ owner of RVA `0x00894800` would permit storage ownership to be implemented. Reference declarations or an EA parameter field name would settle the original switch names. A second writer or a reader with a different width would refute the current writer and byte contract.

## VA 0x012F8064: rendering synchronization time

The only direct writer is RVA `0x006F3FC0`, with two update paths. One adds the dword at `0x012BB1CC`; the other adds that dword multiplied by the computed logic frame delta. Both store the updated clock and pass its value to VA `0x00CFD310`. Readers compare the clock with per-object animation stamps or use it for animation elapsed time. Direct readers begin at RVAs `0x0075B2E0`, `0x0075C940`, `0x0076B800`, `0x0076C080`, `0x0076CAF0`, `0x0076EB10`, `0x0076EB50`, `0x0076EBE0`, `0x0076EDA0`, `0x00773360`, and `0x0077B3F0`.

RVA `0x0076EB10` has an independently witnessed ILT entry at VA `0x00436F11`, whose bytes `e9 fa 7b 73 00` jump to `0x00B6EB10`. Padding ends immediately before that body and its return is at `0x00B6EB41`. The probe's overlapping ledger attribution to `Team::tryToRecruit` is not identity evidence and is not used here. The actual body reads the clock, compares it with receiver offset `0x90`, adjusts ECX by `-0xC` for animation advancement when stale, and scans three animation entries. This preserves the evidence without trusting a disputed ledger extent.

Zero Hour `W3DDisplay.cpp` defines `static UnsignedInt syncTime = 0` inside `W3DDisplay::draw` at line 1667, adds `TheW3DFrameLengthInMsec` at lines 1768 and 1801, and calls `WW3D::Sync(syncTime)` at line 1805. This is reference evidence for the analogous clock role, not proof that BFME's exported scalar originally had the same spelling or scope. The main writer remains owned by `game/gen_asm/d_006e2ac0.asm`, which this run cannot edit. The datum is left unchanged. A byte-matched real C++ owner for RVA `0x006F3FC0` would permit consolidation in the required writer file. A non-clock use of the updates or a different interpretation of the frame length would refute the role.

## VA 0x0134CB4C: local versus archive lookup order

RVA `0x00061BE0` and RVA `0x00061DE0` set the byte to 1. The `-mod` parser at RVA `0x000624F0` also sets it to 1. The retail command line table at `0x012A6F48` contains `-mod` string pointer `0x01075204` and ILT `0x00440070`; the five bytes `e9 7b 24 02 00` route to VA `0x004624F0`. File system initialization at RVA `0x009C87A0` sets the flag to 1 when the local file system's existence check for the retail string `shaders.big` at `0x011439FC` returns false.

Both `FileSystem::openFile` overloads at RVAs `0x009C8860` and `0x009C89F0` read the flag twice. With the flag zero, the archive lookup block precedes the local lookup. With the flag nonzero, the archive block runs after the local lookup. The datum selects order; it does not suppress archive lookup or represent shader enablement. These are all eight exact-address references found by the probe.

The datum has no receiver or arguments. The two standalone setters take none; one returns integer 1. The mod parser takes its argument vector and count on the stack. File opening uses a FileSystem receiver and the existing overload arguments. The Zero Hour file system reference has ordinary local/archive lookup and lacks this BFME search-order switch. The retained existing neutral spelling is `g_rva00061DE0`, defined as one `char` in `Rva00061150Set.cpp`. Unsized array declarations and `[0]` accesses become scalar declarations and accesses so every user names the same COFF symbol. This retyping must preserve all function bytes. An archive suppression path controlled by this flag, a reversed observed ordering, or a wider access would refute the correction.

## VA 0x012F1030: shared lazy ID counter

There are exactly three direct reader/writer bodies, at RVAs `0x003BCF00`, `0x0043BCF0`, and `0x004C1240`. Each tests bit 0 of its own static guard, sets that bit on first execution, loads this shared dword, stores the old value into its own cached ID, increments the shared counter, and returns the cached ID. Later calls return that same cached ID without incrementing the counter. Each is a free no-argument function returning its integer result in EAX.

Their exact five-byte ILT entries are VA `0x0040A290` (`e9 6b 2c 3b 00`), `0x00411C20` (`e9 cb a0 42 00`), and `0x0043D8FC` (`e9 3f 39 48 00`). The source already uses one definition named `g_rva012F1030` in `BfmeConv657.cpp`, and the other two sources already declare that same counter. The brief's three `bfmeNextCW*` names survive in the address and pin tables, but occur in no current source declaration. The data row and additive DIR32 spelling make the existing single owner explicit. No source rename, wrapper, or inferred type identity is needed. The Zero Hour engine search provides no corresponding original counter identifier. Separate counter addresses, a reset outside these witnessed stores, or a cached ID not obtained from the shared old value would refute this limited lazy ID role.

## Original declaring-file counts

Counts are distinct game source files declaring or defining the spelling, before this correction. Multiple uses or redeclarations in one file count once. The inventory includes the existing static glow spelling and the existing consolidated ID counter that were absent from the question's spelling list. `inventory.log` records source lines and `inventory.json` stores the same inventory for rechecking.

| VA | Spellings and declaring-file counts |
|---|---|
| `0x012F13FC` | `HighlightRefresh`: 1; `g_Va012F13FC`: 2; `g_bfmeDirtyCU`: 2 (one bool, one unsigned char); `s_glowEffectChanged`: 1 |
| `0x012F1400` | `HighlightColorIndex`: 1; `g_bfmeCurrentFA`: 0; `g_rva0073a610`: 3 |
| `0x0133781C` | `flag0133781C`: 1; `g_bfme1017G`: 1; `g_bfmeDispatchEnabled1281`: 3; `g_bfmeJ1017Flag`: 1; `g_byte0133781C`: 1 |
| `0x0133781D` | `flag0133781D`: 1; `g_bfmeFlag1281`: 1; `g_bfmeSecondaryEnabled1282`: 1 |
| `0x012F8064` | `g_Va012F8064`: 0; `g_bfmeX1058`: 1; `g_rva0075b2e0_value`: 6; `g_va012F8064`: 1 |
| `0x0134CB4C` | `byte_134CB4C`: 0; `g_Va0134CB4C`: 0; `g_bfmeShaderFlagEBB`: 0; `g_rva00061DE0`: 5 |
| `0x012F1030` | `bfmeNextCWB`: 0; `bfmeNextCWC`: 0; `bfmeNextCWD`: 0; `g_rva012F1030`: 3 |

## Raw evidence and validation

Raw local evidence is under `build/rlink/scalars-1791159262/`. `retail-probe.log` retains the initial probe; `retail-probe-v2.log` includes corrected ledger coverage and raw disassembly, without treating competing ledger identities as proof. `direct-accesses.log`, `retail-supplement.log`, and `retail-supplement-v2.log` expose the relevant memory operands, strings, tables, and exact ILT bytes. `reference-drawable.log`, `reference-highlight.log`, `reference-filesystem.log`, `reference-counter.log`, `reference-file-list.log`, `reference-sync.log`, and `reference-sync-global.log` retain reference searches. `spellings.log`, `extra-spellings.log`, and `inventory.log` retain the original declaration evidence.

The three final data gates are `data-color.log`, `data-filesystem.log`, and `data-counter.log`; they record compiler size and retail byte verification. The `uchar-*` and `bool-*` receipts preserve the rejected refresh candidates, whose edits were restored. Each final `build-*.log` records a full scoped source gate, including all the source's ledger rows. `link-before.log` and `link-after.log` record file-level LINKED bytes and remaining blockers against the existing census. `check-csv.log`, `pin-consistency.log`, and `declared-unmatched.log` record the additional requested gates. The final handoff records any failing gate instead of treating compilation alone as verification. No function identity or extent, existing symbols pin, generated source, or shared header is changed.
