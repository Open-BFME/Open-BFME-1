# `??0InputChunk@@QAE@XZ` is not at 0x00061D90

* **Retail stores a literal zero.** 0x00061D90 is `mov eax,ecx; mov dword ptr
  [eax],0; ret`. `DataChunk.cpp`'s `InputChunk` constructor stores
  `??_7InputChunk@@6B@` in that operand, which `build.py` masks, so the row
  byte-matched a body that installs no vtable at all. The DIR32 check read the
  operand as base 0x00000000.
* **InputChunk's table is 0x0108631C.** The matched
  `?openDataChunk@DataChunkInput@@QAE?AVAsciiString@@PAG@Z` (0x001032A0),
  compiled from the same `DataChunk.cpp`, builds a new InputChunk inline and
  stores `??_7InputChunk@@6B@` at +0x1D: retail has 0x0108631C there. That
  table's one slot is the deleting destructor 0x001026F0, which stores
  0x0108631C again.
* **The constructor is 0x001026E0**: `mov eax,ecx; mov dword ptr
  [eax],0x0108631C; ret`, the only other body that installs the table. It
  keeps its row; this retirement only removes the alias.
* Retail has no identical-COMDAT folding, so the alias was an over-claim on a
  body that already carries its own names.
