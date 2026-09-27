# RVA 0x00748860: GlobalLighting writer

Retire `?deleteTriggers@PolygonTrigger@@QAEXXZ` at this address only.
The replacement is `WriteGlobalLighting00748860(DataChunkOutput*)`; the
address token is retained because the original BFME function spelling is not proven.

Independent retail evidence:
- Entry at 0x00748860 reads the first stack argument into ESI. It does not
  consume an incoming this pointer. The final instruction at 0x00748D8B is
  a jump to closeDataChunk ILT 0x00004B42; extent ends at 0x00748D90 (1328 bytes).
- At +0x09 it pushes version 7 and the `GlobalLighting` literal at VA
  0x01121ACC, then calls openDataChunk through 0x0003A256 with ESI in ECX.
- All subsequent direct calls write integers or reals to the same output.
  No trigger traversal, unlinking or deletion occurs.
- GlobalData at VA 0x012ED5C8 supplies time-of-day at +0x218 and lighting
  arrays at +0x290 and +0x518. `name_oracle.py` witnesses these names.
- The independent reader at RVA 0x00747FF0 in WorldHeightMap.cpp consumes
  the same arrays and version-4/5/6/7 extension fields in the same order.
- Zero Hour GeneralsMD/Code/Tools/WorldBuilder/src/WHeightMapEdit.cpp
  lines 730-783 writes the same original GlobalLighting fields and shadow
  color. This establishes the behavior, not a guessed PolygonTrigger owner.

Implementation keeps the unproved third lighting array and flags offset-named.
Native DataChunkOutput declarations come from Common/DataChunk.h.
No new callee pins are required.
