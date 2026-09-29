# 0x0058C2B0 — the caller and the callee are mutually exclusive spellings

## RESOLVED 2026-09-29: the frontier below is a false one

**The first two attempts at this repair were wrong, and the reason is worth
recording: both of them asked the wrong question.** They asked how to *write a
call* to a class-returning function in C++ and correctly found that you cannot.
But the caller TU does not have to write a class-returning call. It has to emit
retail's five instructions, and the function-pointer cast emits them while
naming the callee's real symbol:

```cpp
class Rva0058C2B0RefPtr;

Rva0058C2B0RefPtr __stdcall bfmeCallDUL(const char *what);
typedef void (__stdcall *BFMEDulCall)(void *, const char *);

void *__stdcall bfmeGoDULa(void *other)
{
	volatile int tmp = 0;
	((BFMEDulCall)bfmeCallDUL)(other, (const char *)bfmeStrDULa);
	return other;
}
```

which compiles to, byte for byte, retail `0x006C1C10`:

```
push ecx / push esi / mov esi,[esp+0xc] / push OFFSET FLAT:_bfmeStrDULa /
push esi / mov dword PTR [esp+0xc],0 /
call ?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z / mov eax,esi /
pop esi / pop ecx / ret 4
```

Three properties make this work, and each one is load-bearing:

* The call is **typed** `void (void*, const char*)`, so no return object is
  materialised and no `lea`/`push` pair appears. The result is discarded by
  retail, so nothing is lost.
* The symbol **referenced** is the callee's real, byte-verified name, so the
  body keeps exactly one name and the pin becomes a routing pin at the ILT thunk
  it always was.
* The callee's actual argument layout is (destination, string), which is what
  the cast's parameter types already say. The cast is a lie about the return
  type and nothing else, so it cannot change the encoding.

VC7.1 emits a **direct** `call rel32` through the cast, not an indirect one: the
cast is between two function types and the target's address is a link-time
constant, so the front end keeps the direct form. That is why this works on
7.1 specifically and is not a general property of C++.

Option (a) is therefore **available**, and the landed state is:

| | |
|---|---|
| body `0x0058C2B0` | `?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z`, 170/170, `BfmeCallDUL.cpp` |
| pin `0x0001D467` | `?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z,0x0001D467,route=0x0058C2B0` |
| callers `0x006C1C10`-`0x006C1CD0` | `BfmeConv785.cpp`, 5/5, calling that symbol |

`tools/pin_consistency.py --symbol` now reports one name, one body, and
re-derives `route=0x0058C2B0` from the image as *admissible* under arm (b) — an
`E9` jump stub whose target body carries a matched, identity-naming row for this
very symbol. The old `?bfmeCallDUL@@YGXPAXPBX@Z,0x0001D467,pin` row named a
body that never existed; it is gone.

The rest of this file is the reasoning that led two sessions to say the pair
could not be reconciled. It is kept because the negative results are real and
still hold — every one of them is a statement about *direct* calls, and it is
the direct call that is unspellable, not the callee. Read the correction above
first.

---

**Finding 2026-09-29.** The 170-byte body at `0x0058C2B0` is byte-exact as
`?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z` (sret, class returned by value)
from `game/GameEngine/Source/Common/BfmeCallDUL.cpp`, and the five callers at
`0x006C1C10`-`0x006C1CD0` are byte-exact as calls to
`?bfmeCallDUL@@YGXPAXPBX@Z` (`void* __stdcall (void*, const void*)`, pinned at
the ILT thunk `0x0001D467`). **No single direct spelling produces both**, and
the reason is a property of the VC7.1 *frontend*, not of the bytes.

## What retail does

Caller `0x006C1C10` (32 bytes, every sibling identical but for the string):

