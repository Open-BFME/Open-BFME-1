# Shape levers: the checklist for "everything matches except..."

Run `python3 tools/probe.py <file.cpp> "<symbol>" 0x<RVA>` first: it compiles, diffs against retail with relocations masked, and prints the symptom row below with its lever.

Read this before banking a near-miss. Each lever below turned a 0.9+ partial into
a byte-exact landing on 2026-09-02. Each row states its own mechanism.

| Symptom in the byte diff | Lever |
|---|---|
| One ModRM/SIB byte: ours `[edi+edx]`, retail `[edx+edi]` | Add the pointer as an INTEGER on the right of the counter: `*(const char *)(i + (unsigned int)p)`. `p[i]`, `*(p+i)`, `i[p]` all give the other order. |
| `mov ecx,esp` before `mov [esp+N],esp` (EH saved-esp) at a by-value string arg | The string class must be `class AsciiString : private StringBase<char>` with INLINE forwarding copy ctor/dtor to the base; use `reference/shims/stringinline/StringInline.h`. Out-of-line ctor/dtor on the string class itself transposes it on every flag. |
| Scoped parser constructor remains 142/144 bytes versus retail 146, with the saved-`this` slot or EH state wrong despite matching registration calls | Model the receiver's real 12-byte registration base and put the temporary in its initializer: `: BfmeParserRegistrationVE(table, (AsciiString *)&AsciiString("chunk"), label ? label : &AsciiString::TheEmptyString)`. Use the existing `stringbaseascii/Common/AsciiString.h` shim; do not add a second string-base destructor or manually destroy a named local. The temporary ends after base initialization, before derived context/vptr stores. Matched witnesses: `Rva00450460ParserRegistrationCtor.cpp` (146 B), `Rva00352AB0ParserRegistrationCtor.cpp` (153 B with two extra fields), and `Rva0074A680ParserRegistrationCtor.cpp` (139 B with no extra field). Derive each literal, vptr and argument count independently; `registerParser` returns `UserParser*`, not `void*` or `void`. This is a receiver-initialization lifetime issue, distinct from the by-value string-argument row above. |
| Whole body one callee-saved register apart (esi/edi, esi/edx) | Register assignment follows local DEFINITION ORDER. Define locals in the order retail first materializes each value (`const T *q = s2; const T *p = s1;`). |
| Loads retail hoists above a guard (`test ecx,ecx; mov esi,[a]; mov edx,[b]; jle`) | Copy the parameters into locals AFTER the preceding computation and BEFORE the `if`. Inside the guard they sink; at the top they change the prologue. |
| Import called twice: retail `mov edi,[__imp_X]; call edi ... call edi` | Call the real `__declspec(dllimport)` function directly. MSVC CSEs the IAT load into a callee-saved register allocated after existing locals; a pointer global or a cached local allocates first and mirrors ESI/EDI (and flips the vtable temp eax/edx nearby). |
| `flag = 1` reached by two forward jumps, placed after the main path | One fall-through tail: `if (a) { ... if (b) { ...; return; } } flag = 1;` -- never two inline `{ flag = 1; return; }`. |
| PMF constants `{pfn, -100, 0}` and a `[obj+0x68]` vbtable walk | `reference/shims/objectdlink/ObjectDlinkPmf.h`: Object's vbptr is inherited from a base at +0x68 (vbtable[0]==0), DLINK base at +4; pass the PMF as a value. |
| Two parameter loads swapped: retail `mov eax,[esp+8]` (arg2) before `mov edx,[esp+4]` (arg1), body otherwise exact | The allocator claims registers in the order values are first MATERIALIZED, and a field address counts before a field load. Take the address of a field of the later-used pointer into a local before the first expression: `const float *tp = &other->m_x;` then use `tp[0]`, `tp[1]`. It folds into the addressing mode, so only the load order changes. Landed 0x001E24F0 (78 B) on 2026-09-04 after 25 min of local-definition-order and reference-parameter variants had failed. |
| One displacement byte in `mov [esp+N],esp` (the EH saved-esp of a by-value temporary): retail N points at a LATER incoming-argument slot than ours | With no frame locals MSVC parks that saved-esp in a dead argument slot, choosing the first argument that is dead when the temporary is built. Reference the earlier argument in every expression that needs it (`(T *)b - 1` three times) instead of copying it to a local once: its slot stays live past the temporary and the allocator moves on to the next dead slot. Landed 0x002EADF0 (47 B) on 2026-09-04; class-size, typing and copy-order variants all left the byte alone. |
| Frame the right size, but a contiguous run of locals sits on each other's slots, and reordering the declarations changes nothing | Retail holds one more object than your source, packed onto a user local that is already dead. Find the in-place update that should have produced a value and write it as an expression: `offset = offset * r * 0.5f` instead of `offset *= r; offset *= 0.5f;`. See "A run of locals on the wrong slots" below. Took `0x002C8A20` (1154 B) from 58 differing bytes to exact on 2026-09-15. |
| Frame larger than ours by the size of a small struct (`sub esp,0xC` vs `sub esp,8`), spill slots otherwise identical, no extra stores | Retail kept an aggregate local whose stores were forwarded away but whose frame space stayed. Declare `float v[3]` (or the struct) and fill it from the calls, then build the return value from `v[0..2]`: the array gets the frame, the loads are forwarded, and the body is otherwise unchanged. A `volatile` or an address-taken scalar does NOT do it. Landed 0x005F9DE0 (65 B) on 2026-09-04. |
| A temporary's or RAII local's destructor call (string releaseBuffer, Release_Ref reload-and-branch) sits LATER in ours than in retail, e.g. after a `return expr;` copy-construct or at the end of the enclosing block | The destructor fires at the end of the object's OWN scope. Wrap the local in its own nested `{ }` block ending where retail's destructor call sits; the rest of the body is unchanged. Landed 0x0010D940 (326 B, 137-byte diff -> exact) and 0x0071B1F0 (384 B) on 2026-09-05. |
| Identical-looking return tails NOT merged (an extra `call` + epilogue per `return f(v).first;` site, body ~30 B long, one relocation more than retail), and a pointer loaded before an out-of-line comparator/functor call is RELOADED from memory after it | The callee is opaque: MSVC 7.1 assumes a declared-only function may write the object it gets a pointer into, so it reloads and cannot cross-jump the tails. Give the callee a VISIBLE body and `__declspec(noinline)` (`__declspec(noinline) bool operator()(const K &a, const K &b) const { return a.m_bits < b.m_bits; }`): the call stays out of line (still a REL32 to pin) but the compiler now knows it has no side effects. Landed the two 629 B SparseMatchFinder MatchMap hinted insert_unique bodies 0x001429C0 / 0x001426A0 on 2026-09-05 after key size, const-ness, ctor/dtor triviality, allocator and include-order experiments all left the body at 661 B. |
| An EH state store (`mov byte ptr [esp+N],K`) appears in ours around a call that retail makes with NO state change (typically a by-value string temporary passed to a lookup: retail goes ctor, call, dtor with no state bytes between) | Retail knew that callee cannot throw. Declare it `throw()` (`PreferenceNode *find(const AsciiString &) const throw();`): MSVC 7.1 then elides the unwind state for the temporary across that call. Landed the three 377 B getPreferredMap bodies 0x0009E470 / 0x00086A20 / 0x0009E830 on 2026-09-05 (together with the StringInline shape for the by-value temporary and the ZH `isValidMap(ret, TRUE)` tail). |
| Split epilogue with `xor eax,eax` vs a folded one | `return new X;` splits; `new X;` as a statement folds. |
| A trivially-copyable class arg gets built as a local + pushed copy | Give the class a declared copy ctor/dtor (non-trivial) so it is constructed in place. |
| "Owning class unidentified" | `python3 tools/vtable_lookup.py <vtable VA>` -- retail slot table, ledger names per slot, and the ctors/dtors that install it. If only the body RVA is known, use `--target 0x<RVA>` to find candidate table heads through bounded slots and retail thunks; verify the installing constructor and caller ABI before assigning a name. |
| Callee "unpinned" in an old stash | Look it up again -- `reverse/zh_sweep/requeue_resolved_callees.csv` lists 72 bodies whose blockers have since been pinned. |
| Extra register saves or local copies around a non-inlined helper taking a local's address | Check the real helper's definition in the original TU. MSVC 7.1 uses knowledge that the helper does not retain the pointer even with `__declspec(noinline)`. `python3 tools/callee_visibility.py` reproduces this; [controls and limits](callee_visibility.md). Do not invent a non-retaining stub. |
| Two `if` arms test the same value against two constants, and ours folds the first arm's exit into the second arm's (`jmp <je>` where retail has its own `je`) | MSVC propagates the first constant into the second test, so the first arm's false edge skips the second compare and the two identical exits cross-jump. A `_ReadWriteBarrier()` between the two `if` statements stops both and emits no byte. Read the field into a local BEFORE the barrier, or the barrier forces a reload and adds a byte. Landed 0x008D20F0 (52 B) on 2026-09-11 after 8 phrasings and a flag sweep had left the fold. |
| A 12-bit bitfield store emits the MSVC insert (`shl; xor; and; xor`) where retail has `and <keep-mask>; or` | Retail knew the value fits the field, and a clamp written as an `if` does not tell MSVC that. Declare the word as a union of the bitfield struct and a plain `unsigned int`, read the count through the bitfield so retail `xor esi,esi; mov si,[p+6]; and esi,0xfff` survives, and write through the dword with an explicit keep-mask and shift. Took 0x008D6010 (163 B) from 52 differing bytes to 11 on 2026-09-11. |
| A member read that retail performs twice is served once, and the live pointer steals the register retail spends on the next value | MSVC keeps the first read alive across the guard chain. Qualify the member `volatile`, as `Rva008D2070AvailabilityScan.cpp` does for `m_owner`, or put a `_ReadWriteBarrier()` before the second read. Both restore the second load. Recovered the size and the register assignment of 0x008D6010 on 2026-09-11. |
| The SEH registration prologue is in the wrong order. Ours is `push -1`, `push <scopetable>`, `mov eax,fs:[0]`, `push eax`. Retail is `mov eax,fs:[0]`, `push -1`, `push <scopetable>`, `push eax` | One thing decides the order, whether the function allocates a frame slot. A function that emits `push ecx` or `sub esp,N` for a local or a compiler temporary reads `fs:[0]` third. A function that allocates none reads it first. So stop respelling the local as a temporary or a reference, and find what wants the slot instead. Usually it is the raw pointer MSVC parks for a `new` expression while the constructor may still throw. MSVC puts that pointer in a dead incoming-argument slot when one is free, and an argument is only dead once it has been read into a callee-saved register and never reloaded. Two probe functions that differ only in how many values stay live across the `new` print both forms side by side. The matched witness for the no-slot form is `?apply@SkirmishScreenState@@QAE_NPAXH@Z` (443 B) in `SkirmishScreenStateApply.cpp`, which pushes four callee-saved registers and allocates nothing. This replaces the guess in the project note seh-prologue-has-two-forms that a named local with a constructor picks the form. |
| Every instruction matches but the argument setup before a `p->f(...)` call on a global receiver uses the wrong registers. Retail holds one argument in ecx, pushes it, then reloads ecx with the receiver. Ours loads the receiver into ecx before the pushes and parks that argument in edx | Look at the guard chain above the call. A byte-sized equality test written as a term in the `&&` chain and the same test written as a one-case `switch` both emit `movzx eax,byte ptr [esp+N]`, `dec eax`, `jne`, so the bytes before the call are identical and the diff starts at the call setup. The switch is what frees eax for the first hoisted load, which pushes the second load into ecx, which makes MSVC sink the receiver load below the last push. Landed `?bfmeKey0052CDA0@BfmeA1021@@QAEHHHEE@Z` (99 B) after five sessions had banked the `&&` spelling at 0.97 with a 15-byte residue. The matched neighbour `?bfmeHandleAI@BfmeOwnAI@@QAEHPAXHEH@Z` at 0x005597B0 needs the same switch. |
| A float guard emits `fcomp; fnstsw ax; test ah,5; jp` where retail has `test ah,1; je`, or the other way round | Spell the comparison the way retail reads the status word. `a < b` tests C0 and C2 together, so it needs `test ah,5` and a parity jump to keep an unordered pair out of the true arm. `!(a >= b)` tests C0 alone and gives `test ah,1` with a plain `je`. The pair `test ah,0x41` with `jp` is what `a <= b` gives. Respelling the guard costs no bytes anywhere else. Took 0x0069AE40 from a wrong compare to a byte-exact one through +0x35 on 2026-09-15, and was one of the two changes that landed the 174 B ramp step at 0x0069ACE0. |
| Two return arms each build the same class from a different pointer, and ours pushes the string literal as an immediate where retail loads it into a register first, with one `push esi` before the branch where retail has one inside each arm | Move the choice of pointer into a `static` free function that returns it, and call that function inside the single `return Class(pick(...));`. MSVC 7.1 inlines the helper, gives its return value a register, and duplicates the construction into both arms with its own register save in each. Writing the same choice as two `return Class(...)` statements, as a local assigned in both arms, or as a ternary all fold the literal back into the push and hoist the save. This landed the 101 B room-type name accessor at 0x0069D240 on 2026-09-15 after a nine-shape search over loop and return spellings had left it two bytes short. |
| Retail keeps `this` in ECX across a call and never reloads it, and ours copies `this` into a callee-saved register | MSVC 7.1 treats ECX as surviving a `__thiscall` call whose receiver is the caller's own `this`, so a member that calls its own members keeps `this` in ECX and never reloads it. It makes no such assumption about a receiver it computed, such as `((Block *)(global + 0xb8 + i))->method(...)`, which it recomputes before every call. Read the retail call site and see whose object it passes. A receiver that is `this` reaches retail's shape as soon as the callee is declared a member of the same class. A computed receiver does not reach it at all, so bank the body rather than respell it, as 0x00699AF0 and 0x00699B90 had to be. Register pressure also beats the assumption. At 0x0069F3B0 the search loop claimed ECX for its candidate pointer and `this` spilled to EBX anyway. |
| Retail keeps two identical return tails, one reached by falling through a guard and one reached by a jump, and ours keeps only the first with the second arm jumping back into it | MSVC 7.1 cross-jumps identical tails. One barrier intrinsic is not enough, because the arm without it still jumps backwards into the arm with it. Put a DIFFERENT barrier intrinsic in each arm, `_WriteBarrier()` in the early return and `_ReadWriteBarrier()` in the late one. The same intrinsic in both arms merges the tails again, and `_ReadBarrier` costs five bytes. Neither `_WriteBarrier` nor `_ReadWriteBarrier` emits an instruction or a relocation. Took the second retail copy of STLport `basic_string<char>::find(char, size_type)` at 0x00653990 from 61 bytes to all 69 on 2026-09-15, after four sessions had banked it at 0.82 and ruled out condition polarity and `#pragma optimize`. A third site returning the same value picks whichever copy carries the SAME intrinsic it does, so tag it with that one to choose which copy retail jumps back into. That took `LinePassableStruct::linePassableCallback` at 0x003E5950 from 191 bytes to all 203 the same day, where retail keeps two copies of a twelve-byte `return 1` tail and a third site jumps back into the first. Order the arms so the copy retail falls through to is the fall-through in the source too, or the block layout still differs. |

