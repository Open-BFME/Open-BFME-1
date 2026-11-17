# Full refresh versus persisted common-index context

At `ddbd03635893f4995b0ccf293c333cb7203a53dc`, native
`link_check.refresh_current()` completed for all 22,992 ledger objects and
byte-verified all 1,863 data rows. It rebuilt ten objects whose prior input
receipts were stale or missing. Against the reviewed private snapshot at
`f85160db0383f60ba060ec2324fbed22e7001bcd`, object order, strong definitions,
COMMON definitions, aliases and every COMDAT identity/object/digest were equal.

Three verdicts changed from unknown to retail in the full native preview:

| COMDAT | Unchanged digest |
| --- | --- |
| `??_7BfmeAptScreenSpellStore@@6B_bfme_AptGameWindow@@@` | `2ba354312120` |
| `??_7LivingWorldAnimObject@@6B@` | `22364ca7d906` |
| `??_7W3DGameWindow@@6B@` | `104f3a4f8659` |

Independent `object_facts()` calls on the actual objects, both alone and with
the persisted common index's `weak_context()`, did not reproduce every positive
verdict. This does not establish a bug in either native path: full-refresh
context and persistable context need separate evidence. It is not a source
change, a new implementation, or measured linked-byte progress.

The three promotions were **not adopted**. The original common index and all
its unknown verdicts were retained. Only the attested tool-only commit boundary
advanced, after full refresh established unchanged provider identities, digests
and object order. No frozen census, verifier, baseline or linker decision was
edited. Subsequent source edits still require the ordinary byte gates and
current selected-provider checks; unknown remains unknown.

The full native preview and per-object comparison are preserved under
`diagnostics/continue-20261117-contract/` as `native-full-refresh-result.pkl`,
`provider-table-delta.json` and `provider-index-refresh.json` (private diagnostics).
Revisit the context receipt difference before using these promotions as evidence.
