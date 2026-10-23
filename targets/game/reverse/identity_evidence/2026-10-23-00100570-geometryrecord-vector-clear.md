# 0x00100570 is the clear() of the vector whose erase is 0x000FF890

Retail 0x00100570 (13 bytes):

    mov eax, [ecx+4]     ; _M_finish
    mov edx, [ecx]       ; _M_start
    push eax
    push edx
    call 0x0001BD38      ; ILT -> 0x000FF890
    ret

ILT 0x0001BD38 jumps to 0x000FF890, the matched
`vector<GeometryRecord>::erase(iterator, iterator)` (GeometryRecordVector.cpp,
identity from the GeometryInfo constructor caller at 0x00100580). A thiscall
member that passes its own `[begin, end)` to that erase and returns is
STLport's `vector::clear()`; retail had no ICF, so the only clear calling this
erase is the GeometryRecord one. The body sits immediately before the
GeometryInfo constructor 0x00100580 that owns the vector.

The generated row named it after a placeholder element type
(`Gen_t_000ff890_p16cd`); the explicit `vector<GeometryRecord>`
instantiation in GeometryRecordVector.cpp already emits this clear and it
compiles to the same 13 bytes.

## Why the row stays opaque

`tools/ilt_oracle.py` contradicts the `GeometryRecord` spelling for this clear
(slot window 1548:1621-1631) and for the matched erase at 0x000FF890 as well
(21975:14615-14620), so the element type's real name is not `GeometryRecord`.
The row is `?dup_00100570@@YAXXZ` with `object-symbol=` the clear that
GeometryRecordVector.cpp emits: the bytes and the callee are proven, the type
name is not.
