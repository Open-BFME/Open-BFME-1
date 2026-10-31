# Adopt canonical Coord3D for worker supply-distance calculations

Base `c3d7af31883ed61a1c1fad176be40e619fb7b469`. Source `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_gainOneBox.cpp`; scope claimed before editing.

Use the registered coordinate storage for the worker-to-warehouse delta. Preserve position-copy, subtraction and float length expression ordering in local inline helpers, including the square-root narrowing and quarter-scan-distance threshold. Audio and supply-count side effects retain their existing order; no new native helper identity is asserted.

The normal byte gate preserves 1 matched row(s), with existing
extents 286 bytes. Actual COFF comparison
preserves 7 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
?length@Coord3D@@QBEMXZ, ?set@Coord3D@@QAEXPBU1@@Z, ?sub@Coord3D@@QAEXPBU1@@Z.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-no-qwen-20261101-0015/b1-06-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
