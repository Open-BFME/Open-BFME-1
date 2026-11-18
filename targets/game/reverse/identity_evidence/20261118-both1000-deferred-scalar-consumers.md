# Deferred primitive-header adoption

GameSpyStagingRoom_ctor.cpp remains on its original private typedefs. Its
original source passes both existing rows. Adding the full narrow ScalarTypes
header renumbers the compiler's cleanup labels, and the normal gate cannot
resolve the existing dup_00C41408 row's $L2038 label in that candidate.
Other labels the gate proves by unwind state are recognized independently.
No manual EH label, alias or pin is added, and no verifier or baseline changes.
The whole unbanked cohort was restored before selecting the other consumers.
This file and the failed native experiment count as zero completed tasks.
Revisit only when native funclet identity evidence or the consumer context changes.
