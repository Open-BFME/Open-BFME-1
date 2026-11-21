# Value wrapper: call the existing float-field owner

The native `link_check.py near --packet` served the complete one-row source
`game/GameEngine/Source/Common/Rva0058B590Value.cpp` (81 bytes at0058B590).
It called `Player::getUpgradeCostChange`, a pinned spelling with no actual
definition. The existing authored seven-byte provider is
`Rva000C9C20FloatField::get() const` in `DispFloatFieldGetters.cpp`.

Independent BFME1 evidence is the actual ILT225BB -> C9C20 and the complete
getter `D9 81 44 06 00 00 C3`: read a four-byte float at ECX+644, return
through ST0, no stack arguments or receiver adjustment. The retained const
member model is the provider's existing declaration; no original class name
or full Player layout is recovered. The already verified
`UpgradeTemplate_calcCostToBuild.cpp` uses the same address-derived call view.
The unscaled Player method, floor import, FISTP helper, constants and compiler
profile remain unchanged. There is no added body, pin, alias, header or datum.

The normal whole-source gate passes1/1, its float constant and all3 DIR32
references; `find_declared_unmatched.py` passes. Both normal objects reproduce
all81 original bytes without masked or unresolved calls. Their complete runtime
section bytes, sizes, flags, definitions, default libraries, weak/COMDAT and FPO
metadata match. The sole reference-name change is REL32+19, from the absent
Player spelling to the existing C9C20 provider. The comparison-only name mapping
is justified by the original route; no resolver or ledger mapping was changed.

Before: the normal link preview reported the absent getter and UNKNOWN while
17 changed ledger objects were unprovable. After, the ordinary preview with its
normal definer budget reports `LINKS`, `LINKED0 ->81 bytes`, no remaining blocker.
This is a current per-file prediction against index42237e2367, not a fresh whole
census, image link or runtime result. Existing C++ coverage is retained, not new.

BFME2 reference1e864b34e05f68568db539537b6959d94d104f57 was reviewed within this
target: `Code/GameEngine/Include/Common/Player.h` and
`Code/GameEngine/Source/Common/System/UpgradeTemplateCalcCostToBuild.cpp` use a
different name-dependent upgrade-discount API and layouts. There is no matching
`Rva0058B590Value.cpp` donor. No BFME2 name, offset, signature or toolchain flag
is imported; BFME1 original calls and its owned provider determine this repair.

Reproductions, normal before/after logs, both objects, full runtime comparison
and their hash manifest are under
`W:/OpenBFME/diagnostics/one-per-project-20261122/bfme1/`.
The initial link-next AI COMDAT item was unchanged against its existing HDF;
its temporary claim was released without editing/recompiling that family.
The parked unpublished Node13 branch was not checked out or changed.
This task's lease is0058B590=b9c2733866f3497399a48535e856843a.
