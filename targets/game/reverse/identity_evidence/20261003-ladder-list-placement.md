# LadderList source placement

Move the unchanged compiler-emission TU for `??_GLadderList@@QAEPAXI@Z`,
RVA `0x006306D0`, 30 bytes, from the noncanonical
`game/GameNetwork/Source/GameSpy/` directory to
`game/GameEngine/Source/GameNetwork/GameSpy/`. The official GeneralsMD tree
places LadderDefs.cpp in GameEngine/Source/GameNetwork/GameSpy; the matching
canonical header is GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h.
The earlier reviewed header-adoption change is preserved byte-for-byte.

AGENTS.md requires game source at its official BFME path. This is a source
placement correction, not a new class, helper name or identity claim.

Ghidra and the unpacked PE independently give the full scalar-deleting
wrapper: call ILT401F3C ->62AB10, test deleting flag1, conditionally call
scalar delete881EB0, return original receiver, RET4 at6306EB..6306ED, then
INT3 at6306EE. The current old-path build verifies all30bytes. The same
source at its new path is verified by add_match --replace-existing; no
header, compiler switch, pin, extent or covered-byte count changes.