## Filter construction: visible non-retaining constructors

`Rva002622D0Collect.cpp` (532 bytes) initially kept a six-word mask
temporary in separate stack storage: frame `0x84`, retail `0x6C`.
The real `PartitionFilterAcceptByKindOf` constructor copies both masks;
it does not retain either reference. Giving the TU its complete, independently
exact 102-byte constructor at `0x000C3DD0`, with `__declspec(noinline)`,
lets VC7.1 reuse the mask's storage for the relationship-filter temporary.
This is the same callee-visibility mechanism as the pathfinding lookup below,
not permission to invent a non-retaining stub or shorten a lifetime.

Native `BitFlags<192>` construction also matters. The immediate `0x40000`
belongs to the fourth word here: bit **114**, not bit 18. Derive the word
offset before assigning a semantic flag name. Temporary filters are destroyed
after iterator initialization and before iteration, as in the other filter
witnesses.

The caller's nested pointer-vector base exposed a second boundary: native
inlined node allocation emitted 130 bytes, whereas retail's 97-byte base at
`0x001D95B0` calls the 29-byte node allocator at `0x00061CE0` out of line.
A TU-local specialization of the scoped pointer allocator preserves the
zero-count check and element-size multiplication, but calls that real,
independently exact allocator through a noinline definition. This recovers
the base without changing the 532-byte caller. It is a local template
inlining decision, not a reason to change the shared allocator or pin a
130-byte emission to a 97-byte body.

