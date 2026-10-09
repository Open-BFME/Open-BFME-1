# 0x00764290: private helper ABI and visibility records

## Result and reopening condition

The target remains a partial reconstruction, banked at `targets/game/reverse/attempts/0x00764290.cpp` under the existing `BfmeRva64290::method` identity. Its measured trial is retained as `build/target-00764290/bank-final.cpp`. The scoped byte gate fails. A new experiment must explain how to move the end-field zero store across the x87 comparison at target offset +0x21E and how to load the accumulated value before the increment at +0x29B. Repeating sum commutation, a local float temporary, declaration ordering, or the exhausted reset-store variants is unsupported. The exact helper recovery is dependency evidence and adds no newly recovered bytes to the ledger.

## Revision and new hypothesis

The tested base revision is `1d3dbc6e51cad6ace6cea0d2e30f25ada4e38e3e`. The model is `gpt-6.1-sol`. The prior full attempt used a function-pointer call because `0x0075BCC0` had a compiler-private register argument. The current ledger supplies its landed C++ body in `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp`. The retry hypothesis was that compiling this static helper with its caller and the canonical render-object declarations would reproduce that ABI. A different argument register or cleanup sequence would refute it. `build/target-00764290/helper-gate.log` verifies all 160 helper bytes with the existing direct callee resolution. The target calls now reproduce the EDI receiver and four caller-cleaned stack slots. No pin or ledger row is added, including any STL symbol.

The nearby landed `Open2Conv006.cpp`, `Gen00764700ControllingPlayerNotify.cpp`, and `AudioEventRTS.cpp` were read rather than inferred from their ledger labels. The Zero Hour donor was also read. Its visibility loop supports the literal and broad method identity, but its recursive helper and smaller records do not describe the BFME implementation.

## Boundary, receiver, and identity

`build/target-00764290/retail-evidence-full.log` decodes the complete target and the helpers used for layout and ABI evidence. `build/target-00764290/boundary-audit.log` records every return and branch. The target ends at its RET at RVA 0x00764612, with every conditional destination instruction-aligned and internal. It has no EH frame or tail jump. The helper at 0x0075BCC0 ends at +0x9F, and all its branches are internal. The audited constructor's sole indirect switch has five table entries, all reaching the three decoded internal return paths.

`build/target-00764290/vtable-identity.log` independently finds target slot 28 in table VA 0x01123C68. The complete constructor at RVA 0x00773360 installs that table at primary receiver +0x0C and the primary table at +0. Thus this entry receives the secondary interface pointer. Target render-object +0x28 corresponds to primary +0x34, while its drawable reference at receiver -4 corresponds to primary +8. The pinned `W3DModelDraw::updateSubObjects` name, the installing constructor, and the Zero Hour error literal jointly support the method identity. The bank retains its established address-derived owner and member names. No guessed semantic name replaces a banked name.

## Actual record construction and ownership

The landed writer at RVA 0x00775C70, size 640, is decoded in full. Both its append paths actually call ILT 0x000334EC, which reaches the complete 103-byte copy helper at RVA 0x00768D20. That helper calls the complete 121-byte `StringBase<char>` copy body at RVA 0x00887B60 for offset +0, copies one byte at +4, skips +5 through +7, and copies every dword at +8, +0x0C, +0x10, and +0x14. No payload field is omitted. The string copy reads the source buffer pointer, writes the destination pointer, increments the buffer's reference count when non-null, and uses the imported critical-section operations. The record therefore owns a reference-counted narrow string, followed by a normalized hide byte and four 32-bit carriers. The writer's incoming float values and the target's x87 reads and writes establish all four carriers as floats. Allocation size and matching template names were not used to distinguish a scalar from a pair.

The constructor and complete insert-overflow helper at RVA 0x00771B10 establish two three-pointer vector representations and a 24-byte element stride. Relative to the target receiver, their begin/end/capacity fields occupy +0x40/+0x44/+0x48 and +0x4C/+0x50/+0x54. The bank's vector view preserves the earlier begin/end member names and exposes all three pointers. The existing witnessed `m_subObjectVec` label at primary +0x5C is not transplanted into this view because it does not identify the start of either decoded vector.

`build/target-00764290/copy-unwind.log` follows the copy helper's EH handler, FuncInfo, unwind map, and sole cleanup action. State zero transitions to -1 and passes the placement and allocated-pointer slots through ILT 0x0002AAA9 to the one-byte RET body at RVA 0x000607F0. It does not destroy a completed element. This agrees with failed placement construction rather than an owned child pointer. The target itself constructs no record and has no constructor unwind states.

## Calls and declarations

