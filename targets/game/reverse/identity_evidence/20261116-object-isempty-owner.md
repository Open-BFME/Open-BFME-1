# Task49 /500: remove Object.cpp's wrong isEmpty copy

Five canonical AsciiString calls explicitly use the existing inherited
StringBase<char>::isEmpty. Original export1656 independently identifies
ILT0000C752 ->0005E4C0; the existing22B owner in StringBase.cpp is unchanged.
The canonical four-byte AsciiString base remains at+0; no class definition,
header, flag, alias, pin, verifier, baseline or ledger row changes.

Ordinary before/after objects preserve all191 owned rows/8488B.
The combined normal gate verifies409/409 functions across8
sources. A separate complete ordered-runtime projection drops only the one
wrong5B AsciiString::isEmpty tail-forwarder: E9 REL32 to the existing Base
member. All other1075 runtime sections,
their full bytes/flags/extents/relocations, local target section/offset roles,
SafeSEH targets, external definitions and weak/alias contracts match exactly
under that one original-address-proven binding. There are no new definitions
or remaining references to the removed wrapper. This also checks unowned
emitted code/data; it is stronger than checking the owned rows alone.

The source formerly supplied the selected wrong copy in census43852286500.
Removing it may change selection elsewhere; the next whole-image measurement
must decide that result. Frozen per-file previews are retained locally and
current predictions may be UNKNOWN. No aggregate linked-byte, new authored
coverage, runtime or crash-fix gain is asserted here.

BFME2 aa505f34c898e6fb7c9a1f1632e75ce232f4829a was reviewed read-only for the
strings family. Its standalone shim implements this boolean directly; its
layout/lifetime modes and compiler flags are not copied. BFME1's original
export and existing provider establish the actual repair. The global header
still has the forwarder; the targeted call qualification avoids a shared
header edit while the two documented independent full-gate DIR32 names remain.

Reservations follow the linking lane's name-alone/family ownership protocol;
this is a callee binding repair, not reconstruction of the191 method bodies.
Diagnostic proofs:diagnostics/continue-20261116-fivehundred/object-empty-probe
and batch-14. Native verifiers and thresholds remain unchanged.
