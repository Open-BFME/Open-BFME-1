# Adopt canonical Coord3D in slaved effect offsets

Base `8a57d5347a52d99ffb51c13646f11353e48a65a5`. Source `game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_startSlavedEffects.cpp`; scope claimed before editing.

Replace the private coordinate view with the registered twelve-byte coordinate. Preserve the existing offset union, random-position arithmetic, object-status operations and release ordering. A local inline zero helper keeps the measured grouping without adding a shared member or a new native identity.

The normal byte gate preserves 2 matched row(s), with existing
extents 146, 68 bytes. Actual COFF comparison
preserves 17 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
?zero@Coord3D@@QAEXXZ.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-no-qwen-20261101-0015/b1-05-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
