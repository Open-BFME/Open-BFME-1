# Route-action parser visibility at RVA 008D0B00

The reconstruction remains partial. The saved body compiles to 353 bytes against the independently checked 352-byte target, with 94 relocation-masked positional byte differences and the first differing byte at +0xE8. The previous bank reproduced at 353 bytes with 126 differences. These counts are diagnostics, not relocation acceptance or identity proof. The instruction prefix through +0xE7 now agrees outside corresponding relocation operands.

The tested revision is 07a219def195b93798ffefa35aef97d473559f40. The model was gpt-6.1-sol. The ledger still owns the target as the generated dump in game/gen_asm/d_008cb600.asm. No game source, ledger row, pin, shared header, or verification baseline was changed by this investigation.

## New hypothesis and its controls

The old bank separated the address-taken parse output from a retained receiver. Moving the retained copy before creation enlarged the frame and changed register allocation. The new hypothesis was that the native translation unit exposed the complete parser chain, allowing VC7.1 to prove that the output-slot address does not escape. A single receiver variable could then remain in EBP across creation without requiring the extra local lifetime introduced by that copy.

Both parser bodies were read from their matched sources and checked against complete retail code. The saved body includes inline, non-inlined views of RVA 008C6320 and ParsePath8C4DA0. Their output-pointer argument is passed only between these two helpers and is otherwise used for stores. It is never stored globally or passed to the string constructor, node lookup, pool callback, or another unknown callee. The direct parser forwards the slot at +0xAD; its other output-slot load at +0x75 ends in the store at +0x7F. The path parser's output-address loads at +0x57, +0x68, +0xF5, +0x1A0, and +0x1DF all lead to stores through that address. The named fields in the local views retain address-derived owners.

The refutation condition was that hiding either complete helper body would preserve the recovered prefix. It did not: removing either body produced 349 bytes with 249 masked differences, beginning at +0x18. Keeping both definitions after the target instead of before it reproduced the 353-byte, 94-difference result. This supports whole-translation-unit effect propagation rather than a declaration-order explanation. Static helper copies changed the private call ABI and were rejected; the bank uses external inline copies with __declspec(noinline).

Raw controls are build/route008d0b00/control-path-opaque.log, build/route008d0b00/control-prepare-opaque.log, and build/route008d0b00/control-helpers-after-target.log. The cleaned preferred trial and its complete probe are build/route008d0b00/best-clean.cpp and build/route008d0b00/best-clean.log.

## Boundary, ABI, and lifetime evidence

The complete target ends in RET at +0x15F. Its conditional branches remain inside that extent and all paths reach the common cleanup. Its direct callees are RVA 00898300, 008B8E50, 008C6320, 008CC940, and 008CF740. The four complete callers at RVA 008D19C0, 008D1A10, 008D1AE0, and 008D1B60 independently pass two stack words and perform caller cleanup. The target has no receiver adjustment, hidden result storage, or callee stack cleanup. Its return value is unused by these callers.

The integer conversion consumes the second stack value and returns the independent count in EAX. The parsed receiver is a separate pointer. The array helper consumes ECX and one signed index, checks both bounds, reads its pointer array at +0x20 and count at +0x28, clears the low pointer tag, and ends in RET 4. The parser consumes five cdecl arguments and returns its boolean in AL. Creation receives ECX plus six stack words and every decoded return removes 0x18 bytes. The hub receives ECX plus receiver, callable value, and count, and its complete exit removes 0x0C bytes. The target's three virtual calls use slot +0 or +4 with an ECX receiver and no stack arguments; their results are unused. These are invocation views, not claims about every dynamic class or an unused return value's original source type.

The string is one pointer to a block with a 16-bit reference count at +0 and text at +8. Its default constructor and 22-byte destructor were decoded independently. The complete 125-byte text constructor writes a pointer into the holder, writes four 16-bit header fields at block offsets 0, 2, 4, and 6, and copies the terminator into the text starting at +8. The saved view keeps the other header fields opaque. No container payload type is inferred from allocation size. The literal-looking operand at VA 012D5298 is the shared empty string block, not an installed vtable.

The target's FuncInfo at RVA 00E4965C has one state. State 0 unwinds to -1 through action RVA 00C5A620, which forms ECX from EBP+4 and jumps to the canonical string destructor at RVA 00891B80. The target sets state 0 at +0x51 and resets it to -1 during normal destruction at +0x139. The preferred source retains that single string lifetime; it introduces no owning value wrapper or additional constructor cleanup.

Complete checked-callee inventories and decoded instructions are retained under build/route008d0b00 as callees-XXXXXXXX.log and decode-XXXXXXXX.log. The clean aggregate receipt is build/route008d0b00/evidence-recheck.log. Secondary constructor, node-lookup, CRT conversion, import-thunk, and unwind-action checks are recorded in build/route008d0b00/secondary-summary.log. The unwind map and native string constructor/destructor instructions are in build/route008d0b00/unwind-and-virtual.log; the later attempt in that log to inspect a dynamically initialized fallback pointer failed and provides no virtual-owner evidence.

The integer helper has 136 bytes of executable code followed by a 20-byte jump table and a 42-byte tag map. All five table destinations lie in the decoded code, and both string tags select the same arm. The 198-byte linear checked-callees request rejects the trailing table bytes; the 136-byte code request passes, and build/route008d0b00/residue-map.log retains the complete table interpretation. The node lookup similarly has 840 executable bytes with eighteen RET 8 exits, followed by a 52-byte target table and a 37-byte selector map within its 929-byte ledger extent. These data tails are not instructions or additional return paths. The integer helper's floating conversion tail was followed through the complete 117-byte __ftol2 body; its low EAX result supplies the target's 32-bit count.

