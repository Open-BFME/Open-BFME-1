# AggregateDefClass::Save_W3D returns a byte bool, not WW3DErrorType (RVA 0x00980590)

The ledger carried `?Save_W3D@AggregateDefClass@@UAE?AW4WW3DErrorType@@AAVChunkSaveClass@@@Z`
at 0x00980590 with 83 bytes, from a 2026-08-11 `__declspec(naked)` `__emit` lift in
`game/Libraries/Source/WWVegas/WW3D2/agg_def.cpp`. The lift's name is Zero Hour's, and
Zero Hour's `AggregateDefClass` save family returns `WW3DErrorType`. The retail body at this
address cannot be that signature, so the decoration is retired for BFME's own.

## The body refutes the enum return

Retail 0x00980590..0x009805DF (80 bytes) is:

```
53                push ebx
56                push esi
57                push edi
8b 7c 24 10       mov  edi,[esp+0x10]        ; &chunk_save (the one stack argument)
8b f1             mov  esi,ecx                ; this
68 00060000       push 600h                  ; W3D_CHUNK_AGGREGATE
8b cf             mov  ecx,edi
32 db             xor  bl,bl                  ; byte-sized status, initialised to 0
e8 ...           call Begin_Chunk@ChunkSaveClass@@QAE_NK@Z   (0x009E16F0)
3c 01             cmp  al,1
75 2d             jne  +0x2d                  ; -> epilogue
8b 06             mov  eax,[esi]              ; load vftable
57                push edi
8b ce             mov  ecx,esi
ff 50 1c          call dword ptr [eax+0x1c]   ; Save_Header
3c 01             cmp  al,1
75 1a             jne  +0x1a
8b 16             mov  edx,[esi]
57                push edi
8b ce             mov  ecx,esi
ff 52 20          call dword ptr [edx+0x20]   ; Save_Info
3c 01             cmp  al,1
75 0e             jne  +0x0e
8b 06             mov  eax,[esi]
57                push edi
8b ce             mov  ecx,esi
ff 50 28          call dword ptr [eax+0x28]   ; Save_Class_Info
3c 01             cmp  al,1
75 02             jne  +2
8a d8             mov  bl,al
8b cf             mov  ecx,edi
e8 ...           call End_Chunk@ChunkSaveClass@@QAE_NXZ        (0x009E17F0)
5f                pop  edi
5e                pop  esi
8a c3             mov  al,bl                  ; one-byte return
5b                pop  ebx
c2 0400           ret  4
```

Every status test is `cmp al,1` and the result leaves in `al` after `xor bl,bl` /
`mov bl,al`, i.e. the callees return one byte and this one returns one byte. An
MSVC 7.1 `enum` (always 4-byte `int` in VC7) return is compared in `eax` and widened on
return, which is exactly the divergence logged for this address three times
(`re_attempts.log` rows for `?Save_W3D@AggregateDefClass@@UAE?AW4WW3DErrorType@@AAVChunkSaveClass@@@Z`:
"MSVC emitting movzx eax,bl instead of retail mov al,bl"). The three virtual sub-saves
themselves finish `mov al,bl; pop ebx; ret 4` as well -- 0x009805E0 (Save_Header) and the
anonymous 0x00980680 (Save_Class_Info) both do -- so the whole save family is byte-bool in
BFME and only the Zero Hour source says otherwise.

The family precedent is already in the ledger: `?Save_Info@AggregateDefClass@@MAE_NAAVChunkSaveClass@@@Z`
(0x00980B90, 110 bytes) carries the note "BFME returns bool not WW3DErrorType; Save_Subobject
too. Queue name was Zero Hour's". This correction makes Save_W3D consistent with the member
it dispatches to.

## The class, and the three targets, are not in doubt

* The body wraps `W3D_CHUNK_AGGREGATE` (0x600) around the three sub-chunks, which is what
  `w3d_file.h` names "description of an aggregate object", and its neighbours in retail are
  `?Read_Header@AggregateDefClass@@MAE_NAAVChunkLoadClass@@@Z` (0x009803F0) and
  `?Read_Subobject@AggregateDefClass@@MAE_NAAVChunkLoadClass@@@Z` (0x009804C0), both landed
  from the same file.
* The three indirect calls land on vftable slots +0x1c, +0x20 and +0x28, which are
  Save_Header, Save_Info and Save_Class_Info in this class's virtual order (Save_Subobject
  sits between Save_Info and Save_Class_Info at +0x24). The compiled C++ in
  `agg_def.cpp` reproduces exactly 0x1c/0x20/0x28, which is byte-level confirmation that
  the declaration order in `agg_def.h` is the retail one and not an invented layout.
* The rdata table at 0x0113F0D8 holds 0x00D80590 in its first dword next to the other
  AggregateDefClass members, confirming the address is dispatched as the class's save entry
  point.

Only the return-type decoration changes. The name becomes
`?Save_W3D@AggregateDefClass@@UAE_NAAVChunkSaveClass@@@Z`, which is what MSVC mangles for
`virtual bool AggregateDefClass::Save_W3D(ChunkSaveClass &)`; no member, parameter or class
name is invented.

## Extent

80 bytes, 0x00980590..0x009805DF. The `ret 4` ends at 0x009805DD and 0x009805E0 is the next
function's prologue (`sub esp,0x14; push ebx; push esi; mov esi,[esp+0x20]` -- Save_Header,
114 bytes, ending in a `ret 4` at 0x00980651 with 14 int3 bytes of padding to the 16-aligned
0x00980660). `targets/game/reverse/ghidra_functions.csv` records FUN_00d80590 as 80 bytes. The
lift's 83-byte claim ran three bytes into Save_Header, which is why its last three emitted
bytes were `83 ec 14`; that correction was made first, with its own byte-verified
`--replace-existing` transaction, before this identity correction.
