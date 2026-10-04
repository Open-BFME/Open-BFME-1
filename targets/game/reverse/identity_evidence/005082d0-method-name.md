# 0x005082D0 method name

The retired draft called the body `BfmeAptScreenQuickMatchMenu::populateQMSideComboBox` by analogy with the Zero Hour helper in `WOLQuickMatchMenu.cpp`. That helper is static and filters player templates with Zero Hour's starting-building and locked-general checks. The BFME body uses a menu receiver and filters on the BFME-only `m_bfmeBD` byte. The similar behavior does not establish the BFME method's original name.

Three matched callers reach the BFME body through ILT `0x00035701`. Their source files use address-derived member pointer types and prove the menu receiver plus the `int` and `LadderInfo*` arguments. The retail selector scan found no selector registration for `0x005082D0`.

The matched constructor at `0x00505830` establishes `BfmeAptScreenQuickMatchMenu` as the receiver type. The callers and constructor do not establish this member's name, so the source keeps the RVA in `rva005082D0`.
