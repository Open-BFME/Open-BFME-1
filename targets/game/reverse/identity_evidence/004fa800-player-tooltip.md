# WOLLobby playerTooltip, 004FA800

The independently native WOLLobbyMenuInit at 004FBBE0 installs VA008FA800 as
its player-list tooltip callback at +0415, followed by the existing
GameWindow::winSetTooltipFunc call through 0003D127. The reference callback has
the same GameWindow*, WinInstanceData*, unsigned packed-mouse-position cdecl
signature. The full 1517-byte body ends at +05EC with RET and the following padding
is INT3. It is a separate physical callback from the other menus' same-name
helpers; this conversion preserves the existing WOLLobby identity.

Retail extracts unsigned 16-bit mouse coordinates and reads player-name column 2.
Unlike the Zero Hour map-find expression, it calls GameSpyInfo virtual slot 4C
with a narrow name and checks for a null result. The existing native 609-byte
GameSpyInfo constructor at 00636D90 installs VA011188D0. That table's slot 4C is
00035CB5 -> 00632850, whose independently native 184-byte opaque lookup traverses
the player-info map at +4C, compares the record string at +4, and returns record
node+14 or zero with RET 4. The method retains its target-address name because
this evidence proves the contract without establishing a semantic BFME name.
PlayerInfo's 52-byte layout and the base-name field are already established by
its native copy/fill and parsePlayerKVPairs owners.

The same independently installed GameSpyInfo table routes saved-ignore slot 12C
through 00001500 to native 00632D20/43B, and name-ignore slot 144 through 000154A6 to
native 00635600/45B. Retail tests saved-ignore when the profile is nonzero and
then tests nickname-ignore if that did not match; it does not use the Zero Hour
ternary. Buddy-map lookup is the existing typed 71-byte STLport find at 004E4E20.

The PlayerTemplate field oracle independently identifies m_nameKey+0,
m_displayName+4 and m_side+8. This caller reads the side string directly; a
small typed view preserves that reference lifetime instead of introducing the
Zero Hour value-return getSide accessor's temporary. The const store lookup is
the existing 65-byte getNthPlayerTemplate at 000E1410.

The real StringBase<char>::compareNoCase body remains visible and noinline for
compiler exception analysis. Its independent emitted 91-byte body exactly matches
00090570, including the imported _memicmp and length comparison. This removes
two redundant temporary EH-state stores while retaining the existing call.
It is neither a new helper claim nor a new symbol pin.

Mouse::setCursorTooltip is verified beyond its historical pinharvest spelling:
the complete 481-byte body at 005A56F0 copies the by-value UnicodeString to
this+1100, stores delay at +4DD0, reads RGBColor components from argument 3, releases
the string and returns with RET10. Its fourth float argument is unused by this
BFME body. The independent native MapTransferLoadScreen::update caller uses the
same Mouse receiver and four-argument contract, matching Input/Mouse.cpp and
the canonical Mouse header. The three tooltip calls encode the existing
000346E9 route; no new pin is introduced.

The scoped gate rechecks the existing six TU bodies plus this 1517-byte callback,
including all literal references. The original WOLLobbyMenu.cpp remains the
emitter for its generated EH funclets; only the naked PlayerTooltipThunk.cpp
is removed. New native coverage is 1517 bytes, with no helper ownership changes.
