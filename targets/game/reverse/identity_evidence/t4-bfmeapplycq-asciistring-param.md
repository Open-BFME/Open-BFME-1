# 0x00387060 bfmeApplyCQ takes an AsciiString, not a UnicodeString

The row was named `?bfmeApplyCQ@BfmeHostCQ@@QAEXVUnicodeString@@PAUBfmePairCQ@@@Z`
but every string operation in the body is the narrow instantiation:

- `tools/callees.py 0x00387060 104`: the store calls 0x00887C90
  `?set@?$StringBase@D@@QAEXABV1@@Z` and the by-value parameter's cleanup calls
  0x00887940 `?releaseBuffer@?$StringBase@D@@AAEXXZ` (the narrow destructor body).
- The real UnicodeString destructor (0x0005EEA0) jumps to the wide
  releaseBuffer 0x008881D0, which this body never reaches.

So the parameter and member are `AsciiString` (ascii_string.h). The class and
method names stay the existing placeholders; only the parameter type in the
decoration changes. The TU-local UnicodeString stand-in also emitted a
non-retail `??1UnicodeString@@QAE@XZ` COMDAT (link queue #14).
