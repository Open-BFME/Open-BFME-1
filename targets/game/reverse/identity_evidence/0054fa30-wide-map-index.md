# map<UnicodeString, enum>::operator[] at 0x0054FA30

This 169-byte body was matched as
`map<AsciiString, Rva0054FA30Mapped>::operator[]`
(RvaMapIndexAsciiStringNothrow.cpp). It has been red in the full gate, because
its three string calls do not reach the narrow StringBase<char> bodies:

| Call site | Retail target | Ledger name |
|---|---|---|
| +0x34 | ILT 0x000226EC -> 0x0005FFA0 | `?compare@?$StringBase@G@@QBEHABV1@@Z` |
| +0x42 | 0x00888400 | `??0?$StringBase@G@@AAE@ABV0@@Z`, the wide copy constructor |
| +0x77 | 0x008881D0 | `?releaseBuffer@?$StringBase@G@@AAEXXZ`; `??1?$StringBase@G@@AAE@XZ` is pinned there |

The key is therefore a wide string. The tree calls agree with that:
- +0x23: ILT 0x0003FABC -> 0x0054EE40, the wide-string tree's `_M_lower_bound`
  (RvaTreeLowerBoundWideWalk.cpp).
- +0x62: ILT 0x00033D5C -> 0x0054F3F0, that tree's hinted `insert_unique`
  (RvaTreeInsertUniqueWide.cpp).

The earlier AsciiString-spelled pins at those two ILTs existed only to make the
narrow claim resolve. They are re-spelled for the new instantiation. A third
pin at 0x0003FABC had been mangled by shell `$` expansion
(`?_M_lower_bound@?@V?@G@@...`) and named nothing, so it was dropped.

Shape evidence for the spelling: with the same TU, retail's exact 169 bytes (two
return paths, esi/edi/ebx allocation) come out only when the key class derives
from StringBase<unsigned short> and the mapped type is a scalar. BFME's
UnicodeString derives from StringBase<wchar_t>. A bare StringBase key, or a
4-byte struct value, compiles to 172 bytes with 115 differing bytes.
