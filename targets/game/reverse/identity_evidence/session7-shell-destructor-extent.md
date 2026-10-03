# Complete the Shell destructor stack epilogue

The 253-byte claim at RVA 0057F7A0 ends inside ADD ESP,10h at 0057F89C..0057F89E. Its RET is at 0057F89F, followed by INT3 padding from 0057F8A0. The complete body is 256 bytes. Entry control flow reaches this epilogue, all decoded conditional/loop destinations lie within that span, and no other matched claim intersects it. PE/Capstone and Ghidra read_memory at VA 0097F880 agree.

The unchanged native ShellDestructor.cpp already emits the complete 256-byte function with existing reference bindings. This repairs the executable extent only and retains the inherited destructor name and declarations. The source header comment still describes the historical 253-byte claim; this evidence and the corrected ledger supersede that stale size. No source, header, pin or padding claim changes.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
