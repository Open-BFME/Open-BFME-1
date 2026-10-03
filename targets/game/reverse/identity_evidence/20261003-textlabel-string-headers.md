# GameWindowManager text-label canonical strings

Severity: HYGIENE. AGENTS.md requires: "never redeclare a type a header already covers: #include it".

The existing RVA0047E1B0/175B winTextLabelToText claim has an exact Zero Hour twin in GameClient/GUI/GameWindowManager.cpp: return the empty wide string for an empty label; otherwise default-construct, translate and return a wide string. Include canonical ascii_string.h/unicode_string.h instead of the local duplicate classes. Keep this caller's null/length test and inline wide default/copy constructor definitions visible in the TU; no shared header changes.

Retail/Ghidra independently agree over all175B plus padding: two copy calls888400, translation8891F0, local wide release8881D0 and argument narrow release887940. Full RET8 is47E25C..47E25E; padding starts47E25F. The normal gate passes1/1 and its one DIR32 reference.

Retail operand+0x3B points to VA01336E54. The PE export table independently supplies ordinal1340, RVA00F36E54, `?TheEmptyString@UnicodeString@@2V1@B`, the const static datum. The old TU redeclared this as mutable @A and carried an obsolete comment claiming the const spelling was wrong. The new COFF relocation uses the canonical @B without a new pin or alias. No existing function identity, extent, owner layout or coverage changes.
