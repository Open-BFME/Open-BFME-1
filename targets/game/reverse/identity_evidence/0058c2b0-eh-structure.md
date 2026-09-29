# 0x0058C2B0 — EH structure, the sret return object, and the last 4 bytes

RVA `0x0058C2B0`, 170 bytes. **LANDED 2026-09-29** as
`?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z`, source
`game/GameEngine/Source/Common/BfmeCallDUL.cpp`, byte-exact.

The sections below are kept as written while the body was being recovered; the
"residue" claim in *The residual 4 bytes* is **disproved**, and
*Why the argument is a member address* records the lever that landed it.

## Identity, and a correction to the pin's signature

`0x0001D467` is a 5-byte ILT thunk (`e9 44 ee 56 00` → `jmp 0x0058C2B0`,
ledger `?j_0001d467@@YAXXZ`). The five callers at `0x006C1C10`-`0x006C1CD0`
(`bfmeGoDUL{a..e}`, matched) each push one of `0x0111D7F0`+
("PingAttack", "PingBeacon", "PingGeneric", "PingInformation", "PingUpgrade")
plus a pointer they received, then return that pointer.

`symbols.csv` pins `?bfmeCallDUL@@YGXPAXPBX@Z` at the thunk, i.e.
`void* __stdcall f(void*, void const*)`. **The body contradicts that
signature**: the function returns a *class by value* and takes one
`const char *` (proof below). The pin's decorated name is a repo-invented
placeholder for the five-caller cluster — it carries no `route=` note and the
name is not in any import hint table — so keep the address-keyed name and do
not treat `PAX`/`PAX PBX` as the ABI. The proven mangling of the shape below is
`?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z`.

## Proved frame map

`python3 tools/eh_info.py 0x0058C2B0` plus the raw funclet bytes
(`0x00C37310`..`0x00C3734C`) fix the layout. In a VC7.1 funclet EBP is the
enclosing function's entry ESP (X) — the same offsets appear in our own
compiled funclets — so:

| slot | retail use | funclet use |
|------|-----------|-------------|
| X-0x18 | flags word: bit0 string temp, bit1 return object | `[ebp-0x18]` in all three actions |
| X-0x14 | `BFMERetailAsciiString` temporary | `[ebp-0x14]` → string dtor |
| X-0x10 | raw `operator new` result | `[ebp-0x10]` → `operator delete` |
| X-0x0c | saved `fs:[0]` chain | — |
| X-0x04 | the EH state variable (the pushed `-1` slot) | — |
| X+0x04 | the object's address, written through | `[ebp+0x4]` → `release` |
| X+0x08 | the `const char *` | — |

## The return object is an sret slot (this is the whole body)

```
+006a  mov esi, [X+4]      ; esi = the hidden RETURN pointer, not a value
+006e  mov [esi], eax      ; returnObject.m_ptr = p
+0072  inc dword [eax+4]   ; if (p) ++p->ref
+0099  mov eax, esi        ; small class return: eax = object address
+00a7  ret 8               ; [sret][const char *]
```

Independently, the state-0 funclet at `0x00C37334` is

```
mov eax,[ebp-0x18] ; and eax,2 ; je ret
and dword [ebp-0x18],-3
mov ecx,[ebp+0x4]                       ; destroys the object AT [X+4]
jmp 0x0018336 -> 0x00107550             ; ReferencePointerReleaseThunk::release
```

and `0x00107550` (matched `?dup_00107550@@YAXXZ`) begins `mov ecx,[ecx]`, so
`this` is the object in the first stack slot and it releases `this->m_ptr`.

Only two things can put an object in the first stack slot: MSVC's sret pointer
or a by-value class parameter. The by-value spelling emits a normal-path
destructor call, which retail does not have (retail's normal path never calls
`release`). **So the first stack slot is an sret pointer and the function
returns a four-byte class by value.**

## The lever four earlier verdicts called unreachable

The third cleanup object *is* reachable. Three conditions, all required:

1. **The return type is a small class returned by value** (sret), so the
   object lives in the caller's storage at `[X+4]`.
