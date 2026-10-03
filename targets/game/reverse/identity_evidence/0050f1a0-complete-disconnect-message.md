# Disconnect handler message literal

Both operands at0050F1A0+0x44/+0x5B nameVA01104EE4. Ghidra and local
retail bytes contain the full UTF16 string " has left the game." with
its terminator:40 bytes. Old source omitted the period in both wcslen
and concat expressions. The prior prefix-only check accepted these
shorter strings; reviewed7bfaf884e4 rejects both complete operands.

Correct just the two literals. Preserve the inherited handler/owner,
UnicodeString lifetime, network callbacks, bindings and layout. Retail
ends RET4 at0050F273 thenINT3from0050F276, a complete214B body. No new
identity claim follows from this diagnostic sentence. Require all TU
claims and reviewed full-literal/numeric/DIR32 references to pass.
