# Identity: 0x00908FE0 is `?End_Scene@DX8Wrapper@@SAX_N@Z`

The ledger still carries the scaffold name `?d_00908fe0@@YAXXZ` because the
body is not byte-exact yet (see the banked stash
`targets/game/reverse/attempts/0x00908fe0.cpp`, 175 non-relocation diffs). The
name itself is **proven**, not guessed, so whoever lands the bytes only has to
repoint the row.

## Evidence

1. **Matched caller naming the symbol.** The only call site is
   `0x008FD880`, `?End_Render@WW3D@@SA?AW4WW3DErrorType@@_N@Z`, which is
   `matched` against `game/Libraries/Source/WWVegas/WW3D2/WW3DEndRender.cpp`.
   That source reads:

   ```c
   static void End_Scene(bool flip_frame);
   ...
   WWPROFILE("DX8Wrapper::End_Scene");
   DX8Wrapper::End_Scene(flip_frame);
   ```

   and its retail bytes call `0x00908FE0` with one pushed argument
   (`push eax; ... call 0xd08fe0; add esp,4`), i.e. a static
   `void (bool)`. `tools/callers_of.py 0x00908FE0` reports that single site.

2. **The body is that function.** Retail's body is the D3D9 device
   `EndScene` (vtable +0xA8) followed by `Present` (vtable +0x44) with the
   `D3DERR_DEVICELOST` / `D3DERR_DEVICENOTRESET` retry, then the
   `Set_Vertex_Buffer(NULL)` / `Set_Index_Buffer(NULL,0)` /
   `Set_Texture(i,NULL)` / `Set_Material(NULL)` cleanup the Zero Hour
   `dx8wrapper.cpp` twin performs at the end of `End_Scene`.

3. **The loop bound is the D3D9 caps field.** `[CurrentCaps+0x278]` is read
   twice (+0x1BD, +0x20B); `MaxTexturesPerPass` sits at +0x278 in the D3D9
   `D3DCAPS9` the BFME build uses, while the game's D3D8 `dx8caps.h` accessor
   gives +0x124. Retail is the D3D9 binary, which is consistent with (2).

No vtable slot, export or string contradicts the name.
