# ILT thunks 0x0001DB6F and 0x000026AD are not PrimitiveAnimationChannelClass::operator=

Both 5-byte rows were named as assignment operators, and TU-local "assign shim"
pins made them resolve. Following the jumps in retail:

| Thunk | Chain | Final body |
|---|---|---|
| `??4?$PrimitiveAnimationChannelClass@M@@...` at 0x0001DB6F | 0x0001DB6F -> 0x000A4B60 -> 0x00009895 -> 0x000A3C70 | a generated `_Rb_tree<int, ...>` destructor (tgrid_101.cpp) |
| `??4?$PrimitiveAnimationChannelClass@VVector3@@@@...` at 0x000026AD | 0x000026AD -> 0x00439140 -> 0x00887940 | `releaseBuffer`, the AsciiString destructor body |

Retail's callers of these thunks are almost all unwind funclets: dozens of
`mov ecx,[ebp-X]; add ecx,imm32; jmp thunk` stubs (for example 0x00BF6DF0... and
0x00C2253A...). Unwind funclets call destructors, not assignment operators.

The only "callers" named as channel setters were the five Ring/Sphere
Set_*_Channel rows. Those were 11-byte slices of the same funclets and have
been retracted (commit "Retract five channel setters that were slices of
unwind funclets").

The rows keep their bytes as address-claimed ILT thunks, `?j_0001db6f@@YAXXZ`
and `?j_000026ad@@YAXXZ`, jumping to the existing thunk rows
`?j_000a4b60@@YAXXZ` and `?j_00439140@@YAXXZ`. The two assign-shim pins that
existed only to force the old names are dropped.
