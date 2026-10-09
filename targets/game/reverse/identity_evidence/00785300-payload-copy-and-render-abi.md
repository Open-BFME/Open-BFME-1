# Render attempt at RVA 0x00785300

The saved `Rva00785FD0Item::draw` body remains a partial reconstruction. This run starts at revision `f013ba49642ce1ae4a6536f32321e1e684bd223a` and preserves the existing owner, method and descriptive names. The final source emits 1262 bytes against the verified 1264-byte extent. Its probe reports 235 differing non-relocation bytes, compared with 249 for the previous bank. Both have four relocation sites that do not align with retail operands, so these probe counts are diagnostics rather than relocation verification. The first differing byte is the branch displacement at `+0x30`; the first differing arithmetic instruction is at `+0xF5`, and the first normalized structural difference is at `+0xF8`. No source recovery or ledger conversion is claimed.

## New evidence and refutation tests

The current checkout contains the complete geometry parser, a bounds pass over the same item, the line emitter, the renderer append routine and the counted texture accessor. The retry hypothesis was that independently established payload copy semantics and canonical callee declarations could improve the old scalar reconstruction. It would be refuted if the actual parser routes reached helpers with additional fields or ownership, if complete callers contradicted the receiver or result convention, or if measured typed shapes failed to improve the old bank. The payload tests support float pairs, and the reference-output transform improves the probe. The other tested transform forms regress.

The older claim that the close helpers consume EDX is refuted by both complete bodies: neither reads EDX. The caller still forwards the cursor in that register. The final source retains that forwarding through member-function casts while naming the canonical no-argument declarations. The seven-byte doubled-count body tail-jumps to the append routine, whose EAX pointer result is consumed by this target. Its existing void declaration therefore needs a function-pointer cast at this call site. These casts remove three unresolved spellings without changing the final probe count. No pin was added.

## Complete boundaries and callers

The target decodes through its sole `ret` at `+0x4EF`, with no outgoing direct conditional branch or tail jump. Its kind dispatch is a chain of comparisons, and every branch stays within the extent. The epilogue restores the EH chain, saved registers and aligned stack frame. The decoded flush at RVA `0x00785FD0` passes the queue node's pointer at `+8` in ECX through ILT `0x00049062`, without stack arguments. The complete 191-byte caller at `0x007874F0` copies six dwords into item offsets `+0x10` through `+0x24`, then passes the same item in ECX through that ILT. These observations establish the zero-stack-argument member ABI and affine storage, not EA's original class name.

The parser installs the shape tables at VAs `0x01126AFC`, `0x01126B14` and `0x01126B2C`. Their kind methods return 1, 0 and 2, respectively. Their used accessor slots return ECX unchanged. The textured shape exposes itself through slot 2, the solid view through slot 3, and the line view through slot 4. These are separately decoded indirect-call routes; no receiver adjustment or hidden result occurs at those slots. The existing address-derived names remain appropriate.

Raw complete target, caller and helper disassemblies are retained as `build/apt-render-00785300/decode-<rva>.log`. Checked inventories are `checked-<rva>.log` in the same directory. `vtable-slots.log` records the slot entries and resolved methods. All extents used as payload or ABI evidence were passed to the coordinator's `checked_callees.py` helper. Inventory success alone is not the boundary proof.

## Payload evidence

The complete parser at RVA `0x00788A30` supplies six float inputs to the triangle append route and four float inputs to the line route. Triangle append goes through `0x0003CE84` to `0x00788810`, then through construction thunk `0x0003AA26` to `0x00784DB0`, and finally through `0x00038550` to `0x00783D50`. Line append goes through `0x00048572` to `0x00788860`, through `0x00033AAA` to `0x00784DD0`, and through `0x0003F170` to `0x00783D90`.

Both final copy bodies are 46 bytes and have no calls. The triangle copy loops three times, reading and writing dwords at pair offsets 0 and 4 and advancing both arrays by eight bytes. It covers every dword from 0 through 20. The line copy performs the same loop twice, covering offsets 0 through 12. The target subsequently reads each field with dword x87 loads as coordinates. No additional payload field, pointer retention or destructor operation occurs in those copy bodies. This supports three and two float pairs with field-wise copy constructors, independently of the misleading ProductionPrerequisite and W3DAnimationInfo ledger labels.

The scratch declarations for `Rva00785300Triangle` and `Rva00785300Line` reproduce both copy constructors exactly, with no relocations. Raw probes are `probe-triangle-copy.log` and `probe-line-copy.log`; their source is `paircopy-evidence.cpp`. These are validation experiments, not assigned helper conversions. No STL ledger row or pin was changed.

## Texture ownership and unwind

The complete 43-byte accessor at `0x00785230` reads the source at receiver offset `+0x18`, forwards hidden four-byte result storage to `0x007849F0` through `0x0003BA61`, returns that storage in EAX and executes `ret 4` on both paths. The complete 57-byte helper reads the source's virtual slot 4, copies the returned handle's only pointer and conditionally increments the pointee's 16-bit count at `+4`. The final handle uses the native texture header's Add_Ref and Release_Ref declarations. Its destructor reproduces the 12-byte null-guarded handle release at `0x0005CC00`, which tail-jumps to the complete 36-byte release body at `0x009EB7A0`. That release decrements the low word, checks the delete flag and either returns or tail-dispatches virtual slot 8. Its result is unused.

