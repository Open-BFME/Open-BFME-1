# Three VideoPlayer table leaves

The independently matched VideoPlayer complete destructor0081C590 stores
vtable VA0112CCC0; the constructor0081C550 and named init0081CB30,
addVideo0081D2C0, removeVideo0081CF40 and getVideo0081CD70 entries anchor
this family. Its slot5 points directly to0081C360, slot10 to0081C370,
and slot11 to0081C380. Independent ILT entries007E3B00/10/20 also jump
to those respective starts. Every target is a single RET followed by
fifteen INT3 bytes. Ghidra read_memory at00C1C360 and baseline bytes
agree over all48 bytes. These are three distinct bodies, not one alias.

The canonical BFME subsystem header documents the base's nine retail
slots, including slot1 init,2 loadIniFilesFromLegend,4 reset,5 update.
The separate native Zero Hour SubsystemInterface and VideoPlayer headers
declare update as void with no parameters. BFME's nine base slots are
followed by deinit at9, then the two focus hooks at10 and11. This placement
is bounded by named init at1 and the open-family slot12, called by the
matched PlayMovieAndBlock004E2D50 through +30. ZH VideoPlayer.h declares
both focus hooks void with no parameters; its cpp has empty definitions.

The ZH update implementation services streams, whereas this BFME leaf is
empty. Only the independently aligned ABI is used; no claim that its
behavior equals the ZH update body is made. All three production names
remain fully address-qualified, with no duplicated VideoPlayer or base
class layout and no new pin. Each individual callee inventory is empty.
