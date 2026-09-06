# Shape levers: the checklist for "everything matches except..."

Run `python3 tools/probe.py <file.cpp> "<symbol>" 0x<RVA>` first: it compiles, diffs against retail with relocations masked, and prints the symptom row below with its lever.

Read this before banking a near-miss. Each lever below turned a 0.9+ partial into
a byte-exact landing on 2026-09-02; the mechanism is in `docs/lessons.md`.

| Symptom in the byte diff | Lever |
|---|---|
| One ModRM/SIB byte: ours `[edi+edx]`, retail `[edx+edi]` | Add the pointer as an INTEGER on the right of the counter: `*(const char *)(i + (unsigned int)p)`. `p[i]`, `*(p+i)`, `i[p]` all give the other order. |
| `mov ecx,esp` before `mov [esp+N],esp` (EH saved-esp) at a by-value string arg | The string class must be `class AsciiString : private StringBase<char>` with INLINE forwarding copy ctor/dtor to the base; use `reference/shims/stringinline/StringInline.h`. Out-of-line ctor/dtor on the string class itself transposes it on every flag. |
| Whole body one callee-saved register apart (esi/edi, esi/edx) | Register assignment follows local DEFINITION ORDER. Define locals in the order retail first materializes each value (`const T *q = s2; const T *p = s1;`). |
| Loads retail hoists above a guard (`test ecx,ecx; mov esi,[a]; mov edx,[b]; jle`) | Copy the parameters into locals AFTER the preceding computation and BEFORE the `if`. Inside the guard they sink; at the top they change the prologue. |
| Import called twice: retail `mov edi,[__imp_X]; call edi ... call edi` | Call the real `__declspec(dllimport)` function directly. MSVC CSEs the IAT load into a callee-saved register allocated after existing locals; a pointer global or a cached local allocates first and mirrors ESI/EDI (and flips the vtable temp eax/edx nearby). |
| `flag = 1` reached by two forward jumps, placed after the main path | One fall-through tail: `if (a) { ... if (b) { ...; return; } } flag = 1;` -- never two inline `{ flag = 1; return; }`. |
| PMF constants `{pfn, -100, 0}` and a `[obj+0x68]` vbtable walk | `reference/shims/objectdlink/ObjectDlinkPmf.h`: Object's vbptr is inherited from a base at +0x68 (vbtable[0]==0), DLINK base at +4; pass the PMF as a value. |
| Two parameter loads swapped: retail `mov eax,[esp+8]` (arg2) before `mov edx,[esp+4]` (arg1), body otherwise exact | The allocator claims registers in the order values are first MATERIALIZED, and a field address counts before a field load. Take the address of a field of the later-used pointer into a local before the first expression: `const float *tp = &other->m_x;` then use `tp[0]`, `tp[1]`. It folds into the addressing mode, so only the load order changes. Landed 0x001E24F0 (78 B) on 2026-09-04 after 25 min of local-definition-order and reference-parameter variants had failed. |
| One displacement byte in `mov [esp+N],esp` (the EH saved-esp of a by-value temporary): retail N points at a LATER incoming-argument slot than ours | With no frame locals MSVC parks that saved-esp in a dead argument slot, choosing the first argument that is dead when the temporary is built. Reference the earlier argument in every expression that needs it (`(T *)b - 1` three times) instead of copying it to a local once: its slot stays live past the temporary and the allocator moves on to the next dead slot. Landed 0x002EADF0 (47 B) on 2026-09-04; class-size, typing and copy-order variants all left the byte alone. |
| Frame larger than ours by the size of a small struct (`sub esp,0xC` vs `sub esp,8`), spill slots otherwise identical, no extra stores | Retail kept an aggregate local whose stores were forwarded away but whose frame space stayed. Declare `float v[3]` (or the struct) and fill it from the calls, then build the return value from `v[0..2]`: the array gets the frame, the loads are forwarded, and the body is otherwise unchanged. A `volatile` or an address-taken scalar does NOT do it. Landed 0x005F9DE0 (65 B) on 2026-09-04. |
| A temporary's or RAII local's destructor call (string releaseBuffer, Release_Ref reload-and-branch) sits LATER in ours than in retail, e.g. after a `return expr;` copy-construct or at the end of the enclosing block | The destructor fires at the end of the object's OWN scope. Wrap the local in its own nested `{ }` block ending where retail's destructor call sits; the rest of the body is unchanged. Landed 0x0010D940 (326 B, 137-byte diff -> exact) and 0x0071B1F0 (384 B) on 2026-09-05. |
| Identical-looking return tails NOT merged (an extra `call` + epilogue per `return f(v).first;` site, body ~30 B long, one relocation more than retail), and a pointer loaded before an out-of-line comparator/functor call is RELOADED from memory after it | The callee is opaque: MSVC 7.1 assumes a declared-only function may write the object it gets a pointer into, so it reloads and cannot cross-jump the tails. Give the callee a VISIBLE body and `__declspec(noinline)` (`__declspec(noinline) bool operator()(const K &a, const K &b) const { return a.m_bits < b.m_bits; }`): the call stays out of line (still a REL32 to pin) but the compiler now knows it has no side effects. Landed the two 629 B SparseMatchFinder MatchMap hinted insert_unique bodies 0x001429C0 / 0x001426A0 on 2026-09-05 after key size, const-ness, ctor/dtor triviality, allocator and include-order experiments all left the body at 661 B. |
| An EH state store (`mov byte ptr [esp+N],K`) appears in ours around a call that retail makes with NO state change (typically a by-value string temporary passed to a lookup: retail goes ctor, call, dtor with no state bytes between) | Retail knew that callee cannot throw. Declare it `throw()` (`PreferenceNode *find(const AsciiString &) const throw();`): MSVC 7.1 then elides the unwind state for the temporary across that call. Landed the three 377 B getPreferredMap bodies 0x0009E470 / 0x00086A20 / 0x0009E830 on 2026-09-05 (together with the StringInline shape for the by-value temporary and the ZH `isValidMap(ret, TRUE)` tail). |
| Split epilogue with `xor eax,eax` vs a folded one | `return new X;` splits; `new X;` as a statement folds. |
| A trivially-copyable class arg gets built as a local + pushed copy | Give the class a declared copy ctor/dtor (non-trivial) so it is constructed in place. |
| "Owning class unidentified" | `python3 tools/vtable_lookup.py <vtable VA>` -- retail slot table, ledger names per slot, and the ctors/dtors that install it. |
| Callee "unpinned" in an old stash | Look it up again -- `reverse/zh_sweep/requeue_resolved_callees.csv` lists 72 bodies whose blockers have since been pinned. |
| Extra register saves or local copies around a non-inlined helper taking a local's address | Check the real helper's definition in the original TU. MSVC 7.1 uses knowledge that the helper does not retain the pointer even with `__declspec(noinline)`. `python3 tools/callee_visibility.py` reproduces this; [controls and limits](callee_visibility.md). Do not invent a non-retaining stub. |

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
