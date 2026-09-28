# 042-tracksfix: the terrain-track crash, removed

A crash reported from the field, recovered from three retail minidumps,
reproduced byte for byte and fixed in 148 bytes of cave. It is in the repository
bundle, `mods/dist`. The reproduction and its evidence are in
[`041-tracksprobe`](../041-tracksprobe/README.md).

## The crash

```
EXCEPTION_ACCESS_VIOLATION reading 0x00000004,  eip = 0x0091DD7F
  VertexBufferClass::WriteLockClass::WriteLockClass   0x0091DD70   the buffer == 0
    TerrainTracksRenderObjClassSystem::flush          0x0072FEB0
      RTS3DScene::Customized_Render                   0x007143B0
        RTS3DScene::Render                            0x00715B70
          GameEngine::_bfme_updateClientSubsystems    0x0006B910
```

`flush` hands the vertex buffer at `[this+0]` to `WriteLockClass`, which bumps a
refcount at `buffer+4`: the read of address 4. It checks that the track list at
`[this+0x10]` is non-empty, but never that the buffer still exists.

## How it works

A detour at `0x0072FEB0`, one `.cpp` of about 15 lines, parks the track list
while the buffer is missing and gives it back when the buffer returns. `flush`'s
own empty-list exit, three instructions in, then skips the lock. Parking rather
than dropping the list keeps its refcounted nodes from leaking. Repointing the
entry guard at the buffer would also be safe, but would put a vertex-buffer lock
in every frame, because the list is almost always empty.

## Build

`python3 tools/modbuild.py --dist` builds the bundle into `mods/dist/`.

## Verified

Same binary, same trigger (`041-tracksprobe`'s ctrl+F9), one feature apart:

| | without `042` | with `042` |
|---|---|---|
| outcome | **crash** | **match continues** |
| dump written | `DUMP-20260831-160825-488-308.dmp` | none |
| logic frame | stops at 277 | 143 → 529 and counting, buffer still null |

The crash matches the 2024 field dumps on every discriminating field: `eip`,
faulting address, `edi`/`eax`/`ebp`, and the call frames at the same stack
offsets. With the fix, units, resource income and UI kept working on screen for
several hundred logic frames after the trigger.

## Limits

* It removes the crash, not its cause. `shutdown` (`0x0072EDF0`) nulls the
  buffer, but only from the destructor, so what leaves a live system holding a
  null buffer is unknown.
* It is deliberately silent when it acts; `041-tracksprobe` logs these fields.
* It should rarely act: only two shipped INI objects declare `TrackMarks`, and
  the list stayed empty across 1341 logic frames of ordinary play.
* It is not established that this is the crash ladder players report. The dumps
  come from one multiplayer session in October 2024, and no dump from a reported
  freeze-on-quit has been collected.
