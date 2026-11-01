# BodyParticleSystem deleting destructor emitter

Assigned rank 21, key 0xFB7C8C1C. BFME 1 starting revision for this task:
8630e033dc51d873b7f99607eca330666653600b.

## Independent BFME 1 evidence

The existing identity record
`targets/game/reverse/identity_evidence/0x0020DE10-bodyparticlesystem-dtor.md`
establishes the public virtual destructor, 12-byte node, system ID +4,
next +8 and vtable 0x010A74E8 from createParticleSystems and BodySnapshot.
The native scalar deleting destructor is 0x0020DE20..0x0020DE3F (31 bytes):
it tests delete flag bit 0, saves this, stores its own vptr, conditionally
calls global operator delete at 0x00881EB0 and returns this with RET4.
It does not call the ordinary destructor out of line. The ordinary destructor
at 0x0020DE10 consists solely of its vptr store and RET.

ActiveBody_createParticleSystems.cpp originally declared that destructor
without its definition. MSVC 7.1 emitted a wrong 30-byte scalar deleting copy
which calls the ordinary destructor. Exposing the proven empty body as an
in-class inline definition emits the exact 31-byte retail copy, including
both vtable and delete relocations. RetailTruth changes wrong -> retail.
The existing home in TrivialVirtualDestructors.cpp is retained; both copies
have the same native behavior and target identity. No new pin, ledger row,
private class, import annotation, verifier rule or shared header is needed.

## Donor evidence and applicability

Reviewed official beed8a16790a6812231ac7b05e3e6893e4cb5d1b
Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp, and sibling
/home/yannick/projects/Open-BFME-2 at
597434797b5156afb8a4c500c56aea6194b4f434 at the same source path.
Sibling commit 4bc7463ae790498a3e5472e59b3b9e8656dbd6d4 and its
reverse/attempt_support/link-closure-44151-20261014/engine-evidence.md
record the same declaration-only versus inline-empty destructor mismatch.
This is an applicable compiler-visibility repair. BFME 2's address-derived
Rva004BDA0C identity, 29-byte deleting body, vtable and ActiveBody offsets
are not BFME 1 facts and were not copied. Its imported-forceinline annotation
is unnecessary here: ordinary inline C++ alone produces the exact BFME 1
copy. The fetched newer a49cde3c donor update remains unverified; no donor
checkout or freshness marker was changed.

## Verification and limits

Normal consumer gate passes 2/2 (parent and existing unwind row), one string
literal, eight DIR32 references and body guard. Normal home-provider gate
passes 27/27 with 26 DIR32 references. The consumer's scalar deleting copy
is independently byte- and relocation-exact under RetailTruth; it is 31 bytes,
not the original 30. find_declared_unmatched reports all definitions matched.
Before and after current link_check previews remain UNKNOWN: the available
October 19 e9a5ae5b4c census predates the assigned afbe8bafb6 queue, with
more than 22,000 changed/unavailable ledger objects. No linked-byte gain,
link.exe run or runtime behavior test is claimed.
