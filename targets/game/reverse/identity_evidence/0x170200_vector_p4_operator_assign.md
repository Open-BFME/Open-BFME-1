# 0x00170200 — extent correction and identity retraction

## The extent

The lift `game/GameEngine/Source/Common/RTS/VectorScienceTypeAssignmentThunk.cpp`
carried `??4?$vector@W4ScienceType@@...QAEAAV01@ABV01@@Z` at 0x00170228/221. The
real body starts 40 bytes earlier and is 261 bytes long:

* `0x001701D0`'s landed row is 36 bytes, so it ends at 0x001701F4; `int3`
  padding runs 0x001701F4..0x001701FF and 0x00170200 is 16-aligned.
* 0x00170200 begins `push ebx; mov ebx,[esp+8]; push esi; mov esi,ecx; cmp ebx,esi;
  je` — a self-assign test followed by the `_M_start`/`_M_finish` loads. There is
  no `ret` or `jmp` anywhere in 0x00170200..0x00170228, so the 221-byte row was
  anchored inside a live body.
* The function's last instruction is `pop esi; pop ebx; ret 4` at
  0x00170300..0x00170304, and 0x00170305 onwards is `int3` padding. 261 bytes is
  therefore the whole body.
* `targets/game/reverse/ghidra_functions.csv` agrees independently:
  `0x170200,261,FUN_00570200`.

`tools/add_match.py --replace-rva` refuses a moved start ("a different boundary
needs an explicit evidence-backed retraction"), so the 0x00170228 row was
retracted with a tombstone in `deleted_rows.csv` and the corrected range claimed
as an ordinary new row.

## The identity

The body is STLport 4.5.3's `_STL::vector<T>::operator=(const vector<T>&)` for a
4-byte trivially copyable `T` (`sar`/`lea ... *4` throughout, no per-element
constructor or destructor calls). `game/gen_small/tgrid_102.cpp` already lands
the identical 261-byte body for an anonymous 4-byte POD payload at 0x000BC4B0.

`ScienceType` is **not** evidenced at this address:

* The ledger's own pin note puts the ScienceType spelling on the OTHER retail
  copy: `??4?$vector@W4ScienceType@@...,0x00018A70,PlayerTemplate science-vector
  assignment callee at the retail call site`, and 0x00018A70 is a five-byte `jmp`
  to 0x000BC4B0 — the p4pod instantiation above.
* The only ILT entry reaching 0x00170200 is the five-byte thunk 0x0000D8A5, and
  it has exactly three call sites, all inside matched real C++:
  * 0x0018B8F1 in `?apply@Rva0018B8B0Holder@@QAEXPAVRva0018B8B0Arg@@_N@Z`
    (`game/GameEngine/Source/GameLogic/AI/Rva0018B8B0Apply.cpp`), which types
    the assigned member `_STL::vector<ObjectID>`;
  * 0x00181F28 in `?setFrom@Rva00181EE0Owner@@QAEXPAVRva00181EE0Inner@@@Z`
    (`game/GameEngine/Source/GameLogic/AI/Rva00181EE0LazyCopy.cpp`);
  * 0x00171E4F in `?bfmeGoCDF@BfmeThingCDF@@QAEPAU1@PAU1@@Z`
    (`game/GameEngine/Source/Common/BfmeConv584.cpp`).

  None of them says ScienceType; two of them say a 4-byte object id.

The landed name is therefore address-derived and keeps the address token, per
`docs/naming_evidence.md`:

    ??4?$vector@URva00170200Elem@@V?$allocator@URva00170200Elem@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z

`Rva00170200Elem` is a one-dword payload, which is what the body itself proves.
If a caller or a ZH twin later proves the element type, the address may be
dropped for that name; nothing else about the claim changes.

## Side observation (not acted on)

`targets/game/reverse/symbols.csv` pins `?bfmeCopyOneCDF@BfmePartCDF@@QAEXPAU1@@Z`
at 0x0000D8A5 and `?bfmeCopyTwoCDF@BfmePartCDF@@QAEXPAU1@@Z` at 0x0003B5C5. Both
are five-byte ILT thunks into STLport template bodies (0x00170200 and 0x000CD0),
not hand-written `BfmePartCDF` methods, and the reconstructions that invented
those method names (`BfmeConv584.cpp`, `Rva00181EE0LazyCopy.cpp`,
`Rva0018B8B0Apply.cpp`) type the fields as raw dwords. Those pins are outside
this assignment's scope and were left untouched.

## Independent parent verification

Raw retail decoding confirms00170200..00170304. Call00170231 follows
ILT47C49 to0016FF30: thiscall ret12 with count/first/last; EAX returns
the newly allocated block. Calls001702A9/001702CD follow ILT26148 to
0016F680: FORWARD four-byte copy returning advanced destination in EAX.
Call001702EC follows ILT40868 to000CD160: forward construction with
null destination guard and EAX result. The latter calls pass three pointers
plus unused tag reference and pop16. Pins use real body addresses.
Worker backward-copy description and call offsets were corrected.
Independent probe:261bytes with six relocations exact.
