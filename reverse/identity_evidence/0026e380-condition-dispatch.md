# RVA 0x0026E380 condition dispatch

Full 173-byte no-argument thiscall body, plain RET at +0xAC. Receiver identity
is unresolved and retains the address token. Set byte E8 before the helper;
save owner Object pointer +8 before lookup of ID +AC. A null lookup or target
byte +344 bit0 ends the operation before loading saved owner's AI +204.
A null AI likewise exits. Model-condition bit196 is set and notified only
when previously clear. Existing weapon getter takes null optional slot output.
If a weapon exists and first byte of address returned by 1BEF20 has bit7,
call 1C9AC0 with 7 and conditionally clear/notifiy model-condition bit150.
Finally call AICommandInterface::aiAttackObject on AI+20 with target,1,2.

Callee contracts were decoded independently from retail:

* ILT3FA30 -> 2A9850, complete 2403-byte body. Entry saves ECX into EDI at
  +1F, reads receiver fields +4/+8/+AC, and makes the same object lookup.
  Locals and SEH occupy 0x184 bytes including saved registers. No incoming
  stack arguments or hidden output storage are read. Its cases converge on
  cleanup at +4E7, restoring SEH and 0x174 bytes after four register pops,
  then plain RET at +516. Later blocks branch backward into these paths,
  including terminal +95E -> +442. The existing matched 0025EF90 caller
  independently calls this helper through ILT3FA30 with the same no-argument
  ECX ABI. New pin names the BODY and address-qualified method, not the old
  WeaponSetSpecialAbilityUpdate destructor alias.
* ILT1F253 -> 9A510 is the existing GameLogic::findObjectByID contract.
* ILT2191D -> 1BE1C0 is the existing Object model-condition notification.
* ILT31A7F -> 1BE230, complete47B: optional stack pointer receives slot+27C;
  returns weapon at +26C+4*slot, or null if +284 clear; both paths RET4.
* ILT209FA -> 1BEF20, complete7B: LEA EAX,[ECX+29C]; RET. Use existing
  address-derived Rva001BEF20FieldAddress::get rather than inventing a flag type.
* ILT122AB -> 1C9AC0, complete145B: signed/int index argument used to clear
  a mask and select a mapped bit; RET4 at+8E. Reuse Gen001C9AC0::handle.
* ILT2EDCF -> 1535A0, complete214B: three arguments feed command0B block,
  target Object pointer and integer parameter; virtual command dispatch;
  both epilogues RET12. Existing matched AICommandInterfaceAttackCommands.cpp
  and its reference correspondence establish Object*,int,CommandSourceType.

Canonical object.h supplies Object layout. STLport bitset gives the 40-byte
model-condition representation. Unsigned byte mask0x80 emits retail JNS after
CMP byte,0; signed less-than emitted JGE (same truth values but not byte exact).
Corrected source probes173/173 exact modulo nine relocations. Scoped build
must verify all relocations before landing. No inline assembly or emitted bytes.
