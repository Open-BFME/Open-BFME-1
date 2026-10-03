# Complete the EvaEvent FX parser stack epilogue

The 253-byte claim at RVA 0042BAA0 cuts ADD ESP,94h at 0042BB99..0042BB9E. RET at 0042BB9F completes the reached epilogue; INT3 padding starts at 0042BBA0. The full body is therefore 256 bytes. All decoded branches remain within that interval and no other live matched claim intersects it. Local PE/Capstone decoding and Ghidra read_memory at VA 0082BB80 agree.

The existing native EvaEventFXNugget::parse implementation in FXListNuggetInlineCtorParse_Thunk.cpp emits this complete body. The gate checks all claims in the unchanged TU and existing relocation bindings. The correction extends only the executable range; no semantic rename, source edit, pin change or padding claim is introduced. Inherited constructor/ICF prose in the source is not used as identity evidence.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
