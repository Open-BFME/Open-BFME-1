# 0x008FD1C0 WW3D::Set_Device_Resolution returns BOOL, not WW3DErrorType

The lift in `game/Libraries/Source/WWVegas/WW3D2/ww3d.cpp` carried the name
`?Set_Device_Resolution@WW3D@@SA?AW4WW3DErrorType@@HHHH_N@Z` (return
`WW3DErrorType`), and the Zero Hour twin
(`inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp:611`)
agrees, so the enum return looked proven. Retail's bytes say otherwise.

## Retail body (39 B, unchanged extent)

```
8b 44 24 14  mov eax,[esp+0x14]     ; 5 args pushed, add esp,0x14 after
...
e8 e2 bc 00 00 call DX8Wrapper::Set_Device_Resolution   ; returns BOOL in AL
83 c4 14     add esp,0x14
84 c0        test al,al
0f 95 c0     setne al
c3           ret
```

`setne al` writes the WHOLE return value in AL, and nothing touches the upper
EAX. Any `WW3DErrorType` return from a call whose result is only in AL needs
`movzx eax,al` (MSVC 7.1) or a `neg`/`sbb`/`neg` sequence, all of which the
2026-09-25 session tried and measured at 37 B and 40 B against retail's 39 B.
Only a BOOL return of the callee result is 5 bytes, so the return type is
`bool`: `?Set_Device_Resolution@WW3D@@SA_NHHHH_N@Z`, which is also the shape
already pinned in `targets/game/reverse/symbols.csv` for this address.

## Caller evidence (independent of the disassembly)

`?setDisplayMode@W3DDisplay@@UAE_NIII_N@Z` at 0x006E7F00 is byte-matched from
`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayMode.cpp`, which
declares the callee `static bool Set_Device_Resolution(int,int,int,int,bool)`
and tests it with `== true`. Retail at 0x006E7F4C is `cmp al,1` / `jne`,
which is the codegen of an integer-typed result compared against 1 and matches
that source exactly. A `WW3DErrorType` return compared with `WW3D_ERROR_OK`
(= 0, `w3derr.h:52`) would have compiled to `test al,al`.

## Codegen note

A one-line `return DX8Wrapper::Set_Device_Resolution(...)` is folded by
MSVC 7.1 /O2 into a 5-byte `jmp` thunk (measured: 5 B). The two-statement form
the Zero Hour twin uses for the enum return,

```c++
bool success = DX8Wrapper::Set_Device_Resolution(width,height,bits,windowed,resize_window);
if (success) { return true; } else { return false; }
```

keeps the call inlined and byte-verifies at 39 B with `bool`. `return success;`
and `return (bool)...` fold to the thunk again; `return !!success;` is 40 B.

## Consequence

`ww3d.h:127` declares the return as `WW3DErrorType`, which is now `bool`, and
the present-unmatched duplicate of `setDisplayMode` in
`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp` compared the
result with `WW3D_ERROR_OK`; that comparison is corrected to test the value
(the byte-matched copy of the same body is `W3DDisplayMode.cpp`).
