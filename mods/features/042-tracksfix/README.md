# 042-tracksfix — the terrain-track crash, removed

A crash reported from the field, recovered from retail minidumps, reproduced
byte for byte, and fixed in 148 bytes of cave. The reproduction and the evidence
behind it live in `mods/features/041-tracksprobe/README.md`; this is the fix.

## The crash

```
EXCEPTION_ACCESS_VIOLATION reading 0x00000004,  eip = 0x0091DD7F
  VertexBufferClass::WriteLockClass::WriteLockClass   0x0091DD70   the buffer == 0
    TerrainTracksRenderObjClassSystem::flush          0x0072FEB0
      RTS3DScene::Customized_Render                   0x007143B0
        RTS3DScene::Render                            0x00715B70
          GameEngine::_bfme_updateClientSubsystems    0x0006B910
```

`flush` hands the vertex buffer at `[this+0]` straight to `WriteLockClass`,
which bumps a refcount at `buffer+4` — that is the read of address 4. It guards
on the track list at `[this+0x10]` being non-empty and on
`ShaderClass::Is_Backface_Culling_Inverted`, and neither says anything about
whether the buffer is still there.

## The fix

`flush` already has the exit that is wanted: its own list guard, three
instructions in. So rather than add a second one, the hook takes the list away
while the buffer is missing and gives it back when the buffer returns, and the
engine's existing early-out does the returning. A detour at `0x0072FEB0` into
one `.cpp`, ~15 lines.

**Two shapes that look simpler and are worse.** Repointing the entry guard at
the buffer is a 3-byte poke with no cave at all, and it is safe — `flush`
re-checks the list itself at `0x0072FF66` and skips the fill loop when it is
empty, so the entry guard is an optimisation rather than a correctness
requirement. But that guard is what keeps a `Lock`/`Unlock` pair off the vertex
buffer in the common case, and in BFME the list is almost always empty, so the
poke would put a lock in every frame to fix a crash almost nobody reaches. And
checking both in place does not fit: re-encoding the prologue with a second null
test needs 38 bytes and the region is 34.

Dropping the list instead of parking it would also work and be shorter. It is
not what this does: the nodes are refcounted and the system is the only thing
holding them, so forgetting the head leaks them. Parking costs four lines.

## Red and green

Same binary, same trigger, one feature apart. `041-tracksprobe`'s ctrl+F9 sets
the two fields the retail dumps show and lets the engine take it from there.

| | without `042` | with `042` |
|---|---|---|
| outcome | **crash** | **match continues** |
| dump written | `DUMP-20260831-160825-488-308.dmp` | none |
| eip | `0x00D1DD7F` | — |
| logic frame | stops at 277 | 143 → 529 and counting, buffer still null |

The red run matches the 2024 field dumps on every discriminating field — same
eip, same faulting address, same `edi`/`eax`/`ebp`, and the same call frames at
the same stack offsets (`0x72FF66` at `esp+0x08`, `0x6D4022` at `+0x40`,
`0x7144BD` at `+0xBC`, `0x715CCF` at `+0xDC`, `0x8FE6CB` at `+0x110`). The stack
pointers differ only in their base; the low 16 bits are identical, which is the
frame layout being identical.

Green was confirmed on the screen as well as in the log: units, resources
ticking, UI responsive, several hundred logic frames after the trigger.

## What this does not fix

**The cause.** What leaves a *live* system holding a null buffer is still
unknown: `shutdown` (`0x0072EDF0`) nulls it, but its only caller is the
destructor, which frees the object and nulls the global immediately after — and
`flush`'s caller null-checks that global. So the retail path that produces the
state is not in the call graph yet, and this removes the crash rather than the
reason for it.

It is deliberately silent about that. There is no console behind a code cave and
a shipped build is not the place to log; `041-tracksprobe` is, and it watches
exactly these two fields.

**How often it fires: rarely, and that is expected.** `TrackMarks` is a
`W3DTankDraw`/`W3DTruckDraw` field and exactly two objects in the shipped INI
declare one — `CINE_MordorCatapult_LR` and `Tank`, a leftover Generals test
object — while every real unit uses `W3DScriptedModelDraw`. Measured: the list
stayed empty across 1341 logic frames of ordinary play. On almost every frame
the engine's own guard has already returned before this hook matters, and the
hook reads two pointers and does nothing.

**Whether it is the crash the ladder reports.** The three dumps come from one
session in October 2024 in a multiplayer prefix. Nobody has yet tied them to a
player leaving a match, and no dump from a reported freeze-on-quit has been
collected. If a ladder player's `DUMP-*.dmp` lands on this same eip, that closes
it; if it lands elsewhere, that is a different bug and this fix is still correct
for the one it names.
