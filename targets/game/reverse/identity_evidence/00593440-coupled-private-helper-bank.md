# 0x00593440: complete record helper with its real private callee

Evidence-only bank; neither source nor pins are promoted. Retail 0x00593440
ends with RET at 0x00593621 (482 bytes). Existing matched AptPalantirRva00594740
calls it as a cdecl hidden-result record of three dwords and Object pointer;
its interpretation alone does not establish an EA name.

Ghidra and independent retail disassembly establish the two update lookups,
timer ratio/clamp, alternate-template/hero gate and experience fallback.
The companion 0x0058B610..0x0058B7AF (415 bytes) consumes Object in ESI,
rank output in EDI and progress output in EBX, with no argument stack slots.
Its complete banked definition performs all level/next-level/maximum-rank
checks, three-float ratio and clamp, then rejects rank <= 1 with negative
progress. It is not a dummy helper. Native Object comes from object.h;
unnamed BFME calls use a separate single-inheritance member-pointer view.
The two-pointer level value has nontrivial inline copy construction, matching
retail's outgoing sub-esp-8/store sequence instead of two POD pushes.

The whole coupled draft compiles. A shared parent exit reduces 539 bytes to
487 versus 482, 289 differing non-relocation bytes, first +109, shape 0.957,
measured quality 0.3797. Remaining parent differences include merged timer
loads, swapped comparison registers, and stack outputs at the helper call.
Helper remains 434 versus 415, 301 differences, shape 0.799; compiler uses
Object in EBX and stack outputs with callee-save pushes, not retail's private
ESI/EDI/EBX convention. Fastcall, noinline/default-inline and int-return
variants did not recover it. Int return was rejected in favor of the caller's
AL test. Both extents must strictly verify together before promotion.

The helper's existing generated names/pins cannot justify an ordinary ABI.
No asm adapter, synthetic no-write helper, caller-only match or new pin was
introduced. Re-probe from this bank; finish_measure --one currently refuses
its dependency receipt (include search directories unreadable), although
probe compiles and measures successfully and re_log performs a fresh measure.
