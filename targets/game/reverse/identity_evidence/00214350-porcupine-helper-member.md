# 0x00214350 is a PorcupineDamageHelper member, not a free __stdcall function

Retail 0x00214350 (67 bytes) computes a 2D distance between two coordinate
records and compares it with a float distance, then returns with `ret 0xC`.
The row named it `?withinDistance00214350@@YGEMPBUCoord2D00214350@@0@Z`, a
free `__stdcall` function over a TU-local `Coord2D00214350`.

The calling convention says otherwise:

- `callers_of.py 0x214350` finds exactly one caller, the matched
  `?apply@PorcupineDamageHelper@@QAEXPAVDamageInfo@@@Z` (0x002144D0).
- That body moves its own `this` into EDI at entry (`mov edi, ecx`) and,
  right before the call through ILT 0x0002593C, loads it back into ECX
  (`+0x63 mov ecx, edi`, `+0x68 call j_0002593c`). A `__stdcall` call has no
  reason to set ECX; a `__thiscall` member call on the helper does.
- The callee never reads ECX and pops its three stack arguments (`ret 0xC`),
  which is exactly a `__thiscall` member that ignores `this` (same bytes as a
  `__stdcall` free function, so the byte match never distinguished them).
- The caller's TU (PorcupineFormationBodyModuleApply.cpp) already declares it
  as `PorcupineDamageHelper::withinDistance00214350(Real, const Coord3D *,
  const Coord3D *)`, and symbols.csv pins
  `?withinDistance00214350@PorcupineDamageHelper@@QAEEMPBUCoord3D@@0@Z` at
  0x00214350. That spelling was unresolved in the link because no object
  defined it.

The method name stays address-derived (`withinDistance00214350`): only the
owner and convention are proven, not the original name. Coord3D is the
caller's three-float position record (the body reads only x and y).
