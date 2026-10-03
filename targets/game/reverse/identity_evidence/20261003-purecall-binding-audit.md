# Compiler purecall binding audit (2026-10-03, v3)

This is a confirmed binding contradiction, not a completed identity repair.

The current `__purecall` row claims RVA006CF680/3 from WWLib/Except.cpp with `icf-owner=?Get_Sort_Level@RenderObjClass@@UBEHXZ`. Its entire body is `33 C0 C3` (return zero), then INT3. The existing address-derived reporter at0088C500 is60bytes.

## Independent retail anchor

The complete31-byte deleting destructor at006305F0 writesVA011186B8 into `[esi]` at006305F8. It endsRET4 at0063060C, followed byINT3 at0063060F. The91-entry/364-byte table at011186B8 beginsVA0043B8D6,VA0041789B; its remaining89entries, offsets+8through+168, are allVA00C8C500. The current PeerDefs.cpp COFF table `??_7GameSpyInfoInterface@@6B@` names these89relocations `__purecall`. Thus this binding is anchored by a direct retail operand; it is not inferred solely from a table-name pin or adjacent placement.

Ghidra read_memory and this worktree's unpacked PE independently agree on the complete table, destructor, reporter and zero stub. Reporter0088C500 endsRET at0088C53B thenINT3 at0088C53C. Its direct call goes to independently recorded `_bfme_debugRecordCallsite` at008896A0 with argument1. It loads the existing debug pointer cell01336E5C; virtual calls use+60, +6C with(NULL,0), +38 withVA011334F4 (`Pure virtual function called.`), and+4C withtrue; EAX finally becomes0.

## Name witness and limits

Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_purecall.cpp:32-35` defines `int __cdecl _purecall(void)`, invokes `DCRASH_RELEASE("Pure virtual function called.")`, then returns0. The release macro at debug_macro.h:355 calls SkipNext, CrashBegin(NULL,0), the diagnostic stream and CrashDone(true), agreeing with the BFME dispatch sequence. This independently supports the compiler helper identity at0088C500. It does not prove additional semantic names for the existing local sink views or justify speculative virtual-member renames.

AGENTS.md requires one identity per real body and says retail was linked without identical-COMDAT folding. docs/matching.md, Relocations, requires checking what references point at. A zero-return body elsewhere cannot stand in for this reporter.

## Pending repair

Correct the existing60B reporter identity and official source placement to Libraries/Source/debug/debug_purecall.cpp; retire only the contradicted __purecall row at006CF680 and remove the unused competing definition from Except.cpp. Reverify the affected sources and table bindings, and retain other006CF680identities pending their independent owners' review. Do not add an alias or a second identity at0088C500.

This session's fresh claims on inherited alias blockers003C8340/00803080 were refused as held elsewhere. Any ledger staging still makes alias_guard compare those inherited, now-removed-upstream aliases and fail. No production, pin or ledger changes are included here. The two audited body claims are released after recording; retry the coordinated repair after launcher integration.

Reporter bytes (first60, excluding padding):

```text
6a01e899d1ffff8b0d5c6e33018b0183c404ff50608b0d5c6e33018b116a006a00ff526c8b1068f43413018bc8ff52388b106a018bc8ff524c33c0c3
```