The canonical `RenderObjClass`, `HTreeClass`, `AsciiString`, `StringBase<char>`, `Overridable`, and debug-format declarations are included. The render-object virtual calls were checked separately: slots +0x7C (name and output index), +0x190 (promoted hide byte), +0xE4 (tree pointer), +0x88 (LOD zero and subobject index), +0xBC (bone count), and +0x6C (subobject count). Reference release decrements the count at +4 and dispatches `Delete_This` through slot zero, as in the canonical inline. The helper's object overload of `Get_Sub_Object_Bone_Index` is distinct from the target's two-integer overload.

The complete transition setter at RVA 0x0075C8B0 has receiver ECX, object pointer then float stack arguments, and RET 8. Its target receiver is this -0x0C. The complete override helper at RVA 0x00087A80 returns a pointer in EAX with no stack arguments. ILT 0x000022BB reaches that body. The debug format constructor at RVA 0x008895F0 receives the explicit buffer and varargs on the stack, returns the buffer in EAX, and leaves caller cleanup. The target forwards that return through virtual slot +0x38 and ignores its result before calling slot +0x4C on the original stream. The debug-manager two-zero-argument method has two 32-bit stack arguments and a pointer return; their semantic parameter types remain opaque. The historical global label is retained rather than asserted as a recovered manager class identity.

Raw inventories are `build/target-00764290/checked-target.log`, `checked-hide-helper.log`, `checked-blend-helper.log`, `checked-parent-helper.log`, `checked-value-writer.log`, `checked-value-copy.log`, `checked-vector-insert.log`, `checked-string-copy.log`, `checked-format.log`, `checked-copy-cleanup.log`, and `checked-delete-cleanup.log`. These inventories corroborate the decoded instructions and do not independently prove names.

## Measured experiments

The table is generated from the preserved probe outputs. The diagnostic quality masks relocation slots and is a ranking score, not acceptance. All trials and their sources remain under `build/target-00764290/`; `receipts.jsonl` retains measured experiment timestamps. The store-family search and its immutable trials remain under `build/shape_search/a83f3bd50ec243f2bdb399c763f7c1e6`.

| Experiment | Compiled size | Non-relocation differences | Diagnostic quality | Raw output |
| --- | ---: | ---: | ---: | --- |
| Saved preferred skeleton | 417 | 348 | 0.0 | build/target-00764290/probe-preferred-raw.log |
| Saved full alternative | 871 | 799 | 0.0489 | build/target-00764290/probe-alternative-raw.log |
| Visible helper and bool payload | 908 | 607 | 0.3048 | build/target-00764290/probe-trial03.log |
| Debug call lifetime | 900 | 333 | 0.6274 | build/target-00764290/probe-trial04.log |
| Native string and debug declarations | 908 | 519 | 0.4027 | build/target-00764290/probe-trial12.log |
| Native vector and global declarations | 908 | 486 | 0.4394 | build/target-00764290/probe-trial20.log |
| Shared clamp call | 899 | 7 | 0.9922 | build/target-00764290/probe-trial21.log |
| Commuted float sum | 899 | 7 | 0.9922 | build/target-00764290/probe-trial22.log |
| Reset after rate selection | 899 | 37 | 0.9588 | build/target-00764290/probe-trial23.log |
| Explicit reset decision | 909 | 309 | 0.634 | build/target-00764290/probe-trial24.log |
| Local float sum | 899 | 7 | 0.9922 | build/target-00764290/probe-trial25.log |
| Names preserved in final bank | 899 | 7 | 0.9922 | build/target-00764290/probe-bank-final.log |

The final discrepancy consists of two instruction-order differences. Retail has `fcomp [zero]` at +0x21E followed by `mov [end], ebx` at +0x224; the candidate moves the store before that comparison. Retail has `fld [rate]` at +0x29B and `fadd [increment]` at +0x29E; the candidate exchanges those operands. One zero-global DIR32 operand consequently sits three bytes later than retail. The masked distance must not be mistaken for verified relocation layout. The raw scoped gate fails and reports no unresolved direct call target. The zero-store spelling after rate selection worsens the distance; an explicit decision local also worsens size and distance. Both sum commutation and a local sum collapse to the same compiler result and are exhausted.

## Verification limits

`build/target-00764290/scoped-gate.log` is the failing scoped candidate gate using an in-memory row without changing the ledger. `helper-gate.log` passes strict dependency byte verification. `check-csv-final.log`, `pin-consistency.log`, `class-bank.log`, and `names-final.log` pass. `handoff-validation.log` verifies the bank body against the measured source, confirms no name regression, and confirms that exactly one verdict row was appended. `declared-final.log` fails the zero-ledger-row source rule because the candidate is intentionally a partial scratch body; it is not a source landing. No full gate is required for a bank and evidence note. Source claims, string addresses, and global addresses must be verified through the ordinary landing gate after the instruction mismatch is resolved.
