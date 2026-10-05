# Screen filter fade storage at VA 0x013071A8 through 0x013071D0

Retail establishes two separate fade state groups. The first is `ScreenBWFilter`'s four protected static members, shared with its fixed function fallback. The second is BFME's zoom filter state, shared with its fixed function fallback. The existing `Zoom*` identifiers are retained as repository storage names. This evidence does not assert that they are EA's original C++ spellings or invent a `ScreenZoomFilter` static member declaration.

## Retail storage and accesses

Every cell below is in the virtual, loader zero filled tail of the PE `.data` section. Its initial value is zero. Addresses in the access columns are body RVAs, not ILT entries. The raw reference scan and decoded instructions are in `build/rlink/screen-fade-1791159203/retail-references.log`. The scan checks every occurrence of each absolute address in the complete file backed `.text` section, associates it with narrow ledger or Ghidra boundaries, and reports uncovered occurrences. These are the direct absolute accesses found by that scan; it does not claim to exclude arbitrary indirect accesses.

| VA | Storage identity and type | Bodies that read it | Bodies that write it |
|---|---|---|---|
| 0x013071A8 | `ScreenBWFilter::m_curFadeValue`, `float`, 4 bytes | 0x007D1020, 0x007D1610 | 0x007D1020, 0x007D1AA0 |
| 0x013071AC | `ScreenBWFilter::m_fadeDirection`, `int`, 4 bytes | 0x007D1020, 0x007D1AA0 | 0x0073A8A0, 0x0073B540, 0x007D1020, 0x007D1AA0 |
| 0x013071B0 | `ScreenBWFilter::m_fadeFrames`, `int`, 4 bytes | 0x007D1020, 0x007D1AA0 | 0x0073A8A0, 0x0073B540 |
| 0x013071B4 | `ScreenBWFilter::m_curFadeFrame`, `int`, 4 bytes | 0x007D1020, 0x007D1AA0 | 0x0073A8A0, 0x0073B540, 0x007D0AF0, 0x007D0C00, 0x007D1020, 0x007D1AA0 |
| 0x013071B8 | No directly addressed object established; four loader zero bytes | None found | None found |
| 0x013071BC | `ZoomFadeValue`, `float`, 4 bytes | 0x007D24A0, 0x007D2D30 | 0x007D1F00, 0x007D31C0 |
| 0x013071C0 | `ZoomFadeDirection`, `int`, 4 bytes | 0x007D1F00, 0x007D31C0 | 0x0073A860, 0x0073B540, 0x007D1F00, 0x007D31C0 |
| 0x013071C4 | `ZoomFadeFrames`, `int`, 4 bytes | 0x007D1F00, 0x007D31C0 | 0x0073A860, 0x0073B540 |
| 0x013071C8 | `ZoomCurrentFrame`, `int`, 4 bytes | 0x007D1F00, 0x007D31C0 | 0x0073A860, 0x0073B540, 0x007D1F00, 0x007D2290, 0x007D2390, 0x007D31C0 |
| 0x013071CC | `ZoomLastFrame`, existing `int` storage view, 4 bytes | 0x007D1F00, 0x007D24A0 | 0x007D1F00, 0x007D24A0 |
| 0x013071D0 | `ZoomPulseDown`, existing `bool` storage view, 1 byte | 0x007D1F00, 0x007D24A0 | 0x0073A860, 0x0073B540, 0x007D1F00, 0x007D24A0 |

`0x013071D0` is not a dword object. Its observed stores write byte values zero and one; its loads test that byte. No object extent or identity is established for the three bytes after it. Likewise, the unused cell at `0x013071B8` remains undefined. A verified reference or object layout giving either interval an actual object extent would settle these gaps.

The floats are independently typed by x87 `fstp`, `fld`, `fsub`, and `fdiv` instructions and stores of the IEEE single precision value one. Signed direction comparisons select the positive and negative fade branches. Integer frame counters increment and divide through `fidiv dword ptr`. `ZoomLastFrame` is compared with and updated from `TheGameLogic`'s frame at receiver offset `0x3C`. `ZoomPulseDown` selects increasing versus decreasing pulse branches. Neither equality alone nor byte loads alone prove EA's original integer signedness or `bool` versus character declaration; the established code's compatible types are retained.

## Owners and Zero Hour correspondence

The seven slots of the retail tables at VA `0x0112898C`, `0x011289B0`, `0x011289D4`, and `0x01128A2C` are read as raw dwords and every five byte `E9` thunk is followed to its body in `retail-vtables-callers-corrected.log`. The first table's init and set slots reach RVAs `0x007D0AF0` and `0x007D1020`. The init loads EA's `shaders\monochrome.pso` string, clears the current frame at `0x013071B4`, and receives its shader member address at `ECX+4`. The set body updates the four BW cells and supplies the fade value to pixel shader constant 2. The second table's init and set slots reach `0x007D0C00` and `0x007D1AA0`; both use the same BW cells. Its postRender at `0x007D1610` reads the BW value for alpha. These table slots, shader string, existing matched class identity, and reference body jointly establish the BW ownership without naming its address qualified fallback class.

