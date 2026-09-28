# 0x00483310 is `_STL::list<GameWindow *>::erase(iterator, iterator)`, the two-iterator overload

The row at this address arrived with the 2026-08-11 Open-BFME5
`game/Libraries/Source/WWVegas/WWLib/ListGameWindowEraseBodyThunk.cpp`
lift, and its ledger name is a decoration that stops mid-token:

```
?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_
```

The compiled symbol in that file was not even that: the lift defines
`__declspec(naked) void ListGameWindowEraseBodyThunk()`, so the row's
`object-symbol=?ListGameWindowEraseBodyThunk@@YAXXZ` note is what the
linker actually saw. The name has to be completed and re-homed.

## What proves the completion

**1. The ILT thunk at 0x00024131 carries the whole decoration.** It is a
bare `jmp 0x883310` and the image names it

```
?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVGameWindow@@U?$_Nonconst_traits@PAVGameWindow@@@_STL@@@2@U32@0@Z
```

That is the same address, spelled out, and it is not the lift's name at
all -- it is a decoration the retail link itself published.

**2. The single caller is a `matched` body that passes two iterators.**
`??4?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z`
(`list<GameWindow *>::operator=`) at 0x00483D00, `matched` from
`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp`, calls
it through that thunk at 0x00483D4B with `(begin(), pos1)` -- the
`erase(begin(), pos1)` of STLport's `operator=`. A one-iterator
`erase(iterator)` would take four bytes of arguments, not twelve.

**3. The body's own epilogue agrees.** `c2 0c 00` (`ret 0xc`) is
`this` plus two pointers, and the loop at +0x10 walks `first = first->_M_next`
until it reaches `last`, decrementing `_M_node->_M_size` at +0x08 and
finishing with `_M_node->_M_right = last`. That is the
`while (__first != __last) erase(__first++); return __last;` of the
two-iterator overload with the one-iterator erase inlined into it -- the
`ret 0x4` one-iterator body is separately present and separately named
(`?erase@...U32@@Z` in the same object, and the 5-byte ILT thunk at
0x00024131's sibling at 0x00483B60-adjacent `insert`).

**4. The deallocation is the node allocator, so the element is 4 bytes.**
The body pushes `0xc` and calls 0x0082E5F0, which the ledger already holds
as `?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z` from
`game/Libraries/Source/WWVegas/WWLib/node_alloc_M_deallocateThunk.cpp`.
A 12-byte STLport list node is 8 bytes of `_List_node_base` (prev, next)
plus the element, so the element is 4 bytes -- a `GameWindow *`, exactly
what the decoration says and not, say, an 8-byte `ICoord2D` (which would
push `0x10`).

`targets/game/reverse/lift_arity.csv:288` marks this row `undecided`;
nothing in the body contradicts the name, the name only needed completing.

## Where the body lives

`WindowLayoutInfo::windows` is `std::list<GameWindow *>` -- Zero Hour's
`GameEngine/Include/GameClient/GameWindowManager.h:69` -- and
`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp` is the
TU that instantiates it: the same object already publishes
`list<GameWindow *>::operator=` (0x00483D00) and
`list<GameWindow *>::insert` (0x00483B60) as `matched` rows from it. So
this conversion is that instantiation's own `erase(first, last)`, and the
naked `__emit` copy is deleted rather than carried.

## The compiler agrees, and one toolchain flag was the lever

Written as the stock STLport member -- no spelling of the body is
involved, the class template emits it -- this compiles to 56 bytes that
match retail's boundary exactly, with one relocation to
`?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z`.

The lever was the TU's flag line, not the body. Two defines were needed
that the file did not have:

* `/DBFME_STLP_NODE_ALLOC` + `/Iinputs/reference/shims/stlp_nodealloc`.
  Without the first, `PreRTS.h` defines `_STLP_USE_NEWALLOC` and
  `allocator<T>::deallocate` reaches `__new_alloc::deallocate` instead of
  the node allocator -- a different callee name, not just a different
  address.
* `/D_STLP_USE_STATIC_LIB`. With it absent, `config/vc_select_lib.h`
  leaves STLport in its import-declaration mode and the same
  `_M_deallocate` call is emitted as `call dword ptr [__imp_?deallocate@...]`,
  six bytes where retail has a five-byte `call rel32`; every other
  instruction in the body was already identical. `Team.cpp` and the other
  `stlp_nodealloc` users carry this flag for the same reason.

All 27 existing `matched` rows sourced from
`GameWindowManagerScript.cpp` still byte-verify after the flag change.

## Not landed yet: the decoration is already spent at the ILT thunk

`add_match` will not take this body, and the reason is ledger bookkeeping
rather than shape:

* `functions.csv:52431` already holds the FULL decoration above, at
  0x00024131 -- the 5-byte `jmp 0x883310` ILT stub, from
  `game/Libraries/Source/WWVegas/WWLib/ListGameWindowEraseThunk.cpp`. One
  name, one address: `--replace-existing` stops with "already in the
  ledger at 0x00024131".
* `functions.csv:52430` still holds 0x00483310 under the truncated
  decoration, so `--replace-rva 0x00483310 --correct-identity` stops with
  "target_rva 0x00483310 is already claimed by ... line 52430".

Neither tool call can retire both halves of one identity, so this needs two
ledger steps in that order:

1. Retire row 52430 (0x00483310, truncated name, the lift source) with a
   tombstone in `targets/game/reverse/deleted_rows.csv`.
2. `add_match.py '?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVGameWindow@@U?$_Nonconst_traits@PAVGameWindow@@@_STL@@@2@U32@0@Z'
   0x00483310 56 game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp
   --replace-existing --model <model>`, which repoints the 0x00024131 row
   onto the body and writes its own tombstone.
3. Delete `game/Libraries/Source/WWVegas/WWLib/ListGameWindowEraseBodyThunk.cpp`
   -- the naked `__emit` copy. Its 56 bytes are now real C++ at the same
   address. `ListGameWindowEraseThunk.cpp` (the 5-byte stub) is left alone
   unless its own lane re-homes it to `?j_00024131@@YAXXZ`.

`targets/game/reverse/re_attempts.log` carries the matching `blocked`
verdict with `blocker=identity`, so the next drawer reads the blocker
before it re-derives a shape.
