# Apt route-key array binding

The retained dynamic initializer at 0x00C6DC90 and cleanup at 0x00C70F60
use 178 four-byte elements at VA 0x01338480. Both original route-key
spellings and the C spelling _bfmeObjDAE are recorded at that same VA.
The latter is defined once in Rva00C6DC90ArrayInit.cpp.

Trials in nine consumers used that existing provider directly and then
used the established descriptive source spelling with the existing
__identifier declaration pattern. Scoped builds kept all 21 function
rows across the nine consumers and initializer. Object comparison kept
all 29 external code bodies. The only changes were 18 relocation symbol
names, each still bound to VA 0x01338480. The dated link index did not
yield a current link verdict.

The name-regression hook refused both trials as nine descriptive-to-
placeholder changes, including the one retaining descriptive references
through the source alias. The source edits were reverted. A later change
should reconcile the naming contract for this data identity and use the
project's documented identity-correction evidence path.
