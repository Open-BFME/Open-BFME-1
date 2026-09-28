# 0x0090C080 is a virtual of the animation prototype at 0x0090BD60, not `W3DAnimationLoader`

The 2026-08-11 naked lift `game/Libraries/Source/WWVegas/WW3D2/Load_Animation_W3D.cpp`
carried the name `?Load_Animation@W3DAnimationLoader@@QAEXXZ`. Two independent
facts contradict it.

## The class is the one whose constructor is at 0x0090BD60

`tools/vtable_lookup.py 0x0113A510`:

```
=== vtable 0x0113a510 ===
  slot 0 +0x000 -> 0x00d0bcc0 <unclaimed>
  slot 1 +0x004 -> 0x00d0bb60 <unclaimed>
  slot 2 +0x008 -> 0x00d0c080 ?Load_Animation@W3DAnimationLoader@@QAEXXZ
  ...
  -- .text functions carrying the constant --
  0x0090bc40   103B ??1Rva0090BC40Dtor@@UAE@XZ
  0x0090bd60   148B ??0Rva0090BD60Proto@@QAE@PBDHH@Z
```

0x0090BD60 is `Rva0090BD60Proto::Rva0090BD60Proto(const char *, int, int)`, a
*matched* row (`AnimationPrototype_ctor.cpp`), and it installs 0x0113A510 at
`[esi]` (`mov dword ptr [esi], 0x113a510` at +0x2a).  The vtable therefore has
exactly one owning constructor, and 0x0090C080 is that class's slot +0x08.

The field layout agrees, and is the same prototype ABI as the two already
recovered siblings of this loader family:

| offset | 0x0090BD60 ctor | 0x0090C080 body |
|---|---|---|
| +0x14 | `mov dword ptr [esi+0x14], 0` | `mov dword ptr [esi+0x14], eax` (the owned animation) |
| +0x18 | `lea edi,[esi+0x18]`, then `StringClass` ctor (`Get_String` 0x009DB890) | `mov eax,[esi+0x18]`, `strchr(..., '.')` |
| +0x1c | `mov dword ptr [esi+0x1c], ecx` | `mov ecx,[esi+0x1c]`, pushed to `Open_W3D_File` |
| +0x20 | `mov dword ptr [esi+0x20], edx` | `mov eax,[esi+0x20]`, pushed to `Open_W3D_File` |

`HierarchyPrototypeLoad.cpp` (0x00971990) and `Rva00970EC0Proto_Load.cpp`
(0x00970CD0) are the same prototype shape (owned object at +0x14, name at
+0x18, two W3D-opener arguments at +0x1c/+0x20) behind
`GenBase009EB7D0`; both are already matched under address-derived class names.

## It is virtual, so the calling convention in the old name is wrong too

A body reached through a vtable slot is a virtual member, so the decorated
name carries `@UAEXXZ`, not the lift's `@QAEXXZ`.  The old spelling asserted a
non-virtual public member of a class (`W3DAnimationLoader`) that appears
nowhere else in the tree: no ledger row, no pin, no source, and no caller names
it (the 2026-09-10 verdict recorded exactly that gap).

## What the body itself proves

Retail reads the name at +0x18, replaces its extension with the image's
".w3d" literal at VA 0x011139E4, opens that file through
`?Open_W3D_File@@YAPAXPAX0PBD@Z` and reads one chunk: 0x200 builds a
0x50-byte `HRawAnimClass`, 0x280 a 0x54-byte `HCompressedAnimClass`
(`??0HRawAnimClass@@QAE@XZ` at 0x009599B0, `??0HCompressedAnimClass@@QAE@XZ` at
0x0095B7D0, `?Load_W3D@...@QAEHAAVChunkLoadClass@@@Z` at 0x0095ACC0 and
0x0095C120).  `Register_Animation_Prototype` (0x0090C000) registers the
constructor's `(name, first, second)` triples, so the method is the prototype's
"load the animation named here" step.  "Load_Animation" describes that and is
kept; only the class and the virtual-ness are corrected, to the class the
vtable proves.

Landed as `?Load_Animation@Rva0090BD60Proto@@UAEXXZ` in
`game/Libraries/Source/WWVegas/WW3D2/Load_Animation_W3D.cpp` (the lift file,
now real C++; the naked function is gone).
