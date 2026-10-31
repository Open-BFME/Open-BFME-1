# 0x009EF900: deque<Rva009EF0D0Element*>::push_back (37 B)

## Boundary (BFME 1 retail)

- 0x009EF900 is 16-byte aligned and comes straight after an int3 pad run. Before this
  change no ledger row covered 0x009EF900..0x009EF91F.
- The body is `mov edx,[ecx+0x18]; mov eax,[ecx+0x10]; sub edx,4; cmp eax,edx;
  je +0x20; test eax,eax; je +0x19; mov edx,[esp+4]; mov edx,[edx]; mov [eax],edx;
  add dword [ecx+0x10],4; ret 4`. The `je` at +0x0B targets +0x20, which is
  `jmp 0x009EF0D0` followed by int3 padding.
- The jump at +0x20 is only reached from that branch inside the body. No call, ILT stub
  or table slot reaches 0x009EF920. It is the slow-path tail of the same function, not a
  separate thunk, so the true extent is 0x009EF900..0x009EF925 (37 bytes).
- The generated row `?j_009ef920@@YAXXZ` (game/gen_small/gthunks_086.cpp, notes
  `gen-thunk;gap`) claimed just that 5-byte tail, so it is fully contained in the
  corrected body.

## Identity

- The matched sibling 0x009EF930
  `?push_front@?$deque@PAVRva009EF0D0Element@@...` (AssetRegistryQueueKeys009EFBF0.cpp)
  has the same shape: a fast path through the start node cursor, `ret 4`, then an
  in-body tail `jmp` to the push_front aux at 0x009EF140. It is 31 bytes including
  that jump.
- That translation unit's AssetManagerImpl::AddRequiredAssets already calls
  `m_deques78[...].push_back(asset)` on the same `deque<Rva009EF0D0Element *>`. Its
  emitted push_back COMDAT reproduces all 37 bytes exactly, modulo the one relocation:
  the tail jump to `_M_push_back_aux_v`, retail 0x009EF0D0.
- Fields: +0x10 is `_M_finish._M_cur` and +0x18 is `_M_finish._M_last`, the STLport
  deque layout the push_front sibling uses at +0x00/+0x04 for `_M_start`.

The element class keeps its address-derived name from the existing TU.

## Landing blocked by tooling (2026-10-31)

`add_match.py --replace-rva 0x009EF920` refuses the new row because it starts at a
different address. A different start is accepted only through `--correct-identity` of a
real-source claim, and `?j_009ef920@@YAXXZ` is a generated `gen-thunk;gap` scaffold.
The same shape shows up 14 times in the ledger: a `gen-thunk;gap` row directly after
uncovered, non-int3 bytes, meaning the thunk is the tail jump of an unclaimed body. Those
rows are 0x0000FB28, 0x00036F16, 0x002C9456, 0x0050DCA6, 0x00519B96, 0x0055CCD6,
0x006D25D6, 0x00711ED6, 0x00713506, 0x00746176, 0x00746186, 0x009EF920, 0x00A5F7A0 and
0x00A619C0. Recovering them needs a sanctioned way to retire a generated thunk row that
lies inside a larger verified body.
