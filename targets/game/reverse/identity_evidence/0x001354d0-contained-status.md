# 0x001354D0 contained-status validation

The retail body begins at 0x001354D0, has a plain `ret` at +0xB8, and its
reachable throw arm ends with `_CxxThrowException` at +0xE7..+0xEB. The
236-byte generated claim ends immediately after that call. Retail has `int3`
from +0xEC through the padding before the next body at 0x00135600. VC7.1
emits one matching terminal `int3` at +0xEC, so `probe.py` reports a 237-byte
compiled symbol matching past the 236-byte extent. This is the same boundary
pattern as the already matched 162-byte `ParseEnableRegion` at 0x003B7BA0:
its C++ probe reports 163 bytes, its retail body ends at the throw call, and
its strict 162-byte source gate passes. We preserve the retail 236-byte
boundary and claim no padding byte.

The entry is an argument-free thiscall: ECX+8 supplies the first linked
`ThingTemplate`. The body calls its matched `resolveNames`, walks its
`m_behaviorModuleInfo` vector at +0x294 in 20-byte entries, examines the
entry's module-data pointer at +8 through virtual slot +0x18, and checks a
byte at module-data+0x156. The matched `parseObjectStatusOfContained` callback
sets that byte, and the error literal names a missing
`ObjectStatusOfContained` entry in `ContainModule`. The outer template's
name-string data at +0x20 supplies the `%s` argument. After the linked list,
the body calls the matched attribute-pool cleanup. No named direct caller or
vtable ownership proves a semantic method or class for the receiver at ECX,
so the exported owner and method retain the 001354D0 address. Virtual slot 6
is named structurally, not by guessed behavior.

The seven relocation positions in the exact C++ probe correspond to:

| Retail operand | Physical target and independent evidence |
| --- | --- |
| call +0x14 | ILT 0x000337A8 to matched `ThingTemplate::resolveNames` 0x001448F0 |
| call +0xAC | ILT 0x0003D375 to matched `bfmeDestroyAttributePoolEntries` 0x0039E720 |
| address +0xC3 | empty AsciiString fallback VA 0x0107388B, already pinned under several empty-string aliases |
| address +0xC9 | format literal VA 0x01090E08, listed in `targets/game/reverse/string_xrefs.tsv` for this body |
| call +0xD5 | matched variadic `INIException` constructor 0x00850600 |
| address +0xDD | INIException ThrowInfo VA 0x011DFC30, decoded in `Rva00094010Register.cpp` |
| call +0xE7 | pinned `_CxxThrowException` at 0x009F6D00 |

The final source probe has zero non-relocation differences through 236 bytes.
`add_match.py --replace-rva 0x001354D0` accepted the unchanged extent;
its strict scoped gate verified the source and both the format literal and
empty-string reference. No new symbol pin or semantic owner was needed.