Zero Hour's `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp:267` through line 270 define these exact four `ScreenBWFilter` members. Its header declares them protected, which agrees with the existing `@@1HA` DIR32 spellings. Reference `ScreenBWFilter::set`, `ScreenBWFilterDOT3::set`, and `setFadeParameters` share the same frame increment, signed direction, division, completion reset, and alpha operations as retail. The 30 byte retail setter at RVA `0x0073A8A0` accepts two stack `int` arguments, clears `0x013071B4`, and stores the first argument to `0x013071B0` and the second to `0x013071AC`. It has no receiver and returns with plain `ret`, consistent with the existing static member ledger contract. The raw call scan found no direct `E8` or `E9` callers of its ILT; no caller contract is inferred from that absence.

The third table's init and set slots reach `0x007D2390` and `0x007D1F00`. Init clears `0x013071C8` and loads the separate EA shader `shaders\monochromezoom.nvp` and `circleFade.tga`. Set updates the BC/C0/C4/C8 group and the last frame and pulse direction cells at CC/D0. The fourth table's init, postRender, and set slots reach `0x007D2290`, `0x007D2D30`, and `0x007D31C0`; they use this same zoom group. The zoom bodies receive their shader and texture fields through ECX while addressing all fade cells absolutely, so these cells are separate shared storage rather than the receiver's instance fields.

There is no `ScreenZoomFilter` in the checked Zero Hour shader manager. Its BC/C0/C4/C8 cells reproduce the BW fade algorithm in a separate BFME filter. CC/D0 perform roles analogous to Zero Hour `ScreenMotionBlurFilter::m_lastFrame` and `m_decrement`, but the reference fields are instance members, and the BFME pulse branch also changes time of day. This is a behavioral analogy, not proof of an exact Zero Hour variable identity. Zero Hour's `ScreenCrossFadeFilter` members are also distinct: retail updateFadeLevel at RVA `0x007D35B0` accesses VA `0x01307200` through `0x0130720C`, uses the reference negative fade branch's increment order, and returns a completion flag. Its raw disassembly is in `retail-owners-disasm.log`.

The two `g_bfme*` pins are not the same object. `g_bfme914Count` at RVA `0x00F071B4` is precisely the BW current frame cell, as the store at body RVA `0x007D0C00+7` proves. `g_bfmeZero986B` at RVA `0x00F071C8` is precisely the zoom current frame cell, as `0x007D2290+7` and `0x007D2390+0x2A` prove. Both existing pins remain untouched.

## Declaration and definition contract

`spellings-and-overlaps.log` lists every competing DIR32 spelling and its number of game files with textual declarations or definitions, before editing. `sources.log` contains the complete directed game source search. `spellings-and-overlaps.log` also proves that each proposed object has no existing data owner and no interior DIR32 name. Counts select no identities: BW uses the reference proven protected members, while zoom keeps the established descriptive storage labels and explicitly leaves EA's exact spelling unresolved.

BW already has exactly one definition of each member in the game's `W3DShaderManager.cpp`. Four data rows record these existing definitions. These members are protected, so `add_data_match.py` can size them through its sanctioned derived access probe; the private member exception is unnecessary. The missing `?m_curFadeValue@ScreenBWFilter@@1MA` DIR32 spelling is added beside every existing spelling. The existing compatible partial class contracts gain declarations and friendship where needed to name the protected storage; this adds no callable wrapper, forwarder, alias, receiver field, or inheritance relationship.

The zoom set translation unit defines the six retained `Zoom*` objects once, with six byte verified data rows. Its pulse count at VA `0x012BC140` is outside this question and remains an extern. Every directed game declaration of the competing labels is respelled to its canonical storage. The R2 direction's misleading `void *` view becomes `int`; converting the unchanged pointer argument to `int` preserves the raw register store and does not rename or retype that function. Its char flag view becomes the existing bool view. No function ledger names, pins, body extents, generated source, or shared headers are changed.

## Refutation and raw verification

A BW table slot routing to a different owner, a shader string belonging to another filter, a different setter operand address, or a byte mismatch in any changed source refutes the BW correction. A zoom slot routing elsewhere or an incompatible type or extent in the observed accesses refutes its shared storage contract. An EA symbol, debug string, independently proven layout, or original BFME declaration tying the zoom group to exact member names would resolve the remaining original spelling question; algorithm similarity alone would not.

Raw disassemblies are `dis-007d1020.log`, `dis-007d1aa0.log`, `dis-007d1f00.log`, `dis-007d24a0.log`, and `dis-007d31c0.log` under `build/rlink/screen-fade-1791159203/`. The owner initializers, setters and cross fade comparison are in `retail-owners-disasm.log`; table bytes, thunk chains, and exact shader and texture strings are in `retail-vtables-callers-corrected.log`. Reference extracts are in `reference-and-reader.log`, `owners.log`, and `contracts.log`. The source, data, ledger, pin and link gate receipts and outcomes are recorded in `build/worker-final.md`.
