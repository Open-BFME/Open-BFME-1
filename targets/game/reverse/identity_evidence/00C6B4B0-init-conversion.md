# 0x00C6B4B0 initializer conversion (dynamic-initializer $E stub)

Retail 0x00C6B4B0 (29 B) is a compiler $E dynamic initializer, not a
hand-written function: Ghidra decompiles it as
`thunk_FUN_004b2cc0(&AsciiString::TheEmptyString,0);
_atexit(FUN_0106ff60);` with no caller but the CRT init table
(refs: DATA 012a57cc). Raw bytes: `push 0; push 0x01336E50;
mov ecx,0x012F1318; call 0x00025306; push 0x0106FF60; call _atexit;
pop ecx; ret`.

Operands, each independently established:
- ctor ILT 0x00025306 jumps to the landed two-arg AudioEventRTS ctor
  `??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z` at 0x000B2CC0
  (AudioEventRTSCopyAndLifetime.cpp).
- teardown 0x0106FF60 is the landed `?bfmeForward_00C6FF60@@YAXXZ`
  (S3SingletonForwarders.cpp).
- global 0x012F1318 is the recorded `?BfmeTheEmptyAudioEvent@@3VAudioEventRTS@@A`
  (dir32_addresses.csv); consumers read it through
  `extern AudioEventRTS BfmeTheEmptyAudioEvent` (ThingTemplateSounds.cpp).
- arg 0x01336E50 is the recorded AsciiString empty-string slot the whole
  tree reads (dir32_addresses.csv).

The prior row `?Rva00C6B4B0InitializeEmptyAudioEvent@@YAXXZ` spelled this
stub as a hand-written named function. Per the $E landing convention it is
retired here and replaced by `?Rva00C6B4B0Init@@YAXXZ` with
`object-symbol=_$E1`: the TU defines the global once
(`AudioEventRTS BfmeTheEmptyAudioEvent(...)`), so MSVC emits the stub as
bare `_$E1`, and only the ledger name is address-derived. Probe: 29/29
bytes EXACT modulo relocation slots. Extent unchanged (29 B).