```
push ecx                       ; [E-4]  = the volatile int tmp home
push esi
mov  esi,[esp+0x0c]            ; esi = the caller's own 4-byte argument
push 0x0111D7F0                ; "PingAttack"
push esi                       ; <-- the destination object, passed FIRST
mov  dword ptr [esp+0x0c], 0   ; the volatile int tmp
call 0x0001D467                ; 5-byte ILT thunk: e9 44 ee 56 00 -> 0x0058C2B0
mov  eax, esi
pop  esi
pop  ecx
ret  4
```

Callee `0x0058C2B0` (170 bytes) writes through the first stack slot
(`mov esi,[X+4]; mov [esi],eax; inc dword [eax+4]`), returns that pointer
(`mov eax,esi`) and cleans two arguments (`ret 8`). Its state-0 funclet at
`0x00C37334` is `mov ecx,[ebp+4]; jmp 0x0018336 -> 0x00107550`, and in a VC7.1
funclet EBP is the establisher's entry ESP (confirmed independently by
funclet 1 reading the raw `operator new` result at `[ebp-0x10]`, which the body
stores at `X-0x10`). So the callee OWNS the object at `[X+4]` on the unwind
path and does not destroy it on the normal path, and the caller KEEPS that
object. One stack argument, one class-sized object, and the two halves take it
in incompatible ways.

## Why option (a) is a compiler error, not a byte diff

Re-spelling the pin to the sret name and rewriting the caller's declaration
cannot work, because this frontend has no syntax for naming a return object.
All of these fail to compile (`build/scratch/t1,t4,t7,t8,t9,t10.cpp`), each
with the identical diagnostic:

```
error C2660: 'f' : function does not take 2 arguments
```

| spelling | tried |
|---|---|
| `T f(const char*); f(*(T*)p, "x")` | t1 (trivial T), t7 (`struct T`) |
| `f(new T, "x")` | t4 |
| `T f(const char*)` with non-trivial `~T` | t8, `T *q` indirection t9 |
| reference source | t10 |

The return object is a hidden argument the caller never writes down. What the
compiler emits instead (t12, listing from `build/asm.sh.py`) is a fresh frame
temporary and a fresh `lea`/`push` pair:

```
push ecx                        ; [E-4] = the temp
push OFFSET FLAT:"x"
lea  eax, DWORD PTR $T304[esp+8]
push eax                        ; <-- 8 bytes where retail has `push esi` (1)
call ?f@@YG?AVT@@PBD@Z
```

so a class-return caller is ~40 bytes where retail's is 32, and the callee
would have one explicit argument (`ret 4`), not two (`ret 8`).

## Why option (b) cannot reach the third cleanup object

The unwind map needs three cleanup objects and the third is at `[ebp+0x4]`. In
VC7.1 exactly one construct owns a caller-provided object at `[X+4]` and skips
its destructor on the normal path: MSVC's sret return object. Measured under
the repo's compiler (`tools/probe.py`, `build/scratch/body_b1.cpp`,
`body_b2.cpp`):

| spelling | bytes | 3rd funclet | why it cannot match |
|---|---|---|---|
| landed sret, 2 stack args | 170 | yes | caller unspellable (above) |
| `void* (void* out, const void*)` + inline assign | 156 | **no** (2 funclets) | no owned object, so no `or ebx,2`, no `mov byte [esp+0x20],2`, no funclet 3 |
| `(RefPtr out, const void* what)` by value | 203 | yes | MSVC passes it as a pointer, so it *does* own it: a 4-byte copy into the param slot plus a normal-path `release()` that retail has not; frame is `sub esp,0x10` |
| `RefPtr& out` / `RefPtr* out` | 152 / 150 | no | a reference or pointer is never owned |

The first divergence of the 156-byte out-pointer build is at `+0x21`, and the
whole 89-byte non-relocation difference follows from the missing third
cleanup: retail stores the trylevel byte `2` before the `Owner` constructor and
`or ebx,2` after it; the out-pointer build stores trylevel `1` and never sets
bit 1.

