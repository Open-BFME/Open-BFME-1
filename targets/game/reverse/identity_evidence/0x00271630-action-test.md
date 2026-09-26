# 0x00271630 privateMoveToObject: the ActionManager callee is not canEnterObject

The banked body called its ActionManager test `canEnterObject(const Object *,
const Object *, CommandSourceType)`. Retail refutes that name for this call:

- The call at `0x00271630+0x19` is `e8` to ILT `0x00012B57`, which jumps to
  body `0x000C4080` (113 B). That body ends in `ret 0xC`: three stack
  arguments, receiver in ECX (`mov ecx,[TheActionManager]` at `+0x10`).
- `BFMEActionManager::canEnterObject` is already pinned
  (`targets/game/reverse/symbols.csv`) at ILT `0x0002D588`, body `0x000C5440`
  (849 B), with the five-argument ABI (`CanEnterType`, `Bool *`) that
  `privateEnter` (0x00271690) pushes.
- Retail is linked without identical-COMDAT folding, so the 113-byte body
  cannot be another name for the 849-byte one. It is a different member.

What `0x000C4080` does (from the retail bytes): returns false when either
object is null; calls `0x00435995` with argument 0 on each object and returns
false when the two results are equal; otherwise asks the non-null result's
`0x0040D3B9` view, through its vtable slot `+0x6C`, about the other object.
That is not enough to name it, so the landing keeps the address:
`BFMEActionManager::rva000C4080`.

`m_bfmePad34` in the bank and `m_unmodelled_34` in
`AIUpdateInterfacePrivateCommands.cpp` are both padding over the same
unmodelled `+0x34..+0x48` range of `AIUpdateInterface`; the body is placed in
the class home and uses that TU's existing member model.
