# Render2DSentenceClass::Draw_Sentence 0x0093EB50 (1983 B), s513 bank

Bank: `targets/game/reverse/attempts/0x0093eb50.cpp` (variant GC), compiled as
`game/Libraries/Source/WWVegas/WW3D2/Render2DSentenceDrawSentence.cpp` with `/DNDEBUG /MD /EHsc`
(the sibling Render2DClassAddQuad.cpp flags). Symbol: `?Draw_Sentence@Render2DSentenceClass@@QAEXHHHH@Z`
(the int spelling the caller W3DGameWindowDrawText.cpp uses; W3DDisplayStringDrawText006F5170.cpp
calls the `Render2DSentenceHHHH` IIII view).

probe: **shape 1.000** (identical once registers/constants are normalised), 1980 vs 1983 B, frame
`sub esp,0x98` equal. The residue is frame-slot allocation only. Supersedes the 0.43 bank
(luna-max, ZH-only skeleton).

## Source and evidence
- Donor: BFME 2 `Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceDrawBFME2.cpp`
  (open-bfme-2 b5a7b8290): ZH render2dsentence.cpp Draw_Sentence plus TargetWidth/Height scaling.
- BFME 1 retail facts: TargetWidth/Height +0xC4/+0xC8 vs defaults +0xBC/+0xC0; DrawExtents +0x9C;
  DynamicVectorClass members are 0x18 bytes at +0x04/+0x1C/+0x34; Location +0x58; ClipRect +0x8C;
  IsClippedEnabled +0xAC; floor is the MSVCR71 import (4 calls); Add_Quad out of line (ILT 0x4183A).

## Levers that moved bytes (each measured)
- 0.814 -> 0.844: ZH rect.h user copy ctor + operator= on RectClass.
- 0.844 -> 0.960: **inline ZH `operator+=(const RectClass&)` with MIN/MAX**. Retail calls ??YRectClass
  (0x0093C800) at the first DrawExtents union but inlines the second one: the inliner budget leaves the
  first site out of line. An out-of-line declaration loses the inline second site.
- 0.960 -> 0.991: read `data.ScreenRect` into four float locals (retail flds L,T,R,B once and never
  copies screen_rect first); `RectClass screen_rect;` uninitialised.
- 0.991 -> 0.995: restore the donor's `{ }` block around the screen/uv/clip/quad section.
- 0.995 -> 1.000: compute height before width (`Vector2 size; size.Y = b - t; size.X = r - l;`).

## Remaining (allocation only)
Retail: data pointer spill at [esp+0x10] (shared later with size.Y and the clip width temps);
screen_rect 0x14..0x20; Set_Coordinate_Range RectClass temp at 0x6C; size.X spilled to 0x88 (not
contiguous with size.Y, so retail's size is scalarised). Ours (GC): data at 0x20, screen_rect 0x10..,
size object at 0x6C/0x70, rect temp 0x74 (3 bytes larger from disp32 encodings).
Two scalar floats instead (variant GB: `float height = b - t; float width = r - l;`) are also shape
1.000 but shrink the frame to 0x90, so retail keeps 8 more bytes of locals than GB.
Tried without effect: declaration order of size/screen_rect/uv_rect/locals (C, D, E, F), inner block
for the float locals (GB2), an extra unused Vector2 (GB3), scalar width-first (GA).
SurfaceDescription is 12 bytes (Get_Description 0x008FC5C0 writes three dwords).
Next idea: find the 8-byte object retail has and GB lacks (frame-slot weight; see
docs/shape_levers.md frame sections), or vary the clip block's temporaries (`percent`, clipped rects).
