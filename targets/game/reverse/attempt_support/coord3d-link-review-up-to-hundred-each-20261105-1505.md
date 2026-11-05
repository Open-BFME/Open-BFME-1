# Scoped coordinate header linking review for 100 units

The preceding adoptions retain 169 existing matched rows. Each file has its own
compiler layout, unchanged code/relocation and dependency receipts in the batch evidence.

Dated predictions for disjoint cohorts against the stored census.

```text
link_check: 4 of 10 link cleanly; LINKED 1,639 -> 1,639 bytes (165.0s)
link_check: 5 of 10 link cleanly; LINKED 2,184 -> 2,184 bytes (164.8s)
link_check: 6 of 10 link cleanly; LINKED 2,491 -> 2,491 bytes (163.6s)
link_check: 8 of 10 link cleanly; LINKED 4,482 -> 4,482 bytes (164.2s)
link_check: new since census aafdf413e9, previewed at its link-order place: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerStartRenderToTexture.cpp
link_check: 6 of 10 link cleanly; LINKED 2,391 -> 2,391 bytes (219.0s)
link_check: 7 of 10 link cleanly; LINKED 2,917 -> 2,917 bytes (163.6s)
link_check: 7 of 10 link cleanly; LINKED 4,545 -> 4,545 bytes (164.0s)
link_check: 5 of 10 link cleanly; LINKED 2,228 -> 2,228 bytes (163.1s)
link_check: 4 of 10 link cleanly; LINKED 975 -> 975 bytes (164.6s)
link_check: 4 of 10 link cleanly; LINKED 1,475 -> 1,475 bytes (165.6s)
```

The first available linking pick was the RefHandle008958D0 destructor copy.
The three consumers still predict zero linked bytes in the aafdf413e9 index.
The existing 35-byte owner at 0x00784A70 predicts 35 -> 35 bytes in the same scope.
The documented consumer inline versus emitted destructor prerequisite remains.
See refhandle008958d0-inline-depth-20261028.md and donor-refresh-20261101-1231.md.
The unchanged f6d845ecd439374ef476ce04c992a2b848eb2c99 donor pin and its
verified freshness record in donor-refresh-20261104-1410.md still apply.
No new donor evidence changes the documented prerequisite.

The preview scope leaves the full-image linking and runtime verdict open.

