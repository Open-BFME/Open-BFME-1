# 0x0074E820 identity: `?bfmeInitJK@BfmeSubAJK@@QAEXH@Z`

## What the lift name claimed

The generated row carried the dump name `?d_0074e820@@YAXXZ`, i.e. a
`void __cdecl()` with no arguments and no receiver. The body contradicts every
part of that: it ends `ret 4` and consumes `ECX` plus one stack dword, so it is
a `__thiscall` member taking one `int`.

## Evidence for the landed name

* **Matched caller.** `?bfmeClearJK@BfmeBigJK@@QAEXXZ` (0x0074E8C0, 161 B,
  `game/GameEngine/Source/Common/BfmeConv2077.cpp`) is byte-matched and its
  source calls `m_bfmeSubAJK.bfmeInitJK(1);`. A matched caller that names the
  symbol is the strongest identity evidence available, and the class
  `BfmeSubAJK` it names is the same offset-0 owner this body treats as the
  receiving vector.
* **Argument.** The single incoming dword (`[esp+0x54]` after the frame) is
  reloaded and pushed as the callee's `unsigned` count, so the parameter is
  `int` by value and callee-cleaned (`ret 4`).
* **Callee.** The call target 0x00025BF3 is the ILT thunk
  `?j_00025bf3@@YAXXZ` (`game/gen_small/thunks_017.cpp`), which tail-jumps to
  0x0074E710, the matched
  `?resize@?$vector@UGen_t_0074d9c0_p128pod@@V?$allocator@UGen_t_0074d9c0_p128pod@@@_STL@@@_STL@@QAEXIUGen_t_0074d9c0_p128pod@@@Z`
  (`game/GameEngine/Source/Common/BfmeVectorResize36.cpp`). Its `ret 0x28`
  proves the element is passed **by value** and is 36 bytes, which is what
  forces the local-then-`rep movsd` copy in this body.

`BfmeSubAJK` remains an address-derived shim class (declared identically in
BfmeConv2077.cpp); no retail name for it is proven. `bfmeInitJK` is the matched
caller's own spelling and is kept unchanged.

## Element layout proven by the store shapes

The 36-byte element is written as eight `mov dword [esp+N], 0` **immediates**
followed by `mov byte`, `mov byte`, `mov word` from `CL`/`CX`. MSVC 7.1 emits
the immediate form for a zero `float` store; the same eight stores declared
`int` collapse onto one zeroed scratch register, which then also serves the
byte/word tail and changes the register rotation (`xor eax,eax` / `mov edx,ecx`
instead of `mov eax,ecx` / `xor ecx,ecx`). `double` fields go through x87
(`fld`/`fstp`) and do not match either. So the leading eight fields are floats
and the tail is `unsigned char`, `unsigned char`, `unsigned short`. The float
stores must precede the tail stores in the source for retail's ordering.
