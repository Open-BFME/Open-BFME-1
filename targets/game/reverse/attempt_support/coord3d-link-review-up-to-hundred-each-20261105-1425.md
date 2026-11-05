# Scoped coordinate header linking review for 100 units

The preceding adoptions retain 143 existing matched rows. Each file has its own
compiler layout, unchanged code/relocation and dependency receipts in the batch evidence.

Dated predictions for disjoint cohorts against the stored census.

```text
link_check: 5 of 10 link cleanly; LINKED 1,082 -> 1,082 bytes (123.6s)
link_check: 5 of 10 link cleanly; LINKED 1,422 -> 1,422 bytes (124.8s)
link_check: 4 of 10 link cleanly; LINKED 1,057 -> 1,057 bytes (124.1s)
link_check: 8 of 10 link cleanly; LINKED 2,187 -> 2,187 bytes (123.9s)
link_check: 5 of 10 link cleanly; LINKED 1,941 -> 1,941 bytes (125.0s)
link_check: 5 of 10 link cleanly; LINKED 1,767 -> 1,767 bytes (122.0s)
link_check: 7 of 10 link cleanly; LINKED 1,883 -> 1,883 bytes (122.9s)
link_check: 5 of 10 link cleanly; LINKED 2,690 -> 2,690 bytes (125.3s)
link_check: 8 of 10 link cleanly; LINKED 3,101 -> 3,101 bytes (125.0s)
link_check: 4 of 10 link cleanly; LINKED 1,748 -> 1,748 bytes (124.4s)
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

