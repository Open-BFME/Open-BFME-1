# RVA 009B1ED0 scalar filter bank

This is evidence for an unpromoted draft, not a named identity or byte match.
The retail PE decodes continuously from VA 00DB1ED0 through RET at 00DB218C,
701 bytes. Ghidra create_function/decompile_function agrees with the extent.
There are no direct calls (tools/callees.py 0x009B1ED0 701); no established
caller, table, or vendor function name was recovered. The source therefore
uses the address-qualified C symbol `_rva009B1ED0`.

Entry argument accesses establish seven cdecl stack arguments: info pointer,
source pointer, destination pointer, signed stride, table selector, pointer to
32-bit thresholds, and unsigned variance. The info receiver is only accessed
at +8 (signed override: values above 100 replace strength with value-100).
The table access at VA 00DB1EDE addresses VA 012D8158, the already-defined
Vp6FilterEdgeTagTable (RVA 00ED8158); no new pin is introduced.

The 8-by-8 scalar traversal gathers eight neighboring unsigned bytes into
32-bit locals. Each weight uses absolute center difference, a variance-based
slope (4 or 8), strength, the negative edge tag, and a cap of min(3*strength,32).
It accumulates weighted samples with initial bias 128 and remaining center
weight 256, then arithmetic-shifts the total by eight and clamps to 0..255.
The compiler unrolls four of the eight samples per inner iteration, as retail.

Fifteen real probes tested signed/unsigned samples and counters, explicit
neighbor pointers, accumulation order, multiply operand order, separate
pointer locals, ternary clamping, assignment decomposition, and /G6 /G7.
The decisive frame lever is keeping source/destination arguments as void
pointers and introducing byte-pointer locals: this recovers retail's 0x30
frame and its outer traversal from +0x22 through the first weight's +0x160.
Remaining-weight subtraction before weighted addition is the best measured
ordering; direct array multiplication improves instruction shape.

Best probe: 699 bytes versus 701, 195 non-relocation differences, first +0x0C,
one misaligned relocation site (initial table-load order), shape 0.866.
Score 0.7161 is the measured byte/length metric, not the shape score. The
remaining differences concern the two entry table loads, multiply/register
scheduling across the four unrolled samples, and final clamp scheduling.
No production source or symbol/ledger identity is changed by this bank.

Fresh-upstream check: local fetch stalled downloading a 519850-object pack.
While it ran, ls-remote gave master a859ea8e1d65a1e410890b513a00d2f63c81c718;
streaming that commit's raw functions.csv confirmed this RVA remains the
701-byte generated dump. The fetch issue was reported to the lead.
