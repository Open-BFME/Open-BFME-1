# Retail duration arithmetic operands

The11-byte helper at000B94B0 loads its float argument, multiplies by the
32-bit value at VA01082C38, and returns at000B94BA followed by INT3.
The234-byte WeaponTemplate::parseShotDelay at001E1350 multiplies its two
parsed signed integers at001E1404 and001E141C by VA010A0528, calls the
existing ceil import and __ftol2, and returns at001E1439 followed by INT3.
Both referenced retail words are0AD7A33B (IEEE754 binary32 0.005f).
The old source's local LOGICFRAMES_PER_MSEC_REAL is8FC2F53C (0.03f).
The prior local-constant verifier did not compare these x87 memory loads.

Retain the inherited ledger names; no semantic identity inference follows
from the numeric correction. The helper's existing duration interpretation
is unproven, so its native implementation is address-named Rva000B94B0 and
selected explicitly with object-symbol. The parser uses the existing
canonical WeaponTemplate/INI declarations and unchanged member offsets,
control flow, string tokens, ceil and conversion callees, with a TU-local
0.005f arithmetic helper. It is split from Weapon.cpp to avoid changing
other users of the shared Zero Hour conversion constant. No header or
source-wide constant substitution is justified by these two witnesses.

The reviewed7bfaf884e4 local readonly x87 verification is used in addition
to the ordinary strict gate. This is a source/operand repair, not a rename,
extent change, pin change, or weakening of the checker. Existing unrelated
Weapon.cpp pool-literal mismatch remains separately recorded in the audit.
