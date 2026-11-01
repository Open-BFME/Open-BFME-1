# Apt resolver: remove the non-retail lookup wrapper

Queue rank 79, claim 0xFD78BB0A. Existing resolver row is
`?rva8CC570Resolve@@YAPAVRva8CCCE0Value@@PAX00@Z`, RVA 0x008CC570,
280 bytes. No identity or extent change is proposed.

The local inline BfmeNode1220::bfmeTest1220 was a forwarding wrapper, whereas
its pinned retail identity is the 929-byte lookup at 0x0089C290. Move the
existing member-pointer ABI conversion into the sole call site. This preserves
the exact same target and two stack arguments without defining the forwarding
wrapper under the retail lookup name. The real lookup remains a generated row;
this change does not recover that body.

Validation: normal scoped build passes 1/1, including seven DIR32 references.
COFF object_references now contains ?d_0089c290@@YAXXZ, and neither its roots
nor COMDAT edges contain bfmeTest1220. find_declared_unmatched reports all
functions matched. Current linking preview must not be interpreted as newly
linked bytes: the available census is e9a5ae5b4c (2026-10-19), older than the
queue's bb53b24f2b, and most current objects are unavailable in this worktree.

BFME 2 checkout /home/yannick/projects/Open-BFME-2 at
2e97f871794a7b0cc6463976dd3b6fc3c1d780f8 was searched in Code/Libraries/Source/
(Apt and EA) and Common for bfmeTest1220/Rva8CC570. No corresponding named
provider or additional usable identity evidence was found. Its source is not
used by this repair. BFME 1 evidence is the existing row, existing typed call
conversion and scoped byte/relocation verification; no new semantic names.
