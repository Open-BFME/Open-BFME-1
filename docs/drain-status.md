# Readability drain: state at 2026-08-29

Both lanes stopped on a weekly usage limit, mid-queue. Tree is clean, nothing
unpushed, no rebase stranded. This is where to pick up.

## What the queue actually is

Measured end to end -- 273 destinations, one compile each. This supersedes every
earlier estimate, including the one the drain was originally budgeted against:

| verdict | count |
|---|---|
| markers with **no ledger row at all** | 5,182 |
| real misses (excluding 5-byte jmp stubs, whose counts are meaningless) | ~493 |
| errors -- symbol absent from the destination's object | 217 |
| MATCH -> 16 distinct symbols -> **10 landed** | 46 |

**The queue is ~5% foldable and ~85% unclaimed bodies.** The fold work is
substantially done. What remains is authoring (writing bodies with no matched
retail address) and layout work behind shared headers -- both different projects
from the drain. Do not size a lane against the marker count.

The ten destinations judged "at floor" were screened: zero MATCHes. Measured,
not assumed.

## Next actions, in priority order

1. **The mis-anchored rows** -- the highest-value work left, and the one the user
   asked for by name ("what can we do so the repo isn't corrupted?").
   - Start with the two `VertexMaterialClass` colour-source rows. They are green
     ONLY because a +4 layout error slides our field under retail's load, so a
     correct fix turns them RED and that is the fix working. Name them as
     predicted casualties in the commit message.
   - Then `Squad::isOnSquad` (apply the liveness test), `AutoHealBehavior`, the
     AsciiString trio, and the 67-row candidate list.
   - **Disposition is RE-HOMING, not deletion** -- the bytes really are an ILT
     thunk, only the name is false, and gen_small's 1,048 `?j_XXXXXXXX` rows are
     the existing honest form. Verify per row; leave trivial ModuleData
     constructors alone, since they plausibly do fold under ICF.
2. **The GameWindow header pass.** A dozen near-misses, all exact-size, all the
   same four-byte shift. Contains a real question: do the two `winSetLayout`
   spellings want one header or two? They are genuinely two functions at two
   addresses.
3. **`OBJECT_STATUS_UNDER_CONSTRUCTION` is bit 2, not bit 3** -- BFME drops one
   enum entry ahead of it. 240 use sites, so a shared-header change, but
   solvable rather than guessable: `test()` compiles the enum INDEX, so every
   matched body testing any status bit constrains the ordering. Collect the
   constraints and solve; do not edit and see what survives.
4. **Free rows**: `winGetInputFunc` in TurretAI.cpp is already byte-exact and
   needs only a `--symbols` move.
5. The ~493 real misses, smallest-first where the destination has no `$L`
   anchors. Expect most to end as recorded layout facts rather than folds.

## Open questions, recorded not resolved

- **Is our `PartitionManager` class retail's `ShroudManager`?** Two pins sit at
  0x012ED5BC; only one describes a live symbol. See their cross-annotations.
- **`?d_001086c0@@YAXXZ`** blocks the ninth DIR32 site. `registerObject` was
  pinned there FROM that call site, so using it to argue about that call site is
  circular; the global has an engine-init tag and nine agreeing references, so
  the method pin is the weaker claim.
- **Nothing references the real ThePartitionManager at 0x012ED5B8.**
- `LANAPI::update`'s `and esp,-8` is not a double: no fld/fstp/fild/movq or
  qword operand in 2030 retail bytes.
- retail `LANPlayer::setName` (72 bytes) never touches `this`.

## Environment

`ssh-agent` died mid-session and was not restarted (the user's call, not ours).
Every push needs:

    GIT_SSH_COMMAND="ssh -i $HOME/.ssh/id_ed25519 -o IdentitiesOnly=yes"

Use `tools/push_retry.sh`, which verifies the commit ARRIVED rather than
trusting an empty commit range -- that range is empty both when you are pushed
and when a conflicted rebase has left your commit in the reflog only.

## Lane discipline

One agent per checkout, always. Nine agents in one working tree lost a batch of
work early in the session, and `git reset --hard` run in a shared checkout for
what looked like a read-only investigation cost another lane a diagnosis cycle.
Investigate from your own worktree or with `git cat-file` against a ref.
