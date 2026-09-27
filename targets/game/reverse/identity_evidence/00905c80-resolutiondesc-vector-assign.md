# 0x00905C80 is VectorClass<ResolutionDescClass>::operator=, not VectorClass<StringClass>::operator=

The 2026-08-11 `*Thunk.cpp` lift `game/Libraries/Source/WWVegas/WWLib/StringClassVectorAssignmentThunk.cpp`
carried the name `??4?$VectorClass@VStringClass@@@@QAEAAV0@ABV0@@Z` into
`targets/game/reverse/functions.csv` for the 217-byte body at 0x00905C80. The
element type in that name is refuted by the body itself, and the real element
type is proved below. The byte-identical replacement lives in
`game/Libraries/Source/WWVegas/WW3D2/ResolutionDescVectorAssign.cpp`, which
reproduces the retail WWLib `VectorClass<T>::operator=` as an explicit
specialization of the header member (Zero Hour's `vector.h` copy drops the three
`IsValid` stores retail makes, which is the whole 10-byte delta).

## 1. The element is 16 bytes, StringClass is a pointer

Retail at +0x005A...+0x0063:

```
+005a push 0xd036e0     ; element default ctor
+005f push edi          ; element count
+0060 push 0x10         ; sizeof(T)
+0062 push ebp          ; new block
+0063 call 0x40ae5c     ; -> 0x0005C600 array-ctor iterator
```

and the copy loop at +0x0084 walks `add eax, 0x10` / `add edx, eax` /
`add edi, eax`, copying four dwords per element. Both say `sizeof(T) == 0x10`.
`StringClass` holds one buffer pointer
(`game/Libraries/Source/WWVegas/WW3D2/RenderDeviceDescClass_assign_Thunk.cpp`
documents the upstream `wwstring.h` layout as `TCHAR *m_Buffer`; see also
`game/Libraries/Source/WWVegas/WWLib/VectorClass_ID_StringClass.cpp`), so a
`VectorClass<StringClass>` body would carry `shl ecx, 3` and a stride of 8.
There is no such body in the image for this element size, and the lift's name is
the only claim of one.

## 2. The shared ctor 0x009036E0 is `ResolutionDescClass::ResolutionDescClass()`

```
0x009036E0  8b c1 / 33 c9 / 89 08 / 89 48 04 / 89 48 08 / c3   (13 bytes)
```

Three zero stores, fourth dword left alone. `rddesc.h` (Zero Hour,
`Libraries/Source/WWVegas/WW3D2/rddesc.h:50-62`) declares

```cpp
class ResolutionDescClass {
public:
    ResolutionDescClass(void) : Width(0), Height(0), BitDepth(0) { }
    ...
    int Width; int Height; int BitDepth; int RefreshRate;
```

four `int` members (16 bytes, matching the `push 0x10`) with exactly the three
initialised members this body zeroes. The same ctor address is referenced by
the byte-proven `VectorClass<ResolutionDescClass>::Resize` at 0x00905DC0
(`ResolutionDescVectorResize.cpp`, 299 bytes matched), which passes the same
`0x10` and the same 0x009036E0.

## 3. A matched caller names the symbol

`??4RenderDeviceDescClass@@QAEAAV0@ABV0@@Z` at 0x009078A0 (188 bytes, matched,
clean C++, Zero Hour's `rddesc.h` body unchanged) ends with

```
+0093 lea  esi, [ebp + 0x5a0]   ; source ResArray
+0099 lea  edi, [ebx + 0x5a0]   ; destination ResArray
+009f push esi
+00a0 mov  ecx, edi
+00a2 call 0xd05c80              ; VectorClass<T>::operator=
+00a7 mov  eax, [esi + 0x10]     ; ActiveCount
+00b0 mov  ecx, [esi + 0x14]     ; GrowthStep
```

That is `ResArray = src.ResArray;` (`rddesc.h:93`) on
`DynamicVectorClass<ResolutionDescClass> ResArray` (`rddesc.h:146`): the inline
`DynamicVectorClass<T>::operator=` calls
`VectorClass<T>::operator=` and then copies ActiveCount and GrowthStep. A
matched caller naming the callee outranks the name the lift shipped with.

## 4. The instantiation group is ResolutionDescClass

The vtable at 0x0113A0E4 is `??_7?$DynamicVectorClass@UResolutionDescClass@@@@6B@`
(`targets/game/reverse/dir32_addresses.csv:661`) and its slots are the matched
siblings of this body:

| slot | address | body |
|---|---|---|
| 1 | 0x00905D60 | `??8?$VectorClass@VResolutionDescClass@@@@UBE_NABV0@@Z`, 89 B, dxwrapper.cpp |
| 2 | 0x00905DC0 | `VectorClass<ResolutionDescClass>::Resize`, 299 B, ResolutionDescVectorResize.cpp |
| 4 | 0x00905EF0 | `VectorClass<ResolutionDescClass>::ID(const T&)`, 70 B, dxwrapper.cpp |

0x00905C80 sits inside that same group (0x00905C60 `ID(T const*)`, 0x00905D60
`operator==`, 0x00905DC0 `Resize`, 0x00905EF0 `ID(const T&)`).

The second retail caller of 0x00905C80, the 33-byte
`??4?$DynamicVectorClass@VTangentsClass@HermiteSpline3DClass@@...` at 0x00907320
(hermitespline.cpp), calls the same address: a 16-byte `TangentsClass` and a
16-byte `ResolutionDescClass` produce the identical body, and the ledger already
carries nine `DynamicVectorClass<T>::operator=` names on that one 33-byte
address. One body gets one name; the ResolutionDesc identity is the one a
matched caller and the whole instantiation group support.

`symbols.csv:10004` already lists `??4?$VectorClass@VResolutionDescClass@@@@QAEAAV0@ABV0@@Z`
as a `pinharvest` candidate for 0x00905C80. That is a candidate, not proof; the
proof is above.
