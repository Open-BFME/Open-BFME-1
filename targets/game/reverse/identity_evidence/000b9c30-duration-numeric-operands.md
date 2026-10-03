# INI duration parser numeric operands

The complete retail bodies at000B9C30/33B,000B9C60/67B and000B9CC0/68B
multiply by the same readonly binary32 atVA01082C38. Local PE bytes and
Ghidra read_memory agree on0AD7A33B (0.005f). The FMUL operand offsets are
+0x17,+0x26,+0x26 respectively. Their RET instructions are at000B9C50,
000B9CA2 and000B9D03, each followed byINT3 padding.

The old source calls the shared GeneralsMD GameCommon.h inline conversion,
which defines LOGICFRAMES_PER_SECOND=30 and MSEC_PER_SECOND=1000 and emits
0.03f (8FC2F53C). Function-byte rebasing hid the different referenced data;
reviewed7bfaf884e4/a61c481fd0 reference checks positively reject all three
old operands. Correct only these three native parser uses with a TU-local
address-qualified helper; do not extrapolate this value to shared constants
or assert that it establishes the retail simulation tick rate.

Retain the existing INI method names/ABIs: the GeneralsMD INI.cpp twins
parse real/unsigned tokens and write the appropriate real/dword/word result,
with ceil and __ftol2 for the integral variants. Independently decoded
retail calls use getNextToken850970,scanReal8526E0,scanUnsignedInt852680,
MSVCR71!ceil IAT1359394 and __ftol2 at9F6E38. No callee binding or pin changes.
Each sub-100B parser receives independent complete-byte/reference checks;
all claims emitted by ini.cpp must pass the scoped gate.
