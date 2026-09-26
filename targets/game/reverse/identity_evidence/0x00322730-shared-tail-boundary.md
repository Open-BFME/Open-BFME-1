# 0x00322730 shared return tail: boundary repair pending

The current generated row claims `[0x00322730, 0x00322755)` (37 bytes), and a
separate C++ alias row claims `[0x00322755, 0x0032275D)` (8 bytes). Retail's
first body's `je` at +0x07 targets **0x00322755** when its sole stack argument
is zero. That target contains `mov eax, 1; ret 4`; it is a reachable return
tail, not padding after the 37-byte range. The other exits are `ret 4` at
+0x12, +0x1A and +0x22. The complete reachable range is 45 bytes.

```
00322730  mov eax, [esp+4]
00322734  sub eax, 0
00322737  je 00322755
00322739  dec eax
0032273A  je 0032274D
0032273C  dec eax
0032273D  je 00322745
0032273F  or eax, -1
00322742  ret 4
00322745  mov eax, 4
0032274A  ret 4
0032274D  mov eax, 2
00322752  ret 4
00322755  mov eax, 1
0032275A  ret 4
```

With the repository's MSVC 7.1 probe toolchain, this native C++ body is
**exactly 45/45 bytes with zero relocations** at 0x00322730:

```cpp
int __stdcall rva00322730(int value)
{
    switch (value)
    {
        case 0: return 1;
        case 1: return 2;
        case 2: return 4;
        default: return -1;
    }
}
```

The probe command was
`python3 tools/probe.py build/round-next-00322730.cpp '?rva00322730@@YGHH@Z' 0x00322730 --size 45`
using `// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`.
`tools/callees.py 0x00322730 37` reports no direct callees.
`tools/callers_of.py` reports no named direct caller of either 0x00322730
or 0x00322755. The current 8-byte row is `?dup_00322755` with an
`object-symbol=` alias from `W3DVolumetricShadow.cpp`; that alias alone does
not independently prove an entry at 0x00322755 or an owner for the 45-byte
body. Its byte coverage and dependent source must be accounted for before
retiring it.

No ledger row changes accompany this note. `add_match.py --boundary-evidence`
can expand a scaffold claim, but correctly rejects the overlapping matched
8-byte alias. A future repair needs an evidence-backed transaction that
resolves both rows and byte-verifies the affected sources. Keep the 45-byte
body address-derived until a caller or another independent witness names it.
