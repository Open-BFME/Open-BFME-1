# Six BFME1 storage adoptions: bounded batch evidence

Initial outgoing base `43f5cd7743e2f1047f1bdb80b83ed99e3c749ee0`. Six claimed source units adopt existing
registered Coord3D storage, removing six private copies. Normal gates preserve
6 existing native function/EH rows (2451 bytes of ledger extents),
42 retained external code bodies and their resolved relocation targets.
An additional read-only comparison preserves 0 retained named TU-local
C++ code definitions; added/removed static components have no retained runtime root.
Compiler-label funclets/EH stubs are covered separately by whole-section
preservation (BFME1) or native EH verification (BFME2), not unstable name identity.
No new native/authored-byte or matched-row gain is claimed.

- [Use canonical Coord3D storage in buffered audio positions](buffered-audio-position-coord3d-20261101-2150.md): 1 rows, 748 bytes, 18 retained external bodies.
- [Use canonical Coord3D storage in sample audio positions](sample-audio-position-coord3d-20261101-2150.md): 1 rows, 369 bytes, 12 retained external bodies.
- [Use canonical Coord3D storage in audio 3d configuration](audio-3d-configuration-coord3d-20261101-2150.md): 1 rows, 196 bytes, 1 retained external bodies.
- [Use canonical Coord3D storage in audio 3d filters](audio-3d-filters-coord3d-20261101-2150.md): 1 rows, 301 bytes, 2 retained external bodies.
- [Use canonical Coord3D storage in audio screen center](audio-screen-center-coord3d-20261101-2150.md): 1 rows, 211 bytes, 1 retained external bodies.
- [Use canonical Coord3D storage in radar cell coordinates](radar-cell-coordinates-coord3d-20261101-2150.md): 1 rows, 626 bytes, 8 retained external bodies.

All non-debug sections preserve bytes and external or resolved local relocation
positions in each source. Only the existing registered coordinate header replaces
the private POD. The owning accept tool validates actual removals but retains
historical queue keys under its control; no queue entries are deleted by hand.

The native linking-first picker still serves RefHandle008958D0 at census
bb53b24f2b. Its three selected sources last changed at e8b16ffa12 (Oct24).
Prior blocked inline-depth/helper-visibility trials remain applicable; no changed
prerequisite supports repeating them, and this review is not counted as a task.
The BFME2 donor remains at59e3f8f825b698775df9e1728265fe962a5d0c02; its successful
Nov1 13:06 UTC reference check is still within72h. No donor scan was repeated.
The available downloaded frozen index is used only for bounded predictions.

The updated shell locator requires a complete Git for Windows installation;
the existing complete cached installation is selected in the process PATH.
No gate/tool/baseline is modified, and no system-wide installation is changed.

Final bounded preview, distinct from a fresh census:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
game/GameEngineDevice/Source/MilesAudioDevice/BufferedStreamStarter006B7E70.cpp: LINKS  LINKED 748 -> 748 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 748)
game/GameEngineDevice/Source/MilesAudioDevice/SampleStarter006B4090.cpp: LINKS  LINKED 369 -> 369 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 369)
game/GameEngineDevice/Source/MilesAudioDevice/Rva006B3F90Configure3D.cpp: LINKS  LINKED 196 -> 196 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 196)
game/GameEngineDevice/Source/MilesAudioDevice/Rva006B3F90InitFilters3D.cpp: LINKS  LINKED 301 -> 301 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 301)
game/GameEngineDevice/Source/MilesAudioDevice/Rva006956D0ScreenCenter.cpp: LINKS  LINKED 211 -> 211 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 211)
game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_taintCell_rva006C2710.cpp: LINKS  LINKED 626 -> 626 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 626)
link_check: 6 of 6 link cleanly; LINKED 2,451 -> 2,451 bytes (97.3s)
```

Complete current provider/consumer selection remains unproven wherever
index/receipts are incomplete. Full-image link, gameplay and RAM/leak/crash/FPS
gains are not claimed. No shared header, compiler option, native-address pin,
alias, new identity or baseline is changed. Controls remain in the ignored
build/six-each-half-resources-20261101-2150 directory and diagnostic package.
BUILD_POOL=7 per independent repository process: aggregate14 of28 logical CPUs;
memory budget47GiB of95.69GiB. No local model is needed. Claims are released after
ordinary publication.
