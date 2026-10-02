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
