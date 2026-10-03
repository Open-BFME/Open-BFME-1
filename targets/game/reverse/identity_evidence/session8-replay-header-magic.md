# Restore the complete eight-byte replay signature

The 1006-byte readReplayHeader body reads eight bytes then calls imported strncmp with count 8. Its PUSH at RVA 0009953B has a DIR32 operand at body +0xAC targeting VA 0107FDB0. Retail contains 42 46 4D 45 52 45 50 4C 00 (BFMEREPL followed by NUL), while the source literal terminates after BFMERE. This changes the signature comparison of every valid retail replay. Local PE decoding and Ghidra read_memory at 0107FDB0 agree through the complete terminator. The full body ends in RET 4 at RVA 0009987B..0009987D followed by INT3; its 1006-byte extent is retained.

Replace only the literal with BFMEREPL. Preserve the eight-byte fread/strncmp count and existing receiver, replay layout, string lifetimes and callees. This finding is independent of the inherited semantic name and type provenance.

Rule: docs/matching.md Relocations requires a string literal to byte-equal the referenced string. Severity WRONG: the old NUL terminator replaces witnessed nonzero retail bytes. This repair retains the existing semantic identities and does not independently validate them. Source layout, call ABIs, pins and function extents are unchanged.
