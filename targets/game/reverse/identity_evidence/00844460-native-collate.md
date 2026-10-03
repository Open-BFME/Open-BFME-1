# Wide collate transform at RVA 0x00844460

The 87-byte body is STLport 4.5.3 `_STL::collate<unsigned short>::do_transform`.
The vtable at VA 0x0112EAE8 has complete-object locator 0x011DE074 at its
preceding word. The locator points to type descriptor 0x012C7838, whose name
is `.?AV?$collate@G@_STL@@`. Its four slots are:

- 0: VA 0x00C326A0, the matched wide collate deleting destructor.
- 1: VA 0x00C44300, the matched wide `do_compare`.
- 2: VA 0x00C44460, this body.
- 3: VA 0x00C44200, the wide range hash.

`inputs/vendor/stlport/stl/_collate.h` declares these virtuals in that order.
This is independently named owner and per-family slot evidence, also used by
`stlport_collate_wide_compare.cpp`. The body zeros a three-pointer string in
the hidden result buffer, initializes the supplied character range, and
returns that buffer. RET 12 at RVA 0x008444B4 ends at 0x008444B7; INT3 follows.

## Native declarations and existing helper

Scratch native-header variants include `<string>` and `<locale>` instead of
copying the bank's replacement definitions of string, allocator, iterator tags,
or collate. The operation remains `return wstring(low, high)`. No production
source or ledger change survived this investigation.

A forced-inline scratch specialization of the native forward-range initialization
adapter can call the existing address-derived `Gen_006616A0::bfmeAssign` declaration.
There is no new helper pin or second semantic identity. Retail's direct call
is ILT 0x00042BB8 -> body 0x006616A0, independently decoded in all 106 bytes
and decompiled with Ghidra:

- ECX addresses three pointers at offsets 0, 4, and 8.
- First and last are two-byte-element pointers; the allocation is distance+1.
- It allocates, copies through the memmove import, and writes a 16-bit zero.
- Its third stack word is never read; RET 12 consumes all three arguments.

The existing matched `Bfme5WideStringRanges.cpp` reproduces that contract.
The adapter preserves pointer bit patterns when converting unsigned-short
ranges to its legacy short-pointer spelling. No element is read by the adapter.

## Compiler and binding results

The old bank probes exact modulo five relocations, but that is not a landing.
Fresh native-header results reveal why inspecting only bytes is insufficient:

| Variant | Size | Result |
|---|---:|---|
| Declaration-only native forward-range specialization | — | MSVC C1001 at `_string.h:376` |
| Native three-argument adapter, ordinary inline | 87 | One tag-offset byte differs; call remains to template wrapper |
| Same adapter plus bank's tag-address assembly | 87 | Masked exact; strict gate rejects unresolved template-wrapper call |
| Forced-inline native adapter, no assembly | 87 | Existing Gen_006616A0 call verified in COFF; one tag-offset byte differs |
| Forced-inline adapter plus named native allocator | 87 | Same one-byte residue |
| Forced-inline three-argument adapter with assembly | 82 | Wrong shape; two shifted relocations |
| Assembly in forced-inline two-argument range wrapper | 87 | Masked exact; COFF call moved outward to `_M_initialize_dispatch`, still not the retail callee |
| Force dispatch wrapper inline too | 43 | Constructor remains outlined; no parent EH frame |
| Also specialize and force native range constructor inline | 94 | Seven extra bytes; explicit stack stores for the assembly temporary |

The one-byte native C++ residue is +0x38: LEA ESP+0x20 rather than ESP+0x18.
These are the dead high-argument and hidden-result homes. The independently
decoded callee never reads that third argument. No helper pin was added to
pretend that one of the short generated wrappers is the 106-byte retail body.
The strict gate failure was reverted and the nonmatching production draft
removed. The existing preferred bank is unchanged; none of these experiments
was claimed as a conversion or an improved partial.

For reproducing the useful native C++ binding result, the scratch adapter is:

```cpp
#include <string>
class Gen_006616A0 {
public: void bfmeAssign(const short *, const short *, void *);
};
namespace _STL {
template<> template<>
__forceinline void basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >::_M_range_initialize<const wchar_t *>(
    const wchar_t *first, const wchar_t *last, const forward_iterator_tag &tag) {
    reinterpret_cast<Gen_006616A0 *>(this)->bfmeAssign(
        reinterpret_cast<const short *>(first),
        reinterpret_cast<const short *>(last),
        const_cast<forward_iterator_tag *>(&tag));
}
}
#include <locale>
namespace _STL {
wstring collate<wchar_t>::do_transform(const wchar_t *low, const wchar_t *high) const {
    return wstring(low, high);
}
}
```

Use the bank's `/O2 /EHsc /MD /D_STLP_USE_STATIC_LIB` flags and `// stlport`.
This is evidence for a still-blocked one-byte C++ candidate, not a new bank.

## Unwind ownership

The parent at 0x00844460 pushes handler RVA 0x00C55B08. That handler uses
FuncInfo RVA 0x00E44CE8, with one unwind state, 0 -> -1, whose action is
RVA 0x00C55B00. The action loads ECX from EBP+4 (the hidden result pointer)
and jumps through ILT 0x00032D85 to 0x004D4DE0. Thus cleanup belongs to the
string being constructed in the caller's result buffer, not to a fabricated
local string or neighboring function. The native range constructor maintains
that one-state base-construction lifetime. No cleanup row or identity is
claimed by this change.
