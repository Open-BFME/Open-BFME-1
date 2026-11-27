# AIMoveToState::onEnter,0x00173470: exact C++ in AIStates.cpp

Private worker result,2026-11-20. Root owns the existing lease,production
edits,ledger,journal,ordinary builds,commit and publication. No production
file,pin,alias,header,flag or baseline was changed by this worker. The result
is a fresh private native proof; ordinary acceptance remains required.
Unmodified AIStates.cpp input SHA256:
b405c7e9f2731cb31e548d0c3897535757d794efde790f3bfa2772d35199d196.

## Identity and boundary

The existing named lift has322B at0x00173470. Its ctor0x00173430 names
AIMoveToState and installs table0x01098F08. The state-vtable relationship,
two distinct CritterDesync setAdjustDestination strings,and the matching
GeneralsMD AIMoveToState::onEnter algorithm agree. Native field facts are
machine+0x1C,goalPosition+0x24,adjustDestination+0x4C; machine owner+0x10,
machine goalPosition+0x24; Object template+4,position+0x38,ID+0x74,AI+0x204;
kind mask first word at template+0xC8; Object geometry+0xAC. The constructor
comment also mentions a separate derived flag at+0x50; do not confuse it
with the adjustment flag: retail MOV BYTE [ESI+4C],1/0 and this body use+0x4C.

The two final tail jumps to existing AIInternalMoveToState::onEnter end
at+0x120 and+0x142; next bytes are INT3. All internal branches stay inside
322B. The return is the existing StateReturnType enum,receiver inECX,no
stack arguments. No reduced prefix or new boundary is substituted.

## Reference provenance and semantic corrections

Reviewed BFME2 donor147fd3e52b36ee0306aaeef5b316beb09f7c7671,
Code/GameEngine/Source/GameLogic/AI/AIMoveToStateOnEnter.cpp (264B),and the
GeneralsMD original AIStates.cpp plus Common/Thing.h,Override.h,Overridable.h.
BFME2 supplies the same semantic state-entry algorithm and normal member-call
structure. Its /O1/G7/SSE flags,geometry+0xA8,AI+0x258 and template mask+0x108
are not transferred. BFME1 supplies every offset,callee and literal above.
The actual OVERRIDE member and recursive walker are guided directly by
GeneralsMD,not an arbitrary opaque pointer carrier.

The old preferred bank produced331B/181 masked differences. Rebinding its
fastcall casts to already recorded native members,the true vararg logger,
the existing enum and correct class keys did not alone change the bytes.
Three new evidence-backed changes resolved it:

1. The old bank added a second null guard before dereferencing the resolved
   owner template. Retail unconditionally tests [EAX+C8] after the wrapper's
   null-return path,as the reference getTemplate()->kind test does. Removing
   the extra guard gives323B. This preserves retail's valid-object contract;
   it does not claim a new gameplay null-safety fix.
2. Keep the machine captured after the goal-position copy for the first
   geometry goal lookup. Its live range fixes the old early EDI-push blocker;
   the first136 bytes then reproduce exactly. The later goal lookup reloads
   self->m_machine,as retail does. No read is hoisted across an unknown call.
3. Preserve the real OVERRIDE<ThingTemplate> member and visible recursive
   getFinalOverride implementation. Retail materializes the wrapper address
   (`add eax,4;mov eax,[eax]`),while the raw-pointer bank folds the member
   into `[ecx+4]`. Declared-only walk gives317B; the native inline walk gives
   exact322B and fixes the fallback-copy register context too. This is an
   observed compiler effect,not proof that the source text was identical.

## Integration at the required home

The lift explicitly names game/GameEngine/Source/GameLogic/AI/AIStates.cpp.
The accepted proposal appends the real AIMoveToState::onEnter member body
there; it creates no separate one-function production file. The current TU
already uses BFME field views in its matched chooseWeapon,AIEnterState and
AIMoveToPositionAndEnterState bodies. Its shared State base comes from the
existing sweep header and includes MemoryPoolObject+Snapshot; replacing that
global hierarchy just to move one member would also affect other providers.

