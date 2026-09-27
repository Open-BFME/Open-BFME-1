# 0x0035BFB0 is not ScriptList::ParseScriptsDataChunk

The row carried the name the naked `__emit` lift arrived with. The lift's own
`// readable body of` comment named `Scripts.cpp`, and a reference transcription
of the Zero Hour `ScriptList::ParseScriptsDataChunk` sat next to it -- but the
retail body contradicts the name in three independent ways.

## 1. Calling convention and arity

The body is `thiscall` with two stack arguments:

```
0035BFCD  mov esi, ecx          ; ECX (the this pointer) is kept in ESI
0035C036  mov eax, [esi + 0x10] ; and +0x10 / +0x0C are read off it
0035C054  mov ecx, [esi + 0x0C]
0035C080  ret 8
```

`?ParseScriptsDataChunk@ScriptList@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z`
is `__cdecl` (`SA_`) and takes THREE arguments, so it would load `[esp+4]`,
`[esp+8]`, `[esp+0xC]` as `DataChunkInput &`, `DataChunkInfo *`, `void *` and
return with `ret 12`. Nothing in the body ever dereferences a `DataChunkInfo *`
argument, and it ends in `ret 8`.

The two stack arguments are `DataChunkInput &` (loaded into EDI at +0x34 and
used as `this` for both `registerParser` and `parse`) and a `const AsciiString &`
(loaded into EAX at +0x2D and pushed as `registerParser`'s second argument).

## 2. The class is a parser registration, not ScriptList

`tools/vtable_lookup.py 0x010E8538` reports exactly one function in the image
carrying that vtable constant: the constructor at 0x00352810, landed as
`??0Rva00352810ParserRegistration@@QAE@PAX0PAVDataChunkInput@@PAVAsciiString@@@Z`
(`game/GameEngine/Source/Common/Rva00352810ParserRegistrationCtor.cpp`). Its
slot 1 is the ILT thunk 0x00035AAD, which jumps to 0x0035BFB0, so the body is a
virtual of `Rva00352810ParserRegistration` -- the object that registered the
"PlayerScriptsList" chunk (literal VA 0x010E8544, verified against the image).

The only caller, 0x001916F0 (landed as `BfmeOwnCP::rva001916f0`,
`game/GameEngine/Source/Common/BfmeConv1774.cpp`), reaches it through that same
vtable slot with two pointer arguments and a `bool` result.

`ScriptList` is a different object entirely: it is not polymorphic at +0x04 in
the way this body needs, and the members the body writes through (`+0x0C` list
array, `+0x10` count pointer) are the constructor's `dataContext` and
`localList` arguments, which is what the constructor row already named them.

## 3. What the body actually does

* builds the literal "ScriptList" (VA 0x010E8C98) into a temporary and registers
  it as a nested parser, callback operand 0x00404877, userData 0;
* releases the temporary;
* parses with `void *` userData pointing at a local read-info whose first dword
  (the count) is the only field it initialises -- the 0x88 frame holds the
  4-byte temporary plus a 132-byte `{Int; void *[32];}` read-info, which is what
  makes the frame 0x88;
* on success stores the count through `*m_10` and copies that many entries out
  of the read-info into `m_0c`, reloading `*m_10` every iteration.

The callback operand 0x00404877 is a 5-byte ILT slot that the SafeDisc-stripped
baseline leaves as `0xCC` padding, so the parser it names is NOT identified here
and the operand is left a literal: no ledger row can be placed at that address,
so no C++ symbol can be named for it either.

## Replacement identity

`?bfmeReadScripts_0035BFB0@Rva00352810ParserRegistration@@QAE_NAAVDataChunkInput@@ABVAsciiString@@@Z`
-- the class is proven by the vtable above, the method keeps the address token
because nothing names it, and the body lives with the rest of that class in
`game/GameEngine/Source/Common/Rva00352810ParserRegistrationCtor.cpp`.
