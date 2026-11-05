# Scoped coordinate header linking review for 100 units

The preceding adoptions retain 212 existing matched rows. Each file has its own
compiler layout, unchanged code/relocation and dependency receipts in the batch evidence.

Dated predictions for disjoint cohorts against the stored census.

```text
link_check: 3 of 10 link cleanly; LINKED 2,193 -> 2,193 bytes (164.2s)
link_check: 5 of 10 link cleanly; LINKED 3,936 -> 3,936 bytes (162.3s)
link_check: 6 of 10 link cleanly; LINKED 4,129 -> 4,129 bytes (164.6s)
link_check: 6 of 10 link cleanly; LINKED 2,947 -> 2,947 bytes (163.3s)
link_check: 2 of 10 link cleanly; LINKED 889 -> 889 bytes (162.6s)
link_check: 3 of 10 link cleanly; LINKED 3,029 -> 3,029 bytes (162.1s)
link_check: 7 of 10 link cleanly; LINKED 3,644 -> 3,644 bytes (164.3s)
link_check: 3 of 10 link cleanly; LINKED 2,391 -> 2,391 bytes (161.9s)
link_check: 4 of 10 link cleanly; LINKED 4,371 -> 4,371 bytes (164.3s)
link_check: 2 of 10 link cleanly; LINKED 1,876 -> 1,876 bytes (164.4s)
```

The current linking picker serves the BfmeSharedString destructor selection, with
636 estimated bytes in two LivingWorldEntryFind units at its recorded census.
The reviewed handoff link14-bfmesharedstring-dtor-noneh-20261101.md identifies the
remaining EH funclet calls. The recently landed DX8 constructor suppression is
not transferable to that call path without a distinct native destructor proof.
The local donor checkout now matches the published dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce pin.
The tracked DX8 donor repair documents its reference review. No donor code or build
profile enters these coordinate changes.

The preview scope leaves the full-image linking and runtime verdict open.

