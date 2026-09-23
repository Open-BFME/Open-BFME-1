# W3DFileSystem constructor at 0x006F6330

The 14-byte body at `0x006F6330` takes its receiver in ECX, returns it in EAX,
writes vtable `0x011202B0` to `[this]`, and publishes the pointer at
`0x012D9128`. The vtable's slot 0 is ILT `0x0000B98D`, which resolves to the
already matched `W3DFileSystem` scalar deleting destructor at `0x006F6350`.
Slot 1 routes to the matched `W3DFileSystem::Get_File` at `0x006F6A30`.
Slot 2 routes to a 23-byte deletion helper at `0x006F62A0` whose code is
identical to the separately landed `W3DFileSystem::Return_File` at `0x00470A80`;
its ledger name is an unrelated asset-manager alias, so slot 2 is not used as
identity evidence. Slots 0 and 1 independently identify the constructed
class, rather than inferring it from equal bytes.

The aligned `W3DDisplay::init` call at `0x006ED5B0+0x46` allocates four bytes,
passes that pointer in ECX through ILT `0x00034F86` to `0x006F6330`, then uses
the returned pointer. The local source at
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp` expresses
this operation as `TheW3DFileSystem = NEW W3DFileSystem`. The corresponding
constructor in `W3DFileSystem.cpp` has been marked `present-unmatched`; probing
its decorated symbol `??0W3DFileSystem@@QAE@XZ` yields the complete 14 retail
bytes with aligned relocations.

The prior `?apply@Rva006F6330@@QAEPAV1@XZ` row came from a 14-byte local shim
that reproduced the vtable and global stores but had no independent evidence
for an `apply` method. That shim's identity is superseded by the class vtable,
caller, and existing constructor source. The address-derived class and method
should be retired together.
