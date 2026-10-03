# Callback reference audit, 2026-10-03

W3DModuleFactory::init at RVA006BFFE0, 1136 bytes, has 41 absolute
callback constants. The existing link_debt cast detector misses their unsigned
suffix. Full retail decoding ends at RET6C044F and CC6C0450; Ghidra agrees.
Retail pushes VA0041F0FA at6C001D and VA004063BB at6C0022, for example.

A candidate replaces 40 occurrences with 38 existing address-derived ILT
symbols. Each is a five-byte E9 whose decoded target agrees with its existing
ledger note. All 1136 bytes, 16 strings and 40 DIR32 references pass scoped
verification. VA00424AFA remains unresolved and unchanged; its E9 reaches
RVA006BF600. No semantic callback identity or new pin is proposed.

The normal commit hook rejects the candidate: name_regression reports 38
substitutions from `u` to the existing j_XXXXXXXX identifiers. Its tokenizer
splits the old hexadecimal literal from its suffix and interprets that suffix
as a descriptive identifier. This is a lexer false positive, not evidence of
38 semantic renames. The tool and correction registry have not been weakened.
The measured candidate is preserved in attempt_history; production is restored.
A preferred active stash is forbidden for an already matched real C++ row,
so the provisional partial record is explicitly superseded by blocked.

The same broader scan finds six raw function-pointer values in the existing
OnlineQuickMatch constructor at RVA00559400, 755 bytes. Retail materializes
VA00436C64 at55952E and VA00411E14 at55956E. Full decode ends RET4 at5596F0
and CC5596F3. These spellings also escape the narrow cast hook. No production
change or semantic callback rename was attempted for that constructor.

These findings concern relocatable references, not new byte coverage. Future
work must preserve exact named-reference verification and independently
justify any additional callback/ILT anchor. Do not replace these addresses
with plausible callback names merely from neighboring registration strings.

Session 2: the tokenizer false positive is repaired in20c4dd27a1, with170
name-regression tests including real u/L identifier protections. Restoring the
archived candidate again passes the strict1136B/16strings/40DIR32 gate. The
38 referenced j_ symbols retain their existing ILT identities; no new semantic
name or pin is introduced. The40-reference source repair is now committed
separately from that tool correction. The remaining VA00424AFA stub decodes
E9 01 AB 69 00 -> RVA006BF600; its proper source declaration is separate work.

OnlineQuickMatch session2 repair replaces all six raw values with the existing
j_ILT symbols. Independent retail E9 decoding gives these VA->RVA routes:
436C64->558450,411E14->559360,43730D->5592D0,423015->558440,
42F5E0->558470,4178DC->558FB0. The preserved single-inheritance callback
representation remains unchanged; these declarations only name the stored
addresses. Strict before/after checks pass755B and8 strings; checked DIR32
references increase from11 to17. No semantic callback identity is inferred.

### QuitMenu callback reduction, session2

`??0BfmeAptScreenQuitMenu@@QAE@PAX@Z`, RVA0056A2F0,1024B, stores callback VA00410B86 at instruction56A5DB. The existing `?j_00010b86@@YAXXZ` row is a five-byte ILT; baseline and Ghidra both read `e9 15 86 55 00`, reaching RVA005691A0. Replacing the literal with the address of that existing symbol preserves the eight-byte member-pointer union representation and asserts no callback signature or semantic name.

The constructor's RET4 at56A6ED ends at56A6F0 padding, also independently checked in Ghidra. Strict before/after verification passes both this constructor and the unchanged280B onInitialized sibling:17 strings; DIR32 references increase26→27. The legacy local string declarations are a separate header-adoption concern; the current adoption checker reports no eligible automatic swap for this source. No new pin, extent, identity or coverage claim is introduced.
