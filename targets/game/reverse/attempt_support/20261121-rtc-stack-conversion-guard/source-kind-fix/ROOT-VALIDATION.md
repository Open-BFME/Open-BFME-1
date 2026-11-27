# Ordinary Root replay of the generic source classifier

The exact hash-closed candidate files are installed at their normal tool/test
paths. The supplied transport patch had CRLF record terminators against the LF
source; its failed apply changed nothing. The actual candidate file bytes are
identical to the independently reviewed/private tested hashes.

Ordinary Root conversion/progress tests:269 passed,2 failed,3 setup errors.
All26 new cases pass; the same five old baseline fixture nodes are the only
failures. Two fail before gate invocation due Windows symlink privilege1314;
three fail during dump_apply reproduction before gate judgement. No fixture,
skip, source or baseline was changed to suppress them. This is not a green
whole suite. Root now executes the candidate directly, including encoding
cases whose private harness had reloaded the production path.

Only the shared source_kind import, RuleB predicate/comment and its26 tests
change executable/test code. No RTC-specific path/address or imported-row
exception is introduced. ActualC++→nonCPP protection is retained/strengthened;
original binary archive ownership is not mislabeled as readable C++.
The RTC body candidate is separately parked and earns0bodycredit until replay.
