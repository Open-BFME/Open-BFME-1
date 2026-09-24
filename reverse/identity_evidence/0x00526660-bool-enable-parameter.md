# First parameter of the 0x00526660 route is a bool

Follows `0x00526660-false-drawable-route.md`, which replaced the refuted
Drawable names with the address-derived chain wrapper `0x00527200` ->
ILT `0x0001C8D2` -> body `0x00526660`, typing every link `(int, int)` because
the body had not been decoded.

## Retail evidence

The 523-byte body at `0x00526660` (ends `C2 08 00` at `+0x208`) reads its
first stack argument only as a byte: `mov cl, byte ptr [esp+0x24]` at `+0x74`
copies it into the dead second-argument home, and `mov al, byte ptr
[esp+0x24]` at `+0xC8` and `+0x1AB` feed it straight into `&&` chains whose
results are pushed to `GameWindow::winEnable(bool)`. No instruction reads the
upper three bytes. The second argument is compared as a full dword against
`-1` and `8` and used as a slot index. The body is now matched as
`?run@Rva00526660Body@@QAEX_NH@Z` in
`Code/GameEngine/Source/GameClient/GUI/Rva00526660SlotControls.cpp`: its
statements track Zero Hour's `EnableAcceptControls(Bool Enabled, ..., Int
slotNum)` in `GameNetwork/GUIUtil.cpp`, whose `Enabled` is `Bool` (`bool`).

The two forwarding links carry that type unchanged:

* ILT `0x0001C8D2` is one `E9` jump to `0x00526660`. A scratch
  `Rva0001C8D2Thunk::forward(bool, int)` calling `run(bool, int)` still
  compiles to that single 5-byte jump (probe: exact modulo the relocation).
* The 15-byte wrapper at `0x00527200` is `mov eax,[esp+4]; push -1; push eax;
  call 0x0001C8D2; ret 4`. `Rva00527200Owner::rva00527200(bool)` forwarding
  its argument as `forward(arg0, -1)` compiles to the same 15 bytes (probe:
  exact modulo the relocation); MSVC 7.1 forwards a bool argument with a
  dword load.

The other caller, the still-dumped `0x00528B60`, pushes EDI as the slot and
EBP, which it zeroed at `+0x20` (`xor ebp, ebp`), as the flag before calling
ILT `0x0001C8D2` at `+0xE6`: a constant `false`.

## Correction

Retype the chain rather than keep `(int, int)` names beside a matched
`(bool, int)` body: an `int` first parameter cannot produce the body's byte
reads without a cast, and leaving `?run@Rva00526660Body@@QAEXHH@Z` pinned to
`0x00526660` would give one address two signatures. Only the parameter type
changes. Class and method names keep their address tokens, because the
owning class and the BFME method name remain unproven. The old
`(int, int)` pin for the body is removed once nothing calls it.