The 898-byte LevelGrant action at `0x00260180` exposed the same issue for
object-status masks: use native `BitFlags<86>` (12 bytes), not a hand-written
three-word struct with chained zero assignments. Native temporary construction
removed an extra EBP lifetime. Its `0x20` store is in the second mask word,
so the absolute bit index is **37**, not 5. Two other semantic details were
necessary for the exact body: sequential, left-associated filter appends
(`a.link(&b)->link(&c)`), and the query position at the primary owner's
`this + 0xB0`, not at its nested Object pointer plus `0xB0`. Trace the receiver
reloads independently; matching field displacements do not identify the owner.

The 777-byte DominateEnemy action at `0x0025AEE0` confirms the distinction:
its 32-byte filter is two `BitFlags<86>` masks, not one `BitFlags<192>` mask
despite equal total storage. Identify the installed vtable before choosing
the mask type. Its template accessor needs an explicit null return before
following the override; the caller still dereferences that result, as retail
does. A signed-byte high-bit test `(value & 0x80) != 0` produces retail's `js`
where `value < 0` produces `jl`. Finally, its local-static key initializes from
`"TemporarilyDefectUpdate"`, not the enclosing class name: inspect string
relocations even after a masked probe says exact.

For the 806-byte GrabPassenger action at `0x0025F2D0`, finish the control-flow
inventory before changing compiler flags: retail has **three** nearest-object
queries, including the `0x2000` option path. Its two distance calculations need
different local shapes: interleave each terrain-point component copy with its
subtraction, but keep the object-position delta as a `Coord3D`. A whole-struct
copy followed by both calculations gives different x87 spill scheduling.
The final dispatch reloads Object through the secondary receiver rather than
reusing the earlier Object local. Preserve that reload and the observed
null-target branch; do not initialize or copy coordinates on a path where
retail does neither merely to make the reconstruction look safer.

