# Shared-string result storage: new compiler evidence, no consumer edit

Task began 2026-11-10 22:52:29 UTC. The link-task lease 0xF235F431 is held by another agent (9d0b4f7a); no consumer source, body claim, pin or bank was changed. These are isolated generic ABI experiments, not a recovered target body.

## Target and provider facts rechecked

- Retail getters at0x363360/315B and0x3634F0/321B call the existing32B producer at0x361960 via ILT0x1897B. Producer uses ECX receiver, one stack hidden-result pointer, EAX=result address, ret4; it copies receiver+0x10 via StringBase<char>'s sharing constructor0x887B60.
- Native8B cleanup actions0xC19E10 and0xC19E30 jump through ILT0xD828. They do not call releaseBuffer directly. On normal paths the parents call releaseBuffer0x887940.
- Existing CarvedBFMERetailAsciiStringDestructor.cpp and NetworkStringGetterIdentities.cpp pass6/6 normal rows together. Independently, strict RetailTruth judges the5B BFMERetailAsciiString destructor and32B copyString@Rva00361960 retail. The canonical cleanup provider is therefore usable, rather than another unresolved pin-only proposal.
- Read-only class_contract BFMERetailAsciiString (seeded sample6, jobs2): six compiled views, no errors, size4, base majority empty, one pointer at0. This does not authorize an arbitrary class identity or prove all consumers agree.

## Isolated MSVC7.1 harness

[harness.cpp.txt](harness.cpp.txt), `/O2 /DNDEBUG /MD /EHsc`, private output under build/queue-retry/shared-string. No target-named function is reconstructed in this harness.

1. Converting a SharedResult return to a different CanonicalResult emits the expected converting constructor plus two destructors.
2. A member-pointer union viewing the producer as returning CanonicalResult preserves its existing callable symbol but still emits a CanonicalResult COPY constructor and two destructors. This refutes the simple proposed return-view fix for a named local under these flags.
3. Binding a const reference to that PMF result still emits the copy and two cleanup lifetimes. A reference alone does not fix it.
4. Starting from a raw void-function thunk instead of the original PMF leaves the extra copy; both named-local and const-reference forms were compiled.
5. A force-inline return bridge remains out of line in this harness. Its call therefore cannot reproduce the target's original getter call shape.
6. Fastcall return storage uses ECX=hidden result and EDX=producer, with an explicit stack argument. This is the wrong ABI for the target (ECX=producer, hidden result on stack).
7. An inline constructor on a one-word result object, invoking a void-return member-pointer view with the result pointer as its explicit stack argument, emits only one getter call and one destructor lifetime. It initializes no extra pointer and registers its cleanup only after construction. This supplies the target's witnessed ECX/stack ABI in the generic harness without a converting temporary.

## Next supported experiment

If the task owner chooses to test the explicit-storage constructor approach, use the already proved canonical cleanup type/provider and its target-supported four-byte representation; reconcile its private views and preserve the native compare's ushort-length layout. The getter must remain bound to its existing symbol/thunk. Verify BOTH parent rows, emitted native unwind actions/state ownership, producer and strict provider truth together. Constructor emission and register allocation are still unknown for the actual consumer. This note does not claim that the generic harness matches either parent, nor any new matched or linked bytes.

Reviewed prior link14-bfmesharedstring-dtor-{,noneh-}20261101 notes, RegistryPrototypeLookup return-view evidence and shape_levers. BFME2 pinned2bac16a6 and fetched officialcfe11f2c: the earlier donor suppression recipe does not settle these EH lifetimes. No donor edit or address imported.
