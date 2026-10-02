# RVA 0x0024ED40: SlaughterHordeContain primary slot 30

Retail PE decoding establishes the owner without interpreting decompiled C.
Matched constructor RVA 0x0024E7A0 calls HordeGarrisonContain's constructor,
then at VA 0x0064E7BC installs primary table **0x010B11C0**. It clears
full-object fields +0x9BC and +0x9C0, which this body also updates.

Primary slot 2 routes to six-byte getter RVA **0x0024E820**, returning
literal VA **0x010909E4**, whose retail bytes spell `SlaughterHordeContain`.
Thus the owner proof does not depend on the constructor's proposed name.
Slot **30 (+0x78)** at VA **0x010B1238** contains ILT **0x0040AC31** ->
body **0x0024ED40**. Complete-image pointer search finds exactly that slot;
the body has no direct caller. Neighboring primary helpers are largely
address-qualified, so their spellings provide no native method proof.

The body takes one Object pointer with full-object ECX, gets its controlling
Player, computes bounty/experience and money/UI effects, then transfers or
kills the contained object and updates Horde bookkeeping. This is consistent
with a specialized containment insertion helper. A precise native method name
cannot be inferred from that behavior, nor from the differently placed and
two-argument `onContaining` secondary-interface methods.

The complete extent is 1066 bytes: final RET 4 at +0x427, followed by INT3
at +0x42A. `tools/callees.py` lists 30 direct targets, including several
unproved signatures and a dump-owned helper; there is also SEH and x87 work.
The preserved 0.25 bank's previous 821-byte/relocation-drift verdict remains
conversion work. No source, pins, bank, progress row or native method rename
changes in this owner-evidence commit.
