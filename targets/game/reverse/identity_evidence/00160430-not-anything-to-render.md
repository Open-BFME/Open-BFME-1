# 0x00160430 is not DX8FVFCategoryContainer::Anything_To_Render

Retail 0x00160430 (7 bytes) is `mov al, byte ptr [ecx+0xE5]; ret`. The row
named it `?Anything_To_Render@DX8FVFCategoryContainer@@IAE_NXZ` from a ZH
reference compile (`gen-alias`, object-symbol from
inputs/reference/.../WW3D2/dx8renderer.cpp), whose container layout puts
`AnythingToRender` at +0xE5.

BFME's layout is different. The matched constructor
`??0DX8FVFCategoryContainer@@QAE@I_N@Z` at 0x009469B0 (365 B, native
game/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp) writes:

- `mov dword ptr [esi+0xE4], 4`: +0xE4 is a dword, not a bool;
- `mov byte ptr [esi+0xEC], dl` (the `sorting` argument);
- `mov byte ptr [esi+0xED], bl` (`AnythingToRender = false`);
- `mov byte ptr [esi+0xEE], bl` (`AnyDelayedPassesToRender = false`).

The native TU's own inline `Anything_To_Render` compiles to
`mov al,[ecx+0xED]; ret`, and retail truth rejects that copy at 0x00160430.
A byte read at +0xE5 falls inside the +0xE4 dword, so the body cannot be this
class's accessor. `callers_of.py` finds no named caller of 0x00160430 or of its
ILT 0x000081D4.

The identity is unproven, so the row takes the address-derived opaque name
`?get@Rva00160430@@QBEEXZ` in game/GameEngine/Source/Common/TinyCarvedAccessorsBatch.cpp,
next to the other opaque byte getters.