The standard EH helper rejects the stack-alignment prefix, so the registration sequence was parsed at target `+6`. Handler RVA `0x00C50D58` references FuncInfo RVA `0x00E403D0`. States 0, 1 and 2 all have predecessor -1 and clean up EBP-relative handles at `-0x38`, `-0x2C` and `-0x34`, respectively. Each cleanup tail-jumps through `0x00030652` to the same counted handle destructor. The final object's FuncInfo has three states with predecessor -1, the same frame offsets and the same cleanup semantics. Raw evidence is in `eh-manual.log`, `object-eh-final-source.log` and `probe-final-dtor.log`.

The target's renderer bind uses ECX for the renderer and EDX for a handle address. The complete bind routine retains the new pointer's 16-bit count, releases the old pointer and writes the new pointer. The line emitter takes the cursor address in EDX, two point addresses, a four-byte float width and a four-byte color on the stack, and ends in `ret 16`. The append routine takes ECX and an EDX count and returns a pointer in EAX on both return paths. Its indirect buffer lock passes the receiver on the stack as well as offset, size, output address and flags. The close routines use a stack receiver for their indirect unlock and ignore the forwarded EDX cursor. These observations agree with the final declarations and casts.

## Measurements and rejected shapes

Every trial source and unedited probe output is under `build/apt-render-00785300/`. The running measurement record is `build/verdict.txt`. The bounded EH search and its source snapshots are retained under `build/shape_search/8a402e64f4d548b398108779dd07a9b5/`.

| Trial | Emitted bytes | Probe differences | Observation |
|---|---:|---:|---|
| baseline | 1262 | 249 | Reproduces the old bank. |
| canonical | 1279 | 550 | Casting the explicit-out accessor to a value return introduces a temporary. |
| pair | 1262 | 581 | A two-argument coordinate setter changes store scheduling. |
| routes | 1262 | 249 | Canonical renderer call casts alone do not improve the bytes. |
| paircopy | 1262 | 549 | Correct copy declarations alone worsen the target shape. |
| pairbyvalue | 1310 | 918 | Returning transformed pairs creates extra storage and copies. |
| pairout | 1262 | 235 | Separate scalar output references improve the first transform. |
| pairreference | 1262 | 544 | A paired output reference regresses. |
| pairassignment | 1278 | 872 | Explicit field-wise assignment reduces the by-value overhead but still regresses. |
| typedhandle | 1262 | 235 | Correct counted-copy semantics do not change the best shape. |
| nativehandle-fixed | 1262 | 235 | Canonical texture declarations preserve the best shape. |
| final-source | 1262 | 235 | Canonical renderer casts preserve the best shape and resolve three former spellings. |

The initial native-header trial failed on duplicate placement-array operators. The corrected trial uses always.h's existing guard because STLport already included the standard new header. This is a source include fix, not evidence against the target body. The bounded EH search tested the unchanged source and the no-exceptions STL prefix; neither improved the bytes. The earlier operand-spelling and symbol-name sweeps were not repeated.

## Remaining blockers and reopening condition

The target still differs in x87 operand and term order, with the first remaining arithmetic divergence at `+0xF5`. Later residues include the solid vertex at `+0x236`, textured vertex and UV expressions starting at `+0x39C`, and the final textured iteration. The resulting instruction lengths leave two bytes missing and shift later relocation operands. `probe-final-source.log` retains the full side-by-side decode, so the offsets and exact instructions can be rechecked without relying on the probe's candidate label.

The scoped byte gate fails for the mismatching body and the single remaining unresolved spelling `?bfmeGoRD@BfmeThingRD@@QAE?AVRva00785300TextureRef@@XZ`. Its actual hidden-return ABI is independently decoded above; a future exact landing must resolve this spelling to the proven route without inventing an identity. The canonical renderer spellings already resolve. Full relocation equality remains unverified, and the source has no matched ledger row. The declared-unmatched check therefore refuses it as a landing. The class gate passes, and the name-regression module reports no descriptive-to-placeholder substitutions. The CLI accepts revision pairs rather than source paths, so the source comparison uses its `regressions` function directly. The banked path was probed again and reproduces the final source's count; its raw probe and failing gate are `probe-banked.log` and `scoped-gate-banked.log`. The banking tool selects the new source with measured quality 0.8109 against the old source's measured 0.7998. The historical 0.886 label was an instruction-shape score, not the current byte-distance quality. Exactly one verdict row was appended for this run.

Reopen this target with an independently established affine/coordinate API or compiler context that predicts the remaining x87 ordering, rather than another spelling sweep. An improvement must survive a retail-size probe against this final source, complete relocation resolution and the scoped byte gate. No full gate is required for this partial evidence-only handoff because no game source, shared header, ledger row or symbol pin changes.
