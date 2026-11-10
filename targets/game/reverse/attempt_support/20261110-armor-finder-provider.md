# Armor finder: repair the provider, retain the template family

Base BFME 1 2b36dbf51a; task started 2026-11-10 22:45:23 UTC. Queue12/census90c15cdeca.

## Target facts

Retail0x00146780 is73 bytes ending ret4. `callees.py` and `dis_retail.py` independently show calls through ILT0xAE20 to0x1412A0, ILT0x2AFA4 to0x144300, ILT0x36C0A to0x1451E0. Cache address is receiver+0x31C, vector header receiver+0x310, cached node value at+0x14. Existing target evidence in link17-armor-weapon-map-family-swap.md establishes the armor relation and the map-family misidentities. No map-family name or layout is promoted from byte equality.

The original generic implementation passes the ordinary resolver but strict RetailTruth judges its selected copy wrong because its emitted map calls use the opposite family's ledger homes. Bind only these three calls to existing address-derived thunk identities with the existing x86 single-inheritance member-pointer recipe. No new pin, alias, name correction, data record or generated-file edit. Preserve the established cache lookup/null/slow lookup/conditional insertion semantics.

## Trials and verification

- Consumer-only thunk respelling passes all three consumer rows and yields census previews83+715B. Reverted: checking the thunk unit500/500 exposed unresolved downstream b_* names, so this alone did not repair the selected provider. No linked gain claimed from that trial.
- Provider with vector-reference local formed before lookup changes instruction scheduling, and removal of the generic call stops emitting18 other ledgered template rows. Rejected.
- Form vector reference at the slow call and explicitly instantiate the original findBestInfo member. Whole provider122/122 functions plus its data row, strings/constants/DIR32/body guards pass. Strict RetailTruth independently returns `(73, retail)` for findArmorTemplateSet. This fixes the provider itself, with consumers restored.
- EH label numbering changes. `eh_state_pins.py --source ... --fix --model gpt-6.1-sol` reports the one existing pin unprovable/unanchored and changes nothing. Normal build independently identifies the renumbered funclet body; no manual label rebind or exception added.

Current-dependency link preview requires objects absent from this isolated worktree; report unknown until all affected current definers are available. Generated thunks remain500/500 exact but the whole thunk TU has unrelated unresolved targets. A strict-retail provider verdict is not a complete executable linking result.

## Donor evidence

Reviewed pinned2bac16a657d32220670e4b9c7ec056986de61692 and fetched officialcfe11f2c1af1a9c6ef19a56abb4d77912e06fb89: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp and Code/GameEngine/Include/Common/SparseMatchFinder.h (maps to game and the corresponding local reference header). Latest donor adds the P120/P121 mixed-family repair: the weapon-spelled cached finder actually serves armor and must call the armor slow finder. This corroborates the family conflict, not BFME1 RVAs or ABI. The donor has different TUs, flags, sizes and private-access specialization; none of those are imported. BFME1's native call targets and fields determine this adaptation. Existing bank/family evidence reviewed; no bulk rename attempted.
