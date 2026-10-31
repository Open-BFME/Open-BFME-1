# Adopt canonical Coord3D storage in supply-center selection

Base `771f65b9d554ee7acf8f0b048a9a2e0dccdffdf1`. Source `game/GameEngine/Source/GameLogic/AI/AIPlayerFindSupplyCenter.cpp`; scope claimed before editing.

Use the existing twelve-byte struct with x/y/z at +0/+4/+8. Direct stores initially changed x87 evaluation order; an isolated, correctly mapped private probe showed that capturing Y then X before the original X/Y stores restores all 886 bytes. The final source uses those locals, and zeroing retains X/Y/Z order. Reviewed the pinned BFME 2 AIPlayer.cpp findSupplyCenter body: the same enemy-center calculations and zero/set semantics apply, while target addresses/layouts remain independently established. No donor class-key or build context is imported. The original direct variant and exact private probe are preserved. Sanitized external ROTWK crash follow-ups are recorded separately; this adoption is not claimed to fix either crash.

The normal byte gate preserves 1 matched row(s), with existing
extents 886 bytes. Actual COFF comparison
preserves 22 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
?set@Coord3D@@QAEXMMM@Z, ?zero@Coord3D@@QAEXXZ.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-no-qwen-20261101-0015/b1-02-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
