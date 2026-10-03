# RVA 0x007F4770 callback: independent 15-byte boundary and ABI

Retail-1.03-unpacked lotrbfme.exe SHA256 is
1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.
The matched registrar 0x007F46F0/67 pushes callback VA 0x00BF4770 at
RVA 0x007F470F while passing its original ESI owner as the callback context.
That DIR32 callback reference proves the start without a Ghidra inventory row.

The complete native body loads argument1 from [ESP+4] into EAX and argument2
from [ESP+8] into ECX, pushes EAX, calls 0x007F4780 and ends RET at
0x007F477E. The single INT3 at 0x007F477F is padding, excluded from the
15-byte extent. Next matched body 0x007F4780/87 is separate and ends RET4.
BoundaryValidator returned reject=null; no known body overlaps this range.
The ordinary add_match compiled-boundary guard independently accepted15.
No carved.csv row or Ghidra boundary was manufactured.

The source-backed callee BfmeThingVJL::bfmeGoVJL(int) at 0x007F4780 saves
incoming ECX into ESI and consumes its stack argument with RET4. Its existing
class declaration is reused unchanged; virtual slots are seven entries at
byte offsets0..0x18, not nineteen slots. The callback is static two-argument
cdecl with no hidden receiver. Preserve the established bfmeCbAZC basename
under the organizational address scope Rva007F4770, making no EA class claim.
The registrar now declares that real signature and points to the same native
address; only the unused old _bfmeCbAZC candidate pin is retired. Existing
historical DIR32 metadata is retained unchanged, and no new address pin,
alias, assembly, generated-source edit or exception baseline is introduced.
