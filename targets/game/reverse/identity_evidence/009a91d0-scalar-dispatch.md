# Scalar dispatch body RVA009A91D0

The retail body starts after padding at009A91D0 and ends with RET at009A92C6,
followed by INT3 at009A92C7. Direct PE disassembly and a newly created Ghidra
function agree on all247 bytes. Its entry loads the count from ESP+8, the
output pointer from ESP+C and the input pointer from ESP+4 before register
saves; the plain RET establishes caller cleanup. The body reads four source
bytes and writes five weighted outputs per group. The last group reuses its
fourth input at the right edge. No source-level function name is established:
retain Rva009A91D0 and the independently witnessed three-argument cdecl ABI.

The matched BfmeCodecCpuDispatch installer assigns this same entry to the
outlier generic slot. Update its old void-parameter declaration to the actual
signature, and retire the obsolete no-argument symbol pin at the same RVA.
The new matched row supplies the three-argument binding; no alias is added.

The served bank produced249 bytes with66 differing bytes. Archived source
03b6f8179227592ae07e2914295ab34f4798ba82bd44221f0132419e8a2f64d2
produced247 bytes with22 differences. Computing the third sample's154 weight
once reduces the remaining difference to the terminal sample load (14 bytes).
Keeping that terminal sample as unsigned int, rather than the archive's
unsigned char, restores MOVZX EAX,[EAX+3] and MOV ESI,EAX. The final clean C++
probe is exact for247 bytes with zero relocation slots.
