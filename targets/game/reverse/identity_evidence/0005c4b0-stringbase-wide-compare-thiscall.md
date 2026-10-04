# 0x0005C4B0: the counted wide compare is a thiscall member

The row stays address-derived; only its signature changes, to the one every
retail caller proves. StringBase.cpp already calls it as
`Rva0005C4B0WideTraits::compare`; the old stdcall spelling
`?Rva0005C4B0CompareWide@@YGHPBG0H@Z` had no caller in the tree, so the object
defining the body and the object calling it named different symbols and
`link_check.py` reported StringBase.cpp's call unresolved.

`tools/callers_of.py 0x0005C4B0` lists the wide `startsWith`/`endsWith` bodies at
0x008870D0, 0x00887170, 0x00887320 and 0x00887380, all inside StringBase.obj's
block. Each loads ECX with the address of a stack temporary immediately before
the call through ILT 0x00020581 (0x008870D0+0x34: `8d 4c 24 14 e8 ..`). The
body (54 bytes) returns `ret 0Ch` and overwrites ECX before any read
(`8b 4c 24 08`): a thiscall member of an empty helper object whose `this` is
unused, not a stdcall free function. The row becomes
`int Rva0005C4B0WideTraits::compare(const WCHAR *, const WCHAR *, int)`; the
body's bytes are unchanged and the existing ILT pin for that name re-derives to
this body (`pin_consistency.py --symbol`: consistent).