## Model-condition bit masks: retain the native accessor layers

When retail materializes a constant mask in a register (`mov eax,mask;
test eax,ecx; or ecx,eax`) but a raw word expression emits an immediate OR
or a compare against the updated word, preserve the native accessor layers:
a small condition wrapper with inline `test/set/reset` forwarding to
`_STL::bitset<320>`, consumed by a free `__forceinline` conditional-update
helper that calls the real Object notifier. Calling bitset directly from an
Object member was not equivalent for VC7.1's code generation.

Verified witnesses are `Rva0025EF90ChargeApplication.cpp` (230 B),
`Rva0018E210TurretAngleConditions.cpp` (405 B), and
`TurretAI::friend_turnTowardsAngle` in `TurretAI.cpp` (274 B). The last went
from an 11-byte residual to exact with the accessor layers; direct bitset
calls still differed by 53 bytes. Its canonical-header integration also
needed BFME's callback slot `0x30`, not the reference header's `0x20`.

Keep the full field base and the bit index honest: Object's 40-byte array
starts at `+0x110`; accesses at `+0x114`, `+0x124`, and `+0x130` are interior
words, not new arrays. Derive names from the shipped enum table rather than
Zero Hour's different numbering. This lever does not validate a routine's
identity or excuse a changed lifetime or comparison.

Also check that the attempts log entry is not stale: `grep ,0xRVA, reverse/functions.csv`
-- if the row already points at a `.cpp`, someone landed it.

## Verified results from the Astra campaign (2026-09-04)

These are targeted hypotheses, not flags to apply to every translation unit.
Each landed through the ordinary relocation-aware byte and identity gates.

| Observed mismatch | Proven cause and bounded experiment |
|---|---|
| Two identical branch tails merge into one; body is seven bytes short | In `luaV_execute` (0x00997C80, 2924 B), an MSVC `_WriteBarrier` intrinsic inside one conditional-pop arm preserves both tails while emitting no instruction or relocation. `_ReadWriteBarrier` also worked; `_ReadBarrier` added five bytes. Document this as reconstruction shaping, not original source. The same experiment did not solve Weapon or road-junction register drift. |
| A large constructor lacks 16 frame bytes and several EH states | In the ParticleBuffer copy constructor (0x00989A20, 4714 B), four texture getters return owning one-pointer handles through hidden result slots. Legacy raw-pointer declarations hid their lifetimes. TU-local ABI shims, normal destructors, and the retail `else if` LOD clamp recovered the whole body. Check getter retain, setter handle-address consumption, cleanup release, and a matched caller before assigning identity. |
| Constant-2 register reuse spreads through a body with local statics | `ParticleBufferClass::Render_Line` (0x0098AD00, 1763 B) needed `/EHsc` instead of the build default `/EHsc-`. The default emitted extra EH states 0/2/4 around `atexit` registrations; that state 2 induced unrelated-looking EBX reuse. Retail omits those states. Correcting the exception model recovered the whole body without forced registers or barriers. |
| Final `rep movsd` setup has its source address and count loads swapped | In the terrain matrix helper (0x007DCF00, 281 B), put the final matrix assignment inside each branch after its last matrix multiplication. MSVC still merges the copy tails but emits retail's `lea esi` before `mov ecx,16`. Explicit intrinsic `memcpy` did not help. Independent relocation review also corrected the old bank's terrain-global name and reversed scale signs; masked equality alone hid both defects. |

