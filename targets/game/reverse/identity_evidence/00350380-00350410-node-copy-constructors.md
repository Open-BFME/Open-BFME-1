# 0x00350380 / 0x00350410: BfmeNodeCU / BfmeNodeCV copy constructors

BFME 1 target evidence (retail 1.03 unpacked):

- 0x00350380 (109 B) and 0x00350410 (109 B) were ledgered as
  `BfmeNodeCU::bfmeCopyCU(const BfmeNodeCU &)` / `BfmeNodeCV::bfmeCopyCV`.
- Each body allocates 0xC bytes and, inside an EH state that deletes the
  block on unwind (funclets 0x00C191D0 / 0x00C191F0), calls the ILT
  0x0003910D / 0x0003CFDD with ECX = the new block and the source's +0
  pointer pushed. Those ILTs are `e9` jumps to 0x00750380 / 0x00750410,
  i.e. back to these same two bodies.
- So the "item" constructor the new-expression runs is the body itself:
  a recursive deep copy of a 0xC-byte singly linked chain (+0 next,
  +4/+8 copied ints) that returns `this` in EAX. A new-expression whose
  constructor is this function, plus the returned `this`, makes each body
  the class's copy constructor: `??0BfmeNodeCU@@QAE@ABV0@@Z` and
  `??0BfmeNodeCV@@QAE@ABV0@@Z`.
- The old placeholder ctor pins `??0BfmeItemCU@@QAE@PAX@Z` (ILT 0x0003910D)
  and `??0BfmeItemCV@@QAE@PAX@Z` (0x0003CFDD) named the same bodies under a
  second class; nothing defines them (link_queue #332/#333 unresolved).

Class names stay address-family placeholders (BfmeNodeCU/CV); only the
member identity (copy constructor instead of an invented copy method) is
corrected. Bytes are unchanged.
