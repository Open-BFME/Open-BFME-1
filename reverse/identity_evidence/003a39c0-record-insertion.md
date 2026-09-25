# RVA 0x003A39C0: indexed record insertion

The native 160-byte thiscall body has one input reference and ends at 0x003A3A60 with `ret 4`. It shares the constructor, vector insert and destructor contracts independently verified for 0x003A3A90 (see `003a3a90-record-insertion.md`). The position is `begin + (receiver.word20 + 2)`; the field's wider meaning is not asserted.

The previous bank wrote the input's three words to element offsets 0/4/8. Full retail decoding instead writes +0xA4/+0xA8/+0xAC, exactly as the now-landed sibling does. Correcting these fields recovers the 160-byte size with only four different bytes (two adjacent loads in opposite order). Copying the three-word aggregate reproduces those loads and all remaining instructions without compiler flag experiments.

The input and owning class remain address-qualified. The opaque element prefix, three-word aggregate and tail preserve the existing 184-byte Rva003A35A0Element specialization. Its externally implemented lifetime and existing helper symbols are reused, with no new pins or header edits. The ASM remains untouched. This adds 160 rebuilt bytes while preserving boundaries and total exact coverage.
