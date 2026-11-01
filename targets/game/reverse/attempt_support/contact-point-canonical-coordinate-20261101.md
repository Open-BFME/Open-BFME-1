# Use canonical coordinate storage in object contact-point queries

Base `528ee065e3cd5759da42146d949f0c70fda28c05`. Source `game/GameEngine/Source/GameLogic/Object/Object_getWorldspaceBestContactPoint.cpp`; scope claimed before editing.

Replace the private coordinate definition with the existing registered twelve-byte storage. Preserve the three output stores in a TU-local inline helper, along with all geometry, inverse-transform, rubble-height and tracing behavior. Preserve the existing GeometryInfo binding unchanged. The current BFME 2 donor is reviewed separately; no donor address or layout is copied into this target. The bounded afbe8bafb6 preview preserves LINKED609->609; current full provider selection remains unknown. The independently reviewed donor refresh is recorded in donor-refresh-20261101-1231.md.

The normal byte gate preserves 1 matched row(s), with existing
extents 609 bytes. Actual COFF comparison
preserves 11 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
?set@Coord3D@@QAEXMMM@Z.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/one-each-no-qwen-20261101-1231/b1-01-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
