# Movie counter storage at RVA 0x00EF12B0

The guarded retail image has SHA-256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75. VA 0x012F12B0 is a writable, loader-zero-initialized four-byte cell in the virtual tail of .data. The supplied descriptive Count0040E9E0 identity is preserved; no original EA name is asserted.

Complete bodies at RVAs 0x0040DE00 and 0x0040E9E0 contain six direct DWORD references: loads at VAs 0x0080DE7A and 0x0080EB67, incremented stores at 0x0080DEA9 and 0x0080EB86, and zero stores at 0x0080DF04 and 0x0080EBCF. Both paths compare the old value with 30 and use signed JLE before resetting it. The complete retail disassembly and original ownership census are retained in build/rlink/identity-1791432209/retail-probe.txt. A byte-address search across all raw sections accounts for exactly these six operands and no interior-address reference.

The ordinary int declaration and its genuine compiler-bound zero-initialized storage emit the existing ?Count0040E9E0@@3HA identity once. Compiler sizeof and unchanged normal data admission prove four bytes. The definition is in the source of the existing movie-frame consumer; no function body, alias, wrapper or artificial consumer is introduced. The separate generated numeric-address body is unchanged and does not rely on this decorated exemption.

A different access width, escaped interior pointer, nonzero loader initializer, competing owner or changed signed comparison would refute the counter view. A source or data gate refusal prevents landing. The two separately assigned registration cells remain unresolved and retain their exemptions.
