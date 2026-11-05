# Scoped coordinate header linking review for 21 units

The preceding adoptions retain 76 existing matched rows. Each file has its own
compiler layout, unchanged code/relocation and dependency receipts in the batch evidence.

Dated predictions for disjoint cohorts against the stored census.

```text
link_check: 4 of 10 link cleanly; LINKED 1,500 -> 1,500 bytes (133.9s)
link_check: 1 of 10 link cleanly; LINKED 2,404 -> 2,404 bytes (134.8s)
link_check: 0 of 1 link cleanly; LINKED 0 -> 0 bytes (24.6s)
```

The current linking picker serves SpecialPowerTemplate::getName, with 790 estimated
bytes across three consumers at its recorded census. The 52-byte retail provider is
already rowed in SpecialPower.cpp. The retained handoff
20261102-specialpower-getname-provider.md identifies the remaining inline copies
in InGameUI and SpecialPowerModule. Reconcile those class-header views before
changing the verified provider or the callers.
The local donor checkout matches the published dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce pin.
The relevant donor review remains in the existing provider handoff. No donor
code or build profile enters these coordinate changes.

The preview scope leaves the full-image linking and runtime verdict open.