## Additional verified family results (2026-09-04)

- Shader resource cleanup: an inline `int decrement(int *p) { return --*p; }`
  followed by a separate member zero test preserves retail's address materialization.
  Use the global object directly in the guarded `Release_Ref()` call; caching it
  in a local changes register allocation. This recovered shutdown (0x00717DA0,
  187 B), dependent-resource cleanup (0x00717C90, 218 B), and resource creation
  (0x00716770, 399 B). Counter wrapper classes and volatile fields were unnecessary.
  Identify the object independently: VA 0x012F9D1C holds a DX8 vertex buffer,
  proved by the matched constructor at 0x0091F2F0, despite an old bank calling it
  a texture. COM `Release` alone does not identify the resource subtype.
- Lua `codepushbool` (0x0099EF70, 151 B): `__assume(i != 0)` after instruction
  encoding preserves the encode/codelineinfo ordering without emitting bytes.
  The assumption is justified by the nonzero OP_PUSHBOOL opcode, not merely by
  the desired disassembly. Do not generalize it to opcodes that may encode zero.
- StreakLine construction: the real empty Vector3/Vector4 constructors retain
  null EH states that a POD declaration loses. Nonthrowing array deallocation
  also recovered the StreakLine and MaterialInfo destructors. Inspect the actual
  member constructors and deallocation contract before inventing guard objects.
- MaterialRemapper mesh mapping (0x0092F2C0, 493 B): retain each source owning
  texture handle as a loop local, while passing the remapped temporary to the
  setter. Nested getter/setter expressions give different cleanup lifetimes.
- Display clock wipe (0x006EBF20, 2319 B): restore the original parentheses in
  `start + (width / 2 * percent)` and equivalent height expressions. They constrain
  MSVC 7.1 x87 reassociation even when the algebra is otherwise equivalent.

These are verified source-shape examples, not claims that the reconstructed
spelling is the original EA source. Failed neighboring hypotheses remain banked.

## Solo viewport family results (2026-09-05 UTC)

- Viewport rendering at 0x00716AD0 (913 B): all instructions matched but 38
  stack-displacement bytes differed. Two separate display-dimension floats,
  instead of a `Coord2D` local or a two-element array, restore retail's stack
  placement. Constructor, assignment, inheritance, and declaration-order changes
  did not fix the aggregate version. The vertex-buffer layout and owning append
  lock came from independently matched creation and lock functions.
- The adjacent quad renderer at 0x00716F50 (532 B) reuses that model. Keep
  `inverse = 1.0f / size` and `halfTexel = inverse * 0.5f` as separate locals;
  a single expression lets MSVC fold the numerator, removing a retail FPU
  instruction. Populate each vertex's position, color, and UVs together. Both
  complete bodies passed the normal relocation-aware byte gate and have a
  matched highlight-filter caller. Neither needs new symbol pins or inline asm.

## Verify the deleting-destructor ABI before chasing frame layout

`Campaign::newMission` (RVA `0x005BC7C0`, 343 bytes) was banked as a
stack-layout near miss. The old shim emitted 337 bytes. Modeling the retail
null check and virtual deleting-destructor call (`push 1; call [edx]`) made
the complete body exact; explicit virtual destruction emitted flag zero.
Mission's retail vtable at VA `0x0110F658` leads through `0x0044534A` to
`0x009BBDF0`, whose flag-one path calls global delete at `0x00C81EB0`.
The Generals reference's get-pool / destroy / freeBlock implementation is
therefore not the lifetime model for this BFME caller. The accepted source
uses a TU-local lifetime view and emits no vtable. For another family, trace
its actual vtable and free path first; this is not a global pool-shim change.

## Fleet tools (all read-only except add_match/re_log)

