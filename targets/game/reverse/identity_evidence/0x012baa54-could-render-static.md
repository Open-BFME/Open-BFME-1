# VA 0x012BAA54: couldRender, a function-local static of 0x006EB500

Retail VA 0x012BAA54 is one byte in .data with initial value 01. Its only code references are in 0x006EB500, the extracted per-frame render pass of BFME's W3DDisplay::draw:
- +0x0194: a store of 1 on the render path;
- +0x042D and +0x0436: the closing `if (couldRender) couldRender = false;` test.

Zero Hour's W3DDisplay::draw (`GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp`) declares the same flag as `static Bool couldRender = true;` and uses it the same way. The datum is therefore defined as that function-local static, `?couldRender@?1??rva006EB500@W3DDisplay@@QAE_NI@Z@4_NA`, in `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006EB500.cpp`. Its size is 1 byte (bool).
