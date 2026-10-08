# Boundary and ABI at 0x008CA3A0

The recovered claim is 766 bytes at RVA 0x008CA3A0. The old 1405-byte generated row crosses independent functions at RVA 0x008CA6A0 and RVA 0x008CA890. The new function name retains its address because the exact EA method spelling is unproven.

## Boundary

The complete executable body occupies 708 bytes. Its ordinary return is at RVA 0x008CA663. The other two exits at RVA 0x008CA47C and RVA 0x008CA65C tail-call virtual slot zero after restoring the stack and registers. Every outgoing conditional branch stays inside the executable body. The indirect switch at RVA 0x008CA4EE reads four pointers at RVA 0x008CA664 and a 42-byte tag map at RVA 0x008CA674. Its destinations are RVA 0x008CA4F5 for tags 1 and 42, RVA 0x008CA5A2 for tags 5 and 7, RVA 0x008CA542 for tag 6, and RVA 0x008CA5EE for all other tags. The tables end at RVA 0x008CA69E, followed by two padding bytes. The separate 494-byte function at RVA 0x008CA6A0 returns at RVA 0x008CA88D; the separate 141-byte function at RVA 0x008CA890 returns at RVA 0x008CA91C or tail-jumps to RVA 0x008A30C0.

## Caller and identity

The opcode table starts at VA 0x012D5A68. Entry 0x66 at VA 0x012D5C00 contains VA 0x00CCA3A0. Independently landed BitAnd and StoreRegister occupy entries 0x60 and 0x87. The complete 375-byte dispatcher at RVA 0x008CCED0 reads an unsigned byte opcode at offset 0x93 and calls the table at offset 0xBB. It pushes the context address followed by the interpreter pointer, then removes eight bytes. It does not consume the handler return value. This proves a cdecl handler with two pointer arguments and no hidden return storage. The target reads only its first argument; the second is unused. Its interpreter accesses match the neighbouring named handlers: count at offset zero and value-pointer array at offset eight. The method and source names retain the target address.

## Value and helper evidence

The full coercion bodies at RVA 0x00898300 and RVA 0x008983D0 independently establish flags at offset four, a boolean byte or integer or float or string pointer at offset eight, and the indirect value pointer at offset 0x20. Their executable extents are 136 and 108 bytes, followed by independently decoded switch tables. Tag 1 uses the string pointer directly; tag 42 follows the indirect value. The actual target compares the unsigned 16-bit string length at payload offset two and text at payload offset eight. No container type is inferred from allocation size.

The coercion methods take ECX without adjustment, take no stack arguments, and return an integer in EAX or a float in ST0. The six-byte version getter at RVA 0x00892370 returns a dword in EAX. Every path of the 184-byte factory at RVA 0x008996B0 takes one byte value in a four-byte cdecl stack slot and returns its pointer in EAX. The comparison helper at RVA 0x009F6FA0 is the six-byte import jump through VA 0x0135933C; the PE import table names MSVCR71.dll and _strcmpi. The target pushes its two text pointers and removes eight bytes.

The factory installs the vtable at VA 0x011360A8. Its first two slots point to RVA 0x008991B0 and RVA 0x008991E0. Complete decoding of those 41-byte and 120-byte bodies proves reference increment and decrement on the packed flags, no explicit arguments, ECX receivers without adjustment, and ordinary returns or the decrement body's virtual cleanup tail. The target uses vtable byte offset four for Release and byte offset zero for AddRef. No constructor is reconstructed and the target has no exception-handler frame or owned temporary requiring unwind cleanup.

## Reproduction and refutation

The source was compiled with the flags in its cl comment against the retail baseline at revision cc6a27760aea345a3d4378e9c30a0c5ae9903e07. Trial 12 probes exact across all 766 bytes modulo relocations. The scoped gate passes every relocation and both compiler-generated switch tables. Refute this recovery if an outgoing target leaves the stated executable extent, the dispatch argument setup differs, a virtual slot has a different ABI, any payload field contradicts the coercion bodies, or the scoped byte gate fails. Raw disassemblies, checked-callee outputs, source trials and unedited probe receipts are retained in build/apt-equality-008ca3a0/.