| Need | Tool |
|---|---|
| Send a worker fresh, non-stale work with per-body context | `python3 tools/brief.py --dump <gen_asm file> \| --rvas ... \| --csv <worklist>` |
| Find banked bodies already landed, or whose blockers got resolved | `python3 tools/stale_partials.py [--stale] [--requeue out.csv]` |
| Find which one pin/model unlocks the most dump bodies | `python3 tools/dump_families.py [--show N]` |
| Whose function is this (vtable in the prologue) | `python3 tools/vtable_lookup.py <vtable VA>` |
| Compile, retail-diff, name the wall | `python3 tools/probe.py <cpp> "<symbol>" 0x<RVA>` |
| Per-site inline-ctor load order | Same `__forceinline` ctor inlined at N macro sites; retail loads the buffer pointer first at early sites but the terminator byte first at late sites (`mov cl,[m_NullChar]` before `mov edx,[esp+N]`), ours pointer-first everywhere (1 byte off: AL short form). | Add a tag-overloaded ctor variant reading the byte through `*(volatile char *)&m_NullChar` and use a second macro for the late sites only; the volatile read forces byte-first at those sites and leaves the others alone. Landed 0x00717E90 setShroudTex (2072 B) with the last 3 of 8 sites switched. |
| Static function with a private register convention | Retail body reads its argument from esi with no stack load and starts with `push ecx`; a standalone extern function compiles a normal prologue (twin landed inside its big ported TU, the copy did not). | Declare the function `static` and give it a TU-local caller (marked absent-from-retail); MSVC 7.1 then passes the argument in a register exactly as in the port. Landed WOLLobbyMenu and LanLobbyMenu shutdownComplete (0x004F98B0, 0x004CE910). |
| Store-before-load ordering via escaped address | Retail stores a static flag before loading through a pointer parameter; ours sinks the store next to the call. Volatile does not move it. | The flag's address escapes somewhere in the retail TU, so MSVC cannot prove the pointer does not alias it. Add an absent-from-retail helper returning `&flag`; the store then stays ahead of the pointer load. Landed 0x004CE910. |
| Twin inside a large ported file: copy the include block | Copying only the function and the obvious headers produced a wrong field offset (MeshClass::Model at 0x94 instead of 0xc8). | Header order defines the class layouts; copy the ported file's cl: line and its full #include block into the new TU. Landed 0x006F8720. |
| sret result addressed through eax | A helper returns a record by value (sret slot pushed first); retail then uses the returned eax as the record's address (`mov edi,eax; push edi; mov cl,[edi+4]`) and starts the record's EH state after the call, while a named local (or a reference bound to the result) makes MSVC re-derive the address with `lea [esp+N]` (+3 bytes). | Make the record a full-expression temporary consumed inside the next call: `insert(Record(helper(a, b)))` with a small adapter struct deriving from the pair type. Destruction order then matches retail too (pair first, record second). Landed 0x003476F0 setHumanImpassableArea (192 B). |
| STLport helper kept out of line (`_M_create_node`, `__destroy_aux`, `_M_fill_insert`...) or an extra try/catch region where retail inlines the node creation straight from `__node_alloc::_M_allocate` | Retail game TUs were built with STLport exceptions off per TU: `#define _STLP_NO_EXCEPTIONS 1` before the vendor `<map>`/`<vector>`/`<list>` (before `PreRTS.h` in port-style TUs, with `#include <map>` first so the default node allocator is kept). Landed the `_M_insert` family, hinted inserts (684, 1122, 629 B), vector twins, PSPlayerStats dtor. Second copies of a claimed name take an alias tag (empty comparator subclass / tagged element); `build/autopin.py` pins the callees. |
| Extra `mov [esp+N],-1` (EH state reset) after a vector-constructor iterator or array new, plus a loop-alignment `lea` NOP, 8-16 bytes long | Retail's TU saw `operator delete[]` declared `throw()`: with a nothrow array delete MSVC 7.1 has no reason to reset the EH state before the later `delete[]`. Declare `void __cdecl operator delete[](void *) throw();` before the includes (VectorClass<Vector2/3/4>::Resize, 480/515/550 B). |
| Twin of a port function blocked because adding a define to the port breaks its gen-funclet rows | The dump is a copy-paste twin in another retail TU: copy the whole port source into a new file, add the define, wrap everything after the includes in `namespace RvaXXXXXXXXTwin { }`, claim only the twin; autopin resolves its file-local statics and string literals (DIR32) to the retail copy's own (WOLWelcomeMenuUpdate twin 1164 B). |
| Body 4 bytes short: retail keeps `test edi,edi ... je` (the `delete` null test) after the next-link load; ours drops the test, or moving the store under an explicit `if` gives test/branch/store instead of retail's test/store/branch | VC7.1 folds the `delete n` null test once `n` itself has been dereferenced. Read the link through the FIELD, not the local: `e->m_list = e->m_list->m_next; delete n;`. Volatile reloads, a do-while, an explicit `if (n)`, and an inlined pop-front all still fold it (BfmeSecondZUnregister.cpp, 92 B). |

## AI pathfinding: authentic lookup visibility

`AIUpdateInterface::doPathfind` (RVA `0x0027B3A0`, 2031 bytes) was six
non-relocation bytes short of an exact match: two independent loads after
`destroyPath` appeared in reverse order. Local ordering and volatile reads
did not recover it. The out-of-line `findObjectByID` declaration hid the real
BFME hash-map lookup, which differs from Zero Hour's later flat vector.
Giving the TU-local lookup view its authentic body with `__declspec(noinline)`
recovered the caller exactly and allowed the old volatile cast to be removed.
The visible helper independently matches all 82 bytes at `0x0009A510`, and all
69 claimed emissions in AIUpdate.cpp pass the normal gate. This is another
case where callee side-effect knowledge affects scheduling in its caller;
the helper must be real, not an invented pure stub.


The same mechanism recovered two more AI siblings from real source:

- `blockedBy` (`0x00274630`, 1052 B): the opaque
  `Thing::bfmeRelativeAngleTo` call kept address-taken coordinate locals in
  separate stack slots. Its authentic non-inlined definition lets VC7.1 prove
  the pointers are not retained, reducing the frame from 0x5C to retail 0x4C
  and restoring copy scheduling. The helper independently matches 214 B at
  `0x00150510`. Nontrivial Coord3D copying is also required; the helper's
  arithmetic-only delta stays a trivial three-float temporary.
