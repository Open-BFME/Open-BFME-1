# 0x00754E70 -> ?insertDefault@List00754E70@@QAE?AUIter00754E70@@U2@@Z

## Extent

`ret 8` at 0x00754EFD (RVA +0x7D) closes the body; the next 0x00754EFD-0x00754F40
range is INT3 padding. 128 bytes, thiscall, two 4-byte stack slots popped by
the callee.

## Caller evidence (strongest)

The independently byte-matched caller

    ?apply@Synchronize00755170@@QAEXPAPAPAUEntry00755170@@0@Z
    game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
      Rva00755170RenderSynchronization.cpp  (retail 0x00755170, 943 bytes)

reaches 0x00754E70 only through the ILT entry `E9 rel32` at 0x0002385D. The
ledger's pin

    targets/game/reverse/symbols.csv
    ?insertDefault@List00754E70@@QAE?AUIter00754E70@@U2@@Z, 0x00754E70

was written from that call site's declared callee, and the caller's own
`List00754E70::insertDefault(Iter00754E70)` declaration now resolves to this
address. That matched caller naming the symbol is the evidence the name is
real, not guessed.

## ABI agreement with the call site

`QAE?AUIter00754E70@U2@@Z` decodes to a `__thiscall` member returning
`Iter00754E70` and taking it by value. `Iter00754E70` is a one-word class with a
user-defined copy constructor, so MSVC 7.1 returns it through a hidden buffer
pointer. The retail body matches that exactly:

* `[esp+4]` (read at +0x6B into `eax`, then `mov [eax],esi` at +0x6F) is the
  hidden return buffer; the freshly linked node pointer is written through it.
* `[esp+8]` (read at +0x56 into `eax`, then `mov ecx,[eax+4]`) is the by-value
  `Iter00754E70` argument: its single `node` word is the position node, and the
  body rewrites the four links around it.
* `this` in `ecx` is never read, because `list::insert(iterator, const value&)`
  only needs the position node. `ecx` is therefore free for the placement-new
  destination, exactly as the body uses it (`lea ecx,[esi+8]` at +0x35).

## Body evidence

* 0x00754E86: `push 0x14` then the matched `__new_alloc::allocate`
  (0x0082E540) - a 20-byte STLport list node (8 link bytes + a 12-byte
  `_STL::vector<Object *>` payload).
* 0x00754E9C: `push esp+0x10` then ILT 0x000494AE, which is
  `E9` -> 0x00753C60, the independently matched vector copy constructor
  (`??0BfmeVecAY@@QAE@ABV0@@Z`, `Rva00753C60VectorCopy.cpp`), constructing the
  node's payload at `node+8` from a default-empty 12-byte temporary built by the
  three inline null stores at +0x1C/+0x20/+0x24.
* +0x5D/+0x5F/+0x62/+0x68: the four link stores
  `tmp->next=__n; tmp->prev=__p; __p->next=tmp; __n->prev=tmp`, which are
  verbatim `_STL::list::insert` (`inputs/vendor/stlport/stl/_list.h:295`).

## Source

`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
List00754E70InsertDefault.cpp`

`_STLP_NO_EXCEPTIONS` is required: with the `try`/`unwind` pair in
`_M_create_node` (`_list.h:236`) present, MSVC 7.1 outlines the node creation
and the body collapses to 92 bytes without the allocation or payload copy calls.
The same lever is used by the matched sibling `Rva000D07A0ListPushBack.cpp`.
