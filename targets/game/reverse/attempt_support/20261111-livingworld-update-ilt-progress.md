# Living World update: six direct ILT bindings

Queue rank 36, census 90c15cdeca, RVA 0x006174D0 / 369 bytes.
Read prior attempt log and
`2026-11-04-livingworld-update-begin-relocation.md` before editing.
`callees.py 0x006174D0 369` independently reports the native call routes.

Replace six body-name calls with existing ILT symbols: resetAll -> 45142,
bfmeTickDQ -> 284A2, updateState -> 2ADE7, flag getter -> 36CFF,
ShowControlBar -> 24848, bfmeGo977C -> 423B6. Receiver-only calls use the
existing fastcall cast convention, with ECX receiver and no stack arguments;
the free getters retain cdecl and their existing result types.
Normal build verifies the entire 369-byte body, both strings and all 11
DIR32 references. No provider, signature pin or ledger identity changes.

The two stack-argument member calls were also tried with fastcall casts and
an explicit unused EDX argument. These added `xor edx,edx` and failed bytes;
both original calls were restored. The iterator begin relocation and those
two member routes remain prerequisites for strict provider truth. This is
partial linking repair, not a linked-byte gain or a new recovery.

BFME 2 76f0baefa6 was searched for the manager spelling and implementation;
no same-owner implementation was found. No donor layout, name or compiler
override imported. Existing BFME 1 MSVC 7.1 flags and headers retained.
Current linking remains unknown: the earlier current preview reports 653
missing/changed ledger objects. The source's census status is blocked.
