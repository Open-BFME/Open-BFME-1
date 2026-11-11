# MapObject flag wrappers: call the verified provider

Both 9B wrappers at 0x88B50 and 0x88B60 modify bit 0x10 at receiver+0x44,
then tail-jump with the same receiver to 0x88480. The target's independent
identity is recorded in identity_evidence/00088480-mapobject-ambient-audio.md:
MapObject::duplicate calls it on the new MapObject, whose runtime flags are
at +0x44. Keep the wrappers' existing opaque identities; no rename is inferred.

Replace the unprovided Gen_00088B60::bfmeNext declaration with a call to the
matched MapObject::ambientAudio00088480 provider through the same receiver.
No offset adjustment, callee pin or alternative-name alias is introduced.

BFME 2 donor 76f0baefa6f285d54bc1ca922397674312a5913f,
Code/GameEngine/Source/Common/BfmeConv888.cpp, carries the same pair at
0x30E2EC/0x30E2F5 using an explicit receiver cast. This supports the small
source repair; BFME 1's addresses, layout and identity come from its own
retail bodies and the above evidence. BFME 1's build inputs are unchanged.

Validation: normal build of S3FlagForwarders.cpp and the provider
MapObjectAmbientAudio00088480.cpp passes all 3 rows (1037B), including all
relocations. find_declared_unmatched reports no missing rows. Before census
preview: unresolved bfmeNext, 0 linked bytes. The current worktree lacks most
census dependencies, so the after selection preview may be UNKNOWN; no
linked-byte increase is claimed. The verified change removes the obsolete
symbol reference while preserving both wrapper bodies and the provider.
