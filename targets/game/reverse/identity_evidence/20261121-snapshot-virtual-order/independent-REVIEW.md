# Snapshot core declaration-order prerequisite: independent read review

**Boundedly positive. No concrete P1/P2 defect found in this two-declaration
swap.** No compiler, production/tool/claim/Git mutation or gate exception was
performed by this reviewer. Root's ordinary candidate verification and Melee's
final original-address reconciliation of changed tables remain separate evidence.

## Independently supported original contract

This review parsed the ORIGINAL retail1.03 PE export directory directly, rather
than trusting the C++ ledger's names. Original image SHA256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
There are17 complete exported FXParticleSystem families carrying:

- `void LoadPostProcess()`, public virtual non-const member, UAEXXZ;
- `const char *GetSnapshotName()`, public virtual **non-const member**,
  UAEPBDXZ; const qualifies the pointed-to characters, not the receiver;
- `void DoXfer(Xfer&)`, UAEXAAVXfer@@@Z. The reference spelling is bound by
  the actual decorated exports, not inferred merely from a32-bit argument width.

The original ParticleSystemInfo table at VA01073878 has exactly four bounded
entries: deleting destructor005F1A0, LoadPostProcess0005C980, name0005C990,
DoXfer005C3230, then0. The three actual table words point to the exact PE export
thunks1464B/D896/28C1D, which resolve to those targets. Thus name ordering and
types are independently connected to real table positions, not only to labels.

Original exported Snapshot constructor0006B180, copy0005C530 and virtual
destructor0005C520 install VA01073744. That actual table is bounded to four
slots: deleting destructor0005C550 and three purecalls0088C500, followed by0.
The purecall entries alone cannot distinguish their role names; the concrete
export-bound tables provide that evidence.

Original exported `Xfer::operator==(Snapshot&)` at009D6410 additionally loads
the supplied Snapshot receiver into ECX, pushes its own Xfer receiver and calls
`[snapshot_vptr+0xC]`. This independently connects the genuine Snapshot type
with transfer at slot3 and the observed receiver/one-reference-argument ABI.
The existing header already declares all these names/types correctly; the
candidate changes only LoadPostProcess/GetSnapshotName declaration order.

## Reviewed exact scope and payload

Candidate patch alters only game/GameEngine/Source/Common/System/snapshot.h:
four-slot order becomes destructor0/LoadPostProcess1/GetSnapshotName2/DoXfer3.
No field, base, member qualifier, argument, return type, method body, macro mode,
allocator, CRC stand-in, pin, row, alias or source provider is added or changed.

The supplied private measurements are99/99 compiles and1126/1126 existing
rows equal in each phase. This reviewer independently inspected all99 stored
footprint delta records:84 are equal;15 objects contain41 changed vtable
sections. In every changed section, only DIR32 targets at+4 and+8 exchange
places. Raw body, size, flags, all other targets, definitions, undefineds and
aux records remain equal. Do not summarize that as only15 physical tables.
Code equality is preserved while runtime virtual-dispatch data is intentionally
repaired toward original order. Code matching alone would not prove this fix.

The actual private inclusion cohort is76 System-header users plus22 different
game-header controls and the657B Foundation control. Foundation's recorded
System-header trace is empty; its unchanged exact body is a control, not proof
that its broader Module/Behavior41 hierarchy has been reconciled. The legacy
game/GameEngine/Include/Common/Snapshot.h still has the distinct ZH CRC/xfer
model; this small patch neither changes nor canonically validates that model.

## Baseline correction and remaining limits

Root's ordinary unchanged build.cmd run covers99 sources in nine batches;
the stored run log reports0/9 failures, and all nine normal logs say DIR32 OK.
The private Melee harness's30 unowned-name errors occurred before AND after;
they therefore do not prove a red master or a required check/baseline repair.
They do limit that private guard invocation. No check skipping or whitelist
change is justified. Root's normal candidate build/hook result is still needed.

Melee is finishing original-table/receiver binding for the actual changed
tables. Original PE signatures and representative tables strongly support the
contract; this reviewer did not independently authenticate every41 emitted
table copy's exact runtime address/thunk/secondary-this placement. Those details
matter for tables such as Drawable's secondary Snapshot view; whole-object
code equality does not substitute for them.

No full1871-context rebuild,151 stale/unknown-context clearance, full-image
link, executed save/load, runtime CRC agreement or new Foundation1261B body
recovery follows from these receipts. The broader hierarchy issues remain open.
The evidence supports this narrow runtime-data correction; it does not establish
the entire game works. Private or newly passing checks are not new body credit.

Original PE/table/caller bytes and all41 exact delta checks are in
ORIGINAL-PE-REVIEW.json. REVIEW-SCOPE.json binds the scoped receipts and Root's
ordinary baseline logs. No new P1/P2 finding or requested code change.
