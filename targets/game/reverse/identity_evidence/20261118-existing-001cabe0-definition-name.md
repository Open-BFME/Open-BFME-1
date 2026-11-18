# Restore the already-ledgered definition spelling at 0x001CABE0

The source introduced at 221a9674148 declared and defined bfmeAskBIC while
functions.csv and its source comments named rva001CABE0. A normal build of the
original source fails with the ledger symbol absent, independently of this
session's ScalarTypes trials. Both declarations now spell the existing
address-derived member rva001CABE0; no semantic name or new identity is claimed.

The normal source byte gate verifies its complete existing376-byte row, string
reference, all3 recorded DIR32 references and Body guard. No ledger, pin,
baseline or provider address changed. The original partial attempt, its later
landing, and current callees were inspected. This restores a previously claimed
row's actual source definition, not newly authored coverage or a measured
LINKED/runtime gain. ScalarTypes edits were removed from this independent repair.