- `setPathFromWaypoint` (`0x00270B40`, 398 B): an inline Coord3D copy constructor
  reduced the mismatch to one swapped load/store pair (seven bytes at +0x94).
  Local-order, memcpy, flag, and copy-expression variations did not fix it.
  Exposing real `Path::prependNode` with `__declspec(noinline)` and its real
  inline PathNode constructor recovered the caller exactly. The helper also
  independently matches its existing 104-byte body at `0x0026E4D0`.

For a remaining load/store swap or excess frame slots, inspect the actual
called helper's memory effects before attempting register-order variations.
Keep the authentic helper and verify its emission; a fabricated side-effect
stub would manufacture a compiler assumption rather than recover the program.

## GameSpy packets: preserve native accessor expressions

An inlined getter can affect VC7.1 register allocation even when its result is
the same member load. The BFME results packet at `0x006386F0` compiled to
1694 bytes with direct seed/quick-match field reads, against retail's 1684.
Restoring `getSeed()`, `isQuickMatch()` and `getQuickMatchType()` as ordinary
inline accessors recovered all 1684 bytes. The earlier bank had broad register
and stack-home drift, not merely ten isolated extra bytes. The complete source
is `GameSpy/GenerateGameSpyGameResultsPacket.cpp`.

The same source-level context helped the 1583-byte ladder packet at
`0x00639190`: native seed, ladder-port and quick-match getters restored the
register schedule. The final one-byte difference was a real extra leading
variadic argument at `+0x4AB`. That malformed retail call shifts the format's
values and can feed a small integer to `%s`; preserve and document it for byte
matching rather than silently correcting it. This body's previous 1580-byte
claim also omitted its final `ret 4`, proven at `+0x62C` before INT3 padding.

For `PlayerInfoMap::operator[]` at `0x006359C0`, STLport's old built-in
value-initialization workaround emitted an extra `__default_constructed`
call. Selecting direct `PlayerInfo()` construction locally before parsing
`<map>` recovered all 288 bytes and the register schedule. See
`GameSpy/PeerDefs_PlayerInfoMap_Subscript.cpp`; no vendored header was edited.

## Special-power containers: access expressions and lifetimes

At `0x0025C7C0` (266 B), caching a separate vector-entry pointer produced a
264-byte weighted-choice body with 179 non-relocation differences: VC7.1
hoisted the extent and changed the loop and register allocation. Keeping
`choices[i]` in the accumulation and string selection recovered the complete
body, including its extent reloads. The entries contain an owning AsciiString
and a float; accumulation truncates to an integer after each addition.
See `Rva0025C7C0ElvenWoodChoice.cpp` under Object/SpecialPower.

At `0x0025ED50` (355 B), the filter objects die at the end of the iterator's
initialization expression, **before** the enumeration loop. Named locals that
survive the loop change both lifetime and emitted cleanup. Genuine temporary
virtual filters, STLport's `_STLP_NO_EXCEPTIONS` configuration, and copying the
ObjectID to a local before `list::push_back` recovered the body. Passing a
reference to the Object's field instead changed the allocation/load schedule.
See `Rva0025ED50ChargeTargets.cpp`; it uses actual three-slot BFME filter
views and verified vtables, not hand-written vptr stores or dummy predicates.

## Read the member again instead of caching it in a local

Retail sometimes computes a sub-object address before it loads through that
address. The 156-byte body at `0x00615FE0` reads a pointer member at +4 as
`mov eax, [edi+8]`, `add eax, 4`, `mov eax, [eax]`. The obvious C++ spelling
compiles to the shorter `mov eax, [ecx+4]` and shifts the rest of the body by
two bytes. Five other spellings of the plain member load fold the same way:

- a cast through `char *`
- a cast through `unsigned int`
- an array member that decays to a pointer
- a second base class placed at offset 4
- a pointer local holding `&obj->member`

Caching the member in a local inside an inline accessor folds too. What splits
the address off is reading the member several times through one accessor and
letting VC7.1 common up the loads. This spelling reaches all 156 bytes:

```cpp
Overridable *getFinal() const
{
    if (m_override != 0 && m_override->m_nextOverride != 0)
        return (Overridable *)m_override->m_nextOverride->getFinalOverride();
    return m_override;
}
```

The matched `LivingWorldRegionManager::rva003C8A50` at `0x003C8A50` shows the
same shape from another angle. It passes `candidate->m_name` by const
reference into an inline `compare` that reads `that.m_data` twice.

## Write a bounds test as one conjunction, not four early returns

VC7.1 compiles `if (a < b) return fail;` to `test ah, 1` plus `jne`, and
`if (a > b) return fail;` to `test ah, 41h` plus `je`. Retail's 202-byte Apt
point-in-bounds test at `0x008C6730` uses `test ah, 1` with `jne` and
`test ah, 41h` with `jp` instead. The `jp` form also branches on an unordered
compare, which is the jump-if-false of `a <= b`, not the jump-if-true of
`a > b`. Writing the four tests as one conjunction produces exactly that:

```cpp
if (x >= bounds.left && x <= bounds.right
    && y >= bounds.top && y <= bounds.bottom)
    return AptInteger::Create(1);
return fallback;
```

The same edit also fixed which callee-saved register held the argument count
and moved the success block ahead of the failure block, so a residue that
looked like three separate problems was one.

