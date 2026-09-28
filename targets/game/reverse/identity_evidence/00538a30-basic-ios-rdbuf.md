# STLport basic_ios<char>::rdbuf(basic_streambuf *) at 0x00538A30

The 39-byte body at 0x00538A30 is matched under the placeholder name
`BfmeThingVIM::bfmeSetVIM` (BfmeConv1376.cpp). Here is the evidence that it is
STLport 4.5.3 `basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf *)`.

- Body semantics match `stl/_ios.c` exactly. It saves the old `_M_streambuf`
  (+0x58) and stores the argument. The inline `clear()` then sets `_M_iostate`
  (+0x08) to `buf == 0` (badbit). The inline `_M_check_exception_mask()` tests
  that against `_M_exception_mask` (+0x14). The body returns the old buffer
  (`ret 4`). The +0x58/+0x08/+0x14 offsets are the ones the matched
  `basic_ios<char>::copyfmt` (0x0083F5A0) uses.
- The call it makes goes to 0x0083E8F0. That body is
  `fputs("ios failure", stderr)`, the no-exception
  `ios_base::_M_throw_failure`. It is already pinned under that real name and
  used by the matched STLport file-stream constructors.
- Matched caller: STLport `ios_base::sync_with_stdio(bool)` (0x00842F80,
  iostream.cpp, exact 742/742). It reads each standard stream's old rdbuf. It
  then calls ILT 0x00031FE3 (a `jmp 0x00538A30`) once each for cin, cout, cerr
  and clog, with `this` = stream + virtual-base offset and the new streambuf.
  In the source those calls are `ptr_cin->rdbuf(new_cin)` and so on, and the
  compiler emits exactly this mangled name for them.

Retail was linked without identical-COMDAT folding, so the address carries one
identity. The placeholder name is retired. The new source is
`game/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_rdbuf.cpp`, which is
exact 39/39 with one relocation. The ILT 0x00031FE3 gets the real name as a
pin, as the `basic_ios<char>::init` ILT pin (0x00004E8F) does.
