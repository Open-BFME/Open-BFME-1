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

## Native helper-visibility recovery (2026-10-04)

The bounded fresh hypothesis succeeds. The canonical-header declaration-only
baseline reproduces 87 bytes with exactly the recorded +0x38 difference
(ESP+0x20 instead of ESP+0x18). Exposing the complete existing
`Gen_006616A0::bfmeAssign` implementation removes that difference. All four
ordinary/noinline-helper by implicit/explicit-noinline-native-base-destructor
variants reproduce all 87 parent bytes. No assembly or fabricated STL type is
needed. The final source uses the ordinary existing helper and the canonical
header's native base destructor, with no new helper annotation or body change.

The parent now lives alongside its existing helper in
`Bfme5WideStringRanges.cpp`. Its native forced-inline range adapter preserves
the established address-qualified helper identity and maps unsigned-short
pointers to the existing short-pointer spelling without reading any element.
The real helper's visibility lets VC7.1 reuse the hidden result-pointer home
for the unused empty forward-iterator tag. The body remains native
`return wstring(low, high)`.

The final object independently reproduces the complete 106-byte helper at
006616A0 and all three other original claims in that TU: 004FA770/106B,
004F9C80/77B and 00661730/23B. The changed STLport/EH/MD compile context does not
change any of their bytes or call bindings. The parent call remains the real
existing Gen_006616A0 COFF symbol, bound through ILT 00042BB8 to 006616A0.
The helper's DIR32 copy pointer resolves through the actual retail import
directory to MSVCR71.dll!memmove at VA 0135945C. No helper pin or ledger
identity was added, renamed or migrated.

The same final object emits the native `_String_base<unsigned short>`
destructor, independently exact at 004D4DE0 for all 43 bytes with its actual
deallocator calls resolved. This supports the already-established construction
cleanup lifetime; it is not a new ledger claim or new recovered-byte credit.

The parent and complete unwind graph were independently rebound and compared
without relocation masking: 87-byte parent, 10-byte handler, 28-byte FuncInfo,
8-byte unwind entry and 8-byte cleanup action, 141 bytes total. Handler C55B08
uses E44CE8; its single unwind state (0 -> -1) at E44CE0 selects C55B00, which
loads ECX from EBP+4 and jumps through ILT 00032D85 to 004D4DE0. The handler's
runtime jump reaches the existing ___CxxFrameHandler at 009F6DD6. All parent
relocations are accounted for; the three __except_list sites remain fs:[0].

Fresh RTTI and boundary reads reconfirmed the wide-collate type descriptor,
vtable slots and RET12/INT3 boundary documented above. Checks used the normal
compiler and byte/reference verifiers with no unresolved parent/helper/base
calls, no gen-alias or archive masking, and no changes to gates or runtime.

The recommended complete source artifact is
`build/cloud-wide-collate/Bfme5WideStringRanges.recovered.cpp`, SHA256
`effd61dce7974d465f4846ffc15edf4736d5cae41f95de694bad7ef8c5b54a18`.
This identifies the reviewed source; integration into the production path
passed the normal whole-TU gate for all five rows and both DIR32 references.
The same production object separately passed the full 141-byte EH graph
assertions and strict 43-byte native base-destructor check. `verify_eh.py` asserts exact graph extents,
relocation offsets and types; native parent-handler naming; FuncInfo magic
0x19930520 and one state; unwind predecessor -1; cleanup bytes 8B4D04E9;
real ILT E9 destinations; and ___CxxFrameHandler membership in the existing
normal symbol map. It then applies those independently established bindings
to the raw COFF parent/handler/data/cleanup bytes and asserts complete equality
against retail for all 141 bytes. The final result is saved in
`build/cloud-wide-collate/final-result.json`; no ledger entry for these
auxiliary bytes is implied.
