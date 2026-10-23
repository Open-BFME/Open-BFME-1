# Link queue row 12: `??1RefHandle008958D0@@QAE@XZ` COMDAT divergence

Date: 2026-10-23. Census 2615147aca. Queue hint: "a COMDAT copy that is not
retail's body: fix or remove the wrong emitter" (Find.cpp, CreateHandle.cpp open).

## Facts (all verified this session by compiling the TUs and dumping COFF)

Four TUs define the handle dtor inline; all four emit it as a select-any COMDAT
and all four inline every use (zero external references in every object, so the
kept copy is dead weight either way):

| TU | COMDAT sha (code+relocs identical within group) |
|----|--------------------------------------------------|
| Rva00893030ManagerFind.cpp (sec 11, 32 B) | 6053e50c9d22237c |
| Rva00895A00CreateHandle.cpp (sec 25, 32 B) | 6053e50c9d22237c |
| Rva00895D30ManagerSubmit.cpp (sec 23, 32 B) | 6053e50c9d22237c |
| Rva00895B20Dependencies.cpp (sec 15, 34 B) | 28897ac9fc8172fb |

The 3-copy shape: `push esi; mov esi,[ecx]; test; dec [esi]; jne; mov ecx,esi;
call ~BfmeDropObjectA; push 0x18; push esi; call [TheBfmeFree]`.
The Dependencies shape: `mov eax,[ecx]; test; dec [eax]; jne; push esi;
mov esi,[ecx]; ...` (double-loads `m_object`, saves esi late).

## Retail evidence (lotrbfme.exe, raw file search)

- Good-shape fragment `ff 0e 75 13 8b ce e8` (dec [esi]; jne; mov ecx,esi;
  call): 5 hits, all in the Apt region (0x8955d5, 0x895616, 0x8959c7,
  0x8964d7, 0x896586).
- Wrong-shape fragment `ff 08 75 17` (dec [eax]; jne +0x17): 0 hits in the
  whole 16 MB binary.
- Neither full standalone pattern exists anywhere: retail ships no out-of-line
  copy of this dtor at all.

So the Dependencies.cpp copy is provably the divergent one.

## Why it cannot be fixed by respelling (tried, reverted)

Dependencies.cpp line 42 `if (m_object && decrement(m_object)==0)` respelled to
the cached-temp form makes its COMDAT byte-identical, but its own verified row
`?method@Rva00895B20@@QAE_NVRva00895B20Ref@@@Z` (0x00895B20, 294 B) FAILs 1/1:
retail's inlined destruction at +0x86-0xa5 is
`test eax,eax; je; dec [eax]; cmp [eax],0; jne; mov ecx,[esp+0x14]; ...`,
which requires the double-load spelling (no cached register temp). The respell
perturbs register allocation across the whole 294 B body. Removing the
definition instead would turn the inlined destruction into an out-of-line call
and break the same row. Working tree left clean (edit reverted).

## Update 2026-10-23 (retry): link order keeps the good copy

`link_census.link_order` sorts objects by lowest matched retail RVA, so
Find.obj (0x008958D0) links before CreateHandle (0x00895A00), Dependencies
(0x00895B20) and Submit (0x00895D30). link.exe therefore folds to a good copy
and the shipped game already carries retail-consistent bytes; the wrong copy
is discarded. The queue row's loser labels contradict this recomputation, so
the row is most likely census staleness or a subtlety invisible without a
full census rebuild (~35 min) — either way, zero game impact.

Also ruled out: `__forceinline` does NOT suppress the out-of-line COMDAT
(CreateHandle.cpp's dtor is `__forceinline` and still emits sec 25), so the
wrong emitter cannot be silenced by declaration spelling. There is a pin
`??1RefHandle008958D0@@QAE@XZ -> 0x000463AD` (ILT thunk), but retail holds no
standalone copy of either shape, so the dtor cannot be landed as its own row
to give the census a retail verdict.

## Suggested next step

Rebuild the link census and check which copy link.exe keeps. If a good copy is
first in link order, the linked game is already correct and this row is
hygiene-only (all four copies are unreferenced). Do not touch
Rva00895B20Dependencies.cpp line 42 without also re-deriving method's body.
