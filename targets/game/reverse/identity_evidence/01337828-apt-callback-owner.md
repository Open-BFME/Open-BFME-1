# Apt callback ownership at VA 0x01337828

This is an existing-owner reference correction, not a newly inferred EA name.
The spelling WideAllocPtr is a reference view of a shared allocator cell;
there is no distinct WideAllocPtr data owner to link. Keeping that extern
spelling leaves the object unresolved. No evidence establishes it as EA's
name for the cell. The matched singleton owner is Rva008C5D70Alloc, whose
address-derived name deliberately makes no such semantic identity claim.

## Independent retail and data evidence

- AptArray's 168-byte body at RVA 0x008B8D60 calls the allocator at
  0x008B8DA5: `FF 15 28 78 33 01`, indirect through VA 0x01337828.
- Its free call at 0x008B8DE7 is `FF 15 2C 78 33 01`, through the distinct
  adjacent callback cell at VA 0x0133782C.
- The matched installer at RVA 0x00789440 writes allocation target
  VA 0x00B831E0 to the first cell and free target VA 0x00B831F0 to the
  second. The native consumers establish cdecl byte-count/pointer ABIs.
- The data ledger has one four-byte owner per cell:
  `?Rva008C5D70Alloc@@3P6APAXI@ZA` in Rva008C4650HeaderedAlloc.cpp and
  `?g_bfmeFreeDWF@@3P6AXPAX@ZA` in BfmeConv791.cpp. Both original cells
  are zero-filled. These existing definitions and their bytes are unchanged.
- The independently byte-derived DIR32 registry places both old/new
  allocator spellings at 0x01337828 and both free spellings at 0x0133782C.
  The source change therefore selects the existing definition of each same
  proven cell, without introducing storage, pins or linker aliases.

## Verification

The complete AptArray TU verifies its one function and two DIR32 operands;
the existing owner TUs verify three data rows. Pin consistency passes.
A full census at 82dc61ee38 completed on 2026-10-04 with 22,151 objects
and zero missing. Same-root link_check before the edit reports unresolved
WideAllocPtr and WideFreePtr; after the one-file edit it reports LINKS,
0 -> 168 LINKED bytes, 1/1 clean, exit 0. This is a scoped census preview.
The source and both owner files are hash-identical to the publication base.
The hash-bound correction entry covers only this precise AptArray edit.
