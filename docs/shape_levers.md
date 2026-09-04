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
| Split epilogue with `xor eax,eax` vs a folded one | `return new X;` splits; `new X;` as a statement folds. |
| A trivially-copyable class arg gets built as a local + pushed copy | Give the class a declared copy ctor/dtor (non-trivial) so it is constructed in place. |
| "Owning class unidentified" | `python3 tools/vtable_lookup.py <vtable VA>` -- retail slot table, ledger names per slot, and the ctors/dtors that install it. |
| Callee "unpinned" in an old stash | Look it up again -- `reverse/zh_sweep/requeue_resolved_callees.csv` lists 72 bodies whose blockers have since been pinned. |

Also check that the attempts log entry is not stale: `grep ,0xRVA, reverse/functions.csv`
-- if the row already points at a `.cpp`, someone landed it.

## Large-body results from the Astra campaign (2026-09-04)

These are targeted hypotheses, not flags to apply to every translation unit.
Each landed through the ordinary relocation-aware byte and identity gates.

| Observed mismatch | Proven cause and bounded experiment |
|---|---|
| Two identical branch tails merge into one; body is seven bytes short | In `luaV_execute` (0x00997C80, 2924 B), an MSVC `_WriteBarrier` intrinsic inside one conditional-pop arm preserves both tails while emitting no instruction or relocation. `_ReadWriteBarrier` also worked; `_ReadBarrier` added five bytes. Document this as reconstruction shaping, not original source. The same experiment did not solve Weapon or road-junction register drift. |
| A large constructor lacks 16 frame bytes and several EH states | In the ParticleBuffer copy constructor (0x00989A20, 4714 B), four texture getters return owning one-pointer handles through hidden result slots. Legacy raw-pointer declarations hid their lifetimes. TU-local ABI shims, normal destructors, and the retail `else if` LOD clamp recovered the whole body. Check getter retain, setter handle-address consumption, cleanup release, and a matched caller before assigning identity. |
| Constant-2 register reuse spreads through a body with local statics | `ParticleBufferClass::Render_Line` (0x0098AD00, 1763 B) needed `/EHsc` instead of the build default `/EHsc-`. The default emitted extra EH states 0/2/4 around `atexit` registrations; that state 2 induced unrelated-looking EBX reuse. Retail omits those states. Correcting the exception model recovered the whole body without forced registers or barriers. |

## Fleet tools (all read-only except add_match/re_log)

| Need | Tool |
|---|---|
| Send a worker fresh, non-stale work with per-body context | `python3 tools/brief.py --dump <gen_asm file> \| --rvas ... \| --csv <worklist>` |
| Find banked bodies already landed, or whose blockers got resolved | `python3 tools/stale_partials.py [--stale] [--requeue out.csv]` |
| Find which one pin/model unlocks the most dump bodies | `python3 tools/dump_families.py [--show N]` |
| Whose function is this (vtable in the prologue) | `python3 tools/vtable_lookup.py <vtable VA>` |
| Compile, retail-diff, name the wall | `python3 tools/probe.py <cpp> "<symbol>" 0x<RVA>` |
