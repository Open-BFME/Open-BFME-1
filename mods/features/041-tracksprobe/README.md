# 041-tracksprobe — the terrain-track crash, reproduced

**INSTRUMENT.** `--dist` refuses it, and it must never ship: it writes a JSONL
line per state change and its ctrl+F9 deliberately crashes the game.

## What it is for

Three retail minidumps sat unread in `~/.wine/.wine-with-marcell/drive_c/Program
Files (x86)/BFME1/` — `DUMP-20241020-115238`, `-115537`, `-115755`, three
crashes inside six minutes with a different pid each time, from a prefix whose
`Network.ini` holds a multiplayer name. The `lotrbfme.exe` beside them is md5
`34af1cd…`, byte-identical to `baselines/bfme1/workshop-vanilla-1.03`, so every
address in them lands on the ledger.

All three are the same crash byte for byte, down to `esp`:

```
EXCEPTION_ACCESS_VIOLATION, read at 0x00000004,  eip = 0x0091DD7F (RVA)
  VertexBufferClass::WriteLockClass::WriteLockClass   0x0091DD70   edi (the buffer) == 0
    TerrainTracksRenderObjClassSystem::flush          0x0072FEB0
      RTS3DScene::Customized_Render                   0x007143B0
        RTS3DScene::Render                            0x00715B70
          GameEngine::_bfme_updateClientSubsystems    0x0006B910
            GameEngine::update                        0x0006E910
```

## The defect

`flush` hands the vertex buffer at `[this+0]` straight to `WriteLockClass`,
which bumps a refcount at `buffer+4` — the `read at 0x00000004`:

```asm
0x0072FF3B  mov ecx, [edi]      ; the vertex buffer, never null-checked
0x0072FF53  push ecx
0x0072FF61  call 0x0091DD70     ; WriteLockClass(vb, 0)
```

It guards on two things and neither is a lifetime: the **track list** at
`[this+0x10]` being non-empty, and `ShaderClass::Is_Backface_Culling_Inverted`
(`0x00910ED0`), a render-state query. So the crash needs three conditions at
once, and the probe watches all three:

| | | at the crash |
|---|---|---|
| system | `[0x012F9D98]` | non-null — its caller null-checks it at `0x006D4013`, so it was |
| tracks | `[system+0x10]` | non-null — flush's own guard, so it was |
| buffer | `[system+0x00]` | **NULL**, and unchecked |

## Reproduced, exactly

Skirmish, Rohan vs Isengard on Ettenmoors, retail 1.03 under wine. ctrl+F9 sets
the two fields and lets the engine crash itself, so the game's own handler
writes a dump comparable with the retail three:

| | field 2024-10-20 | reproduced 2026-08-31 |
|---|---|---|
| exception | `0xC0000005` read at `0x4` | **same** |
| eip | `0x00D1DD7F` | **same** |
| edi / eax / ebp | `0` / `0` / `0xFFFFFFFF` | **same** |
| esp, esi | `…F55C`, `…F594` | `…F55C`, `…F594` |

The stack pointers differ only in their base — the low 16 bits are identical,
which is the frame layout being identical. And the frames themselves are, at the
same offsets: `0x72FF66` (`esp+0x08`), `0x6D4022` (`+0x40`), `0x7144BD`
(`+0xBC`), `0x715CCF` (`+0xDC`), `0x8FE6CB` (`+0x110`).

## What is forced, and what that leaves open

**The precondition is forced, not natural.** The probe nulls the buffer and puts
a node in the list. What the reproduction establishes is that this state
produces *exactly* the retail crash on the byte-identical binary — so a null
check in `flush` is a fix for the observed dumps rather than for a guess. What
causes the state in the field is still unknown.

Two facts constrain that hunt, both worth more than they look:

* **The list is hard to fill.** `TrackMarks` is a `W3DTankDraw`/`W3DTruckDraw`
  field and exactly two objects in the shipped INI declare it —
  `CINE_MordorCatapult_LR` and `Tank`, a leftover Generals test object. Every
  real BFME unit uses `W3DScriptedModelDraw`. Measured: `trk` stayed 0 across
  1341 logic frames of Rohan gameplay with units marching. Whatever put a node
  in that list in the field was already unusual — which is a lead, and fits a
  crash that only happens *sometimes*.
* **The buffer has no known nuller while the system is live.** `shutdown`
  (`0x0072EDF0`) nulls it, but its only caller is the destructor, which frees the
  object and nulls the global (`0x00B310AE`) immediately after — and the flush
  caller null-checks that global. So the retail path that leaves a *live* system
  holding a null buffer is not in the call graph yet.

## Two attempts, and why the first was wrong

A bare non-null list head does not work, and the first attempt proved it: the
per-frame update at `0x0072EEB0` walks the list **before** flush runs and read
`next` off the fake node, dying at `0x0072EEDC` on address `0x12FD`. That is a
crash of the probe's own making in the wrong function, and it is kept in the
scratch dumps as `attempt1-fake-node.dmp` because it is the reason the node is
now a real zeroed `0x1300`-byte allocation from the engine's own `operator new`
(`0x00C81F30`): `next` at `+0x12FC` reads 0 so the walk terminates on it.

## Running it

```bash
python3 tools/modbuild.py --only 041-tracksprobe -o build/lotrbfme.tracks.exe
```

It shares the client-frame hook `0x0006B910` with `039-replayctl`, so it is
built alone — `cave.py` makes a second claim on an address a hard build error.
Records land in `My Battle for Middle-earth Files\Tracks.jsonl`, one line per
change in the (system, buffer, tracks) shape plus a heartbeat every 600 frames.
