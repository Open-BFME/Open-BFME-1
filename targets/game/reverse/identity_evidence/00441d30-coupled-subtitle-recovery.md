# InGameUI slot 19 and its private line-width helper

The inherited identity evidence is `0x00441d30-ingameui-slot-rehome.md`:
matched slot20 caller 0x0043E510 passes UnicodeString by value and duration
to slot19. Slot21 is the matched removeMilitarySubtitle. Preserve the existing
address-qualified InGameUI name, using an opaque emitted owner view. No new EA
method name is inferred from behavior. Retail has RET8 at 0x00441F76 and ends
0x00441F79: complete 585 bytes, including string cleanup and both early exits.

The helper 0x0043E5C0 ends with RET at 0x0043E6A8: 233 bytes. Parent +0x18C
pushes the subtitle record, +0x18D clears EBX, +0x18F calls helper, +0x19F pops
the argument. Helper ECX is DisplayString, EBX is starting character index,
and the sole stack argument is a const reference to the record's first native
UnicodeString. Ghidra's zero-stack inferred signature was incorrect. Full
helper walks to newline/end, saves native display text through slot8, sets a
native substring through slot4, queries dimensions through slot0x3C, restores
the old string, releases it and returns width (or zero for an empty line).

Compile both real bodies together. The absent-from-retail forwarding caller
keeps the helper's nonconstant-index contract visible; without it, VC7.1
specializes this sole zero-index call. It does no substitute work. Both actual
bodies must strictly verify; matching the parent's call alone is insufficient.
Native StringBase getCharAt's inline nullable return restores the helper's
MOVZX/CMP sequence, reaching 233/233. Use integer color fields cast to byte at
the packing expression, not early byte temporaries: parent reaches 585/585.

Canonical WWLib unicode_string.h and string_base.h supply all string types.
TU-local definitions forward native UnicodeString constructors (including
substring) and destruction into the real private StringBase bodies. Access
control is preserved: no public-name pins for private StringBase methods.
The owner/virtual-table views are explicitly address-qualified; no fake vtable
is emitted. The 0x48 record uses native UnicodeString and opaque offset fields.
Owner+0x818 is the record pointer (name_oracle confirms militarySubtitle),
+0x878 is title font; +0x87C point size and +0x880 style are independently read
by the proven adjustFontSize/getFont calls. Display slot0x14 resets, slot0x18
sets font; manager slot0x24 creates display strings. Record layout stores are
visible throughout the exact parent. Source asserts record size0x48 and PMF
width4. No shared-header changes or guessed native type declarations occur.

Lead approved these opaque ABI views in help/b3.answer.md on 2026-10-03,
requiring canonical strings and strict verification of both extents. A shared
header proposal records DisplayString BFME slot0x3C versus ZH0x30, and the
BFME subtitle record versus ZH MilitarySubtitleData for later adoption.

Validation: add_match scoped gate verifies both extents together (818 bytes),
including one floating constant and five DIR32 references; zero unverified
string literals. Pin consistency passes. The obsolete naked emitter and old
noncanonical helper bank are removed.
