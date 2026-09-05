# A non-inlined callee can change its caller

Run `python3 tools/callee_visibility.py`. This is a compiler experiment, not a
retail conversion. On the repository's MSVC 13.10.3077 toolchain, with the normal
`/O2 /GR- /EHsc-` defaults, it produces:

| Definition of `write(int *)` visible to the compiler | Caller size |
|---|---:|
| Declaration only | 28 B |
| Writes the pointed-to integer; does not retain its address | 23 B |
| Writes the integer and saves its address in a global | 28 B |

The caller is identical in all three cases:

```cpp
int consume() {
    int x;
    write(&x);
    int saved = x;
    tick();
    return saved;
}
```

`write` is explicitly `__declspec(noinline)`. Both calls remain REL32
relocations in all three objects. With the non-retaining body visible, the
caller reads its stack slot after `tick()`. With only the declaration, it saves
the value in ESI before `tick()` and preserves ESI in the prologue/epilogue.
The escaping-body control restores exactly the declaration-only caller bytes.
This isolates knowledge of pointer retention, rather than inlining or a
different caller spelling. The script saves source, compiler hashes, command,
raw instructions, bytes and relocations under `build/callee_visibility/`.

## Evidence in a real reconstruction

The banked SegLine renderer at `0x00960A30` contains its real subdivision
companion body. Controlled removals from that bank gave:

| Change | Render size |
|---|---:|
| Full bank | 14,081 B |
| Remove only `subdivision_util` definition | 14,113 B |
| Retain that definition as an uncalled, renamed member | 14,113 B |
| Explicitly mark the called subdivision method `noinline` | 14,081 B |
| Remove only `Scale` | 14,081 B, identical masked bytes |
| Remove only `getVertexBuffer` | 14,034 B |

The subdivision call remains out of line. Removing its definition changes stack
allocation and introduces a copy of the subdivision count after the call.
The unused-member control used the same two member declarations in both files;
only which member had a definition changed. This supports the same pointer
retention explanation as the small control. `getVertexBuffer` has a separate
inlining effect and must not be conflated with it.

The 14,081 B bank is **not exact**: it still has 1,254 non-relocation byte
differences against retail. The first application elsewhere, adding
`AIGroup::getCenter` to the `recompute` bank at `0x00154B80`, left its nine-byte
scheduling mismatch unchanged. That remained true after recovering the actual
222 B centroid body, including BFME's extra `Object::isMobile()` predicate.
The centroid landed independently in `AIGroupCenter.cpp`: replacing raw list
nodes with the real STLport list/iterator corrected its EBX/EBP assignment.
That conversion demonstrates a separate type-context effect, not a successful
application of the non-retention lever to `recompute`.

## When to investigate it

If a reconstruction passes a local's address to a named, non-virtual helper,
copies the result, then calls other functions, check whether the original
helper belonged to the same translation unit. A standalone declaration loses
information even if it preserves the signature and the eventual call.

Use a verified real companion body and compare both configurations. Do not
invent a non-retaining stub to force a match: retaining a pointer is behavior,
and the fabricated body would also be emitted into the object. `const` alone
does not establish that the address is not retained. MSVC 7.1 rejects the newer
`__declspec(noalias)` attribute, so that is not an available substitute.

This is a demonstrated source-context effect. Its contribution to conversion
throughput remains unmeasured; it is not evidence for a project-wide speedup.
