# GameLogic::xfer 0x00391C40 (2323 B) - wf session 2026-11-11 handoff

> `build/wf/00391c40/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x00391c40.cpp`.

Bank `targets/game/reverse/attempts/0x00391c40.cpp` reproduces as logged: 2323/2323 B,
79 relocs, 10 non-reloc diffs at +0x736..+0x740, shape 0.999 (probe.py, default
`-O2 -GR- -EHsc-` + bank cl line). Best candidate is unchanged: `build/wf/00391c40/base.cpp`.

## Residue (exact)

```
retail +0736 mov ebp,[ebx+8] | mov eax,[ebx+4] | mov ecx,[esp+0x30] | sub ebp,eax
ours   +0736 mov ecx,[ebx+4] | mov ebp,[ebx+8] | sub ebp,ecx        | mov ecx,[esp+0x30]
```
Inlined `_M_skip_to_next` of the control-bar map (ebx = iterator `_M_ht`, [esp+0x30] = CSE'd
`&cur->_M_val` spilled into the dead begin()-temp slot). Only the register of the bucket
`_M_start` temp differs (retail EAX, ours ECX); the order is a post-RA scheduling
consequence (ECX reuse by the key reload pins `sub` before the reload).

Observation (new): matched/retail sibling walks show the same inlined skip with start in a
non-ECX register whenever an IL-level key computation/reload sits between the loads and
the `sub` (WindowTableNameClearForEach 0x00462540: start=EBP, reload=EAX; Player::update
0x000D9B17 and ParticleSystemManager dtor 0x005CB3D7: start=EAX, `add esi,4` key). Ours,
retail loop 1 (+0x4e5) and a reduced mini TU always give start=ECX when the key is a
callee-saved register or a spill reloaded at its use. Hypothesis (unproven): in retail the
key is an IL-level memory load (memory-homed variable), not a spilled CSE temp.

## Tried this session (all 2323/10 unless noted)
- Flags: /Ob2, /G5, /G6, /GB, /Gy, /GF, /DWIN32 /D_WINDOWS (sibling GameLogic.cpp) all 10;
  /Ob1 2138B, /G7 2307B, /Oy- 2143B. Removing `_STLP_NO_EXCEPTIONS`, `_STLP_USE_NEWALLOC`,
  `_STLP_USE_MALLOC`, `_STLP_NO_NODE_ALLOC`: 10.
- Explicit `_M_skip_to_next` specialization for the button map: 228 generated bodies
  (bkt_num / bkt_num_key / _M_hash%size, key spellings, size()/bucket_count(), named
  locals, 4 loop forms; plus inline/__forceinline): 117 stay 10, the rest fall into the
  global 2326B/1536 or 2342B/1544 attractors (prologue reschedule at +0x1b). Direct
  `_M_start/_M_finish` access is protected; a struct view of the bucket vector -> 2326/2338.
- Explicit `operator++` specialization (const iterator): STLport form 10; early-return 10;
  `if(!n) n=skip(); cur=n` 17 (moves cur into ECX at +0x730); SGI 4.0 `__old` form 2342.
- Per-map hash functor (ZH rts::hash, str() local, const by-value, hash<const char*>):
  10; manual 5*h+c loop 2322/368.
- Loop-2 body: key pointer/reference locals, `(*it).first`, `const pair&` (2326),
  separate button local (2326), const-ref value source, if/else value (2346).
- Loop-2 iterator: nonconst iterator 2318/574; `!(it==end())`, `it++`, pre-declared,
  function-scope iterator: 10; cached end 2342.
- Per-iteration const_iterator copy of a nonconst iterator (shape lever 2996 #3) 2342/1465;
  `it.operator->()` entry pointer local 2326/1525.
- Map members as plain hash_map instead of wrapper; inline getName() accessor: 10.
- Declaration-order/scope toggles (id, version union, team/number, flag union, empty
  scopes, const owner): 10 or stack-slot-only changes (19..41 diffs).
- 250 random combinations of the above 10-preserving variants: all 10.

## Next
Reopen only with a source shape that makes the skip key an IL-level load (e.g. a
memory-homed iterator/key object evidenced by another BFME walk), or new donor evidence
for BFME's control-bar override loop. Do not repeat the families above.
Note: the bank is not landing-ready regardless (union member-pointer calls through ILT
`j_` thunks, opaque views); landing needs canonical headers per the gate rules.
