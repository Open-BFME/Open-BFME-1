# Identity evidence: 0x00835A20 `__write_decimal_backward<long>`

## Boundary

The body occupies `[0x00835A20, 0x00835A96)`, 118 bytes. The final `ret`
sits at `+0x75` (opcode byte `0x00835A95`), so the body ends at `0x00835A96`
and padding/`int3` follows. Two return paths converge on that single `ret`:
the negative path at `+0x55` (`dec esi; mov byte [esi],0x2d; mov eax,esi`)
and the showpos path at `+0x6a`, both falling into the shared epilogue.

## Call site

`tools/dis_retail.py 0x00835940 216` — the matched, clean-C++ row
`??$__write_integer_backward@J@_STL@@YAPADPADHJ@Z`
(`game/Libraries/Source/STLport/WriteIntegerBackward.cpp`) — reaches this body
at `+0x004f`:

```
+0042  lea    edx, [esp + 0xc]     ; address of a zero byte
+0046  push   edx                 ; arg4: const __true_type&
+0047  push   ebp                 ; arg3: __flags
+0048  push   eax                 ; arg2: __x      (long)
+0049  push   ecx                 ; arg1: __ptr    (char*)
+004a  mov    byte ptr [esp + 0x1c], 0
+004f  call   0x00835A20
```

Four stack arguments in that order match the vendor signature
`__write_decimal_backward(char *__ptr, _Integer __x,
ios_base::fmtflags __flags, const __true_type &)`
at `inputs/vendor/stlport/stl/_num_put.c:291-309`. The caller passes the
`__true_type` tag by reference to a zero byte, so the signed overload is the
one selected.

## Body shape

The callee reads its arguments at the offsets a `sub esp,8` + `push ebx` +
`push esi` prologue implies, and its arithmetic is the signed vendor helper:

- `mov eax,[esp+0x10]` / `test eax,eax` / `setl bl` — the sign of the 32-bit
  `__x` (arg2).
- `cdq` / `neg eax` / `adc edx,0` / `neg edx` — `__max_int_t __temp = __x`
  widened to 64 bits, then negated when negative.
- `push 0; push 0xa; push ecx; push eax; call __aulldvrm` — the `__temp /= 10`
  and `__temp % 10` of the division loop, using `__aulldvrm` (0x009F7C30).
- `add cl,0x30; mov [esi],cl` — the digit.
- `mov byte [esi],0x2d` for `-`, `test ah,8` (`showpos`, 0x0800) then
  `mov byte [esi],0x2b` for `+`.

The `showpos` constant 0x0800 is the same one the matched caller tests at
`+0x0013` (`test ch,8`), so the flag bits agree across the boundary.

## Frame layout agrees with the vendor source

`/FAsc` on the authentic vendor template reports the object table
`___ptr$=8, ___negative$=12, ___x$=12, ___flags$=16, ___formal$=20`: the sign
flag aliases the (dead) `__x` argument slot, exactly as retail's
`mov [esp+0x18],bl` does after the two pushes (`[esp+0x18]` = `[entry_esp+8]`).
Retail and our build therefore hold the same objects on the same slots; the
residue is register choice alone, not layout.

## Conclusion

The name `??$__write_decimal_backward@J@_STL@@YAPADPADJHABU__true_type@0@@Z`
is proven by the matched caller, the argument order, the callee's argument
offsets and the vendor body in `_num_put.c`. The 118-byte extent is proven by
the single trailing `ret` at `+0x75`.
