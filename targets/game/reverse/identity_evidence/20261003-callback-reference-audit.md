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
