# Quick-match pointer identity at VA 0x012F4820

Unresolved: retail proves a single four-byte screen pointer, but no existing declaration or reference fact selects a canonical C++ type and global spelling from the five competitors. No definition, data row, pin or declaration at this address is changed.

Retail `.data` has four loader-initialized zero bytes here, in its virtual tail. There are no initial pointer relocations. The next DIR32-named datum lies outside the four-byte extent, and no data row overlaps it. The complete retail operand scan is in `build/rlink/identity-15/012F4820-retail.log`.

Constructor RVA `0x00505FB0` stores its primary `this` value into this slot. Factory RVA `0x00506040` clears it. Native screen consumers load it into ECX, access the widget pointer at `+0x294` and other established quick-match offsets, and call the gadget, save-options and ladder methods. Teardown RVA `0x00507E10` loads `+0x294`, invokes save-options when applicable and clears the singleton. These operations prove pointer storage and the screen role. They do not establish that the invented windows, ladder-panel and receiver class views are the complete concrete type.

The Zero Hour reference has the WOLQuickMatchMenu callback implementation and image globals, but no `TheQuickMatchScreen` declaration that proves the BFME APT singleton spelling. The existing ladder-panel method pin explicitly describes an unnamed image function. This is evidence for the role, not for a canonical class identity.

Competing spellings and before-correction declaration counts are below. Raw declaration lines are in `build/rlink/identity-15/declaration-counts.log`.

- `?Rva012F4820QuickMatchWindows@@3PAVRva00506720Windows@@A`: 2 game file(s).
- `?TheBfmeQuickMatchScreenSlot@@3PAXA`: 1 game file(s).
- `?TheQuickMatchLadderPanel@@3PAVBfmeQuickMatchLadderPanel@@A`: 4 game file(s).
- `?TheQuickMatchScreen@@3PAUQuickMatchScreen@@A`: 1 game file(s).
- `?g_q1Receiver012F4820@@3PAVQ1Receiver012F4820@@A`: 1 game file(s).

A reference declaration or independently named APT vtable owner that establishes the concrete screen type and singleton name would settle the question. A second word used as part of the slot, or a non-pointer producer, would refute the four-byte pointer conclusion. Every E9 call chain in the retail probe is read from its five bytes; no decompiler identity is used.