Accordingly,three data-only views in namespace Rva00173470 expose only the
witnessed state,machine and Object fields. A separate geometry-prefix view
exposes the native+0xAC address without changing shared GeometryInfo or using
the old canonical Object accessor's+0xA8 view. No whole-class size or complete
Object/StateMachine layout is claimed.

The final geometry accessor is static __forceinline and returns a const
GeometryInfo reference. It emits **no** separate helper. Direct pointer
arithmetic/direct member form produced MOV+ADD and324B; the reference-returning
call gives retail's LEA and exact322B. The goal ID is read into a local before
the ignored-obstacle getter,matching the actual read-before-call sequence.

## Callee contracts and strict proof

Normal native build.compile_function reports322 concrete bytes,masked=false,
unresolved=[],all bytes equal. Its20 relocations include13 relative calls or
tail jumps. Existing providers are retained:

- CRCParameterCheck logger0x00065C80 through ILT0x0003A17A: genuine cdecl
  vararg declaration from CRCParameterCheckLog.cpp; existing global and byte
  guard names,correct two literal strings.
- StateMachine::getGoalObject0x000A1490 through ILT0x0000E570: normal member,
  six calls,zero stack arguments,pointer return.
- Existing opaque Gen_0026f940::m getter0x0026F940 through ILT0x0001A36B:
  complete body `mov eax,[ecx+164];ret`,7B,thiscall,no stack arguments,no
  side effects. The native ledger already owns this address-derived identity.
  Its declaration avoids inventing a new alias or changing the shared ZH
  const-enum getIgnoredObstacleID declaration merely to fit the bank's old
  nonconst-int pin. The reference/caller identifies the queried role; no
  semantic rename of the existing provider is claimed.
- Overridable::getFinalOverride0x00087A80 through ILT0x000022BB: current
  real provider and actual shared visible inline walk.
- GeometryInfo::getMaxHeightAbovePosition0x0087E000: current real provider.
- AIInternalMoveToState::onEnter through existing ILT0x00021E27: two tail
  jumps,ordinary actual member declaration,not a new adapter/pin.

The two new19B header COMDATs (OVERRIDE<ThingTemplate> operator* and conversion)
also pass strict independent checks against their own existing ControlBar.cpp
rows0x00097E70 and0x000C36F0. The final static geometry helper emits no public
or private out-of-line body. The only other new definitions are the primary
method and its two literal strings. No extra helper receives progress credit.

## Whole-TU control and limits

Private diagnostics compile both original and proposed complete AIStates.cpp
with the unchanged native cl directive and current headers. Relative quoted
includes are mapped to the same physical original headers. A private #line
directive preserves the original file/line context; it is a diagnostic-only
control and must not be copied into production. The actual source append is
the small enter-AIStates-append.cpp.txt fragment without any #line directive.

Every existing103 rowed body in the TU passes native strict resolution in both
fresh objects. Their verified extents and relocation graphs are unchanged.
Existing emitted code definitions that can be compared independently are also
unchanged. This is stronger than an equality-only control,but does not replace
the normal production-path build,full data/string/body gates,or linkwinner
preview. No full-image,game-start,runtime,memory or crash-fix result is claimed.

All compiler outputs are explicit private files under
build/agent-transport-20261120; no shared match object/receipt was written.
Directory-inventory drift refused private dependency caching; all measurements
compiled freshly. No verifier or baseline was changed.

## Landing artifacts

R/agents/transport/enter-AIStates-append.cpp.txt: append to the required TU.
Replace its existing old lift-pointer comment with a same-line-count pointer
to the native implementation in this same file,then run ordinary add_match
for the original symbol,RVA0x00173470,size322,AIStates.cpp,--replace-existing.
Only after success remove AIMoveToState_onEnter_Thunk.cpp. Root must preserve
the existing lease trailer and run the regular whole-TU build/hooks.

Primary proof: AIStates-integration.json; whole provider proof:
enter-whole-provider-proof.json. Raw decodes,compiler logs and reproducible
private scripts remain in this round's diagnostics/agents/transport folder.
This recovery materially reviewed BFME2 donor evidence; the commit should use
the repository's [BFME 2 donor] title prefix.
