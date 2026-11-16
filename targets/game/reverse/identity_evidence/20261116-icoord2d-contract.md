# ICoord2D canonical data contract and adoption proof

BFME1 baseline: 21724c8adaf6f047c9e7dcd448c3ab798f5d4f6d.
The native class_contract.py inspects 236 existing source views; 226 compile
successfully. Its frozen ICoord2D.json has no undecided attributes: struct,
sizeof8, no base or virtual state, int x at+0 and int y at+4. The compiled
Zero Hour GeneralsMD/Code/Libraries/Include/Lib/BaseType.h independently
supports sizeof8 and no bases. Fields agree in226/225 native CodeView views.
Those are source ABI facts supported by the reference, not a new claim that
the retail executable contained this exact source declaration.

The new game/Libraries/Include/Lib/ICoord2D.h exposes this data model only.
The pre-existing WWMath/icoord.h inheritance remains a different source view;
it does not override the contract or prove original inheritance. Its provider
and existing users are unchanged. Method/constructor reconciliation is deferred.

Read-only BFME2 reference7209b9e7397e3ed356627a8110e4b7aab234f6e8:
Code/Libraries/Include/Lib/ICoord2D.h and reverse/class_contracts/ICoord2D.json
support the common two-int data header approach. Code/ maps to BFME1 game/;
reverse/ to targets/game/reverse/. BFME2 optional methods, constructor modes,
base adapters, RVAs and compiler settings are not copied. BFME1 uses its own
original compiler, source flags and headers. Donor scope is a structural lead;
every target unit receives its own before/after layout and object proof.

Only global-scope struct views are selected. Before and after native CodeView
must independently show precisely sizeof8, two int fields x/y at0/4 and no
bases or virtual state. No aggregate initializer or constructor rewrite is
needed for plain data views. Each source is reserved before experiments.

Private controls use one physical compiler-input path and the original logical
source/include context, writing only unique diagnostic objects. Separate
ordinary builds produce the verified objects. The complete ordinary runtime
section graph preserves bytes, flags, relocation sites/kinds, external symbols,
local target roles and offsets, EH actions and resolved SafeSEH identities.
Strict ordinal inventory separately proves unchanged disconnected private
tables. Newly emitted/changed COMDATs require an existing matched owner and
native RetailTruth full-byte/relocation proof; unknown new bodies and removal
of correct providers are refused. Normal retail row gates run independently.

The first batch introduces the shared header, registry entry and contract and
pays the normal shared-header commit gate. Subsequent batches use it unchanged.
No compiler option, pin, source alias, verifier or baseline is changed. Cleanup
locators, if required, use only eh_state_pins.py. Verdicts use re_log.py.

Each independently verified and published source adoption is one task, not a
new reconstructed function. Frozen-census and current-provider previews are
reported separately; UNKNOWN proves no linked-byte increase. No complete-link,
runtime, leak, memory optimization or crash-fix claim follows from this work.

Latest complete census43711614660, input7c314a3e6c, Nov15 12:54, has
3,088,824 LINKED B in15,522 files. It separately confirms the previous450B
but predates these adoptions. The unchanged DXERR library-member blocker is
not retried: its StringVPrintfWorkerW route-pin prerequisite remains recorded
in attempt_support/dxerr9-summer2003/printfw-route-pin-blocked-20261113.md.
Current donor changes do not alter the selected DXERR files or import binding.
