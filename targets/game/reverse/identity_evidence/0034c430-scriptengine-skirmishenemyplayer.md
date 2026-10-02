# RVA 0x0034C430 is ScriptEngine::getSkirmishEnemyPlayer

All addresses were independently checked with pefile/Capstone against the
retail-1.03-unpacked PE. GhidraMCP finds the same unique stored ILT pointer.

## Constructor, table and BFME caller establish identity

Matched ScriptEngine constructor RVA 0x00347E60 installs its primary table
VA **0x010E7A30** at VA **0x00747E90**, and its +8 Snapshot table at
0x00747E96. Primary slot **18 (+0x48)** at **0x010E7A78** contains ILT
**0x00406E6F** -> body **RVA 0x0034C430**. The next slot is ILT
0x00406E10 -> independently identified ScriptEngine::getCurrentPlayer at
RVA 0x0033DA70. That getter's unique `***Unexpected NULL player:***`
literal independently establishes the current-player field at +0x170AC,
also loaded at the start of our body.

The already matched 635-byte player-mask parser at RVA **0x0034CB60**
pushes retail literal **0x010E7DDC**, `<This Player's Enemy>`, at VA
0x0074CC68. Its equality arm calls **slot +0x48** at VA **0x0074CC7E**,
then uses the returned Player's index at +0x24 to make a player mask.
This is BFME-native enemy-player behavior, independent of the proposed name.
The already matched SKIRMISH_FIRE_SPECIAL_POWER_AT_MOST_COST action at
RVA 0x002F81F0 also calls the same slot at VA 0x006F8203 and uses that
enemy receiver. GeneralsMD's declaration places getSkirmishEnemyPlayer
immediately before getCurrentPlayer, agreeing with both table and callers.

## Body, ABI and current conversion limit

The body reads m_currentPlayer at +0x170AC, calls ILT 0x00415438 ->
RVA 0x000C9420, then falls back to scanning ThePlayerList through its
getNthPlayer ILT. The 20-byte helper reads Player+0x220 and tail-dispatches
AI slot +0x30; Player+0x220 is independently witnessed as m_ai. No name is
inferred for the fallback's +0x2C field solely from Zero Hour's layout.

Plain RETs at +0x41 and +0x44, followed by INT3 at +0x45, prove 69 bytes
with no stack arguments and a Player pointer result. The public virtual
signature is `?getSkirmishEnemyPlayer@ScriptEngine@@UAEPAVPlayer@@XZ`.

This resolves the prior native owner/method identity blocker. The unchanged
bank still differs in the early ESI save, cold zero return and count/global
load encoding. The existing ScriptEngine header is a partial class and must
be adopted/extended coherently before a native member conversion; no
duplicate class, shared-header change, pin or production reconstruction is
introduced by this evidence-only commit.

## Native conversion, 2026-10-02

The bank as served emitted 66 bytes, despite its earlier 68/69 description.
A bounded two-trial source search started with that exact stash, then restored
GeneralsMD's result lifetime: assign each candidate to `enemy`, clear `enemy`
after a failed test, and return that same variable after the scan. This gives
69 bytes with all four relocation sites aligned. It also puts the null-current-
player return after the ESI epilogue and keeps both count reads in EDX.

The native TU adopts the existing `scriptenginevtable` ScriptEngine header and
Zero Hour PlayerList header. It reads BFME's proven current-player offset
explicitly rather than using the reference class's different data layout. The
Player +0x2C test remains an offset, without inventing a shared field name.
The matched `Rva000C9420::call` spelling is reused for the no-argument thiscall
current-enemy helper, preserving its EAX result. The matched native
`PlayerList::getNthPlayer(int)` handles the other call. No new pins are needed.

Independent retail-byte checks again confirmed table VA 0x010E7A78 contains
0x00406E6F, whose E9 reaches VA 0x0074C430. Callee ILTs 0x00415438 and
0x00444F30 reach VA 0x004C9420 and 0x004DF240 respectively. The first returns
zero or tail-dispatches AI slot +0x30; the second bounds-checks a single stack
index against 32 and returns a pointer with `ret 4`. RETs at body +0x41 and
+0x44 followed by INT3 at +0x45 independently retain the 69-byte extent.

The bank's `BfmeSubAAT::bfmeCheckAAT` was an invented helper name. Its call
reaches the already matched `Rva000C9420::call` body through ILT 0x00015438,
so this conversion reuses that existing declaration rather than creating a
second identity. The name-regression pairing is recorded for these exact
source snapshots; it does not rename the existing callee.