## A frame four bytes too big: put the local in its own block

When every stack displacement in the body is exactly four higher than retail's
and nothing else differs, the frame carries one extra slot. The compiler will
say which one. Add `/FAsc /Fa<path>.cod` to the source's `// cl:` line, compile
once, and read the `_name$ = -NN` table at the top of the listing's function.
That table gives every local and every `$T` temporary its frame offset.

The 359-byte push button number draw at `0x00794B70` listed `_width$ = -48`
through `_size$ = -20`. It also gave `$T470` and `$T471` a slot of their own at
-32. Those two are the pointers MSVC keeps to each by-value `UnicodeString`
argument so the unwind funclet can destroy it. Retail allocated `0x20` of
locals where we allocated `0x24`. Declaring the two colours in their own block
moved `_textColor$` onto -32 beside the two temporaries, and the body went
exact:

```cpp
{
    Color textColor;
    Color dropColor;
    getButtonTextColors( window, instData, &textColor, &dropColor );
    ...
    text->draw( textX, textY, 1, 1 );
}
```

VC7.1 overlaps a compiler temporary with a user local only when the local's
scope says the two cannot both be live. A local declared at the top of the
function blocks the overlap even when nothing writes it until far below.
Moving the declaration down without a block does not help. `Color textColor;`
on the line above `getButtonTextColors` left the frame at `0x24`. So did
dropping `register`, reordering the six declarations, and deleting a dead
struct.

The listing catches the opposite mistake too. At `0x009C0A30` we merged the
`fild` temporary with a user integer on `[ebp-4]`. Retail kept the two apart on
-4 and -8, so every double below them sat eight bytes lower than ours.

## A run of locals on the wrong slots: retail had one more object

Read this when the frame is the right size, every local is the right size, and
a contiguous run of them still sits on each other's slots. The 1154-byte
`WorkerAIUpdate::findGoodBuildOrRepairPosition` at `0x002C8A20` spent four
sessions there. Ours listed `offset` at `esp+0x14`, `workingPosition` at
`0x20` and `theirPosition` at `0x2c`. Retail wants `workingPosition` at
`0x14`, `theirPosition` at `0x20` and `offset` at `0x2c`. The three slots
above them, `bestPosition` at `0x38`, `ourPosition` at `0x44` and the options
record at `0x50`, already agreed, and so did `sub esp,0x64`. All 58 remaining
bytes were displacement bytes.

Seven declaration orders failed, and the reason is that declaration order does
not decide this. Swapping two declarations reordered the code and left every
slot where it was. What decides it is how many objects the function holds. Add
`/FAsc /Fa<path>.cod` to the `// cl:` line and read the `_name$ = -NN` table,
then compare it against the slots the retail diff asks for. Count the objects
retail needs. Retail wrote the scaled vector to `0x44`, the slot its own
`ourPosition` occupied, and `ourPosition` is dead by then. That is a seventh
object packed onto a dead sixth, and our source only had six.

The source change that supplies the seventh object is one line. Ours scaled
the vector in place:

```cpp
offset *= targetRadius;
offset *= 0.5f;
```

Retail builds a new value instead, which MSVC materializes as a `$T`
temporary:

```cpp
offset = offset * targetRadius * 0.5f;
```

The listing then reads `$T666 = -68` beside `_offset$ = -68` and
`_halfOffset$ = -44` beside `_ourPosition$ = -44`, the whole run moves onto
retail's slots, and the body goes from 58 differing bytes to 24. The same one
line then closed the other 24 without another edit. It fixed the order of the
three squares in the inlined `Length2`, where ours summed `Z*Z` first because
`Z` sat in `st(0)`, and it fixed `fld offset.X; fadd workingPosition.x`, which
ours emitted the other way round because MSVC reads `a += b` and `a = b + a`
as the same thing and loads the destination. Neither of those is reachable by
respelling the statement that shows the residue.

So when a run of slots is rotated rather than swapped, do not respell the
declarations. Count the objects, find the in-place update that should have
produced a value, and write it as an expression.

## The two-register lea operand order is not a spelling

Four bodies sit at exactly one non-relocation byte, and in all four that byte
is the SIB of a `lea` that adds two registers. Retail writes `lea edi,
[eax+ecx]` at `0x0078D410+0x88`, `lea edi, [ecx+eax-6]` at `0x007901F0+0x9b`,
`lea edx, [ebx+ecx]` at `0x005A0450+0xde` and `lea edx, [edi+eax]` at
`0x0045C2F0+0x62`. Our build picks the same two registers every time and swaps
which one is the base.

Nothing in the C++ reaches it. On `0x005A0450` the addends were swapped, a
`__forceinline` helper was added and removed, the helper was moved onto the
sibling assignment, and the two assignments were reordered. On `0x0078D410`
twelve forms were tried, including an unsigned round trip, an assign-then-add
pair, a dead pre-store, an inline helper, and hoisting the locals to function
scope. Each one left the identical byte. `/G5`, `/G6` and `/GB` reproduce it
and `/G7` rewrites 116 bytes.

MSVC commutes the addition before it picks the base, so the source order of
the two operands never survives to the encoder. Within one body retail stays
consistent and our build does not. `0x005A0450` and `0x0078D410` each contain
two leas of the same shape, and in both we match the second and miss the first.
Bank the body and take another one. Do not spend a session on this byte.
