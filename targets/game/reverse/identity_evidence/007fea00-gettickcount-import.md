# DirtySock tick forwarder: native GetTickCount import

The existing `_Rva007FEA00` forwarder at RVA007FEA00 has a proven 29-byte
retail extent. Its FF15 at+6 refers to VA01358E0C. The actual retail PE import
directory identifies that exact IAT slot as KERNEL32.dll!GetTickCount;
`callees.py 0x007FEA00 29` independently reports the same identity. Its two
other calls are the existing __RTC_CheckEsp helper.

The installed native PlatformSDK WinBase.h:3488-3493 declares WINBASEAPI
DWORD WINAPI GetTickCount(VOID). The existing pristine Gamespy C windows.h
shim declares `__declspec(dllimport) DWORD __stdcall GetTickCount(void)` at
line107. DWORD is unsigned long, 32 bits for this native compiler. No prototype,
type, header or pin is invented. The wrapper keeps its existing unsigned-int
return contract; that 32-bit value conversion changes no bytes. The existing
matched idle pump's use of its result remains unchanged. The tracked canonical
DIR32 row already binds __imp__GetTickCount@0 to VA01358E0C.

The TU now includes the existing C shim and calls its canonical API instead
of an address-derived import alias. All other unresolved address-derived
Windows import declarations remain unchanged. This is one native import-edge
repair, not a claim that the entire DirtySock TU is link clean.

Before and after scoped gates both exit0: 40/40 matched functions and 113
DIR32 references, zero constants/literals. Independent COFF comparison proves
all forty raw bodies identical, with every relocation offset/kind preserved.
Only the forwarder's external DIR32 at+8 changes from
__imp__Rva01358E0CImport@0 to __imp__GetTickCount@0. Compiler-local labels, if
renumbered, retain their value/section/type/storage.

The TU has a shared ordinary .text section. Strict controls extract exactly
the actual compiled 29-byte ledger interval, preserving its raw bytes and all
three original named relocations; the extracted COFF is independently reparsed
and compared to the input. This avoids including the unrelated function bodies
or fabricating definitions for their remaining import aliases.

Controls in build/y4_tick_import/controls.py/json use genuine retail-native
import libraries, /NODEFAULTLIB and no /FORCE; the single __RTC_CheckEsp stub
is explicitly labelled verification scaffolding:

- Native positive LINK0: selected FF15 operand is VA10002000, exactly the
  selected PE's actual KERNEL32.dll!GetTickCount import-directory slot.
- Unrepaired alias: LINK96, canonical libraries do not supply the old alias.
- Native Kernel32 archive omitted: LINK96, canonical IAT is unresolved.
- Fake canonical IAT stub: LINK0, but selected_import_audit refuses the cell
  because its selected address has no actual native import-directory identity.

Input object/archive hashes, MAPs, actual numerical exits and PE-binding
receipts are frozen in build/y4_tick_import. The raw IAT word on disk is not
used as runtime pointer identity evidence. No new matched code/data bytes or
whole-program/TU closure gain is asserted.

Official current link_check against the immutable accepted5d21 census still
reports LINKED0->0 for this TU (6,988 own bytes), with 31 remaining unresolved
names including ten other import aliases. No whole-TU improvement is claimed.
Pin consistency and check_csv pass (171166 functions /89946 symbols /21 data).
