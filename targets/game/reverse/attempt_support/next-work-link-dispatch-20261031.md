# Explicit link-tier dispatch repair

At `15bc2b34a714398fe6cad9ca404aab0611dc9b75`, the advertised
`python3 tools/next_work.py --tier link --json` exits with `KeyError: 'link'`.
`selected_queue` accepts a link list but omits its dictionary entry; main
neither builds nor passes that list. An empty off-turn fallback also reaches
the missing entry. This is a work-selection bug, not a recovered game body.

The explicit tier now delegates to the existing `repair_queue.link_items`
adapter, preserving its provenance, shared eligibility, claim-required fields
and sharding. Ranked JSON and human output expose that same queue. The normal
picker order is retained; AGENTS still directs linking-first work through
`tools/link_check.py next`. No byte, identity, claim, census or admission rule
is changed, and selection creates no lease.

Three regression tests cover explicit selected/ranked output, disjoint and
complete shards, and empty off-turn fallback. All three fail against the
original module with `KeyError: 'link'` and pass after the repair. The picker,
finish, dump-extent and gate-exploit suites together report 64 passed and two
existing skips (93.35 seconds). The skip policy and exploit fixtures are
unchanged; this is not a claim to close an existing open audit escape.

A live CLI run passes the ledger check and returns `link repair`, a
claim-required candidate and the committed census provenance. The census and
its queue remain potentially stale: a served item still needs current source,
history and provider review before work. No linked-byte or game-runtime gain
is claimed.

Qwen was used only to review a bounded design description on four CPU threads.
It incorrectly treated the unconditional dictionary entry and the repaired
main wiring as still absent. That conclusion was rejected against the actual
patch and the old/new regression controls; it supplied no source change.
