# 041-tracksprobe: logs the terrain-track crash state and reproduces it

**Developer instrument.** `--dist` refuses it and it must never ship: it writes
a JSONL line per state change, and its **ctrl+F9 deliberately crashes the
game**.

## What it is for

Three retail minidumps from one October 2024 session, in a multiplayer Wine
prefix (`DUMP-20241020-115238`, `-115537`, `-115755`), show the same crash byte
for byte. The `lotrbfme.exe` beside them (md5 `34af1cd…`) is identical to
`inputs/baselines/bfme1/workshop-vanilla-1.03`, so every address lands on the
ledger:

```
EXCEPTION_ACCESS_VIOLATION, read at 0x00000004,  eip = 0x0091DD7F (RVA)
  VertexBufferClass::WriteLockClass::WriteLockClass   0x0091DD70   edi (the buffer) == 0
    TerrainTracksRenderObjClassSystem::flush          0x0072FEB0
      RTS3DScene::Customized_Render                   0x007143B0
        RTS3DScene::Render                            0x00715B70
          GameEngine::_bfme_updateClientSubsystems    0x0006B910
            GameEngine::update                        0x0006E910
```

`flush` hands the vertex buffer at `[this+0]` to `WriteLockClass`, which bumps a
refcount at `buffer+4`: the read at `0x00000004`. It guards only on the track
list at `[this+0x10]` being non-empty and on a render-state query, never on the
buffer. The probe watches all three fields: the system (`[0x012F9D98]`), its
track list and its buffer.

## Reproduced exactly

In a skirmish (Rohan vs Isengard on Ettenmoors, retail 1.03 under Wine),
ctrl+F9 nulls the buffer and inserts a track node, and the engine crashes
itself. The node is a real zeroed `0x1300`-byte allocation from the engine's own
`operator new` (`0x00C81F30`), so the per-frame list walk at `0x0072EEB0`
terminates on it. The game's own handler writes a dump with the same exception,
faulting address, `eip`, `edi`, `eax` and `ebp` as the 2024 dumps, and the same
call frames at the same stack offsets.

The precondition is forced. The reproduction shows that this state produces
exactly the retail crash, so a null check in `flush` (`042-tracksfix`) is a fix
for the observed dumps, not for a guess. What causes the state in the field is
unknown, and two facts constrain it:

* Only two objects in the shipped INI declare `TrackMarks`:
  `CINE_MordorCatapult_LR` and `Tank`, a leftover Generals test object. The list
  stayed empty across 1341 logic frames of Rohan gameplay with units marching.
* `shutdown` (`0x0072EDF0`) nulls the buffer, but its only caller is the
  destructor, which then frees the object and nulls the global the flush caller
  checks. No known path leaves a live system holding a null buffer.

## Build

```bash
python3 tools/modbuild.py --only 041-tracksprobe -o build/lotrbfme.tracks.exe
```

It shares the client-frame hook `0x0006B910` with `039-replayctl`, so build it
alone; `cave.py` makes a second claim on an address a hard build error. Records
land in `My Battle for Middle-earth Files\Tracks.jsonl`: one line per change in
the (system, buffer, tracks) shape, plus a heartbeat every 600 frames.
