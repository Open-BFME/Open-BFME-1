# Partial reconstruction at RVA 0x0037B9F0

The candidate is a partial, not a conversion. The ledger remains the 393-byte generated assembly row at revision cc6a27760aea345a3d4378e9c30a0c5ae9903e07. The candidate symbol is `?update0037B9F0@Rva0037C310Owner@@QAE_NXZ`. Its owner and method identity remain address-derived. This run used gpt-6.1-sol and found no saved body.

## Retry hypothesis and refutation

Current Object, GameLogic, FXList and StringBase declarations provide verifiable contracts for the earlier accessor and object-effect blockers. The neighbouring `EmotionNugget.cpp` supplies an address-derived owner layout, not proof of the Emotion name. The hypothesis is that the getter returns an owning AsciiString by value from config +0x3C, and that Object query and FX dispatch use their canonical contracts. Extra copied fields, a different hidden-return ABI, stack arguments at virtual slot +0x4C, or different decoded thunk destinations would refute it. Complete decoded helpers and callers support these contracts. Inline frame and delay accessors are the measured scheduling hypothesis that improves trial 2 to trial 3.

## Boundary, types and ABI

All raw evidence is under `build/rva0037b9f0/`. `target_decode.log` decodes entry RVA 0x0037B9F0 through its only return at 0x0037BB78 and subsequent int3 padding. All conditional branches stay inside the extent. `checked_callees_target.log` inventories its eight direct targets. The complete 2052-byte caller is in `caller_decode.log`. At RVA 0x00291565 it loads ECX from owner +0x7C, passes no stack arguments through ILT 0x0000C69E, and consumes AL. `thunks_endpoints.log` decodes the jump to the target. The candidate is a niladic thiscall returning bool with no receiver adjustment.

The actual getter through ILT 0x00041BF0 is the complete 32-byte body at RVA 0x0037B0D0. It passes this+0x3C to StringBase<char>'s copy constructor, returns hidden output storage in EAX, and ends with ret 4. The complete 121-byte copy helper at RVA 0x00887B60 reads one input handle, writes one output handle, and increments the pointed header's reference count at +0. The complete 134-byte release helper at RVA 0x00887940 decrements that count, conditionally frees the header, and clears the handle. The target reads the unsigned short length at header +4. This establishes the owning string independently of allocation sizes and donor names. Trial 11's complete getter measures exact modulo its one relocation in `getter_probe11.log`; it is supporting evidence, not an additional assigned recovery.

`helper_decode.log` and `checked_0x*.log` retain all complete direct helper inventories. The FX member at RVA 0x00428180 requires 166 bytes to include ret 8, although its existing ledger row records 163. `cleanup_decode.log` retains the full 166-byte body; this run does not edit that other row. Object's modifier receives a string reference then a 32-bit count and returns AL. GameLogic lookup takes a 32-bit ID and returns an Object pointer. FX dispatch receives primary then secondary Object pointers and cleans 8 bytes. The notify helper is niladic.

The target's indirect query-result call uses its pointer as ECX, no explicit arguments, and vtable slot +0x4C. EAX replaces the primary Object used in FX dispatch, with null falling back to the original Object. The independent neighbouring `EmotionNugget.cpp` has the same sequence. The slot's semantic identity and concrete implementations remain unknown. The query helper's indirect tail through contain slot +0x68 and all null returns are decoded. No container is accessed by the assigned body; unaccessed owner storage stays opaque.

## Exception cleanup

`eh_info.log` gives one unwind state, 0 to -1, with cleanup RVA 0x00C1B1E0. `cleanup_decode.log` follows lea ECX,[EBP-0x10] through ILT 0x0000D828 to destructor RVA 0x0005EE90 and then releaseBuffer RVA 0x00887940. Their checked inventories are retained. `diagnostic.log` independently reads the compiled COFF: one unwind state to -1 with the same EBP-0x10 adjustment and canonical AsciiString destructor. Only the modifier-application string temporary is protected; no constructor allocation or element cleanup is claimed.

## Compiler measurements

The following table is generated from unedited probe output. Every probe explicitly uses retail size 393; differing bytes exclude relocations and are diagnostic, not acceptance. Every trial source and raw log is retained.

| Trial | Hypothesis | Compiled bytes | Differing bytes | First offset |
|---|---|---:|---:|---|
| 1 | Named string local and direct fields | 393 | 255 | +0x18 |
| 2 | Expression-lived string | 390 | 235 | +0x52 |
| 3 | Inline frame/delay accessors | 393 | 15 | +0xEF |
| 4 | Inline Object getter | 393 | 15 | +0xEF |
| 5 | Inline query-object helper | 403 | 102 | +0xED |
| 6 | Declaration order | 393 | 15 | +0xEF |
| 7 | Canonical FX wrapper | 393 | 15 | +0xEF |
| 8 | Visible GameLogic lookup | 393 | 15 | +0xEF |
| 9 | Integer length accessor | 395 | 243 | +0x52 |
| 10 | Native StringBase emptiness | 393 | 15 | +0xEF |
| 11 | Full noinline getter | 393 | 15 | +0xEF |

The mandatory EH search retained five sources under `build/shape_search/f79ed060b1bd4855a30206de277d33b2/` and did not improve trial 1. The non-EH generator's frame-array alternative was tested in the two-source search under `build/shape_search/0c72df01027e4f35b5e61cd9cd28c816/` and did not improve trial 2. The native Object getter and declaration-order trials are the two unchanged pure allocation experiments. The query-object helper and integer length accessor worsen the body. Canonical FX, lookup, string predicate and complete getter visibility do not reduce the residue. The bank keeps the canonical inline string predicate and a typed string member at +0x3C.

## Remaining blocker and reopening condition

`retained_probe.log` measures the final bank source. `diagnostic.log` lists the remaining offsets: +0xEF, +0xF1, +0xF7, +0xF8, +0x103, +0x105, +0x10D, +0x11A, +0x11E, +0x122, +0x127, +0x12A, +0x12E, +0x139 and +0x13B. The candidate keeps the primary Object in EDI and the ID/FX pointer in EBP; retail reverses them. The query null check is cmp EAX,EBP instead of test EAX,EAX. Reopening needs independent source evidence that changes this pointer lifetime or a demonstrated MSVC lever beyond the rejected getter, helper and declaration-order shapes.

The ordinary scoped verifier in `bank_gate.log` is red, including an absent address-derived getter pin. No pins were added for this partial. The proposed symbol `?copyString0037B0D0@Config0037B9F0@@QAE?AVAsciiString@@XZ` would bind to body RVA 0x0037B0D0, reached through decoded ILT 0x00041BF0. `diagnostic.log` supplies only this verified binding in memory, finds no unresolved calls, and still finds the same fifteen differing bytes. This is not a passing gate or a pin landing. Existing pin consistency passes. Owner and config identities remain unproved.