## The state this leaves behind, and why it is the honest one

* The body keeps its landed name and byte-exact source; the caller keeps its
  byte-exact 2-argument declaration. Both build `Functions: OK`.
* `?bfmeCallDUL@@YGXPAXPBX@Z,0x0001D467` stays the only `bfmeCallDUL` pin.
* The pin **cannot** be given a `route=` note: `route_verdict` admits a jump
  stub only when the target body carries a matched, identity-naming row for
  *this* symbol, and `0x0058C2B0` names itself
  `?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z`. Any `route=` note on the
  `PAX/PAX PBX` name is refused, and the honest re-spelling
  `?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z,0x0001D467,route=0x0058C2B0`
  is admissible but unreachable from a caller that cannot be written.
* Both candidates the resolver walks for the caller's name are needed: the
  call encodes `0x0001D467` and no other address reproduces it, while the
  definition of that mangled name is the 170-byte body at `0x0058C2B0`. That
  is a real retail ODR mismatch (a header declaring the pointer form against a
  definition in the class-return form), and no C++ spelling of one function
  reproduces it.

Do not re-run this search as a *direct* call: option (a) dies in the frontend
and option (b) dies in the EH map, before any byte comparison is reached. The
function-pointer cast at the top of this file is the way out, and it was missed
because the question was framed as "how do I call a class-returning function",
which has the answer "you cannot", rather than "what encoding do these five
instructions have".

## Corroboration from the object file, not the unwind map (2026-09-29)

The EH-map argument above can be replaced by a shorter one that needs no
retail-side reasoning at all: VC7.1 names the slot itself. The listing of the
landed source (`python3 build/asm.sh.py game/GameEngine/Source/Common/
BfmeCallDUL.cpp`) declares

```
___$ReturnUdt$ = 8                                ; size = 4
```

and the third funclet reads that pseudo-variable, i.e. the compiler's own name
for "the caller-provided return object at `[X+4]`":

```
$L415:  mov  eax, DWORD PTR $T412[ebp]
        and  eax, 2
        je   $L416
        and  DWORD PTR $T412[ebp], -3
        mov  ecx, DWORD PTR ___$ReturnUdt$[ebp-4]     ; == [X+4]
        jmp  ??1Rva0058C2B0RefPtr@@QAE@XZ
$L416:  ret 0
```

`___$ReturnUdt$` is emitted for a class return and for nothing else, and the
tail-jump is a destructor call, so the normal path must not also call it. No
`void*`/`RefPtr&`/`RefPtr*` parameter can produce that symbol; only a
by-value class parameter can, and that one adds the normal-path destructor
retail lacks. The other two funclets in the same listing are `$L411`
(`operator delete` on the raw new result) and `$L413` (`~ArgBox`).

Re-measured independently for option (b) with the stores written inline instead
of through a member call (`build/scratch/body_b3.cpp`,
`?bfmeCallDUL@@YGPAXPAXPBX@Z`): **156 vs 170 bytes, 89 non-relocation diffs,
first at `+0x21`, shape 0.804** - the same result as `body_b1`, so the 156/170
gap is a property of the signature, not of how the assignment is spelled. The
first structural difference is at retail `+0x32`, where retail stores the
trylevel step `mov dword ptr [esp+0x1c], 1` and the out-pointer build only
tests bit 0 of `$T412[esp+0x1c]` (`mov ..., ebx` / `je`), never setting bit 1.

**Likely retail mechanism (hypothesis, not proven).** A link-time mismatch like
this survives into a shipped binary when the project was built with `/GL`: the
call sites are bound from the pointer-form declaration in the caller TU while
the body is compiled from the class-return declaration, so no external
reference to either mangled name is ever emitted and the 5-byte `e9` thunk at
`0x0001D467` is all that survives. Nothing in the image can confirm `/GL`;
this only explains why the impossible pair was allowed to link.