2. **Its destructor is USER-DECLARED and not `throw()`.** VC7.1 treats an
   implicit destructor as `throw()` and registers no unwind action for it at
   all. With a bare `void release();` member and no user destructor, every sret
   spelling measured produced only **two** funclets. Adding
   `~RefCountPtr() { release(); }` immediately produced the third funclet,
   `or ebx,2` in the body, and the retail state sequence.
3. The object must be built by an **inlined constructor into the sret slot**
   (`return RefCountPtr(new Owner(...));`). A named local + `return r` gets its
   own local and a `sub esp,0x10` frame.

With those three, `tools/probe.py --shape` reports **2 structural differences
in the whole body**, the state stores `dword 1` / `byte 2` / `dword 0` match
retail exactly, and funclet `$L387` is byte-identical to `0x00C37334`.

Body order: `operator new(0x18)` → `BFMERetailAsciiString(what)` →
`Owner((int)&temp)` → `returnObject.m_ptr = p` (store first, then AddRef) →
string temp destructor → return the object address. The string temporary is
therefore alive until the end of the whole full expression, which is why it
must be a temporary *inside* the new-expression and not a local.

## The residual 4 bytes — SOLVED, it was not a residue

**Every "codegen residue" conclusion in this section is wrong.** The lever is a
one-word class in the right place:

```cpp
class ArgBox
{
public:
	ArgBox(const char *text) : m_s(text) {}
	~ArgBox() {}
	BFMERetailAsciiString m_s;
};

Rva0058C2B0RefPtr __stdcall bfmeCallDUL(const char *what)
{
	return Rva0058C2B0RefPtr(new Rva0058BF70Owner((int)&ArgBox(what).m_s));
}
```

170 bytes, `probe.py` EXACT, all three funclets byte-identical to retail's.

The fold measured here is narrow and that is the whole trick. VC7.1 turns
`&class-prvalue` into the constructor's own `this` return value, so
`(int)&BFMERetailAsciiString(what)` emits `push eax`. `&ArgBox(what).m_s` is a
*different* expression tree — a member selection on a prvalue is an
indirection on the object, not the object's address — so C1 re-materialises the
frame address with `lea ecx,[X-0x14]` instead of reusing the constructor's
return value, and the flag store sinks back after the push, exactly as retail
writes it. `ArgBox` holds nothing but the string, so `&m_s` is the object's own
address (the slot and the `[ebp-0x14]` destructor target are unchanged), and the
`ArgBox` destructor is the inline `~BFMERetailAsciiString`, i.e. the
`releaseBuffer` call at the end of the body.

Measured in `build/sweep_arg5.py`:

| spelling | bytes | argument |
|---|---|---|
| `(int)&BFMERetailAsciiString(what)` | 166 | `push eax` |
| `(int)&ArgBox(what).m_s` | **170** | `lea ecx,[X-0x14]; push ecx` |
| `(int)&*(volatile BFMERetailAsciiString *)&ArgBox(what).m_s` | 170 | same shape |

### The measurement that produced the wrong conclusion (kept for the record)

```
retail  +004a  lea ecx,[esp+0xc]      ; +004e push ecx ; +004f mov ebx,1
ours    +004a  mov ebx,1             ; +004f push eax
```

Everything after this point is byte-identical, including `or ebx,2`,
`test bl,1`, `mov dword [X-4],0`, `and ebx,0xfffffffe`, the flags re-spill, the
string destructor call, the `fs:[0]` restore and `ret 8`.

VC7.1 folds `&class-prvalue` to the constructor's return value. Measured
folds (all 166 bytes, no `lea`): direct `&temp`; `(T *)&temp`; `(T)temp`;
`&*(&temp)`; `&temp + 0`; `(long)`, `(unsigned long)`, `(void *)` casts;
`operator int()` / `operator int() const` returning `(int)this`;
`operator BFMERetailAsciiString*()`; a user `operator&`; a `const T&` helper
returning `(int)&s` and a `const T*` helper; a chain of two such helpers; a
`BFMERetailAsciiString(BFMERetailAsciiString(what))` double temporary; a
`?`-conditional on `what` (182 bytes); and declaring the Owner constructor to
take `BFMERetailAsciiString *`, `const BFMERetailAsciiString &` or `void *`
(the reference and pointer forms also fold to `push eax`).

