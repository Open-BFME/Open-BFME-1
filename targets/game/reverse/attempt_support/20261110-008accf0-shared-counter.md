# 0x008ACCF0 bfmeLookup008ACCF0: EXACT (203 B)

Symbol: `?bfmeLookup008ACCF0@@YAHPAUBfmeLookupObject008ACCF0@@PAUBfmeLookupString008ACCF0@@E@Z`
Best source: `build/wf/008accf0/best.cpp` (cl: `/O2 /MD /DNDEBUG`, unchanged from the bank).
probe.py: `size ours=203 retail=203 relocs=2`, `result EXACT`.

## Fix

The banked 202/203 source (attempts/0x008accf0.cpp, score 0.9951) left one SIB byte at +0xB9:
retail `mov eax,[edx+ebx+8]` (base = secondValues), ours `[ebx+edx+8]`. Two source
changes together fix it:

1. Use the first loop's counter `i` again for the second scan (`i = 0; ... ++i; while (i < count)`),
   not a separate `int j`. The BFME 2 donor does the same thing. It reuses `edi` for both scans.
2. Delete the dead `int firstCount = view->m_firstCount;` local.

Each change has no effect without the other. With the dead local, reusing the counter still gives
1 diff at +0xB9 (`min_bank_i`). That explains why an earlier "reuse i for the second loop" trial
was recorded as inert. Removing the local alone also gives 1 diff (`g1_nofc`). With both changes,
all 16 combinations of the other choices are EXACT (port.py): flag as a parameter or a local,
the donor's explicit `off` counter or none, byte-offset or `int[]` indexing, and a `needle` local
or none. So the shared counter and the missing dead local are the only changes that matter.

How it was found: BFME 2 retail `game.dat` 0x006ED490 (231 B) disassembles to the same
pointer-first `[eax+edi+8]` tail. The donor
`Code/Libraries/Source/Apt/AptCharacter.cpp` (`rva006ED490`, rev 2bac16a6) compiled with
BFME 1's VC7.1 reproduces it, which shows our compiler can emit that operand order. I then
moved the donor step by step toward BFME 1's form (bis.py, bis2.py) and it went EXACT once the
`cur` copy was dropped and the counter stayed shared (`exact_donorform.cpp`).

## Ruled out this session (all still 1 diff at +0xB9 unless noted)
- Parameter and local reference aliases (`unsigned char &useSecond = include`, `*&needle = key`,
  `*&cur = object`, `**cur = &object`, `&useSecond = flag`). These flip only the LOOP SIB at
  +0x64, by parity of the alias count (2 diffs). The return SIB never moved.
- Random combinations of 2 to 4 neutral mutations (60 trials): placement of the loop, `i`, `j`,
  `view` and `next` declarations, `for(;;)`/`while(1)`, `next` as a reference, a member or
  free inline result/index accessor, a local index or results pointer, byte-offset inline helpers
  (`secondResult(j*16)`), and in-place `j *= 16` / `j <<= 4` before the return.
- Changing the type of the `m_secondValues` field (int, unsigned, void*, char*, unsigned char*)
  with matching casts, and grouping the count and values fields into a sub-struct or a
  `m_lists[2]` array.
- An offset local in the loop body (`offbody`, 200 B: pointer-first, but it reuses the iv and
  drops the shl). Recomputing the view expression (216 B).

Observation (measured, cause not established): in the return block VC7.1 puts a deep load chain
first, and puts a load before a plain register variable. It put SHL(j,4) first until the
counter was shared and the dead local was gone.

## Landing notes (read-only checks; nothing landed)
- (a) `ilt_oracle.py check` reports UNTESTABLE ("not a thunk target"). Retail reaches this body
  by a direct rel32 call from 0x008AE490+0x73, so no ILT pin is needed.
- (b) No out-of-line helper is emitted. `BfmeLookupString008ACCF0::matches` is inline-only and
  fully inlined. Nothing with its own ledger row is defined.
- (c) Both relocations are `call _strcmpi`, bound through `extern "C" int __cdecl _strcmpi`, which
  is the existing pin `__strcmpi,0x009F6FA0` (matched siblings use the same declaration). The body
  references no globals or vtables.
- (d) Home TU: `game/Libraries/Source/Apt/AptCharacter.cpp`. It holds the neighbour 0x008AD350, and
  it is also the BFME 2 donor's home. With the candidate appended to a scratch copy of that file
  (`home_aptcharacter.cpp`, /O2 /MD /DNDEBUG), both 0x008ACCF0 and 0x008AD350 probe EXACT.
- The caller `game/Libraries/Source/Apt/Rva008AE490AptDispatch.cpp` currently calls
  `d_008accf0` through a cast function-pointer union. Landing with `--replace-rva 0x008ACCF0`
  retires `?d_008accf0@@YAXXZ`, so that caller must declare
  `int bfmeLookup008ACCF0(BfmeLookupObject008ACCF0 *, BfmeLookupString008ACCF0 *, unsigned char);`
  and call it directly. The forward declarations already exist there. Re-verify that caller
  (0x008AE490) after the change.
- The bank's descriptive names are kept. The `register` keyword was dropped and the
  string text is now read through `m_header->m_text` (the same +8). Probe is still EXACT with
  both changes.
