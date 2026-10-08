# 0x008A25C0 retry evidence

The retry did not improve the preferred reconstruction. Keep `targets/game/reverse/attempts/0x008a25c0.cpp`. The tested revision is `b096c2e2309e884791b01ccd253b8b73b4a1c0c3`; the model is `gpt-6.1-sol`. Trial sources, complete probe output, decoding, search receipts and check receipts remain under `build/retry-008a25c0/`. `results.json` contains the measurements produced by `finish_measure.parse`, and `000-bank.log` is the preferred body's unedited probe output.

## New hypothesis and result

The landed `Rva008A12C0Fixups.cpp` supplies a visible reference helper and independently witnesses the object's counted entry table and sixteen-byte named records. The retry tested whether an in-class reference accessor, a nested counted-table declaration, the canonical `Gen_008A0690` storage view, or visible definitions of the already matched search and decrement helpers would recover the kind-10 base lifetime. The refutation condition was unchanged load placement or a distance at least as large as the saved body. Every tested source met that refutation condition. No new source recovery is claimed.

The accessor and one-word offset wrapper produced different instruction streams and worse measured distances. Signed and unsigned base arguments, a byte-pointer argument, pointer payload storage, typed ownership, templated ownership and the forward mirror's integer-reference relocation expression also failed to improve the preferred body. The mechanical EH and pointer-copy searches retained the original. The individual sources and outputs are enumerated in `results.json`; `010-eh-search.json` and `011-family-search.json` retain the bounded-search manifests.

The preferred probe still has 375 differing non-relocation bytes at the explicitly requested retail extent of 1454 bytes. Its COFF range is 1504 bytes, including the switch table, and its last code return is seven bytes later than retail. The repository's finish-ranking measurement remains 0.6733. The first numerical divergence is a branch displacement at +0x153; the first substantive source residue is the kind-10 base load at +0x3E8. Retail loads the base before the count guard and retains it for the final +0x34 relocation. The bank loads it only after the guard and reloads it for that final relocation. Handle assignment also differs in the +0x465..+0x48D region, and the shifted loops acquire different alignment padding.

## Boundary and ABI evidence

The complete target decodes through both `ret 4` paths at +0x58C and +0x5AB. Every direct conditional or unconditional branch remains inside the decoded body on an instruction boundary. The ten switch-table entries at RVA 0x008A2B70 all point to instruction boundaries in that body. `boundaries.json` retains these checks. The table lies after the code extent and is separately read as data.

The complete 547-byte helper at RVA 0x008D3610 consumes ECX as its receiver, consumes two four-byte stack arguments and ends in `ret 8`. The first argument is used as the relocation base; the second is forwarded to the canonical 0x008CC540 helper. Its eight switch destinations are verified in `boundaries.json`. The target supplies the receiver at entry +8, the base as the first stack argument and the address of its +0x30 word as the second. Return values are unused at this site. The original owner and method identity remain unknown, so the address-derived declaration remains appropriate.

`checked-008a25c0.log`, `checked-008d3610.log`, and the other `checked-*.log` files retain the checked direct-call inventories. Complete decoding of 0x008A0690 confirms a signed count at +0x0C, a four-byte entry array at +0x10, pointer equality and a four-byte argument removed by `ret 4`. The canonical storage declaration was used in `024-canonical-search-view.cpp` without asserting inheritance; this did not improve the emitted target. The complete 0x008CC540 body forwards three four-byte stack arguments into a four-argument cdecl call with zero in the third position.

The forward mirror at 0x008A2130 has code ending after `ret 12` at +0x417. Its ledger extent also includes its table, which must not be linear-decoded as instructions. `checked-008a2130-code.log` uses the complete 1050-byte code extent. Its kind-10 walk independently confirms the +0x30 count, +0x34 array pointer, 0x38-byte stride and per-element +0x34 relocation word. It keeps the base live from entry and therefore does not establish a source expression that explains the target's earlier load.

## Ownership and identity evidence

The target's unwind map has one state. `eh-target.log` identifies the cleanup action at RVA 0x00C57CA0, which addresses the one-pointer temporary and jumps through the ILT to the complete 0x00784A70 cleanup. That body decrements the pointed object's first unsigned word through 0x00894D90 and drops the object through 0x00895320 only when the decrement returns zero. Complete decoding of the latter helper and the named 0x00895260 destructor supports the BfmeDropObjectA pointer ownership view used in the typed-handle trial. There is no STL value-construction inference in this target.

The saved bank's introductory statement that the manager is a second direct caller is incorrect. The complete matched BfmeDropObjectA destructor at 0x00895260 directly calls this target with ECX adjusted by +8 and one pointer argument. The matched manager in `AptLoad.cpp` prepares the corresponding deferred-run fields and calls the forward fixup wrapper; it does not directly call this target. The existing opaque `Rva008A25C0Object::run(void *)` pin is supported by the destructor's decoded call site. This proves the address-derived calling view, not the original Apt class name.

## Checks and reopening condition

`check-csv-final.log` and `pin-consistency.log` pass. `gate-candidate-raw.log` is the unedited scoped byte gate and fails. It reports the missing `?run@Rva008D3610Object@@QAEXPAXPAH@Z` pin as well as the nonmatching target. No pin, ledger row, shared header or game source was changed. A full gate is not required for this evidence-only result.

Reopen only with new native inline or helper context that explains the base's lifetime across the count guard, or with a measured source change that improves the preferred body's distance. Equivalent scalar types, reference accessors, typed handles, nested table storage, the tested visible helper bodies and the tested relocation expression do not supply that evidence. The original best bank remains byte-for-byte preserved.
