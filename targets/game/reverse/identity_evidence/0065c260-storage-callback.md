# getPersistentDataCallback — RVA 0065C260, 1617 bytes

This replaces the old `_BFMENetworkRegisteredCallback` naked lift with the
native persistent-storage response callback. Identity is independent of the
new byte match: retail PSThreadClass::Thread_Function at 0065CA50 passes VA
00A5C260 to GameSpy GetPersistDataValues at 009D5330 for the player-statistics
request. The reference PersistentStorageThread.cpp::getPersistentDataCallback
has the same operation-count decrement, retry request, local-player preference
checks, player-statistics parse, and response-queue dispatch. BFME additionally
supplies the 2004 SDK modification-time argument and initializes an absent
account creation date. The complete retail extent runs through RET at +650;
there is no trailing owned table.

The GameSpy 2004 gpersist.h PersDataCallbackFn contract has nine cdecl
arguments: local ID, profile ID, persisttype_t, index, success, time_t modified,
char* data, length, and instance. Retail reads instance at original ESP+0x24,
profile at +0x8, success at +0x14, data at +0x1C and length at +0x20. Its bare RET and
callee-side handling agree with this signature. The older ZH eight-argument
callback is not copied as an ABI declaration. C++ linkage is intentional: the
old C-linkage lift under /EHsc incorrectly suppresses C++ exception cleanup;
the reference callback is C++. Native C++ linkage restores all retail unwind
states without a compiler workaround.

Witnessed layouts and dependencies:

* PSPlayerStats is 0x1C4, with its complete native constructor at 00658EF0,
  copy constructor at 006577D0, assignment at 000A5950 and destructor at
  000A5150. The already-landed BFME key/value parser 00659670 and formatter
  00655360 establish its field names and map order. name_oracle has no BFME
  PSPlayerStats witness; its ZH hint is not used in place of these bodies.
* PSRequest is 0x210, as independently landed default/copy constructors
  0065AB40/006588B0 and destructor 000A5490 establish. PSResponse is 0x1F0,
  corroborated by its existing lifecycle/deque claims; the callback constructs
  only its PSPlayerStats subobject at +4. The unused tail remains opaque.
* Thread operation count is +54 and local-data flag +58, agreeing with the
  constructor 006547F0, native tryConnect 006517B0 and retail worker.
* Queue global VA 012F76F0 has local ID +68, addRequest vslot +10 and
  addResponse +18. Complete 32-byte members 00655060/00655090/006550C0 copy
  strings at +6C/+78/+84 into a hidden result, return it, and RET 4. The
  source explicitly uses their existing BFMENetwork::copyState* symbol view;
  it does not add pins or widen that legacy owner label into an identity claim.
* Existing 99-byte BfmeStampVSE::bfmeStampVSE at 006583F0 calls GetLocalTime,
  formats month/day/year, and assigns the string at +14C. The callback uses
  that proven member contract through its existing typed view.
* All 24 direct callees are present in the ledger. The strict resolver checks
  all 85 relocations, including actual ILT routes for STL string assignment,
  PSRequest/PSPlayerStats lifecycle, UserPreferences and the parser. It reports
  zero unresolved names and zero differing bytes, with no symbols.csv change.

BFME behavior retained: LoTRB4MEOnline\\MiscPref%d.ini; six preference counters
clamp negative values to 10; nonzero counters enqueue a statistics update;
an empty creation date for the local player triggers a date-stamped update;
all successful results enqueue a player-statistics response. The old ZH
TheGameSpyGame/getUseStats guards are absent in retail and remain absent here.

Validation: complete native 1617-byte match, strict call/data relocation
resolution, canonical AsciiString header, normal scoped build and commit/push
hooks. The former naked source is removed. No helper ownership or generated
code is counted as new coverage. Model GPT-6; t=10 minutes including independent
ABI/layout verification; session 2026-09-26/27.
