# setWindowText: existing provider located, route guard prerequisite

Queue22 claim F7D9E5B3. Current caller setWindowText_Thunk.cpp requests
?rva004BD400@@YAXPAVGameWindow@@VUnicodeString@@@Z, pinned at ILT0003A52B.
The BFME1 target call routes to004BD400 and the matching98-byte body already
exists in Gadget/GadgetPushButton.cpp. Its ledger row is opaque
?dup_004bd400@@YAXXZ with object-symbol set to
?GadgetButtonSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z. The provider name
therefore exists in COFF, but not as the ledger's primary name. No new body
needs reconstruction.

Target evidence: callees.py004864E0/416 witnesses ILT0003A52B->004BD400 and
cdecl two-stack-slot ABI; complete provider004BD400/98 calls the wide
StringBase releaseBuffer and ends bare RET. The existing source calls
TheWindowManager->winSendSystemMsg(g,GGM_SET_LABEL,&text,0), with by-value
UnicodeString cleanup. Source identity is carried by the existing provider,
not inferred merely from the thunk address. Existing target caller's second
branch maps to this provider even though the first branch uses GadgetRadio.

Experiment: change only that caller's declaration/call to the existing
GadgetButtonSetText COFF name and add one routing pin at0003A52B with
route=004BD400. pin_consistency --check rejects it: the stub target is named
nothing in its ledger lookup, because it does not accept this row's
object-symbol as the target's canonical identity. The normal build was not
run after this refusal. Per gate-read instructions, do not re-express the
same change to evade the check. Both caller and symbols.csv were restored.

Required next step: establish the primary ledger identity through the normal
identity/naming lane or repair the checker through its own reviewed work.
Then use the existing provider and verify provider plus caller together.
No new code or linked bytes are claimed. Before census-only link_check has
unresolved rva004BD400; after is unchanged (production tree restored).

Donor reviewed a9286edec5374324e40c1f5dd29c3a8ab5582283:
Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp and
Gadget/GadgetPushButton.cpp. Their named setters and by-value ABI corroborate
the source relationship, but their style branch ordering differs from BFME1
and is not copied. No donor includes, layouts, addresses or flags imported.