Only a **named lvalue** gets a fresh `lea`, and a named local would run its
constructor before `operator new`, which is not retail's order. That reasoning
was sound and still incomplete: a **member of a prvalue** is also not a named
lvalue, and it also gets a fresh `lea`, while keeping the construction order
(the `ArgBox` temporary is materialised inside the new-expression's argument,
after `operator new`). `tools/rotation_sweep.py` tried all three toggles (+0),
and `tools/shape_search.py` over the five `eh_levers` choices (9 trials) found
no improvement — the family was right that no amount of rotation or EH-flag
choice reaches this; what reaches it is the expression's *shape*.

## Shapes measured (probe.py, 0x0058C2B0, /O2 /EHsc)

| source shape | bytes | notes |
|---|---|---|
| `void* f(void* out, const void*)` + inline `assign` (old bank) | 150 | 2 funclets; state stores `ebx`/`byte 1` |
| by-value class parameter | 183 | state sequence right, extra normal-path release |
| `RefPtr&` / `const RefPtr&` parameter | 186 / 152 | no `[ebp+4]` action at all |
| named `BFMERetailAsciiString` local | 129 | wrong order: string before `operator new` |
| sret, ctor inlined, **implicit** destructor | 152 / 166 | only 2 funclets — the key negative result |
| sret, named local, implicit destructor | 197 | extra local, `sub esp,0x10` |
| sret, `~RefCountPtr() throw()` | 155 | `throw()` dtor: still 2 funclets |
| sret, inlined ctor, user-declared non-`throw()` dtor | 166 | 3 funclets; funclet #3 byte-identical; 2 structural diffs |
| member function / constructor of the refcounted class | 154 | `this` pinned in edi, store duplicated |
| placement `new (out) RefPtr(...)` | — | emits `operator new(unsigned,void*)` |
| **sret + `(int)&ArgBox(what).m_s`** | **170** | **LANDED: exact, 3 funclets all byte-identical** |

## Superseded claims in the earlier note

* "Retail writes the state with `mov dword [X-0x4], 1` … a shape that leaves
  the trylevel `-1` in place" — the `-1` stays; what produced `ebx`(0)/`byte 1`
  was the missing return object, not the state encoding.
* "the EH state variable is a bit mask over cleanup actions (1|2=3 explains
  retail's byte store of 2)" — no. Retail stores the literal **1** then the
  literal **2** then **0**; these are trylevels. The flags word at `X-0x18` is
  the separate bit mask, and `or ebx,2` sets bit 1 of *that*.
* "the third cleanup object … lives at [ebp+0x4] … Retail's normal path never
  calls that release, so the object is not owned on the normal path" — correct
  as an observation, but the object is the **returned class instance**, and the
  caller owns it. That is why the return type is a class and not `void*`.

## Reading the retired banked scores

Retired: the body is matched, so `targets/game/reverse/attempts/0x0058c2b0.cpp`
was cleared by `tools/add_match.py` and the three `partial` rows in
`re_attempts.log` are superseded by the `converted` row for
`?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z`.

For anyone comparing against the retired numbers: the banked `score=0.4882` was
a raw byte-identity ratio and was *lower* than the 0.667 of the superseded
133-byte bank only because that body was four bytes longer in the middle, so
every later byte was positionally shifted. The structural match was much better:
`probe.py --shape` gave **shape 0.961 with 2 structural differences** against
**0.824 with 8** for the bank it replaced.

## Reusable lessons from this body

1. **A user-declared, non-`throw()` destructor is what makes VC7.1 register an
   unwind action for a returned class.** VC7.1 treats an implicit destructor as
   `throw()` and registers nothing. Any body whose unwind map destroys an object
   whose destructor the callee never calls on the normal path needs this.
2. **`&class-prvalue` folds to the constructor's `this` return; a member of that
   prvalue does not.** This is the cheapest known way to make C1 re-materialise
   a frame address it could otherwise forward in EAX, and it preserves the
   construction order that a named local would destroy. Reach for it before
   concluding that a `lea`/`push` pair is a residue.
3. **A VC7.1 funclet's EBP is the establisher's frame**, and its `[ebp-N]`
   displacements match the enclosing body's own `esp`-relative slots (`ebp = X-6`
   for a body with `sub esp,0xc` + two pushes). Read the funclets before
   hand-decoding the body's locals; here they fixed the frame map and the sret
   reading in one step.
