# 0x00112BF0 is GameStateMap's `embedInUseMap`, not `??1GameStateMap@@`

The 343-byte body at RVA 0x00112BF0 was filed as `??1GameStateMap@@`, a
truncated decoration carried in from the 2026-08-11 Open-BFME5
`GameStateMapDtorThunk.cpp` `__emit` lift. The body is not a destructor and the
name is not salvageable by completing the decoration. It is the TU-local static
helper `embedInUseMap( AsciiString, Xfer * )`, landed as
`?embedInUseMap@@YAXVAsciiString@@PAVXfer@@@Z`.

## The body cannot be a destructor

- `mov eax,[esp+0x1c]; test eax,eax; je; add eax,8; jmp; mov eax,0x0107388B`
  is `AsciiString::str()` on the by-value first argument, with retail's
  null-argument fallback to the empty-string sentinel at 0x0107388B. A
  `this` pointer is never adjusted like this and never falls back to a string
  literal.
- The Xfer receiver lives in a callee-saved register the CALLER installs. The
  only caller, 0x00113280, does `mov ebx,edi` immediately before
  `call 0x512BF0` (+0x332/+0x334), and the body uses `[ebx]` for the
  `beginBlock` / `xferUnsignedInt` / `xferUser` / `endBlock` slots and never
  writes EBX.
- The epilogue calls `AsciiString::releaseBuffer` (0x00887940) through
  `lea ecx,[esp+0x24]` on the by-value `AsciiString` argument slot, after
  storing the EH state -1, which is where a by-value class parameter's
  destructor sits.
- Retail has no vtable slot pointing at 0x512BF0, so nothing dispatches a
  `GameStateMap` destructor there.

## What the body is, positively

- `push 0x01089690` is the literal `InUseMap` and is the block name argument of
  the `Xfer` call through vtable slot 0x14 (`beginBlock`). The immediate
  0x0108969C in the landed sibling 0x00112DA0 is `EmbeddedMap`, its
  extract-side partner, one .rdata string-table entry away.
- The body opens a file with `fopen(name, "rb")` where `name` is
  `map.str()`, sizes it with `fseek(SEEK_END)` / `ftell` / `fseek(SEEK_SET)`,
  allocates `new char[size]`, `fread`s the whole file, and on each of the three
  failure paths calls `bfmeFormatText(&error, 5, 0)` then `_CxxThrowException`
  on the same `XferException` (ThrowInfo 0x011DFE5C), which is BFME's
  `DEBUG_CRASH(( ... )); throw SC_INVALID_DATA;`.
- The Zero Hour reference carries that function verbatim:
  `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
  Common/System/SaveGame/GameStateMap.cpp:135`
  `static void embedInUseMap( AsciiString map, Xfer *xfer )` -- `fopen`, the
  null check, `fseek`/`ftell`/`fseek`, `new char[ fileSize ]`, the null check,
  the `fread` check, `beginBlock`, `xferUser`, `endBlock`, `fclose`,
  `delete []`. BFME adds exactly the two things retail shows and Zero Hour does
  not: the named `beginBlock("InUseMap")` and the `xferUnsignedInt` of the size
  before `xferUser`. The BFME source of the same helper is
  `game/GameEngine/Source/Common/System/SaveGame/GameStateMap.cpp:143`.
- The 0x00113280 parent calls the landed
  `?extractAndSaveMap@@YAXVAsciiString@@PAVXfer@@@Z` at 0x00112DA0 with
  `mov esi,edi` before the call, i.e. the same "install the Xfer in a
  callee-saved register, call the static helper" convention this body shows with
  EBX. Embed and extract are the two static halves of one GameStateMap helper
  pair, and they are called from the same parent in the same TU.

## Reconstructed body

`game/GameEngine/Source/Common/System/SaveGame/GameStateMap_embedInUseMap.cpp`,
written the way its landed sibling `GameStateMap_extractAndSaveMap.cpp` is: TU
local views of `AsciiString` (BFME's `str()` is `m_data + 8` with the 0x0107388B
fallback), the `Xfer` virtual table with retail's slot order, and an internal
call anchor, which is what makes MSVC 7.1 keep the Xfer in the caller's
callee-saved register. All 343 bytes byte-verify against
`inputs/baselines/bfme1/retail-1.03-unpacked`.
