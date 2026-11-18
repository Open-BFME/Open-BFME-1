# Shared enum provider-header promotion remains blocked

At BFME1 fe95dca97234d4601fd25ec4d278ba99f7706716, an initial
cohort103 experiment factored eight existing owned provider headers/shims
through four narrow enum headers. Existing full enum constants were retained;
game_logic_dispatch.h's partial NameKeyType gained the existing native limits.
The native full dependency gate reached1,887 sources and refused one row:
Rva00C06A90Cleanup at0x00C06A90 in GameLogic/AI/TurretAI.cpp.

The old pin $L68690 no longer identified that cleanup. Six candidates
($L68691 through $L68696) were equally compatible with the11-byte row;
masked body bytes could not distinguish their parent unwind states. This is
an unresolved compiler-context/identity prerequisite, not permission to choose
a label, weaken the verifier, edit an EH ledger manually or add a baseline.
The contribution log records this refusal as blocked false-reject EH-state;
that label does not establish that the guard's refusal was incorrect.

All eight provider-header edits were removed together, restoring their exact
HEAD bytes. A normal TurretAI.cpp rebuild then passed43/43 functions,19 DIR32
references and the body guard with zero baselined findings. This localizes the
regression to the broader shared-header experiment; it does not identify which
individual edit caused the label numbering. No provider body, pin or verifier
was changed. No attempted broad factoring is counted as completed work.

The successful scope instead adopts four narrow headers in independently
verified consumers. Their definitions retain the existing native enum source,
constants and EA license; the older provider contexts remain intact. Every
consumer requires whole ordinary COFF identity, explicit compiler enum/class
contracts, real include tracing and the normal native header gate. Future
promotion of the original provider headers needs independent unwind-state
identity or a proven compiler context that preserves the original pin.

Useful diagnostics are preserved locally under
W:/OpenBFME/diagnostics/continue-20261118-fivehundred/:
batch-103-commit-initial-refusal.log and blocked-broad-enum-factoring.patch.txt.
No crash, memory, FPS, linked-byte or runtime result follows from this trial.
