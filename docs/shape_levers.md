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
| Split epilogue with `xor eax,eax` vs a folded one | `return new X;` splits; `new X;` as a statement folds. |
| A trivially-copyable class arg gets built as a local + pushed copy | Give the class a declared copy ctor/dtor (non-trivial) so it is constructed in place. |
| "Owning class unidentified" | `python3 tools/vtable_lookup.py <vtable VA>` -- retail slot table, ledger names per slot, and the ctors/dtors that install it. |
| Callee "unpinned" in an old stash | Look it up again -- `reverse/zh_sweep/requeue_resolved_callees.csv` lists 72 bodies whose blockers have since been pinned. |

Also check that the attempts log entry is not stale: `grep ,0xRVA, reverse/functions.csv`
-- if the row already points at a `.cpp`, someone landed it.

## Fleet tools (all read-only except add_match/re_log)

| Need | Tool |
|---|---|
| Send a worker fresh, non-stale work with per-body context | `python3 tools/brief.py --dump <gen_asm file> \| --rvas ... \| --csv <worklist>` |
| Find banked bodies already landed, or whose blockers got resolved | `python3 tools/stale_partials.py [--stale] [--requeue out.csv]` |
| Find which one pin/model unlocks the most dump bodies | `python3 tools/dump_families.py [--show N]` |
| Whose function is this (vtable in the prologue) | `python3 tools/vtable_lookup.py <vtable VA>` |
| Compile, retail-diff, name the wall | `python3 tools/probe.py <cpp> "<symbol>" 0x<RVA>` |
