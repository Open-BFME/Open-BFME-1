# Adopt canonical Coord3D storage in worker dock initialization

Base `34137de678290d6a44431227c977c1610e579c86`. Source `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_ctor_Thunk.cpp`; scope claimed before editing.

Use the existing twelve-byte coordinate in each sixteen-byte worker dock record. Keep zeroing grouped in a TU-local inline helper, the technique just verified on the related dozer constructor. Preserve all task, voice, state-machine and barrier ordering and the existing array-lifetime callback bindings. Original target factory/member/destructor evidence fixes the layout; the registered BFME 1 coordinate contract is retained rather than importing donor addresses or class-keys.

The normal byte gate preserves 2 matched row(s), with existing
extents 417, 24 bytes. Actual COFF comparison
preserves 5 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
?zero@Coord3D@@QAEXXZ.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-no-qwen-20261101-0015/b1-04-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
