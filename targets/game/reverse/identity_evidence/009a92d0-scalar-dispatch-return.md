# Opaque scalar dispatch body RVA009A92D0

Direct PE disassembly establishes the full 157-byte body, ending in RET at
009A936C followed by INT3 at009A936D. Ghidra FUN_00da92d0 independently
reproduces the two-pointer loop. There are no direct callees or relocations.

The entry reads the unsigned count from ESP+C, the source pointer from ESP+4,
and the signed stride from ESP+8. The plain RET establishes caller cleanup.
The generic branch of matched installer009B0D60 stores VA00DA92D0 at
VA01356E7C with the instruction at009B1073. No original function spelling is
proven; retain the address-derived Rva009A92D0 name.

The EAX result is observable directly in retail: MOV EAX,[ESP+4] at009A92D6
executes before the zero-count branch, and each iteration increments EAX at
009A935F. No later instruction changes EAX before RET. Thus it returns the
advanced source pointer, or the original pointer for count zero. This proof
does not infer the return type merely from a successful source experiment.
The installer holds an untyped dispatch pointer; change its old no-argument
void declaration to this witnessed three-argument pointer-return ABI and
retire the obsolete no-argument pin rather than creating a second identity.

The served bank measured157 bytes/74 differences. An outer unsigned count
guard combined with preweighting the third sample by154 reduced this to15
differences. Returning the advanced source pointer restores the early EAX
load and reuse of the first argument slot for the counter, yielding157 exact
bytes with zero relocation masking. Load/store order is retained, including
potentially overlapping rows and the last read from source[stride*5].
