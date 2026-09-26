# Phase 3: Improve file ownership and cohesion

## Objective

Use elapsed 3:00–7:00 to place code where readers expect it and consolidate
compatible siblings while maintaining byte-exact compilation.

## Implementation

- Placement worker pilots GameNetwork/IPEnumeration_dtor.cpp and
  IPEnumeration_getMachineName.cpp as a cohesive IPEnumeration TU. Confirm the
  +0/+4 layout and compiler flags; preserve AsciiString copy-constructor
  visibility. Add required proven ownership metadata before using merge_cluster.
- Move Common/W4BezierSegmentBFME.cpp and W4BezierSegmentEval.cpp into the
  existing Common/Bezier area with content-derived names after path review.
  Keep separate TUs: their Coord3D declarations have different constructor needs.
- Naming worker continues proven sibling work and trims the historical narrative
  in Common/RTS/TeamPrototypeInstanceWalks.cpp, preserving the concise layout
  rationale, unresolved BitFlags identity and links to essential evidence.
- Evidence worker screens one small NetPacket family or Eva pair for compatible
  ownership/layouts. Consolidate only a verified compatible subset; otherwise
  perform supported naming/comment cleanup and record the precise merge blocker.
  A failed merge is not a reason to force a shared shim or delete evidence.
- Use `merge_cluster.py --plan <destination> --only <donors...>` before an
  eligible move, then author the destination before `--apply ... --into ...`.
  Inspect partial donors and every affected row. Never consume a whole mixed
  file when only one function belongs in the destination.
- Hours 4–7 repeat the review loop, checking whether saved declarations and
  improved discoverability justify each merge. Retire unproductive families.

## Verification

- Run `./build.sh <destination-and-all-surviving-donors>` for each integrated move;
  compare affected row identities, RVAs, sizes and counts before/after. They stay
  identical for a placement-only change. check_csv and normal hooks pass.
- Inspect compile visibility and ownership independently of byte equality. Search
  active source/build/ledger references for obsolete paths. Confirm no unmoved
  function or necessary declaration was lost and no new file is untracked.
- Record readability --staged, reviewed file/declaration reductions, and a
  before/after navigation example. Do not count unrelated bodies sharing a file
  as improved cohesion. Confirm published SHA ancestry and hourly review entries.
