# Canonical x86 SEH import callable at 0x009F6C50

The existing matched claim is `?Rva009F6C50_except_handler3@@YAHXZ` at
`0x009F6C50`, six bytes, in
`game/Libraries/Source/WWVegas/WWLib/Rva009F6C40ImportStubs.cpp`.
The canonical native callable is `__except_handler3`, the C linkage name of
`_except_handler3`. This corrects the address-derived source view; it adds no
second identity or new code bytes.

Independent original evidence:

- Retail bytes `FF 25 C0 92 35 01` jump through IAT VA `0x013592C0`.
  The actual PE import directory names `MSVCR71.dll!_except_handler3`.
- Original msvcrt.lib short-import CODE member SHA256
  `237cff1f28ff0d452dbf8ac9732f079fd6edb1010feb3920650f5551c423454c`
  publishes exactly `__except_handler3` and `__imp___except_handler3` in both
  original archive indexes. It is an i386 native CODE import; the original
  library and its indexes are not changed.
- Original libc.lib `build\intel\st_obj\sehprolg.obj` SHA256
  `8e7229ce436407af60a8fbbb42b08231f0789a44f8366baf66d579dce12294cc`
  defines `__SEH_prolog`. Its DIR32 at +1 names `__except_handler3`; retail's
  corresponding `push` at RVA `0x009F7E88` embeds VA `0x00DF6C50`. Thus the
  original SEH registration helper, not adjacency or a guessed API spelling,
  identifies this exact versioned runtime handler.
- Public VC7.1 `include/excpt.h:82-87` declares the x86 SEH dispatcher contract
  as `EXCEPTION_DISPOSITION __cdecl _except_handler(_EXCEPTION_RECORD *, void *,
  _CONTEXT *, void *)`. The versioned handler uses that registered-dispatcher
  interface. The actual toolchain msvcr71.dll `_except_handler3` export at
  RVA 0x240D corroborates a plain caller-cleaned RET, record/frame/context use
  and disposition return values. Its fourth dispatcher pointer is unused.

Evidence limits: excpt.h names the generic `_except_handler`, not specifically
`_except_handler3`; the four-argument versioned contract is established by that
public dispatcher interface and original registration role, not by six jump
bytes or an asserted original CodeView prototype. The auxiliary toolchain DLL
hash `8094af5ee310714caebccaeee7769ffb08048503ba478b879edfef5f1a24fefe`
does not assert which runtime DLL version the game loads. No unverified
PEXCEPTION_ROUTINE declaration is used. Original consumer .sxdata references
the compiler's handler symbol; direct Error-function DIR32 references are not
claimed.

The authored provider uses public excpt.h types and a strong undefined native
IAT pointer. It compiles to exactly six bytes `FF2500000000` with only
`DIR32 +2 -> __imp___except_handler3`; its function and pointer CodeView types
agree, cdecl CC0, four pointer arguments, int-sized EXCEPTION_DISPOSITION return.
There is no raw assembly, forced symbol, alternate name, new IAT definition or
type-layout copy. All 102 matched source bodies verify strictly in the private
baseline, candidate and diagnostic Z7 control. All code and data sections,
all undefined providers and all other definitions remain identical.

This private proof is not a normal admission. Normal original-path compile,
add_match identity correction, import_binding source-owned callable and
selected-IAT/PE proof, normal gates and commit remain required. The ordinary
route-pin checker currently refuses this address because its old CPP row is
not a gen-import row; no such route pin is proposed.

Normal root verification subsequently passed: the ordinary add_match
--correct-identity transaction admitted this existing CPP identity and the
normal whole-source build retained102/102 rows with101 DIR32 checks. The
normal import_binding check passed a real isolated strict link; its receipt
proves the selected source-owned callable jumps through the strong original
IAT endpoint MSVCR71.dll!_except_handler3, with all frozen input hashes equal.
The original CODE import remains catalogued; the checked temporary library
projection removes only its callable public while preserving the real IAT
public, both archive indexes and all unrelated member payloads. No library
under inputs/ was rewritten and the fixture was not executed. This is one
retained6B provider correction, not a new recovered body or linked-game claim.