## Remaining mismatch and rejected experiments

| Retail offsets | Preferred-source difference |
| --- | --- |
| +0xE7 and +0xEA | The array element is loaded into EAX instead of ECX, and the ownership read uses that receiver. |
| +0xF3 through +0xFE | The compiled release path inserts MOV ECX,EAX at its +0xF7. Its virtual table is in EDX rather than EAX. The extra instruction shifts the loop exit by two bytes. |
| +0x100 through +0x141 | The two-byte shift continues. The fallback at +0x110 uses EAX instead of ECX for the context pointer, the count argument uses ECX instead of EDX, and the final virtual table uses EDX instead of EAX. The stack homes and ownership operations agree. |
| +0x142 through +0x15F | The pool callback pushes the dying block before loading the pool through the five-byte EAX form, rather than loading ECX first. This saves one byte and leaves the full body one byte longer than retail. |

All 94 differing byte offsets, the extra emitted byte at +0x160, and the three displaced relocation sites are retained in build/route008d0b00/residue.json. The corresponding instruction alignment is in build/route008d0b00/residue-map.log. The positional masked count can hide relocation-layout differences; none is treated as accepted bytes.

Rejected families include separate receiver capture before creation and inside argument evaluation; output and string scope permutations; native string base construction and temporary initialization; canonical callee declarations; complete value-helper visibility; native indexed and zero-based accessors; copied and referenced array elements; repeated stack expressions; native pop helpers; for, while, and do loop forms; byte and boolean ownership accessors; qualified field views; virtual-call ABI adapters; fallback statement forms; callback temporaries; and compiler-option controls. Each source and complete raw probe is retained in build/route008d0b00. The old bank's recorded EH and shape searches were read before retrying. The new main-body generator found no applicable register, copy, test, or loop choices; its baseline search reproduced the retained result. This is not proof that assembly is required.

## Acceptance and next experiment

The strict scoped candidate check failed. In addition to the remaining byte mismatch, the old address-derived toInteger, at, makeValue, and finish views and the revised parser view have no symbol-map bindings. No pin was invented to change that outcome. The raw result is build/route008d0b00/scoped-gate.log. Pin consistency passed in build/route008d0b00/pin-consistency.log, and the initial ledger check passed in build/route008d0b00/check_csv_initial.log. No full gate is required for this evidence-only bank update, and no exact recovery is claimed.

Replacing four direct calls with existing canonical declarations preserved the 94-difference result and left only the parser call unbound in the scoped target check. The scoped source-name comparison identified the at-to-bfmeAt call replacement as a descriptive-to-placeholder change. Keeping all original call spellings through transparent in-class facades instead produced 349 bytes with 248 differences. A canonical parser facade with pointer-view casts produced 349 bytes with 249 differences. These trials remain in build/route008d0b00 as best-canonical-four-callees, best-preserved-facades, and best-canonical-five-callees source/log pairs. The preferred bank retains its names and the earlier complete visibility proof. The oracle API reported the existing canonical toInteger name untestable rather than contradicted; the other canonical owners are address-derived views. The raw oracle receipt is build/route008d0b00/oracle-checks.log.

A useful reopening experiment must retain the independently reproduced prefix through +0xE7 while changing the release-loop receiver lifetime or the later callback schedule. It must also preserve the public helper ABIs; making the parser copies static is not an equivalent compiler experiment. Before a landing, bind the call views through canonical declarations or independently proved address-derived aliases, verify the copied helpers' emitted calls and cleanup, and run the ordinary identity, declaration, class, relocation, and byte gates.

The saved bank was recompiled after recording exactly one partial verdict. Its source body is byte-for-byte the retained cleaned trial after removing the generated bank metadata. The repeated probe is build/route008d0b00/bank-final-probe.log, and the strict saved-bank failure is build/route008d0b00/bank-scoped-gate.log. The final ledger check passed in build/route008d0b00/check-csv-final.log. The saved-bank class check passed, and a scoped source-name comparison against the immutable original archive found no descriptive-to-placeholder substitutions. Raw name output is build/route008d0b00/name-preservation.log; command exit codes and measured elapsed time are in build/route008d0b00/handoff-receipt.json. No background process started for this investigation remains active.

The default Git whitespace diagnostic reports the carriage return on the repository tool's appended CRLF verdict row as trailing whitespace. The row was left in its required generated format. The same diagnostic with CR-at-end-of-line handling reports no whitespace error. Both outputs are retained as build/route008d0b00/diff-check.log and build/route008d0b00/diff-check-crlf.log.

## Resolution (2026-10-29, claude-opus-5-5)

The visibility hypothesis held. Two source changes closed the remaining
suffix. (1) The release loop is spelled the way the matched opcode-0x2B sibling
spells it (`value = owner->m_stack[owner->m_count - i]`, with the unsigned-char flag
test inline): 352/352 bytes with 34 differences, all of them one ESI/EDI swap.
(2) The locals follow Open BFME 2's `_FunctionAptActionCallFunction`
(Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp,
donor revision b5a7b8290a): separate `name`, `params` and `function`
locals, with `function = name` in the non-string arm, in place of one
reassigned `top`. That makes it exact. BFME 1 facts: the opcode-table slot 0x3D
(VA 0x012D5B5C) and the complete 352-byte extent. Carried from the donor:
only the local-variable structure. The method keeps its address-derived name.
The body now shares game/Libraries/Source/EA/Apt/Rva008C6320.cpp with the real
0x008C6320 and ParsePath8C4DA0 (0x008C4DA0) rows, rehomed there from
ParsePath8C4DA0.cpp, so both parser bodies are visible under their ledger names.
