# Gen_000ED960::bfmeApplyXG takes an AsciiString at RVA 0x000ED960

The 85-byte matched body at RVA 0x000ED960 in `game/GameEngine/Source/Common/BfmeLabelSetterXG.cpp` keeps its address-derived owner and method name; only the by-value parameter's type is respelled from the TU-local stand-in `AsciiStringXG` to retail's `AsciiString`, so the claim becomes `?bfmeApplyXG@Gen_000ED960@@QAEXVAsciiString@@@Z`.

Evidence (`python3 tools/dis_retail.py 0xED960`, `python3 tools/dis_retail.py 0xBFB710 8`): the body copies through `StringBase<char>::set(const StringBase<char> &)` (0x00887C90) and releases the argument at scope exit by calling `StringBase<char>::releaseBuffer` (0x00887940) directly, and its unwind funclet `uw_00bfb710` does `lea ecx,[ebp+4]; jmp ILT 0x0000D828`, which reaches 0x0005EE90, the matched `??1AsciiString@@QAE@XZ`. That is exactly the shape of a by-value `AsciiString` under the WWLib `ascii_string.h` inline destructor. The stand-in's destructor was pinned at 0x00887940 and emitted as a separate COMDAT that is not retail's body.

The correction preserves the start, extent, instructions and relocation targets. A funclet that destroys the argument through a different destructor, or a scope-exit release other than 0x00887940, would refute it.
