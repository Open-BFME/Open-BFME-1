# Restore the full campaign-review callback literal

The 159-byte destructor at RVA 0050DBD0 constructs an AsciiString from the PUSH operand at body +0x30 (instruction RVA 0050DBFF). The operand binds VA 01104C48 containing AptCampaignReview::InitGadgets followed by NUL; the old source literal AptCampaignReview: incorrectly terminated after the first colon. Local PE bytes and Ghidra read_memory at 01104C48 agree on all 30 characters plus the NUL. The constructed temporary is passed to the existing direct helper via ILT 00036485 and destroyed via StringBase<char>::releaseBuffer. The final RET at RVA 0050DC6E precedes INT3 and confirms the retained 159-byte extent.

Replace only the string operand; preserve the existing destructor, callback helper declaration, receiver layout and call ABI. This is an independently contradicted literal, not a new proof of the inherited owner/helper names.

Rule: docs/matching.md Relocations requires a string literal to byte-equal the referenced string. Severity WRONG: the old NUL terminator replaces witnessed nonzero retail bytes. This repair retains the existing semantic identities and does not independently validate them. Source layout, call ABIs, pins and function extents are unchanged.
