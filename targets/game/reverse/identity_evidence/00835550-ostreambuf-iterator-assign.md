# 0x00835550 ostreambuf_iterator<char>::operator=(char) (52 B)

Facts from BFME 1 retail:
- 0x00835550..0x00835583 (ret 4, then padding): thiscall, `this` in ECX, one
  stack char argument. If the byte at +4 is set it calls ILT 0x00022D4F
  (jmp to the matched `?sputc@?$basic_streambuf@DV...char@...` at 0x005BD380)
  with ECX = [this+0], and stores `result != -1` into the byte at +4; returns
  `this`. That is the STLport 4.5.3 `ostreambuf_iterator::operator=`
  (`_M_buf` at +0, `_M_ok` at +4).
- Callers are the narrow STLport formatting bodies (callers_of.py):
  __copy_integer_and_fill 0x00835310, __copy_float_and_fill 0x0083B9B0,
  time_put::do_put 0x00836DB0, money_put::do_put 0x008379C0 (the latter's
  re_attempts entries already read this body as operator=(char)).
- The old row `?bfmeGo914C@BfmeThing914C` (BfmeConv914.cpp) was a
  private-class stand-in for these exact bytes; its `BfmeSrc914C::bfmeFind914C`
  callee pin 0x00022D4F is the sputc ILT (pin_consistency: owned-by sputc).

Facts carried from the donor (Open-BFME-2 2bac16a6,
Code/Libraries/Source/WWVegas/WWLib/stlport_ostreambuf_iterator_assign.cpp,
52 B at its 0x00009820): the same body source. Donor name/placement is a lead;
identity above is from the BFME 1 bytes, callers and the sputc ILT.

Inference: the link_queue "losers" for this name (Rva00848510.cpp and
Rva00846E80CopyWrappers.cpp) emit non-retail COMDAT copies; a ledgered
retail-identical definition makes the real symbol resolvable from retail.
