# Remaining callback-adjacent blockers: refused private trials

Inspection baseline `b0395820c916f46632c0054e2827f761bd206c67`; BFME1 toolchain VC7.1, original source flags retained in control objects. No applied source, extra pin, verifier/baseline change or completed task.

## Q3 primary vtable store

Source `game/GameEngine/Source/Common/Q3GuardedMemberDestructors.cpp`, SHA256 `eb22a6a69cf3e05494a0d6224721efed4ea744e4954d58907ebb20cf177d890d`. Existing row005CE890 is73B. Original store of the primary vptr occurs at+1D, before leaECX,+3C and EHstate0. A novtable explicit store moves to+28, after EHstate0. Existing private virtual-destructor renaming retained body bytes but emitted a wrong two-slot table; original table has four observed entries. That is still an independent ownership/extent prerequisite.

Four bounded combinations of typed prefix access versus pointer cast, with/without/Oa, all retained a mismatch in005CE890. They do not repair scheduling. No published source changed. Do not repeat the same variants. A complete evidenced original four-slot table/provider or a different witnessed lifetime transformation is required; guessed virtual names and aliases remain invalid.

## Weather handle forwarding

Source `game/GameEngine/Source/Common/GlobalWeatherSystemConstructor.cpp`, SHA256 `876dda0cf33a2fc8d9912c7700ac43b7706741fe73e9ca8dce141534261fb94d`. Existing registered Gen003A0410 constructor3A0410 and AttributeHandleStandIn destructor39D550 are four-byte index views. Existing calls route via ILTs3747A and1A401. Simple explicit typed operation forwarding preserves the140B main constructor but fails complete runtime object proof.

Imported force-inline forwarding emits an unresolved __imp_??1HRBMD_Buffer@@QAE@XZ in cleanup code (CALL_REL32 becomes indirect DIR32 there). Without dllimport, it emits an extra13B HRBMD constructor and5B tail-jump destructor; cleanup calls retain the wrapper. No wrapper owns a verified retail body. Therefore neither variant lands or counts. Main-body bytes alone are insufficient.

The existing game/GameEngine/Include/GameLogic/Rva0039D550.h is a lead for a compatible four-byte indexed-handle view, not proof that another C++ class spelling is the same original identity. Reconcile constructor/destructor ownership through the native workflow before using it; do not add another alias or fabricate an import.

Private diagnostics remain in the session directory and build/codex-20261116-fivehundred. Both probe reservation sets were released with original owner-fenced native claims. No runtime, memory, crash-fix or full-image linking claim.

## Reproducible refused candidates

These patches are diagnostic evidence and must not be applied as a fix. The Q3 patch is the base explicit-store variant; also testing /Oa and a typed prefix did not remove its sole body mismatch. The weather patch is the non-imported forwarding candidate with the extra unowned wrappers.

- [20261117-q3-vptr-store.cpp.patch](20261117-q3-vptr-store.cpp.patch)
- [20261117-weather-handle-forward.cpp.patch](20261117-weather-handle-forward.cpp.patch)

Fresh native Q3 check at the317-task boundary: 8/8 function bytes pass, but exactly one unrecorded DIR32 name remains at destructor+0x1f, ??_7Rva005CE890Object@@6B@: encoded005CE890 versus retailVA0110FE78. This is a scoped failure, not a new full-image gate result.
