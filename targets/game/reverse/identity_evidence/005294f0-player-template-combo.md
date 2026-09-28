# 0x005294F0 is not a team control (bank name SkirmishScreenState::rva005294F0)

The banked stash for 0x005294F0 used to call this method
`SkirmishScreenState::refreshPlayerTeamControl(int)`, the spelling its callers
declare for ILT 0x0002D38A. The body contradicts that name.

It is BFME's form of Zero Hour's `PopulatePlayerTemplateComboBox`
(GeneralsMD GameNetwork/GUIUtil.cpp:238), run on the slot's combo box in
`this+0xC8+4*index`:
- reset the combo;
- add "GUI:Random" (literal at 0x010EB894) with MultiplayerSettings colour -1 and
  item data -1;
- walk ThePlayerTemplateStore (0x124-byte templates), skipping observer and
  non-playable ones;
- format each side as "SIDE:%s" (literal at 0x01100E28);
- de-duplicate the sides through a `set<AsciiString>`;
- add each side's GameText string with item data = the template index;
- add "GUI:Observer" (literal at 0x010EB884) with colour and item data -2.

These are faction (player-template) entries. Zero Hour's `PopulateTeamComboBox`
instead adds "Team:0" and "Team:%d" entries, and none of that appears here. The
class is proven by the matched callers (refreshAllPlayerControls,
handlePlayerSelection, apply); the method's real name is not, so the bank keeps
the address token.
