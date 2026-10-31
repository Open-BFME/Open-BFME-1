# Adopt canonical Coord3D storage in dozer dock initialization

Base `9cc654a37c0549aea22369462f45e10d8065553b`. Source `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtorThunk.cpp`; scope claimed before editing.

Use the registered twelve-byte coordinate in each sixteen-byte dock-point record. The target constructor clears exactly the three component words; the native dock array, owning constructor/destructor evidence and registered coordinate contract establish the offsets. Direct float stores initially moved the loop induction pointer from the last word to the first. An isolated, explicitly mapped private probe proves that a TU-local force-inline zero helper with the same X/Y/Z stores restores every byte; the final normal gate verifies both parent and 24-byte array cleanup. The old zero method copy had only debug incoming edges; retained runtime calls do not change. Existing task/member initialization order and extents stay unchanged. The pinned BFME 2 coordinate contract and Dozer source were reviewed as layout leads; target sizes, class-key and compiler settings are retained. The successful grouping technique is recorded in shape_levers.md.

The normal byte gate preserves 2 matched row(s), with existing
extents 272, 24 bytes. Actual COFF comparison
preserves 9 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
?zero@Coord3D@@QAEXXZ.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-no-qwen-20261101-0015/b1-03-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
